#ifndef __SOCKET_CLIENT_H__
#define __SOCKET_CLIENT_H__
#include "SocketBase.h"

/* Socket�ͻ��˶��� */
class SocketClient : public SocketBase
{
public:
	static SocketClient* construct();
	void destroy();
	/* ���ӷ����� */
	bool connectServer(const char* serverIP, unsigned short port);
	/* ������Ϣ */
	void sendMessage(const char* data, int count);
	/* ������Ϣ�Ļص� */
	std::function<void(const char* data, int count)> onRecv;
	/* �Ͽ������ӵĻص� */
	std::function<void()> onDisconnect;
	/* ѭ�����ȷ��� */
	void update(float dt);

CC_CONSTRUCTOR_ACCESS:
	SocketClient(void);
	~SocketClient(void);

private:
	bool initClient();
	/* ������Ϣ */
	void recvMessage();
	void clear();

private:
	/* �������׽��� */
	HSocket _socketServer;
	/* �ͻ����׽��� */
	HSocket _socektClient;
	/* ��Ϣ���� */
	std::list<SocketMessage*> _UIMessageQueue;
	/* ��Ϣ������ */
	std::mutex   _UIMessageQueueMutex;
};

#endif