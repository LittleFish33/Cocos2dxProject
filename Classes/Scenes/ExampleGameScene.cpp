#include "ExampleGameScene.h"
#include "SimpleAudioEngine.h"
#include <cmath>

USING_NS_CC;

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
	auto visibleSize = Director::getInstance()->getVisibleSize();
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
	auto texture = Director::getInstance()->getTextureCache()->addImage("$lucia_2.png");
	auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 113, 113)));
	player1 = new ExamplePlayerSprite();
	player1->initWithSpriteFrame(frame0);
	player1->initSprite();
	player1->initAnimateFrame();
	player1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 300));
	addChild(player1, 3);
	/* Todo������˫�˶�ս���������һ������Ľ��� */
	
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
		player1->stopLeftMove = false;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		player1->stopRightMove = false;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		player1->stopJump = false;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_1:
		player1->stopMeleeAttack = false;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_2:
		player1->stopRangedAttack = false;
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
		player1->stopLeftMove = true;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		player1->stopRightMove = true;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		player1->stopJump = true;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_1:
		player1->stopMeleeAttack = true;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_2:
		player1->stopRangedAttack = true;
		break;
	default:
		break;
	}
}
#pragma endregion


void ExampleGameScene::update(float delay)
{
	m_world->step(0.1f);
	/* ������ҵ�״̬ */
	updatePlayer1Status();
	updatePlayer2Status();

	/* Todo������HP��MP��ֵ���ϲ��������������ⲿ������ */
	
}

/* Todo���������1��״̬�����ﻹȱ���˱�������������������������ɵ�һ�������������ⲿ�ֵ����ݣ� */
void ExampleGameScene::updatePlayer1Status()
{	
	/*
	*  tag    ����
	*  0      idle
	*  1      moveLeft
	*  2      moveRight
	*  3      jump
	*  4      meleeAttack
	*  5      rangeAttack
	*/
	/* �ж��ǲ��ǽ�����״̬ */
	if (player1->stopMeleeAttack && !player1->isRun) { /* �������ͷţ�ֹͣ�������ȴ�isRunΪfalse����֮ǰ�Ķ����Ѳ�����ϣ� */
		player1->stopAllActionsByTag(4); /* ֹͣ���еĽ������� */
	}
	else { /* ����δ�ͷţ��Ҵ�ʱû�в����������� */
		player1->meleeAttack();  /* ���Ž������� */
		return;
	}

	/* �ж��ǲ���Զ����״̬ */
	if (player1->stopRangedAttack && !player1->isRun) {
		player1->stopAllActionsByTag(5);
	}
	else {
		player1->rangedAttack();
		return;
	}

	/* �ж��ǲ��������ƶ���״̬ */
	if (player1->stopLeftMove && !player1->isRun) {
		player1->stopAllActionsByTag(1);
	}
	else {
		player1->moveLeft();
		return;
	}

	/* �ж��ǲ��������ƶ���״̬ */
	if (player1->stopRightMove && !player1->isRun) {
		player1->stopAllActionsByTag(2);
	}
	else {
		player1->moveRight();
		return;
	}

	/* �ж��ǲ�����Ծ��״̬ */
	if (player1->stopJump && !player1->isRun) {
		player1->stopAllActionsByTag(3);
	}
	else {
		player1->jump();
		return;
	}

	/* ��ʱ��û�в����κ��������������ж��ǲ�������idle������������ǣ����ظ�����idle���� */
	if (player1->getActionByTag(0) == nullptr) {
		player1->idle();
	}
}

/* Todo���������2��״̬������˫�˶�ս����������ⲿ�ִ��� */
void ExampleGameScene::updatePlayer2Status()
{

}

/* Todo����Ϸ����������˫�˶�ս��������ⲿ�ֵĴ��� */
void ExampleGameScene::gameOver(float delay)
{

}


/* Todo��������������˫�˶�ս��������ⲿ�ֵĴ���*/
void ExampleGameScene::hit(float dt)
{
	
}
