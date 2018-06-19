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
#include "Players/ExamplePlayerSprite.h"

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

	/* 更新玩家的状态 */
	void updatePlayer1Status();
	void updatePlayer2Status();

	void hit(float dt);
	void gameOver(float delay);
    
	/* implement the "static create()" method manually */
    CREATE_FUNC(ExampleGameScene);

private:
	PhysicsWorld * m_world;
	Size visibleSize;
	/* 地面和玩家 */
	Sprite* ground,*player2;
	ExamplePlayerSprite* player1;
	cocos2d::ProgressTimer* pT;
	

};

#endif /* __GameScene_SCENE_H__ */
