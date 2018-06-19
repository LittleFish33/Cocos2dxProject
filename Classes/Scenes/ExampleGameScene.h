/**************************************************************************

* Copyright: 

* Author: LittleFish

* Date: 2018-06-18

* Description: ʾ����Ϸ���棬�����ֻ�ǻ�����������ڹ淶��Ϸ������Ļ����ܹ��ģ�
               ��������Ա��ѡ�����Ϸ����ͼƬ֮���������ཨ���Լ�����Ϸ������

**************************************************************************/

#ifndef __EXAMPLEGAME_SCENE_H__
#define __EXAMPLEGAME_SCENE_H__

#include "cocos2d.h"
#include "SelectRoleScene.h"
#include "Players/ExamplePlayerSprite.h"

class ExampleGameScene : public cocos2d::Layer
{
public:
	static PhysicsWorld* world;
	static cocos2d::Scene* createScene();
	void setPhysicsWorld(PhysicsWorld * world);

    virtual bool init();

	/* ��ײ�������� */
	bool onConcactBegin(PhysicsContact & contact);
	/* ��ײ�����������뿪ʱ��Ӧ���� */
	bool onContactSeparate(PhysicsContact & contact);

	/* ���¼��� */
	void onKeyPressed(EventKeyboard::KeyCode code, Event * event);

	/* �ͷŰ��� */
	void onKeyReleased(EventKeyboard::KeyCode code, Event * event);

	void update(float delay);

	/* ������ҵ�״̬ */
	void updatePlayer1Status();
	void updatePlayer2Status();

	void hit(float dt);
	void gameOver(float delay);
    
	/* implement the "static create()" method manually */
    CREATE_FUNC(ExampleGameScene);

private:
	PhysicsWorld * m_world;
	Size visibleSize;
	/* �������� */
	Sprite* ground,*player2;
	ExamplePlayerSprite* player1;
	cocos2d::ProgressTimer* pT;
	

};

#endif /* __GameScene_SCENE_H__ */
