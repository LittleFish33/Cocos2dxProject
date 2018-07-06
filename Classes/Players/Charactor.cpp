#include "Charactor.h"

Charactor::Charactor(string _name) {
	name = _name;
	idleStr = name + "_idle_0%d.png";
	runStr = name + "_run_0%d.png";
	meleeAttackStr1 = name + "_attack_0%d.png";
	meleeAttackStr2 = name + "_attack_%d.png";
	rangedAttackStr = name + "_rangedAttack_0%d.png";
	jumpStr = name + "_jump_0%d.png";
	hitStr = name + "_hit_0%d.png";
	deadStr = name + "_die_0%d.png"; 
	winStr = name + "_win_0%d.png";
	hittedAwayStr1 = name + "_knockOff.png";
	hittedAwayStr2 = name + "_up_0%d.png"; 
	dashStr = name + "_fastMove_0%d.png"; 
	defendStr = name + "_defend_0%d.png"; 
	chargeStr = name + "_charge_0%d.png"; 
	ultimateStr1 = name + "_ultimate_0%d.png"; 
	ultimateStr2 = name + "_ultimate_%d.png";
	boomStr1 = name + "_boom_0%d.png";
	boomStr2 = name + "_boom_%d.png";

	if (name == "Kid_Buu") {
		idleNum = 4;
		runNum = 6;
		meleeAttack1Num = 5;
		meleeAttack2Num = 8;
		meleeAttack3Num = 14;
		rangedAttackNum = 6;
		jumpNum = 6;
		hitNum = 2;
		deadNum = 5;
		winNum = 7;
		hittedAwayNum = 8;
		dashNum = 5;
		defendNum = 1;
		chargeNum = 4;
		ultimateNum = 10;

		ultimateBallNum = 4;
		ultimateBallBegin = 11;
		ultimateBallEnd = 14;//大招
		chargeEffectNum = 11;
		chargeEffectBegin = 0;
		chargeEffectEnd = 10;//蓄力
		rangedBallNumber = 30;//远程攻击
		explosionNum = 17;
		explosionBegin = 31;
		explosionEnd = 47;//爆炸
		hitEffectNum = 8;
		hitEffectBegin = 53;
		hitEffectEnd = 60;//被击打特效
	}
	else if (name == "Goku") {
		idleNum = 4;
		runNum = 6;
		meleeAttack1Num = 4;
		meleeAttack2Num = 9;
		meleeAttack3Num = 15;
		rangedAttackNum = 6;
		jumpNum = 7;
		hitNum = 2;
		deadNum = 5;
		winNum = 8;
		hittedAwayNum = 7; //todo
		dashNum = 2;
		defendNum = 1;
		chargeNum = 4;
		ultimateNum = 10;

		ultimateBallNum = 4;
		ultimateBallBegin = 11;
		ultimateBallEnd = 14;//大招
		chargeEffectNum = 11;
		chargeEffectBegin = 0;
		chargeEffectEnd = 10;//蓄力
		rangedBallNumber = 30;//远程攻击
		explosionNum = 17;
		explosionBegin = 31;
		explosionEnd = 47;//爆炸
		hitEffectNum = 8;
		hitEffectBegin = 53;
		hitEffectEnd = 60;//被击打特效
	}
	else if (name == "Frieza") {
		idleNum = 3;
		runNum = 8;
		meleeAttack1Num = 4;
		meleeAttack2Num = 7;
		meleeAttack3Num = 11;
		rangedAttackNum = 6;
		jumpNum = 7;
		hitNum = 2;
		deadNum = 4;
		winNum = 5;
		hittedAwayNum = 7;
		dashNum = 2;
		defendNum = 1;
		chargeNum = 4;
		ultimateNum = 5;

		ultimateBallNum = 4;
		ultimateBallBegin = 11;
		ultimateBallEnd = 14;//大招
		chargeEffectNum = 11;
		chargeEffectBegin = 0;
		chargeEffectEnd = 10;//蓄力
		rangedBallNumber = 30;//远程攻击
		explosionNum = 17;
		explosionBegin = 31;
		explosionEnd = 47;//爆炸
		hitEffectNum = 8;
		hitEffectBegin = 53;
		hitEffectEnd = 60;//被击打特效
	}
	else if (name == "Vegeta") {
		idleNum = 4;
		runNum = 6;
		meleeAttack1Num = 5;
		meleeAttack2Num = 12;
		meleeAttack3Num = 17;
		rangedAttackNum = 5;
		jumpNum = 7;
		hitNum = 2;
		deadNum = 5;
		winNum = 6;
		hittedAwayNum = 2;  //
		dashNum = 4;   //
		defendNum = 1;
		chargeNum = 4;
		ultimateNum = 7;

		ultimateBallNum = 4;
		ultimateBallBegin = 11;
		ultimateBallEnd = 14;//大招
		chargeEffectNum = 11;
		chargeEffectBegin = 0;
		chargeEffectEnd = 10;//蓄力
		rangedBallNumber = 30;//远程攻击
		explosionNum = 17;
		explosionBegin = 31;
		explosionEnd = 47;//爆炸
		hitEffectNum = 8;
		hitEffectBegin = 53;
		hitEffectEnd = 60;//被击打特效
	}

	rangedBallStr = name + "_boom_" + std::to_string(rangedBallNumber) + ".png";
}

Charactor::~Charactor(){}