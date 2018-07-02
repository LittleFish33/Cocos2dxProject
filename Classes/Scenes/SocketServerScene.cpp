#include "SocketServerScene.h"
#include "SimpleAudioEngine.h"
#include "GameSettingScene.h"
#include "..\SocketUtil\SocketData.h"


using namespace CocosDenshion;
USING_NS_CC;

Scene* SocketServerScene::createScene()
{
    return SocketServerScene::create();
}

/* ���ļ�������ʱ����ӡ���õĴ�����Ϣ�����Ƿֶδ��� */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SocketServerSceneScene.cpp\n");
}

/* ��ʼ���������� */
bool SocketServerScene::init()
{
#pragma region Cocos2dx�Զ����ɵ����ݣ�һЩ��������

	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

#pragma endregion

	auto label = Label::createWithSystemFont("Server", "Arial", 24.f);
	label->setPosition(500, 400);
	addChild(label, 1);
	
#pragma region �������������

	server = SocketServer::getInstance();
	server->startServer(8000);
	server->onRecv = CC_CALLBACK_2(SocketServerScene::onReceive, this);


	schedule(schedule_selector(SocketServerScene::update), 0.05f, kRepeatForever, 0);

#pragma endregion

    return true;
}


void SocketServerScene::update(float dt)
{
	server->update(dt);
}

void SocketServerScene::onReceive(const char * data, int count)
{
	SocketData* myData = (SocketData*)data;
	if (myData->codeSend == 16) {
		if (player1) {
			player1 = !player1;
			return;
		}
		else {
			myData->codeSend = KEYCODESEND::TRANSFER;
		}
		
	}
	CCLOG("%d %d", myData->uid, myData->codeSend);
	server->sendMessage(data, count);
}





