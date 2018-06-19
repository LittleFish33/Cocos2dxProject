/**************************************************************************

* Copyright:

* Author: LittleFish

* Date: 2018-06-19

* Description: ��Ϸ��ɫ�Ļ��࣬���е���Ϸ��ɫ���̳��������

**************************************************************************/

#ifndef __PLAYER_SPRITE_H__
#define __PLAYER_SPRITE_H__

#include "cocos2d.h"

USING_NS_CC;

class PlayerSprite : public Sprite
{
public:
	/* ��ʼ�������� */
	void initSprite();
	/* Ԥ���ö���֡��ֵ */
	void initAnimateFrame();
	/* �ƶ���������������Զ������Ծ��������������*/
	void run();
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

	int getHp() { return hp; }
	int getMp() { return mp; }
	int getDamage() { return damage; }
	int getSpeed() { return speed; }

#pragma endregion

private:
	/* ����ֵ������ֵ�����������ٶ� */
	int hp, mp, damage, speed;
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