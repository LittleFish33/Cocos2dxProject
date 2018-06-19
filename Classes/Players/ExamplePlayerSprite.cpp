#include "ExamplePlayerSprite.h"
#include "../configuration.h"
/* 初始化精灵类的hp,mp,攻击力，速度，跳跃高度 */
void ExamplePlayerSprite::initSprite()
{
	hp = EXAMPLE_PLAYER_HP;
	mp = EXAMPLE_PLAYER_MP;
	damage = EXAMPLE_PLAYER_DAMAGE;
	speed = EXAMPLE_PLAYER_SPEED;
	height = EXAMPLE_PLAYER_HEIGHT;
}
/* 预设置动画帧的值 */
void ExamplePlayerSprite::initAnimateFrame()
{
	auto texture = Director::getInstance()->getTextureCache()->addImage("$lucia_2.png");
	auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 113, 113)));

	/* 静态动画 */
	idleVector.reserve(1);
	idleVector.pushBack(frame0);

	/* 死亡动画 */
	auto texture2 = Director::getInstance()->getTextureCache()->addImage("$lucia_dead.png");
	deadVector.reserve(22);
	for (int i = 0; i < 22; i++) {
		auto frame = SpriteFrame::createWithTexture(texture2, CC_RECT_PIXELS_TO_POINTS(Rect(79 * i, 0, 79, 90)));
		deadVector.pushBack(frame);
	}

	/* 运动动画 */
	auto texture3 = Director::getInstance()->getTextureCache()->addImage("$lucia_forward.png");
	runVector.reserve(8);
	for (int i = 0; i < 8; i++) {
		auto frame = SpriteFrame::createWithTexture(texture3, CC_RECT_PIXELS_TO_POINTS(Rect(68 * i, 0, 68, 101)));
		runVector.pushBack(frame);
	}

	/* 近攻动画 */
	meleeAttackVector.reserve(17);
	for (int i = 0; i < 17; i++) {
		auto frame = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(113 * i, 0, 113, 113)));
		meleeAttackVector.pushBack(frame);
	}

	/* 远攻动画：这里使用和死亡动画相同的动画帧 */
	rangedAttackVector.reserve(22);
	for (int i = 0; i < 22; i++) {
		auto frame = SpriteFrame::createWithTexture(texture2, CC_RECT_PIXELS_TO_POINTS(Rect(79 * i, 0, 79, 90)));
		rangedAttackVector.pushBack(frame);
	}

	/* 跳跃动画：这里使用和行走动画相同的动画帧 */
	jumpVector.reserve(8);
	for (int i = 0; i < 8; i++) {
		auto frame = SpriteFrame::createWithTexture(texture3, CC_RECT_PIXELS_TO_POINTS(Rect(68 * i, 0, 68, 101)));
		jumpVector.pushBack(frame);
	}

	/* 被攻击动画：这里使用和死亡动画相同的动画帧 */
	hitVector.reserve(22);
	for (int i = 0; i < 22; i++) {
		auto frame = SpriteFrame::createWithTexture(texture2, CC_RECT_PIXELS_TO_POINTS(Rect(79 * i, 0, 79, 90)));
		hitVector.pushBack(frame);
	}

}

/* 玩家向左移动：这里和homework4的代码基本一致，所以函数内就不做注释了 */
void ExamplePlayerSprite::moveLeft()
{
	if (isRun) {
		return;
	}
	setFlippedX(true);
	auto begin = CallFuncN::create([&](Ref* sender) {
		if (!stopLeftMove) {
			isRun = true;
		}
	});
	auto end = CallFuncN::create([&](Ref* sender) {
		isRun = false;
	});
	auto moveBy = MoveBy::create(0.8f, Vec2((float)(-speed), 0));
	auto animation = Animation::createWithSpriteFrames(runVector, 0.1f);
	auto animate = Animate::create(animation);
	auto myspawn = Spawn::createWithTwoActions(moveBy, animate);
	auto seq = Sequence::create(begin, myspawn, end, NULL);
	seq->setTag(1); /* 特定动作对应标签 */
	stopAllActions();
	runAction(seq);
}

/* 玩家向右移动 */
void ExamplePlayerSprite::moveRight()
{
	if (isRun) {
		return;
	}
	setFlippedX(false);
	auto begin = CallFuncN::create([&](Ref* sender) {
		if (!stopRightMove) {
			isRun = true;
		}
	});
	auto end = CallFuncN::create([&](Ref* sender) {
		isRun = false;
	});
	auto moveBy = MoveBy::create(0.8f, Vec2((float)speed, 0));
	auto animation = Animation::createWithSpriteFrames(runVector, 0.1f);
	auto animate = Animate::create(animation);
	auto myspawn = Spawn::createWithTwoActions(moveBy, animate);
	auto seq = Sequence::create(begin, myspawn, end, NULL);
	seq->setTag(2);
	stopAllActions();
	runAction(seq);

}

/* 玩家站着不动 */
void ExamplePlayerSprite::idle()
{
	auto animation = Animation::createWithSpriteFrames(idleVector, 0.1f);
	auto animate = Animate::create(animation);
	auto idleAction = RepeatForever::create(animate);
	idleAction->setTag(0);
	runAction(idleAction);
}

/* 近程攻击 */
void ExamplePlayerSprite::meleeAttack()
{
	if (isRun) {
		return;
	}
	auto begin = CallFuncN::create([&](Ref* sender) {
		if (!stopMeleeAttack) {
			isRun = true;
		}
	});
	auto end = CallFuncN::create([&](Ref* sender) {
		isRun = false;
	});
	auto animation = Animation::createWithSpriteFrames(meleeAttackVector, 0.1f);
	auto animate = Animate::create(animation);
	auto seq = Sequence::create(begin, animate, end, NULL);
	seq->setTag(4);
	stopAllActions();
	runAction(seq);

}

/* 远程攻击 */
void ExamplePlayerSprite::rangedAttack()
{
	if (isRun) {
		return;
	}
	auto begin = CallFuncN::create([&](Ref* sender) {
		if (!stopRangedAttack) {
			isRun = true;
		}
	});
	auto end = CallFuncN::create([&](Ref* sender) {
		isRun = false;
	});
	auto animation = Animation::createWithSpriteFrames(rangedAttackVector, 0.1f);
	auto animate = Animate::create(animation);
	auto seq = Sequence::create(begin, animate, end, NULL);
	seq->setTag(5);
	stopAllActions();
	runAction(seq);
}

/* 玩家向上跳 */
void ExamplePlayerSprite::jump()
{
	if (isRun) {
		return;
	}
	auto begin = CallFuncN::create([&](Ref* sender) {
		if (!stopJump) {
			isRun = true;
		}
	});
	auto end = CallFuncN::create([&](Ref* sender) {
		isRun = false;
	});
	auto jumpBy = JumpBy::create(0.5f, Vec2(0, 0), 200, 1);
	runAction(jumpBy);
	auto animation = Animation::createWithSpriteFrames(jumpVector, 0.1f);
	auto animate = Animate::create(animation);
	auto myspawn = Spawn::createWithTwoActions(jumpBy, animate);
	auto seq = Sequence::create(begin, myspawn, end, NULL);
	seq->setTag(3);
	stopAllActions();
	runAction(seq);
}

/* 玩家被攻击 */
void ExamplePlayerSprite::hit()
{

}

/* 玩家死亡 */
void ExamplePlayerSprite::dead()
{

}
