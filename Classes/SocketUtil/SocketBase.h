#ifndef __SOCKET_BASE_H__
#define __SOCKET_BASE_H__
#include "cocos2d.h"
#include <list>
#include <thread>
USING_NS_CC;

#include <WinSock2.h>
#pragma comment(lib, "WS2_32.lib")
#define HSocket SOCKET

/* ��Ϣ���� */
enum MessageType
{
	DISCONNECT,
	RECEIVE,
	NEW_CONNECTION
};

/* ������Ϣ���� */
class SocketMessage
{
private:
	MessageType msgType;
	Data* msgData;

public:

	/* ����һ��SocketMessage */
	SocketMessage(MessageType type, unsigned char* data, int dataLen)
	{
		msgType = type;
		msgData = new Data;
		msgData->copy(data, dataLen);
	}
	/* �������Ϣ */
	SocketMessage(MessageType type)
	{
		msgType = type;
		msgData = nullptr;
	}
	/* ȡ����Ϣ���� */
	Data* getMsgData() { return msgData; }
	/* ȡ����Ϣ������ */
	MessageType getMsgType() { return msgType; }
	/* �������� */
	~SocketMessage()
	{
		if (msgData)
			CC_SAFE_DELETE(msgData);
	}
};

/* Socket���ඨ�� */
class SocketBase : public Ref
{
public:
	SocketBase();
	~SocketBase();
	/* ������ */
	bool nonBlock(HSocket socket);

protected:
	/* �ر����� */
	void closeConnect(HSocket socket);
	/* ������� */
	bool error(HSocket socket);
	
protected:
	/* ������ */
	std::mutex _mutex;

private:
	/* �Ƿ��ʼ���ɹ� */
	bool _bInitSuccess;
};

#endif