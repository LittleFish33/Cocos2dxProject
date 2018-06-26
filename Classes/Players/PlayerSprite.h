/**************************************************************************

* Copyright:

* Author: ����˶

* Date: 2018-06-24

* Description: ��ɫ��

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

	/* ��ʼ�����������ֵ */
	void initSprite(std::string path, Sprite* player);
	/* Ԥ���ö���֡��ֵ */
	void initAnimateFrame();

	/* �ƶ���������������Զ������Ծ��������������*/
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
	/*�����̣����ҳ�̣�ʤ��, �񵲣�����������*/
	void dashLeft(Vec2 oppoentPosition);
	void dashRight(Vec2 oppoentPosition);
	void win();
	void defend();
	void charge();
	void ultimate();


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
	bool stopJump = true, stopMeleeAttack = true, stopRangedAttack = true;
	bool isHitted = false, isHitting = false, isUltimate = false;
	bool isDead = false, isWin = false;
	int hittedCount = 0;
	/*���������жϱ���*/
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
	/*����ɶ���*/
	void hittedAway();
	/* ����ֵ������ֵ�����������ٶ� ,��Ծ���*/
	int hp, mp, damage, speed, height;
	/* �ƶ���������������Զ������Ծ��������������,ʤ��*/
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
	/*����ɣ����ڷɣ�������ɣ�վ����������� ���񵲣�����������*/
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