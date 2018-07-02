#ifndef __SOCKET_SERVER_H__
#define __SOCKET_SERVER_H__

#include "SocketBase.h"

/* �������ݽṹ��װ */
struct RecvData
{
	HSocket socketClient;
	int dataLen;
	char data[1024];
};

class SocketServer : public SocketBase
{
public:
	/* ���������� */
	static SocketServer* getInstance();
	void destroyInstance();
	/* ���������� */
	bool startServer(unsigned short port);
	/* ������Ϣ */
	void sendMessage(HSocket socket, const char* data, int count);
	void sendMessage(const char* data, int count);

	void update(float dt);

	/* ��ʼ */
	std::function<void(const char* ip)> onStart;
	/* ������ */
	std::function<void(HSocket socket)> onNewConnection;
	/* �յ����� */
	std::function<void(const char* data, int count)> onRecv;
	/* �Ͽ����� */
	std::function<void(HSocket socket)> onDisconnect;

CC_CONSTRUCTOR_ACCESS:
	SocketServer();
	~SocketServer();

private:

	void clear();

	bool initServer(unsigned short port);
	
	void acceptClient();

	void acceptFunc();

	void newClientConnected(HSocket socket);
	
	void recvMessage(HSocket socket);
	
private:
	/* ����������ʵ�� */
	static SocketServer* s_server;
	/* �������׽��� */
	HSocket _socketServer;
	/* �������󶨵Ķ˿ں� */
	unsigned short _serverPort;

private:
	/* �ͻ����б� */
	std::list<HSocket> _clientSockets;
	/* ��Ϣ���� */
	std::list<SocketMessage*> _UIMessageQueue;
	/* ��Ϣ���л����� */
	std::mutex   _UIMessageQueueMutex;

};

#endif