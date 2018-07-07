#ifndef __SOCKET_BASE_H__
#define __SOCKET_BASE_H__
#include "cocos2d.h"
#include <list>
#include <thread>
USING_NS_CC;

#include <WinSock2.h>
#pragma comment(lib, "WS2_32.lib")
#define HSocket SOCKET

/* 消息类型 */
enum MessageType
{
	DISCONNECT,
	RECEIVE,
	NEW_CONNECTION
};

/* 网络消息定义 */
class SocketMessage
{
private:
	MessageType msgType;
	Data* msgData;

public:

	/* 构造一个SocketMessage */
	SocketMessage(MessageType type, unsigned char* data, int dataLen)
	{
		msgType = type;
		msgData = new Data;
		msgData->copy(data, dataLen);
	}
	/* 构造空消息 */
	SocketMessage(MessageType type)
	{
		msgType = type;
		msgData = nullptr;
	}
	/* 取得消息数据 */
	Data* getMsgData() { return msgData; }
	/* 取得消息的类型 */
	MessageType getMsgType() { return msgType; }
	/* 析构数据 */
	~SocketMessage()
	{
		if (msgData)
			CC_SAFE_DELETE(msgData);
	}
};

/* Socket基类定义 */
class SocketBase : public Ref
{
public:
	SocketBase();
	~SocketBase();
	/* 非阻塞 */
	bool nonBlock(HSocket socket);

protected:
	/* 关闭连接 */
	void closeConnect(HSocket socket);
	/* 网络错误 */
	bool error(HSocket socket);
	
protected:
	/* 互斥锁 */
	std::mutex _mutex;

private:
	/* 是否初始化成功 */
	bool _bInitSuccess;
};

#endif