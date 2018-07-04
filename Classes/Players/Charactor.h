#pragma once
/**************************************************************************

* Copyright:

* Author: ����˶

* Date: 2018-06-24

* Description: �����洢ÿ����ɫ�������࣬�ڹ��캯�����ʼ��

**************************************************************************/
#ifndef __CHARACTOR_H__
#define __CHARACTOR_H__
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Charactor
{
public:
	Charactor(string name);
	~Charactor();
	/*��֡����10����*/
	char* getUltimateStr2() { return (char*)ultimateStr2.data(); }
	/*��֡�����ڵ���10*/
	char* getUltimateStr1() { return (char*)ultimateStr1.data(); }

	char* getChargeStr() { return (char*)chargeStr.data(); }
	char* getDefendStr() { return (char*)defendStr.data(); }
	char* getDashStr() { return (char*)dashStr.data(); }
	char* getHittedAwayStr2() { return (char*)hittedAwayStr2.data(); }
	char* getHittedAwayStr1() { return (char*)hittedAwayStr1.data(); }
	char* getWinStr() { return (char*)winStr.data(); }
	char* getJumpStr() { return (char*)jumpStr.data(); }
	char* getDeadStr() { return (char*)deadStr.data(); }
	char* getHitStr() { return (char*)hitStr.data(); }
	char* getRangedAttackStr() { return (char*)rangedAttackStr.data(); }
	char* getMeleeAttackStr2() { return (char*)meleeAttackStr2.data(); }
	char* getMeleeAttackStr1() { return (char*)meleeAttackStr1.data(); }
	char* getRunStr() { return (char*)runStr.data(); }
	char* getIdleStr() { return (char*)idleStr.data(); }
	char* getBoomStr1() { return (char*)boomStr1.data(); }
	char* getBoomStr2() { return (char*)boomStr2.data(); }
	char* getRangedBallStr() { return (char*)rangedBallStr.data(); }

	int getIdleNum() { return idleNum; }
	int getRunNum() { return runNum; }
	int getMeleeAttack1Num() { return meleeAttack1Num; }
	int getMeleeAttack2Num() { return meleeAttack2Num; }
	int getMeleeAttack3Num() { return meleeAttack3Num; }
	int getRangedAttackNum() { return rangedAttackNum; }
	int getJumpNum() { return jumpNum; }
	int getHitNum() { return hitNum; }
	int getDeadNum() { return deadNum; }
	int getWinNum() { return winNum; }
	int getHittedAwayNum() { return hittedAwayNum; }
	int getDashNum() { return dashNum; }
	int getDefendNum() { return defendNum; }
	int getChargeNum() { return chargeNum; }
	int getUltimateNum() { return ultimateNum; }
	int getUltimateBallNum() { return ultimateBallNum; }
	int getUltimateBallBegin() { return ultimateBallBegin; }
	int getUltimateBallEnd() { return ultimateBallEnd; }
	int getChargeEffectNum() { return chargeEffectNum; }
	int getChargeEffectBegin() { return chargeEffectBegin; }
	int getChargeEffectEnd() { return chargeEffectEnd; }
	int getExplosionNum() { return explosionNum; }
	int getExplosionBegin() { return explosionBegin; }
	int getExplosionEnd() { return explosionEnd; }
	int getHitEffectNum() { return hitEffectNum; }
	int getHitEffectBegin() { return hitEffectBegin; }
	int getHitEffectEnd() { return hitEffectEnd; }

/*�Ͷ����йصĸ��ֱ������������Ҫ���������������˸�����Ӧ�ĺ���*/
private:
	/*��ɫ��*/
	string name;
	/*ÿ��������֡��*/
	int idleNum, runNum, meleeAttack1Num, meleeAttack2Num, meleeAttack3Num, rangedAttackNum, jumpNum, hitNum, deadNum, winNum, hittedAwayNum,
		dashNum, defendNum, chargeNum, ultimateNum;

	/*������ʼ������֡ʱ���ַ���*/
	string idleStr, runStr, meleeAttackStr1, meleeAttackStr2, rangedAttackStr, jumpStr, hitStr, deadStr, winStr, hittedAwayStr1,
		hittedAwayStr2, dashStr, defendStr, chargeStr, ultimateStr1, ultimateStr2;

	/*������ʼ����ʽ���ڣ�������Ч��֡*/
	int ultimateBallNum, ultimateBallBegin, ultimateBallEnd;//����
	int chargeEffectNum, chargeEffectBegin, chargeEffectEnd;//����
	int rangedBallNumber;//Զ�̹���
	int explosionNum, explosionBegin, explosionEnd;//��ը
	int hitEffectNum, hitEffectBegin, hitEffectEnd;//���������Ч

	/*������ʼ����ʽ���ڣ�������Ч���ַ���*/
	string boomStr1, boomStr2;//������������Ч
	string rangedBallStr;//Զ�̹���
};

#endif

