#include "ExampleGameScene.h"
#include "SimpleAudioEngine.h"
#include "../configuration.h"
#include "../Players/PlayerSprite.h"
#include <iostream>
#include <cmath>

USING_NS_CC;
/*
*  tag    ����
*  0      idle
*  1      moveLeft
*  2      moveRight
*  3      jump
*  4      meleeAttack
*  5      rangeAttack
*  6	  hitted
*  7	  dead
*  8	  win
*  9	  ultimate
*  10	  
*  11	  defend
*  12	  charge
*  13	  dashLeft
*  14	  dashRight
*/
void ExampleGameScene::setPhysicsWorld(PhysicsWorld* world) { m_world = world; }

Scene* ExampleGameScene::createScene()
{
#pragma region ����������

	srand((unsigned)time(NULL));
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	scene->getPhysicsWorld()->setAutoStep(false);
	auto layer = ExampleGameScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;

#pragma endregion
}


/* ���ļ�������ʱ����ӡ���õĴ�����Ϣ�����Ƿֶδ��� */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in ExampleGameSceneScene.cpp\n");
}

/* ��ʼ���������� */
bool ExampleGameScene::init()
{
#pragma region Cocos2dx�Զ����ɵ����ݣ�һЩ��������

	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

#pragma endregion

#pragma region ��������
	/* Todo������ */

	/* ��ӱ���ͼƬ */
	auto bgSprite = Sprite::create("exampleBackground.png");
	bgSprite->setPosition(visibleSize / 2);
	bgSprite->setScale(visibleSize.width / bgSprite->getContentSize().width, visibleSize.height / bgSprite->getContentSize().height);
	this->addChild(bgSprite, 0);

	/* ��ӵ��� */
	ground = Sprite::create("ground.png");
	ground->setScale(visibleSize.width / ground->getContentSize().width, 1.2f);
	ground->setPosition(visibleSize.width / 2, 0);
	auto groundbody = PhysicsBody::createBox(ground->getContentSize(), PhysicsMaterial(1000.0f, 0.0f, 1.0f));
	groundbody->setCategoryBitmask(0xFFFFFFFF);
	groundbody->setCollisionBitmask(0xFFFFFFFF);
	groundbody->setContactTestBitmask(0xFFFFFFFF);
	groundbody->setTag(1);
	groundbody->setDynamic(false);
	ground->setPhysicsBody(groundbody);
	this->addChild(ground, 1);

#pragma endregion

#pragma region ��������
	/* Todo���������������Ҫ�޸�һ������ĳ�ʼ֡ */
	/* ����һ����ͼ��ʹ����ͼ�������� */
	player1 = new PlayerSprite();
	player1->initSprite("Kid_Buu");
	player1->initAnimateFrame();
	player1->setPosition(Vec2(visibleSize.width / 4 * 3, visibleSize.height / 2 - 300));
	player1->setFlippedX(false);
	addChild(player1, 3);
	player1->idle();
	/*chargeEffect1 = new Sprite();
	chargeEffect1->setVisible(false);
	addChild(chargeEffect1, 2);*/
	/* Todo������˫�˶�ս���������һ������Ľ��� */

	player2 = new PlayerSprite();
	player2->initSprite("Kid_Buu");
	player2->initAnimateFrame();
	player2->setPosition(Vec2(visibleSize.width / 4, visibleSize.height / 2 - 300));
	player2->setFlippedX(true);
	addChild(player2, 3);
	player2->idle();
	
#pragma endregion

#pragma region hp����mp��

	/* Todo�����������������ʣ�µ�hp����mp�� */
	Sprite* sp0 = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
	Sprite* sp = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(610, 362, 4, 16)));

	/* ʹ��hp������progressBar */
	pT = ProgressTimer::create(sp);
	pT->setScaleX(90);
	pT->setAnchorPoint(Vec2(0, 0));
	pT->setType(ProgressTimerType::BAR);
	pT->setBarChangeRate(Point(1, 0));
	pT->setMidpoint(Point(0, 1));
	pT->setPercentage(100);
	pT->setPosition(Vec2(origin.x + 14 * pT->getContentSize().width, origin.y + visibleSize.height - 2 * pT->getContentSize().height));
	addChild(pT, 1);
	sp0->setAnchorPoint(Vec2(0, 0));
	sp0->setPosition(Vec2(origin.x + pT->getContentSize().width, origin.y + visibleSize.height - sp0->getContentSize().height));
	addChild(sp0, 0);

#pragma endregion

#pragma region ��Ϸ����Ĳ˵���

	/* Todo: ������Ա�������������Ϸ����Ĳ˵������ͣ��Ϸ�����ã��������� */

