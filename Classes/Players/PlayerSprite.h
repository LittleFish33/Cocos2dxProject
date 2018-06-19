/**************************************************************************

* Copyright:

* Author: LittleFish

* Date: 2018-06-19

* Description: 游戏角色的基类，所有的游戏角色都继承自这个类

**************************************************************************/

#ifndef __PLAYER_SPRITE_H__
#define __PLAYER_SPRITE_H__

#include "cocos2d.h"

USING_NS_CC;

class PlayerSprite : public Sprite
{
public:
	/* 初始化精灵类 */
	void initSprite();
	/* 预设置动画帧的值 */
	void initAnimateFrame();
	/* 移动，不动，近攻，远攻，跳跃，被攻击，死亡*/
	void run();
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

	int getHp() { return hp; }
	int getMp() { return mp; }
	int getDamage() { return damage; }
	int getSpeed() { return speed; }

#pragma endregion

private:
	/* 生命值，能量值，攻击力，速度 */
	int hp, mp, damage, speed;
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