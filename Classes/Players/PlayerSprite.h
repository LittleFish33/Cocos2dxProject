/**************************************************************************

* Copyright:

* Author: 邵梓硕

* Date: 2018-06-24

* Description: 角色类

**************************************************************************/

#ifndef __KID_BUU2_SPRITE_H__

#define __KID_BUU2_SPRITE_H__

#include "cocos2d.h"
#include "Charactor.h"
#include "../ShareSingleton.h"

USING_NS_CC;

class PlayerSprite : public Sprite
{
public:

	/* 初始化精灵类的数值 */
	void initSprite(std::string path, Sprite* player);
	/* 预设置动画帧的值 */
	void initAnimateFrame();

	/* 移动，不动，近攻，远攻，跳跃，被攻击，死亡*/
	void moveLeft();
	void moveRight();
	void idle();
	void meleeAttack1();
	void meleeAttack2();
	void meleeAttack3();
	void rangedAttack();
	void jump();
	void hit();
	void dead();
	void hitByUltimate();
	/*向左冲刺，向右冲刺，胜利, 格挡，蓄力，大招*/
	void dashLeft(Vec2 oppoentPosition);
	void dashRight(Vec2 oppoentPosition);
	void win();
	void defend();
	void charge();
	void ultimate();


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
	bool stopJump = true, stopMeleeAttack = true, stopRangedAttack = true;
	bool isHitted = false, isHitting = false, isUltimate = false;
	bool isDead = false, isWin = false;
	int hittedCount = 0;
	/*被连击的判断变量*/
	bool isDouble = false;

	Sprite* physicPlayer;

	cocos2d::Vector<SpriteFrame*> chargeEffectVector;
	cocos2d::Vector<SpriteFrame*> ultimateBallVector;
	cocos2d::Vector<SpriteFrame*> rangedBallVector;
	cocos2d::Vector<SpriteFrame*> explosionVector;
	cocos2d::Vector<SpriteFrame*> hitEffectVector;

#pragma endregion

private:
	Charactor* charactor;
	/*被打飞动画*/
	void hittedAway();
	/* 生命值，能量值，攻击力，速度 ,跳跃多高*/
	int hp, mp, damage, speed, height;
	/* 移动，不动，近攻，远攻，跳跃，被攻击，死亡,胜利*/
	cocos2d::Vector<SpriteFrame*> runVector;
	cocos2d::Vector<SpriteFrame*> idleVector;
	cocos2d::Vector<SpriteFrame*> meleeAttackVector1;
	cocos2d::Vector<SpriteFrame*> meleeAttackVector2;
	cocos2d::Vector<SpriteFrame*> meleeAttackVector3;
	cocos2d::Vector<SpriteFrame*> rangedAttackVector;
	cocos2d::Vector<SpriteFrame*> jumpVector;
	cocos2d::Vector<SpriteFrame*> hitVector;
	cocos2d::Vector<SpriteFrame*> deadVector;
	cocos2d::Vector<SpriteFrame*> winVector;
	/*被打飞（正在飞），被打飞（站起来），冲刺 ，格挡，蓄力，大招*/
	cocos2d::Vector<SpriteFrame*> hittedAwayVector1;
	cocos2d::Vector<SpriteFrame*> hittedAwayVector2;
	cocos2d::Vector<SpriteFrame*> dashVector;
	cocos2d::Vector<SpriteFrame*> defendVector;
	cocos2d::Vector<SpriteFrame*> chargeVector;
	cocos2d::Vector<SpriteFrame*> ultimateVector;
	cocos2d::Texture2D* texture;

	ShareSingleton* shareInstance = ShareSingleton::GetInstance();
};

#endif