#pragma endregion

#pragma region ����

	/* Todo: ������Ա��������������ֵ���ش��� */

#pragma endregion



#pragma region ��Ӽ�����

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(ExampleGameScene::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(ExampleGameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(ExampleGameScene::onConcactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(ExampleGameScene::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

#pragma endregion

#pragma region ��Ӷ�ʱ��

	schedule(schedule_selector(ExampleGameScene::update), 0.1f, kRepeatForever, 0);
	schedule(schedule_selector(ExampleGameScene::hit), 0.0f, kRepeatForever, 0);
	schedule(schedule_selector(ExampleGameScene::gameOver), 0.0f, kRepeatForever, 0);

#pragma endregion

#pragma region ���Զ����ð�ť------����˶

	auto label = Label::createWithTTF("hit", "fonts/arial.ttf", 24);

	auto changeItem = MenuItemLabel::create(label, CC_CALLBACK_1(ExampleGameScene::hitTest, this));
	auto menu = Menu::create(changeItem, NULL);
	menu->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(menu, 2);

	auto label2 = Label::createWithTTF("dead", "fonts/arial.ttf", 24);

	auto changeItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(ExampleGameScene::deadTest, this));
	auto menu2 = Menu::create(changeItem2, NULL);
	menu2->setPosition(visibleSize.width / 2 + 50, visibleSize.height / 2);
	addChild(menu2, 2);

#pragma endregion

    return true;
}

/* ��ײ�������� */
bool ExampleGameScene::onConcactBegin(PhysicsContact & contact)
{
	return true;
}


/* ��ײ�����������뿪ʱ��Ӧ���� */
bool ExampleGameScene::onContactSeparate(PhysicsContact & contact)
{
	return true;
}


#pragma region ��������¼�

/* ���¼��� */
/* Todo������ֻ���˵�һ����ҵĶ����������˫�˶�ս������ɵڶ�����Ҷ����İ� */
void ExampleGameScene::onKeyPressed(EventKeyboard::KeyCode code, Event* event)
{
	//player1->meleeAttack();
	switch (code) {
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		LeftKeyPressed();
		LeftKeyState = true;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		RightKeyPressed();
		RightKeyState = true;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		player1->jump();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		player1->defend();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_1:
		player1->meleeAttack();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_2:
		createRangedBall(player1);
		player1->rangedAttack();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_3:
		createUltimateBall(player1);
		player1->ultimate();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_5:
		chargeEffect1 = createChargeEffect(player1);
		player1->charge();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		A_KeyPressed();
		A_KeyState = true;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		D_KeyPressed();
		D_KeyState = true;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		player2->jump();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_G:
		player2->meleeAttack();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_H:
		createRangedBall(player2);
		player2->rangedAttack();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_Y:
		chargeEffect2 = createChargeEffect(player2);
		player2->charge();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_J:
		createUltimateBall(player2);
		player2->ultimate();
		break;
	default:
		break;
	}
}

/* �ͷŰ��� */
/* Todo������ֻ���˵�һ����ҵĶ����������˫�˶�ս������ɵڶ�����Ҷ����İ� */
void ExampleGameScene::onKeyReleased(EventKeyboard::KeyCode code, Event* event)
{
	switch (code) {
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		player1->stopActionByTag(1);
		/* �����Ȱ�1��2������1����� */
		if (player1->getActionByTag(2) == nullptr) {
			player1->idle();
		}
		LeftKeyState = false;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		player1->stopActionByTag(2);
		if (player1->getActionByTag(1) == nullptr) {
			player1->idle();
		}
		RightKeyState = false;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		player1->stopActionByTag(11);
		player1->idle();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_1:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_2:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_3:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_5:
		player1->stopActionByTag(12);
		if(chargeEffect1 != NULL) chargeEffect1->removeFromParentAndCleanup(true);
		player1->idle();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		player2->stopActionByTag(1);
		if (player2->getActionByTag(2) == nullptr) {
			player2->idle();
		}
		A_KeyState = false;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		player2->stopActionByTag(2);
		if (player2->getActionByTag(1) == nullptr) {
			player2->idle();
		}
		D_KeyState = false;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_G:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_H:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_J:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_Y:
		player2->stopActionByTag(12);
		if (chargeEffect2 != NULL) chargeEffect2->removeFromParentAndCleanup(true);
		player2->idle();
		break;
	default:
		break;
	}
}
#pragma endregion


void ExampleGameScene::update(float delay)
{
	m_world->step(0.1f);
	/* Todo������HP��MP��ֵ���ϲ��������������ⲿ������ */

	
	/* ����ɿ��������ʱ���ŵ�Ϊ�����ƶ��Ķ���������ͣ������ͬ�� */
	if (LeftKeyState == false && (player1->getActionByTag(13) != nullptr || player1->getActionByTag(1) != nullptr)) {
		firstPressL = false;
		player1->stopAllActions();
		player1->idle();
	}
	if (RightKeyState == false && (player1->getActionByTag(14) != nullptr || player1->getActionByTag(2) != nullptr)) {
		firstPressR = false;
		player1->stopAllActions();
		player1->idle();
	}
	if (A_KeyState == false && (player2->getActionByTag(13) != nullptr || player2->getActionByTag(1) != nullptr)) {
		firstPressA = false;
		player2->stopAllActions();
		player2->idle();
	}
	if (D_KeyState == false && (player2->getActionByTag(14) != nullptr || player2->getActionByTag(2) != nullptr)) {
		firstPressD = false;
		player2->stopAllActions();
		player2->idle();
	}

	/*λ���ж�*/
	if (player1->getPositionX() < 20) {
		player1->setPositionX(20);
	}
	else if (player1->getPositionX() > 1180) {
		player1->setPositionX(1180);
	}
	if (player2->getPositionX() < 20) {
		player2->setPositionX(20);
	}
	else if (player2->getPositionX() > 1180) {
		player2->setPositionX(1180);
	}
}

/* Todo����Ϸ����������˫�˶�ս��������ⲿ�ֵĴ��� */
void ExampleGameScene::gameOver(float delay)
{

}


/* Todo��������������˫�˶�ս��������ⲿ�ֵĴ���*/
void ExampleGameScene::hit(float dt)
{
	
}

void ExampleGameScene::hitTest(Ref* sender)
{
	if (!player1->isDouble) {
		player1->hittedCount = 0;
		scheduleOnce(schedule_selector(ExampleGameScene::hittedCounter), 2.0f);
		player1->isDouble = true;
	}
	else {
		player1->hittedCount++;
	}
	player1->hit();
	createHitEffect(player1);
}


void ExampleGameScene::deadTest(Ref* sender)
{
	if(!player1->isDead)
		player1->dead();
}

/* �����һ�ΰ���ʱ��Ӧ */
void ExampleGameScene::LeftKeyPressed()
{
	if (firstPressL) {
		/* ����ǵ�һ�ΰ��£�firstPressL��Ϊfalse, �����ƶ���Ȼ����ʱ0.3�뽫firstPressL������Ϊtrue */
		player1->moveLeft();
		scheduleOnce(schedule_selector(ExampleGameScene::LeftKeyPressed), 0.30f);
		firstPressL = false;
	}
	else
	{
		/* ��firstPressLΪtrue��˵����0.3f���ڣ��൱��dash */
		player1->dashLeft();
		firstPressL = true;
	}

}

/* ��ʱ0.3�뽫firstPressL������Ϊtrue */
void ExampleGameScene::LeftKeyPressed(float t)
{
	firstPressL = true;
}

void ExampleGameScene::RightKeyPressed()
{
	if (firstPressR) {
		player1->moveRight();
		scheduleOnce(schedule_selector(ExampleGameScene::RightKeyPressed), 0.30f);
		firstPressR = false;
	}
	else
	{
		player1->dashRight();
		firstPressR = true;
	}
}

void ExampleGameScene::RightKeyPressed(float t)
{
	firstPressR = true;
}


void ExampleGameScene::A_KeyPressed()
{
	if (firstPressA) {
		player2->moveLeft();
		scheduleOnce(schedule_selector(ExampleGameScene::A_KeyPressed), 0.30f);
		firstPressA = false;
	}
	else
	{
		player2->dashLeft();
		firstPressA = true;
	}
}

void ExampleGameScene::A_KeyPressed(float t)
{
	firstPressA = true;
}

void ExampleGameScene::D_KeyPressed()
{
	if (firstPressD) {
		player2->moveRight();
		scheduleOnce(schedule_selector(ExampleGameScene::D_KeyPressed), 0.30f);
		firstPressD = false;
	}
	else
	{
		player2->dashRight();
		firstPressD = true;
	}
}

void ExampleGameScene::D_KeyPressed(float t)
{
	firstPressD = true;
}

void ExampleGameScene::hittedCounter(float t)
{
	player1->isDouble = false;
}

/*���ɴ��е���ע������û��remove�����ڱ������б�ʱ����remove*/
void ExampleGameScene::createUltimateBall(PlayerSprite* player) {
	if (player->isRun) return;
	Sprite* Ball = Sprite::createWithSpriteFrame(player->ultimateBallVector.back());
	Ball->setVisible(false);
	Ball->setScale(3.0f);
	ultimateBalls.push_back(Ball);
	addChild(Ball, 3);
	auto animationBall = Animation::createWithSpriteFrames(player->ultimateBallVector, 0.1f);
	auto animateBall = Animate::create(animationBall);
	auto actBall = RepeatForever::create(animateBall);
	/*������ķ���*/
	int direction = 1;
	if (!player->isFlippedX()) direction = -1;
	auto shootBall = MoveTo::create(1.0f, Vec2(player->getPositionX() + 500 * direction, visibleSize.height / 2 - 300));
	/*��Ķ������ӳ٣��ɼ����������ƶ�����ը������*/
	auto seqBall = Sequence::create(DelayTime::create(1.0f), CallFuncN::create([Ball, player](Ref* sender) {
		Ball->setPosition(player->getPositionX(), player->getPositionY() + 300);
		Ball->setVisible(true);
	}), animateBall, shootBall,CallFuncN::create([Ball, player, this](Ref* sender) {
		/*��ը*/
		Sprite* explosion = Sprite::createWithSpriteFrame(player->explosionVector.front());
		explosion->setPosition(Ball->getPosition());
		explosion->setScale(4.0f);
		auto exploseAnimation = Animation::createWithSpriteFrames(player->explosionVector, 0.06f);
		auto explose = Animate::create(exploseAnimation);
		auto seq = Sequence::create(explose, CallFuncN::create([explosion](Ref* sender) {
			explosion->removeFromParentAndCleanup(true);
		}), NULL);
		addChild(explosion, 3);
		explosion->runAction(seq);
		Ball->removeFromParentAndCleanup(true);
	}), NULL);
	Ball->runAction(seqBall);
}

/*����Զ�̹�������ע������û��remove�����ڱ������б�ʱ����remove*/
void ExampleGameScene::createRangedBall(PlayerSprite* player) {
	if (player->isRun) return;
	Sprite* Ball = Sprite::createWithSpriteFrame(player->rangedBallVector.back());
	Ball->setFlippedX(!player->isFlippedX());
	Ball->setVisible(false);
	/*������ķ���*/
	int direction = 1;
	if (!player->isFlippedX()) direction = -1;
	Ball->setPosition(player->getPositionX() + 70 * direction, player->getPositionY() + 20);
	rangedBalls.push_back(Ball);
	addChild(Ball, 3);
	MoveTo* moveTo;
	if (Ball->isFlippedX()) {
		moveTo = MoveTo::create((Ball->getPositionX() + 30) / 360, Vec2(-30, Ball->getPositionY()));
	}
	else {
		moveTo = MoveTo::create((1200 - Ball->getPositionX()) / 360, Vec2(1200, Ball->getPositionY()));
	}
	/*��Ķ������ӳ٣��ɼ����ƶ�������*/
	auto seqBall = Sequence::create(DelayTime::create(0.5f), CallFuncN::create([Ball](Ref* sender) {
		Ball->setVisible(true);
	}), moveTo, CallFuncN::create([Ball](Ref* sender) {
		Ball->removeFromParentAndCleanup(true);
	}), NULL);
	Ball->runAction(seqBall);
}

/*��������Ч��*/
Sprite* ExampleGameScene::createChargeEffect(PlayerSprite* player) {
	if (player->isRun) return NULL;
	Sprite* effect = Sprite::createWithSpriteFrame(player->chargeEffectVector.front());
	effect->setScale(2.0f);
	effect->setPosition(player->getPosition() + Vec2(0, 30));
	addChild(effect, 1);
	auto effectAnimation = Animation::createWithSpriteFrames(player->chargeEffectVector, 0.05f);
	auto effectAnimate = Animate::create(effectAnimation);
	auto effectAct = RepeatForever::create(effectAnimate);
	effect->runAction(effectAct);
	return effect;
}

/*���ɱ�����Ч������hitTest�ﱻ����*/
void ExampleGameScene::createHitEffect(PlayerSprite* player) {
	Sprite* hitEffect = Sprite::createWithSpriteFrame(player->hitEffectVector.front());
	hitEffect->setPosition(player->getPosition());
	addChild(hitEffect, 3);
	auto hitEffectAnimation = Animation::createWithSpriteFrames(player->hitEffectVector, 0.1f);
	auto hitEffectAnimate = Animate::create(hitEffectAnimation);
	auto seq = Sequence::create(hitEffectAnimate, CallFuncN::create([hitEffect](Ref* sender) {
		hitEffect->removeFromParentAndCleanup(true);
	}),NULL);
	hitEffect->runAction(seq);
}
