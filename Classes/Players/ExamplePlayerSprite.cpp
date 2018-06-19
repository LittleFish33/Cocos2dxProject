#include "ExamplePlayerSprite.h"
#include "../configuration.h"
/* ��ʼ���������hp,mp,���������ٶȣ���Ծ�߶� */
void ExamplePlayerSprite::initSprite()
{
	hp = EXAMPLE_PLAYER_HP;
	mp = EXAMPLE_PLAYER_MP;
	damage = EXAMPLE_PLAYER_DAMAGE;
	speed = EXAMPLE_PLAYER_SPEED;
	height = EXAMPLE_PLAYER_HEIGHT;
}
/* Ԥ���ö���֡��ֵ */
void ExamplePlayerSprite::initAnimateFrame()
{
	auto texture = Director::getInstance()->getTextureCache()->addImage("$lucia_2.png");
	auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 113, 113)));

	/* ��̬���� */
	idleVector.reserve(1);
	idleVector.pushBack(frame0);

	/* �������� */
	auto texture2 = Director::getInstance()->getTextureCache()->addImage("$lucia_dead.png");
	deadVector.reserve(22);
	for (int i = 0; i < 22; i++) {
		auto frame = SpriteFrame::createWithTexture(texture2, CC_RECT_PIXELS_TO_POINTS(Rect(79 * i, 0, 79, 90)));
		deadVector.pushBack(frame);
	}

	/* �˶����� */
	auto texture3 = Director::getInstance()->getTextureCache()->addImage("$lucia_forward.png");
	runVector.reserve(8);
	for (int i = 0; i < 8; i++) {
		auto frame = SpriteFrame::createWithTexture(texture3, CC_RECT_PIXELS_TO_POINTS(Rect(68 * i, 0, 68, 101)));
		runVector.pushBack(frame);
	}

	/* �������� */
	meleeAttackVector.reserve(17);
	for (int i = 0; i < 17; i++) {
		auto frame = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(113 * i, 0, 113, 113)));
		meleeAttackVector.pushBack(frame);
	}

	/* Զ������������ʹ�ú�����������ͬ�Ķ���֡ */
	rangedAttackVector.reserve(22);
	for (int i = 0; i < 22; i++) {
		auto frame = SpriteFrame::createWithTexture(texture2, CC_RECT_PIXELS_TO_POINTS(Rect(79 * i, 0, 79, 90)));
		rangedAttackVector.pushBack(frame);
	}

	/* ��Ծ����������ʹ�ú����߶�����ͬ�Ķ���֡ */
	jumpVector.reserve(8);
	for (int i = 0; i < 8; i++) {
		auto frame = SpriteFrame::createWithTexture(texture3, CC_RECT_PIXELS_TO_POINTS(Rect(68 * i, 0, 68, 101)));
		jumpVector.pushBack(frame);
	}

	/* ����������������ʹ�ú�����������ͬ�Ķ���֡ */
	hitVector.reserve(22);
	for (int i = 0; i < 22; i++) {
		auto frame = SpriteFrame::createWithTexture(texture2, CC_RECT_PIXELS_TO_POINTS(Rect(79 * i, 0, 79, 90)));
		hitVector.pushBack(frame);
	}

}

/* ��������ƶ��������homework4�Ĵ������һ�£����Ժ����ھͲ���ע���� */
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
	seq->setTag(1); /* �ض�������Ӧ��ǩ */
	stopAllActions();
	runAction(seq);
}

/* ��������ƶ� */
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

/* ���վ�Ų��� */
void ExamplePlayerSprite::idle()
{
	auto animation = Animation::createWithSpriteFrames(idleVector, 0.1f);
	auto animate = Animate::create(animation);
	auto idleAction = RepeatForever::create(animate);
	idleAction->setTag(0);
	runAction(idleAction);
}

/* ���̹��� */
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

/* Զ�̹��� */
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

/* ��������� */
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

/* ��ұ����� */
void ExamplePlayerSprite::hit()
{

}

/* ������� */
void ExamplePlayerSprite::dead()
{

}
