#ifndef __SOCKET_SERVER_H__
#define __SOCKET_SERVER_H__

#include "SocketBase.h"

/* 接受数据结构封装 */
struct RecvData
{
	HSocket socketClient;
	int dataLen;
	char data[1024];
};

class SocketServer : public SocketBase
{
public:
	/* 单例服务器 */
	static SocketServer* getInstance();
	void destroyInstance();
	/* 启动服务器 */
	bool startServer(unsigned short port);
	/* 发送消息 */
	void sendMessage(HSocket socket, const char* data, int count);
	void sendMessage(const char* data, int count);

	void update(float dt);

	/* 开始 */
	std::function<void(const char* ip)> onStart;
	/* 新连接 */
	std::function<void(HSocket socket)> onNewConnection;
	/* 收到数据 */
	std::function<void(const char* data, int count)> onRecv;
	/* 断开连接 */
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
	/* 服务器单例实例 */
	static SocketServer* s_server;
	/* 服务器套接字 */
	HSocket _socketServer;
	/* 服务器绑定的端口号 */
	unsigned short _serverPort;

private:
	/* 客户端列表 */
	std::list<HSocket> _clientSockets;
	/* 消息队列 */
	std::list<SocketMessage*> _UIMessageQueue;
	/* 消息队列互斥锁 */
	std::mutex   _UIMessageQueueMutex;

};

#endif