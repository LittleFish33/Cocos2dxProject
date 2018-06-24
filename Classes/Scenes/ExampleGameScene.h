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
#include "Players\PlayerSprite.h"

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

	/*���Ժ���*/
	void hitTest(Ref* sender);
	void deadTest(Ref* sender);

	void hit(float dt);
	void gameOver(float delay);

	void RightKeyPressed();
	void RightKeyPressed(float t);
	void LeftKeyPressed();
	void LeftKeyPressed(float t);
	void A_KeyPressed();
	void A_KeyPressed(float t);
	void D_KeyPressed();
	void D_KeyPressed(float t);

	void hittedCounter(float t);
	/*���ɴ�����*/
	void createUltimateBall(PlayerSprite* player);
    /*����Զ�̹�����*/
	void createRangedBall(PlayerSprite* player);
	/*��������Ч��*/
	Sprite* createChargeEffect(PlayerSprite* player);
	/*���ɱ�����Ч��*/
	void createHitEffect(PlayerSprite* player);


	/* implement the "static create()" method manually */
    CREATE_FUNC(ExampleGameScene);

private:
	PhysicsWorld * m_world;
	Size visibleSize;
	/* �������� */
	Sprite* ground;
	PlayerSprite* player1, *player2;
	cocos2d::ProgressTimer* pT;
	Sprite* chargeEffect1;
	Sprite* chargeEffect2;
	/*˫�����̵��ж�����*/
	bool firstPressR = true, firstPressL = true, RightKeyState = false, LeftKeyState = false;
	bool firstPressA = true, firstPressD = true, A_KeyState = false, D_KeyState = false;
	/*�����ڵ��б�*/
	std::list<Sprite*> ultimateBalls;
	std::list<Sprite*> rangedBalls;
};

#endif /* __GameScene_SCENE_H__ */
