/**************************************************************************

* Copyright: 

* Author: LittleFish

* Date: 2018-07-02

* Description: 一个服务器界面类

**************************************************************************/

#ifndef __SOCKETSERVER_SCENE_H__
#define __SOCKETSERVER_SCENE_H__

#include "cocos2d.h"
#include "SelectRoleScene.h"
#include "..\SocketUtil\SocketServer.h"	



class SocketServerScene: public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	/* 发送信息 */
	void update(float dt);

	/* 接受数据 */
	void onReceive(const char* data, int count);

	/* implement the "static create()" method manually */
    CREATE_FUNC(SocketServerScene);

private:
	SocketServer* server;
	bool player1 = true;
};

#endif /* __SOCKETSERVER_SCENE_H__*/