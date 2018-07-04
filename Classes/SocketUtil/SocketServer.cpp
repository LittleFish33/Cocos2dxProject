#include "SocketServer.h"

SocketServer* SocketServer::s_server = nullptr;
/* 单例服务器 */
SocketServer* SocketServer::getInstance()
{
	if (s_server == nullptr)
	{
		s_server = new SocketServer;
	}

	return s_server;
}

/* 销毁服务器实例 */
void SocketServer::destroyInstance()
{
	CC_SAFE_DELETE(s_server);
}

SocketServer::SocketServer() :
	_socketServer(0),
	onRecv(nullptr),
	onStart(nullptr),
	onNewConnection(nullptr)
{

}

SocketServer::~SocketServer()
{
	this->clear();
};
/* 清除服务器数据 */
void SocketServer::clear()
{
	if (_socketServer)
	{
		/* 锁住 */
		_mutex.lock();
		/* 关闭连接 */
		this->closeConnect(_socketServer);
		/* 解锁 */
		_mutex.unlock();
	}
	for (auto msg : _UIMessageQueue)
	{
		CC_SAFE_DELETE(msg);
	}
	_UIMessageQueue.clear();
	Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
}


/* 启动服务器 */
bool SocketServer::startServer(unsigned short port)
{
	if (!initServer(port))
	{
		return false;
	}

	return true;
}

/* 初始化服务器 */
bool SocketServer::initServer(unsigned short port)
{
	/* 如果存在服务器套接字，先关闭连接 */
	if (_socketServer != 0)
	{
		this->closeConnect(_socketServer);
	}
	_socketServer = socket(AF_INET, SOCK_STREAM, 0);
	if (error(_socketServer))
	{
		log("socket error!");
		_socketServer = 0;
		return false;
	}

	do 
	{
		struct sockaddr_in sockAddr;
		memset(&sockAddr, 0, sizeof(sockAddr));
		_serverPort = port;

		sockAddr.sin_family = AF_INET;
		sockAddr.sin_port = htons(_serverPort);
		/*自动设定机器的IP*/
		sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
		int ret = 0;
		ret = bind(_socketServer, (const sockaddr*)&sockAddr, sizeof(sockAddr));
		if (ret < 0)
		{
			log("bind error!");
			break;
		}
		/*监听，允许连接数*/
		ret = listen(_socketServer, 5);
		if (ret < 0)
		{
			log("listen error!");
			break;
		}
		char hostName[256];
		gethostname(hostName, sizeof(hostName));
		struct hostent* hostInfo = gethostbyname(hostName);
		char* ip = inet_ntoa(*(struct in_addr *)*hostInfo->h_addr_list);
		/*启动接受客户端线程*/
		this->acceptClient();
		if (onStart != nullptr)
		{
			log("start server!");
			this->onStart(ip);
		}

		return true;

	} while (false);
	/*关闭连接*/
	this->closeConnect(_socketServer);
	_socketServer = 0;
	return false;
}
/*接受客户端*/
void SocketServer::acceptClient()
{
	std::thread th(&SocketServer::acceptFunc, this);
	th.detach();
}
/*接受的线程*/
void SocketServer::acceptFunc()
{
	int len = sizeof(sockaddr);
	struct sockaddr_in sockAddr;
	/*轮询接受客户端连接*/
	while (true)
	{	
		HSocket clientSock = accept(_socketServer, (sockaddr*)&sockAddr, &len);
		if (error(clientSock))
		{
			log("accept error!");
		}
		else
		{
			this->newClientConnected(clientSock);
		}
	}
}
/* 新的客户端连接进来调用的方法 */
void SocketServer::newClientConnected(HSocket socket)
{
	log("new connect!");
	_clientSockets.push_back(socket);
	std::thread th(&SocketServer::recvMessage, this, socket);
	th.detach();

	/*新连接的回调*/
	if (onNewConnection)
	{
		std::lock_guard<std::mutex> lk(_UIMessageQueueMutex);
		SocketMessage * msg = new SocketMessage(NEW_CONNECTION, (unsigned char*)&socket, sizeof(HSocket));
		_UIMessageQueue.push_back(msg);
	}
}
/* 处理接收到的消息 */
void SocketServer::recvMessage(HSocket socket)
{
	char buff[1024];
	int ret = 0;
	while (true)
	{
		ret = recv(socket, buff, sizeof(buff), 0);
		if (ret < 0)
		{
			log("recv(%d) error!", socket);
			break;
		}
		else  
		{
			if (ret > 0 && onRecv != nullptr)
			{
				std::lock_guard<std::mutex> lk(_UIMessageQueueMutex);
				RecvData recvData;
				/*构建接受消息，并加入队列*/
				recvData.socketClient = socket;
				memcpy(recvData.data, buff, ret);
				recvData.dataLen = ret;
				SocketMessage * msg = new SocketMessage(RECEIVE, (unsigned char*)&recvData, sizeof(RecvData));
				_UIMessageQueue.push_back(msg);
			}
		}
	}

	_mutex.lock();
	this->closeConnect(socket);
	if (onDisconnect != nullptr)
	{
		std::lock_guard<std::mutex> lk(_UIMessageQueueMutex);
		SocketMessage * msg = new SocketMessage(DISCONNECT, (unsigned char*)&socket, sizeof(HSocket));
		_UIMessageQueue.push_back(msg);
	}
	_mutex.unlock();
}


void SocketServer::sendMessage(HSocket socket, const char* data, int count)
{
	/*遍历所有连接的数据*/
	for (auto& sock : _clientSockets) 
	{
		if (sock == socket)
		{
			int ret = send(socket, data, count, 0);
			if (ret < 0) //发送错误
			{
				log("send error!");
			}
			break;
		}
	}
}
/*发送消息*/
void SocketServer::sendMessage(const char* data, int count)
{
	for (auto& socket : _clientSockets)
	{
		int ret = send(socket, data, count, 0);
		if (ret < 0)
		{
			log("send error!");
		}
	}
}
/*调度方法*/
void SocketServer::update(float dt)
{
	if (_UIMessageQueue.size() == 0)
	{
		return;
	}

	/*队列锁住*/
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
	case NEW_CONNECTION:
		if (onNewConnection)
		{
			this->onNewConnection(*(HSocket*)msg->getMsgData()->getBytes());
		}
		break;
	case DISCONNECT:
		if (onDisconnect)
		{
			this->onDisconnect(*(HSocket*)msg->getMsgData()->getBytes());
		}
		break;
	case RECEIVE:
		if (onRecv)
		{
			RecvData* recvData = (RecvData*)msg->getMsgData()->getBytes();
			this->onRecv((const char*)recvData->data, recvData->dataLen);
		}
		break;
	default:
		break;
	}
	/*清除消息*/
	CC_SAFE_DELETE(msg);
	_UIMessageQueueMutex.unlock();
}