#include "SocketClient.h"

SocketClient* SocketClient::construct()
{
	SocketClient* client = new SocketClient;
	return client;
}

/* ���ٿͻ��� */
void SocketClient::destroy()
{
	delete this;
}

SocketClient::SocketClient(void) :
	onRecv(nullptr),
	_socektClient(0)
{
}

SocketClient::~SocketClient(void)
{
	this->clear();
}

/* �Ͽ����������ӣ������Ϣ���У���ע������� */
void SocketClient::clear()
{
	if (_socektClient != 0)
	{
		_mutex.lock();
		this->closeConnect(_socektClient);
		_mutex.unlock();
	}

	for (auto msg : _UIMessageQueue)
	{
		CC_SAFE_DELETE(msg);
	}
	_UIMessageQueue.clear();

	Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
}
/* ��ʼ���ͻ��� */
bool SocketClient::initClient()
{
	this->clear();

	_socektClient = socket(AF_INET, SOCK_STREAM, 0);
	if (error(_socketServer))
	{
		log("init client error!");
		_socektClient = 0;
		return false;
	}

	Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
	return true;
}
/* ���ӷ����� */
bool SocketClient::connectServer(const char* serverIP, unsigned short port)
{
	if (!this->initClient())
	{
		return false;
	}

	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(struct sockaddr_in));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr(serverIP);

	int ret = 0;
	ret = connect(_socektClient, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr));
	if (ret < 0)
	{
		_socektClient = 0;
		return false;
	}

	std::thread recvThread(&SocketClient::recvMessage, this);
	recvThread.detach();

	return true;
}

/* ������Ϣ */
void SocketClient::recvMessage()
{
	char recvBuf[1024];
	int ret = 0;
	while (true)
	{
		ret = recv(_socektClient, recvBuf, sizeof(recvBuf), 0);
		if (ret < 0)
		{
			log("recv error!");
			break;
		}
		if (ret > 0 && onRecv != nullptr)
		{
			std::lock_guard<std::mutex> lk(_UIMessageQueueMutex);
			SocketMessage * msg = new SocketMessage(RECEIVE, (unsigned char*)recvBuf, ret);
			_UIMessageQueue.push_back(msg);
		}
	}
	/* ������Ϣ���󣬷��ͶϿ����ӵ���Ϣ */
	_mutex.lock();
	this->closeConnect(_socektClient);
	if (onDisconnect != nullptr)
	{
		std::lock_guard<std::mutex> lk(_UIMessageQueueMutex);
		SocketMessage * msg = new SocketMessage(DISCONNECT);
		_UIMessageQueue.push_back(msg);
	}
	_socektClient = 0;
	_mutex.unlock();
}
/* ������Ϣ */
void SocketClient::sendMessage(const char* data, int count)
{
	if (_socektClient != 0)
	{
		int ret = send(_socektClient, data, count, 0);
		if (ret < 0)
		{
			log("send error!");
		}
	}
}

void SocketClient::update(float dt)
{
	if (_UIMessageQueue.size() == 0)
	{
		return;
	}

	_UIMessageQueueMutex.lock();

	if (_UIMessageQueue.size() == 0)
	{
		_UIMessageQueueMutex.unlock();
		return;
	}
	SocketMessage *msg = *(_UIMessageQueue.begin());
	_UIMessageQueue.pop_front();

	switch (msg->getMsgType())
	{
		case DISCONNECT:
			if (onDisconnect)
			{
				this->onDisconnect();
			}
			break;
		case RECEIVE:
			if (onRecv)
			{
				this->onRecv((const char*)msg->getMsgData()->getBytes(), msg->getMsgData()->getSize());
			}
			break;
		default:
			break;
	}

	CC_SAFE_DELETE(msg);
	_UIMessageQueueMutex.unlock();
}