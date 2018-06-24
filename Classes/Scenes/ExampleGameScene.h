/**************************************************************************

* Copyright: 

* Author: LittleFish

* Date: 2018-06-18

* Description: 示例游戏界面，这个类只是基本框架中用于规范游戏场景类的基本架构的，
               请美工人员在选择好游戏背景图片之后参照这个类建立自己的游戏场景类

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

	/* 碰撞发生函数 */
	bool onConcactBegin(PhysicsContact & contact);
	/* 碰撞的两个物体离开时响应函数 */
	bool onContactSeparate(PhysicsContact & contact);

	/* 按下键盘 */
	void onKeyPressed(EventKeyboard::KeyCode code, Event * event);

	/* 释放按键 */
	void onKeyReleased(EventKeyboard::KeyCode code, Event * event);

	void update(float delay);

	/*测试函数*/
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
	/*生成大招球*/
	void createUltimateBall(PlayerSprite* player);
    /*生成远程攻击球*/
	void createRangedBall(PlayerSprite* player);
	/*生成蓄力效果*/
	Sprite* createChargeEffect(PlayerSprite* player);
	/*生成被击打效果*/
	void createHitEffect(PlayerSprite* player);


	/* implement the "static create()" method manually */
    CREATE_FUNC(ExampleGameScene);

private:
	PhysicsWorld * m_world;
	Size visibleSize;
	/* 地面和玩家 */
	Sprite* ground;
	PlayerSprite* player1, *player2;
	cocos2d::ProgressTimer* pT;
	Sprite* chargeEffect1;
	Sprite* chargeEffect2;
	/*双击键盘的判定变量*/
	bool firstPressR = true, firstPressL = true, RightKeyState = false, LeftKeyState = false;
	bool firstPressA = true, firstPressD = true, A_KeyState = false, D_KeyState = false;
	/*攻击炮的列表*/
	std::list<Sprite*> ultimateBalls;
	std::list<Sprite*> rangedBalls;
};

#endif /* __GameScene_SCENE_H__ */
