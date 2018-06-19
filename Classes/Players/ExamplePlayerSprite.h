/**************************************************************************

* Copyright:

* Author: LittleFish

* Date: 2018-06-19

* Description: ��Ϸ��ɫʾ���࣬��������Ϸ��ɫ����ո���ķ�����д����

**************************************************************************/

#ifndef __EXAMPLEPLAYER_SPRITE_H__

#define __EXAMPLEPLAYER_SPRITE_H__

#include "cocos2d.h"
#include "PlayerSprite.h"

USING_NS_CC;

class ExamplePlayerSprite : public Sprite
{
public:

	/* ��ʼ�����������ֵ */
	void initSprite();
	/* Ԥ���ö���֡��ֵ */
	void initAnimateFrame();

	/* �ƶ���������������Զ������Ծ��������������*/
	void moveLeft();
	void moveRight();
	void idle();
	void meleeAttack();
	void rangedAttack();
	void jump();
	void hit();
	void dead();
	

#pragma region ����ֵ������ֵ�����������ٶȵ�set��get����

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

#pragma region �����жϵ�ǰ��ɫ��״̬

	bool isRun = false;
	bool stopJump = true, stopMeleeAttack = true, stopRangedAttack = true, stopLeftMove = true, stopRightMove = true;

#pragma endregion

private:
	/* ����ֵ������ֵ�����������ٶ� ,��Ծ���*/
	int hp, mp, damage, speed, height;
	/* �ƶ���������������Զ������Ծ��������������*/
	cocos2d::Vector<SpriteFrame*> runVector;
	cocos2d::Vector<SpriteFrame*> idleVector;
	cocos2d::Vector<SpriteFrame*> meleeAttackVector;
	cocos2d::Vector<SpriteFrame*> rangedAttackVector;
	cocos2d::Vector<SpriteFrame*> jumpVector;
	cocos2d::Vector<SpriteFrame*> hitVector;
	cocos2d::Vector<SpriteFrame*> deadVector;
};

#endif