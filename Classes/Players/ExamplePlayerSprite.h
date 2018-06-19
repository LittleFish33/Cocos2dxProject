/**************************************************************************

* Copyright:

* Author: LittleFish

* Date: 2018-06-19

* Description: 游戏角色示例类，其他的游戏角色请参照该类的方法编写代码

**************************************************************************/

#ifndef __EXAMPLEPLAYER_SPRITE_H__

#define __EXAMPLEPLAYER_SPRITE_H__

#include "cocos2d.h"
#include "PlayerSprite.h"

USING_NS_CC;

class ExamplePlayerSprite : public Sprite
{
public:

	/* 初始化精灵类的数值 */
	void initSprite();
	/* 预设置动画帧的值 */
	void initAnimateFrame();

	/* 移动，不动，近攻，远攻，跳跃，被攻击，死亡*/
	void moveLeft();
	void moveRight();
	void idle();
	void meleeAttack();
	void rangedAttack();
	void jump();
	void hit();
	void dead();
	

#pragma region 生命值，能量值，攻击力，速度的set和get方法

	void setHp(int h) { hp = h; }
	void setMp(int m) { mp = m; }
	void setDamage(int d) { damage = d; }
	void setSpeed(int s) { speed = s; }
	void setHeight(int h) { height = h; }

	int getHp() { return hp; }
	int getMp() { return mp; }
	int getDamage() { return damage; }
	int getSpeed() { return speed; }
	int getHeight() { return height; }

#pragma endregion

#pragma region 用于判断当前角色的状态

	bool isRun = false;
	bool stopJump = true, stopMeleeAttack = true, stopRangedAttack = true, stopLeftMove = true, stopRightMove = true;

#pragma endregion

private:
	/* 生命值，能量值，攻击力，速度 ,跳跃多高*/
	int hp, mp, damage, speed, height;
	/* 移动，不动，近攻，远攻，跳跃，被攻击，死亡*/
	cocos2d::Vector<SpriteFrame*> runVector;
	cocos2d::Vector<SpriteFrame*> idleVector;
	cocos2d::Vector<SpriteFrame*> meleeAttackVector;
	cocos2d::Vector<SpriteFrame*> rangedAttackVector;
	cocos2d::Vector<SpriteFrame*> jumpVector;
	cocos2d::Vector<SpriteFrame*> hitVector;
	cocos2d::Vector<SpriteFrame*> deadVector;
};

#endif