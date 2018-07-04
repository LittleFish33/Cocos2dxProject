#include "PlayerSprite.h"
#include "../configuration.h"
/* ��ʼ���������hp,mp,���������ٶȣ���Ծ�߶� */
void PlayerSprite::initSprite(std::string name, Sprite* player)
{
	physicPlayer = player;
	hp = EXAMPLE_PLAYER_HP;
	mp = EXAMPLE_PLAYER_MP;
	damage = EXAMPLE_PLAYER_DAMAGE;
	speed = EXAMPLE_PLAYER_SPEED;
	height = EXAMPLE_PLAYER_HEIGHT;
	try {
		
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(name + ".plist");
		
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(name + "_boom.plist");
		
	}
	catch (exception err) {
		log("error %s.plist", name.c_str());
		log("error %s_boom.plist", name.c_str());
	}
	log("loaded texture");

	charactor = new Charactor(name);
}
/* Ԥ���ö���֡��ֵ */
void PlayerSprite::initAnimateFrame()
{
	char frameName[30];

	/* ��̬���� */
	idleVector.reserve(charactor->getIdleNum());
	for (int i = 1; i <= charactor->getIdleNum(); i++)
	{
		sprintf(frameName, charactor->getIdleStr(), i);
		idleVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	initWithSpriteFrame(idleVector.at(0));
	setScale(1.5f);

	/* �������� */
	deadVector.reserve(charactor->getDeadNum());
	for (int i = 1; i <= charactor->getDeadNum(); i++) {
		sprintf(frameName, charactor->getDeadStr(), i);
		deadVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/* �˶����� */
	runVector.reserve(charactor->getRunNum());
	for (int i = 1; i <= charactor->getRunNum(); i++) {
		sprintf(frameName, charactor->getRunStr(), i);
		runVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/* ������������ȭ */
	meleeAttackVector1.reserve(charactor->getMeleeAttack1Num());
	for (int i = 1; i <= charactor->getMeleeAttack1Num(); i++) {
		if(i < 10)
			sprintf(frameName, charactor->getMeleeAttackStr1(), i);
		else
			sprintf(frameName, charactor->getMeleeAttackStr2(), i);
		meleeAttackVector1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/* ������������ȭ + �Ϲ�ȭ */
	meleeAttackVector2.reserve(charactor->getMeleeAttack2Num());
	for (int i = 1; i <= charactor->getMeleeAttack2Num(); i++) {
		if (i < 10)
			sprintf(frameName, charactor->getMeleeAttackStr1(), i);
		else
			sprintf(frameName, charactor->getMeleeAttackStr2(), i);
		meleeAttackVector2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/* ������������ȭ + �Ϲ�ȭ + ���� */
	meleeAttackVector3.reserve(charactor->getMeleeAttack3Num());
	for (int i = 1; i <= charactor->getMeleeAttack3Num(); i++) {
		if (i < 10)
			sprintf(frameName, charactor->getMeleeAttackStr1(), i);
		else
			sprintf(frameName, charactor->getMeleeAttackStr2(), i);
		meleeAttackVector3.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/* Զ������������ʹ�ú�����������ͬ�Ķ���֡ */
	rangedAttackVector.reserve(charactor->getRangedAttackNum());
	for (int i = 1; i <= charactor->getRangedAttackNum(); i++) {
		sprintf(frameName, charactor->getRangedAttackStr(), i);
		rangedAttackVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/* ��Ծ����������ʹ�ú����߶�����ͬ�Ķ���֡ */
	jumpVector.reserve(charactor->getJumpNum());
	for (int i = 1; i <= charactor->getJumpNum(); i++) {
		sprintf(frameName, charactor->getJumpStr(), i);
		jumpVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}


	/* ����������������ʹ�ú�����������ͬ�Ķ���֡ */
	hitVector.reserve(charactor->getHitNum());
	for (int i = 1; i <= charactor->getHitNum(); i++) {
		sprintf(frameName, charactor->getHitStr(), i);
		hitVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/*ʤ������*/
	winVector.reserve(charactor->getWinNum());
	for (int i = 1; i <= charactor->getWinNum(); i++) {
		sprintf(frameName, charactor->getWinStr(), i);
		winVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/*��ɶ�������ͬ*/
	hittedAwayVector1.reserve(1);
	hittedAwayVector1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(charactor->getHittedAwayStr1()));

	hittedAwayVector2.reserve(charactor->getHittedAwayNum());
	for (int i = 1; i <= charactor->getHittedAwayNum(); i++) {
		sprintf(frameName, charactor->getHittedAwayStr2(), i);
		hittedAwayVector2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/*�񵲶���*/
	defendVector.reserve(charactor->getDefendNum());
	for (int i = 1; i <= charactor->getDefendNum(); i++) {
		sprintf(frameName, charactor->getDefendStr(), i);
		defendVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/*��������*/
	chargeVector.reserve(charactor->getChargeNum());
	for (int i = 1; i <= charactor->getChargeNum(); i++) {
		sprintf(frameName, charactor->getChargeStr(), i);
		chargeVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/* �����ƶ����� */
	dashVector.reserve(charactor->getDashNum());
	for (size_t i = 1; i <= charactor->getDashNum(); i++)
	{
		sprintf(frameName, charactor->getDashStr(), i);
		dashVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/*���ж���*/
	ultimateVector.reserve(charactor->getUltimateNum());
	for (size_t i = 1; i <= charactor->getUltimateNum(); i++)
	{
		if(i < 10)
			sprintf(frameName, charactor->getUltimateStr1(), i);
		else
			sprintf(frameName, charactor->getUltimateStr2(), i);
		ultimateVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/*���е���*/
	ultimateBallVector.reserve(charactor->getUltimateBallNum());
	for (size_t i = charactor->getUltimateBallBegin(); i <= charactor->getUltimateBallEnd(); i++)
	{
		if (i < 10)
			sprintf(frameName, charactor->getBoomStr1(), i);
		else
			sprintf(frameName, charactor->getBoomStr2(), i);
		ultimateBallVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/*Զ�̹�������*/
	rangedBallVector.reserve(1);
	rangedBallVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(charactor->getRangedBallStr()));

	/*����Ч��*/
	chargeEffectVector.reserve(charactor->getChargeEffectNum());
	for (size_t i = charactor->getChargeEffectBegin(); i <= charactor->getChargeEffectEnd(); i++)
	{
		if (i < 10)
			sprintf(frameName, charactor->getBoomStr1(), i);
		else
			sprintf(frameName, charactor->getBoomStr2(), i);
		chargeEffectVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/*���еı�ը*/
	explosionVector.reserve(charactor->getExplosionNum());
	for (size_t i = charactor->getExplosionBegin(); i <= charactor->getExplosionEnd(); i++)
	{
		if (i < 10)
			sprintf(frameName, charactor->getBoomStr1(), i);
		else
			sprintf(frameName, charactor->getBoomStr2(), i);
		explosionVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/*����ʱ��Ч��*/
	hitEffectVector.reserve(charactor->getHitEffectNum());
	for (size_t i = charactor->getHitEffectBegin(); i <= charactor->getHitEffectEnd(); i++)
	{
		if (i < 10)
			sprintf(frameName, charactor->getBoomStr1(), i);
		else
			sprintf(frameName, charactor->getBoomStr2(), i);
		hitEffectVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
}

/* ��������ƶ� */
void PlayerSprite::moveLeft()
{
	if (isUltimate) {
		return;
	}
	setFlippedX(false);
	if (isHitting || isHitted) {
		return;
	}
	physicPlayer->getPhysicsBody()->setVelocity(Vec2(-250, 0));
	if (isRun) {
		return;
	}
	isMove = true;
	auto animation = Animation::createWithSpriteFrames(runVector, 0.09f);
	auto animate = Animate::create(animation);
	auto MoveAnimate = RepeatForever::create(animate);
	MoveAnimate->setTag(1);
	stopAllActions();
	runAction(MoveAnimate);
}

/* ��������ƶ� */
void PlayerSprite::moveRight()
{
	if (isUltimate) {
		return;
	}
	setFlippedX(true);
	if (isHitting || isHitted) {
		return;
	}
	physicPlayer->getPhysicsBody()->setVelocity(Vec2(250, 0));
	if (isRun) {
		return;
	}
	isMove = true;
	auto animation = Animation::createWithSpriteFrames(runVector, 0.09f);
	auto animate = Animate::create(animation);
	auto MoveAnimate = RepeatForever::create(animate);
	MoveAnimate->setTag(2);
	stopAllActions();
	runAction(MoveAnimate);
}

/* ���վ�Ų��� */
void PlayerSprite::idle()
{
	if (isRun) return;
	auto animation = Animation::createWithSpriteFrames(idleVector, 0.3f);
	auto animate = Animate::create(animation);
	auto idleAction = RepeatForever::create(animate);
	idleAction->setTag(0);
	runAction(idleAction);
}

/* ������������ȭ */
void PlayerSprite::meleeAttack1()
{
	if (isRun) return;
	auto begin = CallFuncN::create([&](Ref* sender) {
		isHitting = true;
		isRun = true;
	});
	
	auto end = CallFuncN::create([&](Ref* sender) {
		isHitting = false;
		isRun = false;
		idle();
	});
	
	auto animation = Animation::createWithSpriteFrames(meleeAttackVector1, 0.1f);
	auto animate = Animate::create(animation);
	animate->setOriginalTarget(false);
	auto seq = Sequence::create(begin, animate, DelayTime::create(0.05f), end, NULL);
	seq->setTag(4);
	stopAllActions();
	runAction(seq);
}

/* ������������ȭ + �Ϲ�ȭ */
void PlayerSprite::meleeAttack2()
{
	if (isRun) return;
	auto begin = CallFuncN::create([&](Ref* sender) {
		isHitting = true;
		isRun = true;
	});

	auto end = CallFuncN::create([&](Ref* sender) {
		isHitting = false;
		isRun = false;
		idle();
	});

	auto animation = Animation::createWithSpriteFrames(meleeAttackVector2, 0.1f);
	auto animate = Animate::create(animation);
	animate->setOriginalTarget(false);
	auto seq = Sequence::create(begin, animate, DelayTime::create(0.1f), end, NULL);
	seq->setTag(4);
	stopAllActions();
	runAction(seq);
}

/* ������������ȭ + �Ϲ�ȭ + ���� */
void PlayerSprite::meleeAttack3()
{
	if (isRun) return;
	auto begin = CallFuncN::create([&](Ref* sender) {
		isHitting = true;
		isRun = true;
	});

	auto attackEnd = CallFuncN::create([&](Ref* sender) {
		isHitting = false;
	});

	auto end = CallFuncN::create([&](Ref* sender) {
		isRun = false;
		idle();
	});

	auto animation = Animation::createWithSpriteFrames(meleeAttackVector3, 0.1f);
	auto animate = Animate::create(animation);
	animate->setOriginalTarget(false);
	auto idleAnimation = Animation::createWithSpriteFrames(idleVector, 0.1f);
	auto idleAnimate = Animate::create(idleAnimation);
	auto seq = Sequence::create(begin, animate, attackEnd, idleAnimate, end, NULL);
	seq->setTag(4);
	stopAllActions();
	runAction(seq);
}


/* Զ�̹��� */
void PlayerSprite::rangedAttack()
{
	if (isRun || mp < 10) {
		return;
	}
	mp -= 10;
	auto begin = CallFuncN::create([&](Ref* sender) {
		isRun = true;
		isHitting = true;
	});
	auto end = CallFuncN::create([&](Ref* sender) {
		isRun = false;
		isHitting = false;
		idle();
	});
	auto animation = Animation::createWithSpriteFrames(rangedAttackVector, 0.12f);
	auto animate = Animate::create(animation);
	auto seq = Sequence::create(begin, animate, end, NULL);
	seq->setTag(5);
	stopAllActions();
	runAction(seq);
}

/* ��������� */
void PlayerSprite::jump()
{
	if (isRun || physicPlayer->getPhysicsBody()->getVelocity().x == 800 || physicPlayer->getPhysicsBody()->getVelocity().x == -800) {
		return;
	}
	auto begin = CallFuncN::create([&](Ref* sender) {
		physicPlayer->setPositionY(300);
		isRun = true;
	});
	auto end = CallFuncN::create([&](Ref* sender) {
		isRun = false;
		physicPlayer->setPositionY(84);
		idle();
	});
	auto jumpBy = JumpBy::create(1, Vec2(0, 0), 200, 1);
	auto animation = Animation::createWithSpriteFrames(jumpVector, 0.1f);
	auto animate = Animate::create(animation);
	auto myspawn = Spawn::createWithTwoActions(jumpBy, animate);
	auto seq = Sequence::create(begin, myspawn, end, NULL);
	seq->setTag(3);
	stopAllActions();
	runAction(seq);
}

/* ��ұ����� */
void PlayerSprite::hit()
{
	if (isRun) {
		return;
	}
	if (hittedCount < 3) {
		if (hp >= 5) {
			hp -= 5;
		}
		else {
			hp = 0;
		}
		auto begin = CallFuncN::create([&](Ref* sender) {
			isHitted = true;
			isRun = true;
			hittedCount++;
		});
		auto end = CallFuncN::create([&](Ref* sender) {
			isHitted = false;
			isRun = false;
			idle();
		});
		auto animation = Animation::createWithSpriteFrames(hitVector, 0.15f);
		auto animate = Animate::create(animation);
		auto seq = Sequence::create(begin, animate, end, NULL);
		seq->setTag(6);
		stopAllActions();
		runAction(seq);
	}
	else {
		hittedAway();
	}
}

/* ������� */
void PlayerSprite::dead()
{
	stopAllActions();
	isDead = true;
	auto animation = Animation::createWithSpriteFrames(deadVector, 0.25f);
	auto animate = Animate::create(animation);
	animate->setOriginalTarget(false);
	animate->setTag(7);
	runAction(animate);
}

/* �����л��� */
void PlayerSprite::hitByUltimate()
{
	if (hp >= 30) {
		hp -= 30;
	}
	else {
		hp = 0;
	}
	stopAllActions();
	auto animation = Animation::createWithSpriteFrames(deadVector, 0.25f);
	auto animate = Animate::create(animation);
	auto end = CallFuncN::create([&](Ref* sender) {;
		idle();
	});
	auto seq = Sequence::create(animate, DelayTime::create(0.2f), end, NULL);
	runAction(seq);
}

/* ��� */
void PlayerSprite::dashLeft(Vec2 oppoentPosition)
{
	if (isRun) {
		return;
	}
	isMove = true;
	setFlippedX(false);
	physicPlayer->getPhysicsBody()->setVelocity(Vec2(-800,0));
	auto animation = Animation::createWithSpriteFrames(dashVector, 0.09f, 0);
	auto animate = Animate::create(animation);
	animate->setTag(13);
	stopAllActions();
	runAction(animate);
}

/* �ҳ� */
void PlayerSprite::dashRight(Vec2 oppoentPosition)
{
	if (isRun) {
		return;
	}
	isMove = true;
	setFlippedX(true);
	physicPlayer->getPhysicsBody()->setVelocity(Vec2(800, 0));
	auto animation = Animation::createWithSpriteFrames(dashVector, 0.09f, 0);
	auto animate = Animate::create(animation);
	animate->setTag(14);
	stopAllActions();
	runAction(animate);
}

void PlayerSprite::win() {
	stopAllActions();
	isWin = true;
	auto animation = Animation::createWithSpriteFrames(winVector, 0.25f);
	auto animate = Animate::create(animation);
	animate->setOriginalTarget(false);
	animate->setTag(8);
	runAction(animate);
}

/* ����ɵĶ������ڱ������е���*/
void PlayerSprite::hittedAway() {
	if (hp >= 10) {
		hp -= 10;
	}
	else {
		hp = 0;
	}
	auto begin = CallFuncN::create([&](Ref* sender) {
		isRun = true;
	});
	auto end = CallFuncN::create([&](Ref* sender) {;
		isRun = false;
		hittedCount = 0;
		isDouble = false;
		idle();
	});
	auto animation1 = Animation::createWithSpriteFrames(hittedAwayVector1, 0.05f);
	auto animate1 = Animate::create(animation1);

	int direction = 1;
	if (shareInstance->opponentFlipx) direction = -1;
	animate1->setOriginalTarget(false);
	float moveByX = 0.0;
	if (direction == 1) {
		if (getPositionX() - 60.0 > 180.0) {
			moveByX = 180.0;
		}
		else {
			moveByX = getPositionX() - 60.0;
		}
		
	}
	else if (direction == -1){
		if (950.0 - getPositionX() > 180.0) {
			moveByX = 180.0;
		}
		else {
			moveByX = 950.0 - getPositionX();
		}
	}


	auto moveBy1 = MoveBy::create(0.5f, Vec2(moveByX * -direction, -10));
	auto myspawn1 = Spawn::createWithTwoActions(animate1, moveBy1);

	auto animation2 = Animation::createWithSpriteFrames(hittedAwayVector2, 0.15f);
	auto animate2 = Animate::create(animation2);
	auto moveBy2 = MoveBy::create(0.2f, Vec2(0, 10));
	auto myspawn2 = Spawn::createWithTwoActions(animate2, moveBy2);

	auto seq = Sequence::create(begin, myspawn1, myspawn2, end, NULL);
	seq->setTag(6);
	stopAllActions();
	runAction(seq);
}

/* �� */
void PlayerSprite::defend() {
	if (isRun) {
		return;
	}
	auto animation = Animation::createWithSpriteFrames(defendVector, 0.09f);
	auto animate = Animate::create(animation);
	auto act = RepeatForever::create(animate);
	act->setTag(11);
	stopAllActions();
	runAction(act);
}

/* ���� */
void PlayerSprite::charge() {
	if (getActionByTag(0) == NULL) {
		return;
	}
	auto end = CallFuncN::create([&](Ref* sender) {
		Vector<SpriteFrame*> finalAct;
		finalAct.reserve(1);
		finalAct.pushBack(chargeVector.back());
		auto finalAnima = Animation::createWithSpriteFrames(finalAct, 0.1f);
		auto finalAni = Animate::create(finalAnima);
		auto final = RepeatForever::create(finalAni);
		final->setTag(12);
		stopAllActions();
		runAction(final);
	});
	auto animation = Animation::createWithSpriteFrames(chargeVector, 0.1f);
	auto animate = Animate::create(animation);
	auto seq = Sequence::create( animate, end, NULL);
	seq->setTag(12);
	stopAllActions();
	runAction(seq);

}

/* ���� */
void PlayerSprite::ultimate() {
	if (isRun || mp < 50) {
		return;
	}
	mp -= 50;
	auto begin = CallFuncN::create([&](Ref* sender) {
		isUltimate = true;
		physicPlayer->setPositionY(800);
		isRun = true;
	});
	auto end = CallFuncN::create([&](Ref* sender) {
		physicPlayer->setPositionY(84);
		isRun = false;
		isUltimate = false;
		idle();
	});
	auto move = CallFuncN::create([&](Ref* sender) {
		setPosition(Vec2(getPositionX(), getPositionY() + 300));
	});
	auto moveBack = CallFuncN::create([&](Ref* sender) {
		setPosition(Vec2(getPositionX(), getPositionY() - 300));
	});
	auto fadeOut = FadeOut::create(0.2f);
	auto fadeIn = FadeIn::create(0.2f);
	auto animation = Animation::createWithSpriteFrames(ultimateVector, 0.15f);
	auto animate = Animate::create(animation);
	auto seq = Sequence::create(begin, fadeOut, move, fadeIn, animate, fadeOut, moveBack, fadeIn, end, NULL);
	seq->setTag(9);
	stopAllActions();
	runAction(seq);
}
