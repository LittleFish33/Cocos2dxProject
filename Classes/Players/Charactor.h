#pragma once
/**************************************************************************

* Copyright:

* Author: 邵梓硕

* Date: 2018-06-24

* Description: 用来存储每个角色的数据类，在构造函数里初始化

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
	/*当帧数在10以内*/
	char* getUltimateStr2() { return (char*)ultimateStr2.data(); }
	/*当帧数大于等于10*/
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

/*和动画有关的各种变量，请根据需要进行增减，别忘了赋予相应的函数*/
private:
	/*角色名*/
	string name;
	/*每个动画的帧数*/
	int idleNum, runNum, meleeAttack1Num, meleeAttack2Num, meleeAttack3Num, rangedAttackNum, jumpNum, hitNum, deadNum, winNum, hittedAwayNum,
		dashNum, defendNum, chargeNum, ultimateNum;

	/*用来初始化动画帧时的字符串*/
	string idleStr, runStr, meleeAttackStr1, meleeAttackStr2, rangedAttackStr, jumpStr, hitStr, deadStr, winStr, hittedAwayStr1,
		hittedAwayStr2, dashStr, defendStr, chargeStr, ultimateStr1, ultimateStr2;

	/*用来初始化招式的炮，波等特效的帧*/
	int ultimateBallNum, ultimateBallBegin, ultimateBallEnd;//大招
	int chargeEffectNum, chargeEffectBegin, chargeEffectEnd;//蓄力
	int rangedBallNumber;//远程攻击
	int explosionNum, explosionBegin, explosionEnd;//爆炸
	int hitEffectNum, hitEffectBegin, hitEffectEnd;//被击打的特效

	/*用来初始化招式的炮，波等特效的字符串*/
	string boomStr1, boomStr2;//基本上所有特效
	string rangedBallStr;//远程攻击
};

#endif

