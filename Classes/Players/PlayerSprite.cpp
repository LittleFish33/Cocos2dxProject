#include "PlayerSprite.h"
#include "../configuration.h"
/* 初始化精灵类的hp,mp,攻击力，速度，跳跃高度 */
void PlayerSprite::initSprite(std::string name)
{
	hp = EXAMPLE_PLAYER_HP;
	mp = EXAMPLE_PLAYER_MP;
	damage = EXAMPLE_PLAYER_DAMAGE;
	speed = EXAMPLE_PLAYER_SPEED;
	height = EXAMPLE_PLAYER_HEIGHT;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(name + ".plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(name + "_boom.plist");
	charactor = new Charactor(name);
}
/* 预设置动画帧的值 */
void PlayerSprite::initAnimateFrame()
{
	char frameName[30];

	/* 静态动画 */
	idleVector.reserve(charactor->getIdleNum());
	for (int i = 1; i <= charactor->getIdleNum(); i++)
	{
		sprintf(frameName, charactor->getIdleStr(), i);
		idleVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	initWithSpriteFrame(idleVector.at(0));
	setScale(1.5f);

	/* 死亡动画 */
	deadVector.reserve(charactor->getDeadNum());
	for (int i = 1; i <= charactor->getDeadNum(); i++) {
		sprintf(frameName, charactor->getDeadStr(), i);
		deadVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/* 运动动画 */
	runVector.reserve(charactor->getRunNum());
	for (int i = 1; i <= charactor->getRunNum(); i++) {
		sprintf(frameName, charactor->getRunStr(), i);
		runVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/* 近攻动画 */
	meleeAttackVector.reserve(charactor->getMeleeAttackNum());
	for (int i = 1; i <= charactor->getMeleeAttackNum(); i++) {
		if(i < 10)
			sprintf(frameName, charactor->getMeleeAttackStr1(), i);
		else
			sprintf(frameName, charactor->getMeleeAttackStr2(), i);
		meleeAttackVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/* 远攻动画：这里使用和死亡动画相同的动画帧 */
	rangedAttackVector.reserve(charactor->getRangedAttackNum());
	for (int i = 1; i <= charactor->getRangedAttackNum(); i++) {
		sprintf(frameName, charactor->getRangedAttackStr(), i);
		rangedAttackVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/* 跳跃动画：这里使用和行走动画相同的动画帧 */
	jumpVector.reserve(charactor->getJumpNum());
	for (int i = 1; i <= charactor->getJumpNum(); i++) {
		sprintf(frameName, charactor->getJumpStr(), i);
		jumpVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}


	/* 被攻击动画：这里使用和死亡动画相同的动画帧 */
	hitVector.reserve(charactor->getHitNum());
	for (int i = 1; i <= charactor->getHitNum(); i++) {
		sprintf(frameName, charactor->getHitStr(), i);
		hitVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/*胜利动画*/
	winVector.reserve(charactor->getWinNum());
	for (int i = 1; i <= charactor->getWinNum(); i++) {
		sprintf(frameName, charactor->getWinStr(), i);
		winVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/*打飞动画，下同*/
	hittedAwayVector1.reserve(1);
	hittedAwayVector1.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(charactor->getHittedAwayStr1()));

	hittedAwayVector2.reserve(charactor->getHittedAwayNum());
	for (int i = 1; i <= charactor->getHittedAwayNum(); i++) {
		sprintf(frameName, charactor->getHittedAwayStr2(), i);
		hittedAwayVector2.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/*格挡动画*/
	defendVector.reserve(charactor->getDefendNum());
	for (int i = 1; i <= charactor->getDefendNum(); i++) {
		sprintf(frameName, charactor->getDefendStr(), i);
		defendVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/*蓄力动画*/
	chargeVector.reserve(charactor->getChargeNum());
	for (int i = 1; i <= charactor->getChargeNum(); i++) {
		sprintf(frameName, charactor->getChargeStr(), i);
		chargeVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/* 快速移动动画 */
	dashVector.reserve(charactor->getDashNum());
	for (size_t i = 1; i <= charactor->getDashNum(); i++)
	{
		sprintf(frameName, charactor->getDashStr(), i);
		dashVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/*大招动画*/
	ultimateVector.reserve(charactor->getUltimateNum());
	for (size_t i = 1; i <= charactor->getUltimateNum(); i++)
	{
		if(i < 10)
			sprintf(frameName, charactor->getUltimateStr1(), i);
		else
			sprintf(frameName, charactor->getUltimateStr2(), i);
		ultimateVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/*大招的球*/
	ultimateBallVector.reserve(charactor->getUltimateBallNum());
	for (size_t i = charactor->getUltimateBallBegin(); i <= charactor->getUltimateBallEnd(); i++)
	{
		CCLOG("%d", i);
		if (i < 10)
			sprintf(frameName, charactor->getBoomStr1(), i);
		else
			sprintf(frameName, charactor->getBoomStr2(), i);
		ultimateBallVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/*远程攻击的球*/
	rangedBallVector.reserve(1);
	rangedBallVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(charactor->getRangedBallStr()));

	/*蓄力效果*/
	chargeEffectVector.reserve(charactor->getChargeEffectNum());
	for (size_t i = charactor->getChargeEffectBegin(); i <= charactor->getChargeEffectEnd(); i++)
	{
		if (i < 10)
			sprintf(frameName, charactor->getBoomStr1(), i);
		else
			sprintf(frameName, charactor->getBoomStr2(), i);
		chargeEffectVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/*大招的爆炸*/
	explosionVector.reserve(charactor->getExplosionNum());
	for (size_t i = charactor->getExplosionBegin(); i <= charactor->getExplosionEnd(); i++)
	{
		if (i < 10)
			sprintf(frameName, charactor->getBoomStr1(), i);
		else
			sprintf(frameName, charactor->getBoomStr2(), i);
		explosionVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}

	/*被打时的效果*/
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

/* 玩家向左移动：这里和homework4的代码基本一致，所以函数内就不做注释了 */
void PlayerSprite::moveLeft()
{
	if (isRun) {
		Vec2 pos = getPosition();
		setPosition(pos + Vec2(-15, 0));
		return;
	}
	setFlippedX(false);
	auto moveBy = MoveBy::create(0.45f, Vec2(-(float)speed * 2, 0));
	auto animation = Animation::createWithSpriteFrames(runVector, 0.09f);
	auto animate = Animate::create(animation);
	auto myspawn = Spawn::createWithTwoActions(moveBy, animate);
	auto MoveAction = RepeatForever::create(myspawn);
	auto seq = Sequence::create(myspawn, NULL);
	MoveAction->setTag(1);
	stopAllActions();
	runAction(MoveAction);
}

/* 玩家向右移动 */
void PlayerSprite::moveRight()
{
	if (isRun) {
		Vec2 pos = getPosition();
		setPosition(pos + Vec2(15, 0));
		return;
	}
	setFlippedX(true);
	auto moveBy = MoveBy::create(0.45f, Vec2((float)speed * 2, 0));
	auto animation = Animation::createWithSpriteFrames(runVector, 0.09f);
	auto animate = Animate::create(animation);
	auto myspawn = Spawn::createWithTwoActions(moveBy, animate);
	auto MoveAction = RepeatForever::create(myspawn);
	auto seq = Sequence::create(myspawn,NULL);
	MoveAction->setTag(2);
	stopAllActions();
	runAction(MoveAction);

}

/* 玩家站着不动 */
void PlayerSprite::idle()
{
	if (isRun) return;
	auto animation = Animation::createWithSpriteFrames(idleVector, 0.3f);
	auto animate = Animate::create(animation);
	auto idleAction = RepeatForever::create(animate);
	idleAction->setTag(0);
	runAction(idleAction);
}

/* 近程攻击 */
void PlayerSprite::meleeAttack()
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
	auto animation = Animation::createWithSpriteFrames(meleeAttackVector, 0.1f);
	auto animate = Animate::create(animation);
	animate->setOriginalTarget(false);
	auto seq = Sequence::create(begin, animate, end, NULL);
	seq->setTag(4);
	stopAllActions();
	runAction(seq);

}

/* 远程攻击 */
void PlayerSprite::rangedAttack()
{
	if (isRun) {
		return;
	}
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

/* 玩家向上跳 */
void PlayerSprite::jump()
{
	if (isRun) {
		return;
	}
	auto begin = CallFuncN::create([&](Ref* sender) {
		isRun = true;
	});
	auto end = CallFuncN::create([&](Ref* sender) {
		isRun = false;
		idle();
	});
	auto jumpBy = JumpBy::create(1, Vec2(0, 0), 200, 1);
	//runAction(jumpBy);
	auto animation = Animation::createWithSpriteFrames(jumpVector, 0.1f);
	auto animate = Animate::create(animation);
	auto myspawn = Spawn::createWithTwoActions(jumpBy, animate);
	auto seq = Sequence::create(begin, myspawn, end, NULL);
	seq->setTag(3);
	stopAllActions();
	runAction(seq);
}

/* 玩家被攻击 */
void PlayerSprite::hit()
{
	if (isRun) {
		return;
	}
	if (hittedCount < 3) {
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

/* 玩家死亡 */
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

/*左冲*/
void PlayerSprite::dashLeft() 
{
	if (isRun) {
		return;
	}
	setFlippedX(false);
	auto moveTo = MoveTo::create((getPositionX() - 80) / 800.0, Vec2(80, getPositionY()));
	auto animation = Animation::createWithSpriteFrames(dashVector, 0.09f, 0);
	auto animate = Animate::create(animation);
	auto myspawn = Spawn::createWithTwoActions(moveTo, animate);
	myspawn->setTag(13);
	stopAllActions();
	runAction(myspawn);
}

/*右冲*/
void PlayerSprite::dashRight()
{
	if (isRun) {
		return;
	}
	setFlippedX(true);
	auto moveTo = MoveTo::create((950.0 - getPositionX()) / 800.0, Vec2(950, getPositionY()));
	auto animation = Animation::createWithSpriteFrames(dashVector, 0.09f, 0);
	auto animate = Animate::create(animation);
	moveTo->setTag(6);
	auto myspawn = Spawn::createWithTwoActions(moveTo, animate);
	myspawn->setTag(14);
	stopAllActions();
	runAction(myspawn);
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

/*被打飞的动画，在被打函数中调用*/
void PlayerSprite::hittedAway() {
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
	/*这里的flipX最好用另一个角色的flipX，单例类完成后更改*/
	int direction = 1;
	if (!_flippedX) direction = -1;
	animate1->setOriginalTarget(false);
	auto moveBy1 = MoveBy::create(0.5f, Vec2(180 * -direction, -10));
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

/*格挡*/
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

/*蓄力*/
void PlayerSprite::charge() {
	if (isRun) {
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

void PlayerSprite::ultimate() {
	if (isRun) {
		return;
	}
	auto begin = CallFuncN::create([&](Ref* sender) {
		isRun = true;
	});
	auto end = CallFuncN::create([&](Ref* sender) {
		isRun = false;
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
