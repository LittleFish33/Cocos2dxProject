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
#include "..\ShareSingleton.h"

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
	void gameOver();
	void isCharge(float dt); /* �Ƿ��� */
	void updateHP_MP(float delay);

	void RightKeyPressed();
	void RightKeyPressed(float t);
	void LeftKeyPressed();
	void LeftKeyPressed(float t);
	void A_KeyPressed();
	void A_KeyPressed(float t);
	void D_KeyPressed();
	void D_KeyPressed(float t);
	void One_KeyPressed();
	void One_KeyPressed(float t);
	void G_KeyPressed();
	void G_KeyPressed(float t);

	void hittedCounter(float t);
	/*���ɴ�����*/
	void createUltimateBall(PlayerSprite* player, bool isPlayer1);
    /*����Զ�̹�����*/
	void createRangedBall(PlayerSprite* player, bool isPlayer1);
	/*��������Ч��*/
	Sprite* createChargeEffect(PlayerSprite* player);
	/*���ɱ�����Ч��*/
	void createHitEffect(PlayerSprite* player);
	/* ���ñ������ִ򿪻��߹ر� */
	void VoicePauseSelectedCallback(Ref * pSender);
	/*������Ϸ��ͣ*/
	void playOrPauseCallback(Object * pSender);


	/* implement the "static create()" method manually */
    CREATE_FUNC(ExampleGameScene);

private:
	PhysicsWorld * m_world;
	Size visibleSize;
	/* �������� */
	Sprite* ground;
	PlayerSprite* player1, *player2;
	Sprite* physicPlayer1, *physicPlayer2;
	cocos2d::ProgressTimer* player1Hp, *player1Mp, *player2Hp,* player2Mp;
	Sprite* chargeEffect1;
	Sprite* chargeEffect2;
	/*˫�����̵��ж�����*/
	bool firstPressR = true, firstPressL = true, RightKeyState = false, LeftKeyState = false;
	bool firstPressA = true, firstPressD = true, A_KeyState = false, D_KeyState = false;
	bool firstPress1 = true, secondPress1 = false;
	bool firstPressG = true, secondPressG = false;
	/*�����ڵ��б�*/
	std::list<Sprite*> player1UltimateBalls, player2UltimateBalls;
	std::list<Sprite*> player1RangedBalls, player2RangedBalls;
	/* ��������Ϊ����β��̫������һЩ�鷳�Ķ����������˲�ͬ */
	bool isFreiza = false;

	__int64 player1LastHit, player2LastHit;
	ShareSingleton* shareInstance = ShareSingleton::GetInstance();

	/*Ϊ�棬���ڲ���*/
	int voiceState;
	MenuItemImage* voiceItem;
	/*Ϊ�� ������Ϸ��Ϊ����ͣ*/
	int playOrPauseState;
	MenuItemImage* playOrPauseItem;
};

#endif /* __GameScene_SCENE_H__ */
