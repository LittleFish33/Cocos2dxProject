#include "OnlineGameScene.h"
#include "SimpleAudioEngine.h"
#include "GamePauseScene.h"
#include "../configuration.h"
#include "../ShareSingleton.h"
#include "../Players/PlayerSprite.h"
using namespace CocosDenshion;
#include <iostream>
#include <cmath>
#include <ctime>
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
void OnlineGameScene::setPhysicsWorld(PhysicsWorld* world) { m_world = world; }

Scene* OnlineGameScene::createScene()
{
#pragma region ����������

	srand((unsigned)time(NULL));
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, -1000.0f));
	scene->getPhysicsWorld()->setAutoStep(true);
	auto layer = OnlineGameScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;

#pragma endregion
}


/* ���ļ�������ʱ����ӡ���õĴ�����Ϣ�����Ƿֶδ��� */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in OnlineGameSceneScene.cpp\n");
}

/* ��ʼ���������� */
bool OnlineGameScene::init()
{
#pragma region Cocos2dx�Զ����ɵ����ݣ�һЩ��������

	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto edgeSp = Sprite::create();  //�����߽�
	auto boundBody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(1000.0f, 1.0f, 0.0f), 3);
	boundBody->setCategoryBitmask(0xFFFFFFFF);
	boundBody->setCollisionBitmask(0xFFFFFFFF);
	boundBody->setContactTestBitmask(0xFFFFFFFF);
	edgeSp->setPosition(visibleSize.width / 2, visibleSize.height / 2);  //λ����������Ļ����
	edgeSp->setPhysicsBody(boundBody);
	addChild(edgeSp);

#pragma endregion

#pragma region ��������
	int selectedBg = ShareSingleton::GetInstance()->selectedBackground;
	char bgName[20];
	sprintf(bgName, "bg/bg%d.png", selectedBg);
	auto bgSprite = Sprite::create("bg/bg4.png");
	bgSprite->setPosition(visibleSize / 2);
	bgSprite->setScale(visibleSize.width / bgSprite->getContentSize().width, visibleSize.height / bgSprite->getContentSize().height);
	this->addChild(bgSprite, 0);
	
	/* ��ӵ��� */
	ground = Sprite::create("ground.png");
	ground->setScale(visibleSize.width / ground->getContentSize().width, 1.2f);
	ground->setPosition(visibleSize.width / 2, 0);
	auto groundbody = PhysicsBody::createBox(ground->getContentSize(), PhysicsMaterial(1000.0f, 0.0f, 10000.0f));
	
	groundbody->setCategoryBitmask(0xFFFFFFFF);
	groundbody->setCollisionBitmask(0xFFFFFFFF);
	groundbody->setContactTestBitmask(0xFFFFFFFF);
	groundbody->setTag(1);
	groundbody->setDynamic(false);
	ground->setPhysicsBody(groundbody);
	ground->setVisible(false);
	this->addChild(ground, 1);

#pragma endregion
	
#pragma region ��������
	/* Todo���������������Ҫ�޸�һ������ĳ�ʼ֡ */
	/* ����һ����ͼ��ʹ����ͼ�������� */
	player1 = new PlayerSprite();

	/* ���player1��������� */
	physicPlayer1 = Sprite::create("physicplayer.png");
	physicPlayer1->setPosition(Vec2(visibleSize.width / 4 * 3, visibleSize.height / 2 - 300));
	auto player1Body = PhysicsBody::createBox(physicPlayer1->getContentSize(), PhysicsMaterial(10000.0f, 0.0f, 0.0f));
	player1Body->setCategoryBitmask(0xFFFFFFFF);
	player1Body->setContactTestBitmask(0xFFFFFFFF);
	player1Body->setContactTestBitmask(0xFFFFFFFF);
	player1Body->setDynamic(true);
	physicPlayer1->setPhysicsBody(player1Body);
	physicPlayer1->setVisible(false);
	physicPlayer1->setScale(1.2f);
	addChild(physicPlayer1, 3);

	player1->initSprite("Goku", physicPlayer1);
	player1->initAnimateFrame();
	player1->setPosition(Vec2(visibleSize.width / 4 * 3, visibleSize.height / 2 - 300));
	player1->setFlippedX(true);
	player1->setVisible(true);
	addChild(player1, 3);
	player1->idle();

	player2 = new PlayerSprite();
	/* ���player2��������� */
	physicPlayer2 = Sprite::create("physicplayerForFrieza.png");
	physicPlayer2->setPosition(Vec2(visibleSize.width / 4, visibleSize.height / 2 - 300));
	auto player2Body = PhysicsBody::createBox(physicPlayer2->getContentSize(), PhysicsMaterial(10000.0f, 0.0f, 0.0f));
	player2Body->setCategoryBitmask(0xFFFFFFFF);
	player2Body->setContactTestBitmask(0xFFFFFFFF);
	player2Body->setContactTestBitmask(0xFFFFFFFF);
	player2Body->setDynamic(true);
	physicPlayer2->setPhysicsBody(player2Body);
	physicPlayer2->setVisible(false);
	physicPlayer2->setScale(1.2f);
	addChild(physicPlayer2, 3);

	player2->initSprite("Frieza", physicPlayer2);
	isFreiza = true;
	player2->initAnimateFrame();
	player2->setPosition(Vec2(visibleSize.width / 4, visibleSize.height / 2 - 300));
	player2->setFlippedX(true);
	player2->setVisible(true);
	addChild(player2, 3);
	player2->idle();

#pragma endregion

#pragma region hp����mp��

	/* Todo���������������Ż�HP����MP�� */
	/* Player1��Hp */
	Sprite* player1hpBorder = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
	Sprite* player1hpContent = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(610, 362, 4, 16)));

	//Sprite* player1hpBorder = Sprite::create("hp1.png");
//	Sprite* player1hpContent = Sprite::create("hp2.png");

	player1Hp = ProgressTimer::create(player1hpContent);
	player1Hp->setScaleX(90);
	player1Hp->setAnchorPoint(Vec2(0, 0));
	player1Hp->setType(ProgressTimerType::BAR);
	player1Hp->setBarChangeRate(Point(1, 0));
	player1Hp->setMidpoint(Point(0, 1));
	player1Hp->setPercentage(100);
	player1Hp->setPosition(Vec2(origin.x + 14 * player1Hp->getContentSize().width + 500, origin.y + visibleSize.height - 2 * player1Hp->getContentSize().height));
	addChild(player1Hp, 1);
	player1hpBorder->setAnchorPoint(Vec2(0, 0));
	player1hpBorder->setPosition(Vec2(origin.x + player1Hp->getContentSize().width + 500, origin.y + visibleSize.height - player1hpBorder->getContentSize().height));
	addChild(player1hpBorder, 0);

	/* Player1��Mp */
	Sprite* player1mpBorder = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
	Sprite* player1mpContent = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(610, 362, 4, 16)));

	player1Mp = ProgressTimer::create(player1mpContent);
	player1Mp->setScaleX(90);
	player1Mp->setAnchorPoint(Vec2(0, 0));
	player1Mp->setType(ProgressTimerType::BAR);
	player1Mp->setBarChangeRate(Point(1, 0));
	player1Mp->setMidpoint(Point(0, 1));
	player1Mp->setPercentage(50);
	player1Mp->setPosition(Vec2(origin.x + 14 * player1Mp->getContentSize().width + 500, origin.y + visibleSize.height - 2 * player1Mp->getContentSize().height - 100));
	addChild(player1Mp, 1);
	player1mpBorder->setAnchorPoint(Vec2(0, 0));
	player1mpBorder->setPosition(Vec2(origin.x + player1Mp->getContentSize().width + 500, origin.y + visibleSize.height - player1mpBorder->getContentSize().height - 100));
	addChild(player1mpBorder, 0);

	/* Player2��Hp */
	Sprite* player2hpBorder = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
	Sprite* player2hpContent = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(610, 362, 4, 16)));

	player2Hp = ProgressTimer::create(player2hpContent);
	player2Hp->setScaleX(90);
	player2Hp->setAnchorPoint(Vec2(0, 0));
	player2Hp->setType(ProgressTimerType::BAR);
	player2Hp->setBarChangeRate(Point(1, 0));
	player2Hp->setMidpoint(Point(0, 1));
	player2Hp->setPercentage(100);
	player2Hp->setPosition(Vec2(origin.x + 14 * player2Hp->getContentSize().width, origin.y + visibleSize.height - 2 * player2Hp->getContentSize().height));
	//player2Hp->setPosition(Vec2(100,100));
	addChild(player2Hp, 1);
	player2hpBorder->setAnchorPoint(Vec2(0, 0));
	player2hpBorder->setPosition(Vec2(origin.x + player2Hp->getContentSize().width, origin.y + visibleSize.height - player2hpBorder->getContentSize().height));
	//player2hpBorder->setPosition(Vec2(300, 300));
	addChild(player2hpBorder, 0);

	/* Player2��Mp */
	Sprite* player2mpBorder = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
	Sprite* player2mpContent = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(610, 362, 4, 16)));

	player2Mp = ProgressTimer::create(player2mpContent);
	player2Mp->setScaleX(90);
	player2Mp->setAnchorPoint(Vec2(0, 0));
	player2Mp->setType(ProgressTimerType::BAR);
	player2Mp->setBarChangeRate(Point(1, 0));
	player2Mp->setMidpoint(Point(0, 1));
	player2Mp->setPercentage(50);
	player2Mp->setPosition(Vec2(origin.x + 14 * player2Mp->getContentSize().width, origin.y + visibleSize.height - 2 * player2Mp->getContentSize().height - 100));
	addChild(player2Mp, 1);
	player2mpBorder->setAnchorPoint(Vec2(0, 0));
	player2mpBorder->setPosition(Vec2(origin.x + player2Mp->getContentSize().width, origin.y + visibleSize.height - player2mpBorder->getContentSize().height - 100));
	addChild(player2mpBorder, 0);

#pragma endregion

#pragma region ����

	auto audio = SimpleAudioEngine::getInstance();
	/*Ԥ���ز�ѭ�����ű�������*/
	//	audio->preloadBackgroundMusic("music/WelcomeSceneBackground.mp3");  
	audio->playBackgroundMusic("music/MainGameSceneBgm.mp3", true);
	audio->setBackgroundMusicVolume(0.80);

	/*Ԥ���ص����Ч*/
	audio->preloadEffect("music/ClickCamera.wav");
	audio->setEffectsVolume(0.80);

	/*���ز����� 3 2 1 ��ʼ ����*/
	audio->playEffect("music/321.mp3", false, 1.0f, 0.0f, 1.0f);

#pragma endregion

#pragma region ��Ϸ����Ĳ˵���

	/* Todo: ������Ա�������������Ϸ����Ĳ˵������ͣ��Ϸ�����ã��������� */
	/*��������,Ĭ�ϴ� voiceState == true*/
	voiceState = 1;
	voiceItem = MenuItemImage::create(
		"button/SoundOn.png",
		"button/SoundOff.png",
		CC_CALLBACK_1(OnlineGameScene::VoicePauseSelectedCallback, this)
	);
	voiceItem->setPosition(ccp(visibleSize.width - voiceItem->getContentSize().width / 2,
		visibleSize.height / 2 - voiceItem->getContentSize().height / 2 - 60));
	auto VoiceMenu = Menu::create(voiceItem, NULL);
	VoiceMenu->setPosition(Vec2::ZERO);
	addChild(VoiceMenu, 0);

	/*��Ϸ��ͣ��ť */
	playOrPauseState = 1;
	playOrPauseItem = MenuItemImage::create(
			"button/play.png",
			"button/pause.png",
			CC_CALLBACK_1(OnlineGameScene::playOrPauseCallback, this)
		);
	playOrPauseItem->setPosition(ccp(visibleSize.width - playOrPauseItem->getContentSize().width / 2,
		visibleSize.height/2 - playOrPauseItem->getContentSize().height / 2));
	//playOrPauseItem->setPosition(Vec2(480, 70));
	auto playOrPauseMenu = Menu::create(playOrPauseItem, NULL);
	playOrPauseMenu->setPosition(Vec2::ZERO);
	addChild(playOrPauseMenu, 0);

#pragma endregion

#pragma region ��ʼ���ͻ��˳���

	client = SocketClient::construct();
	client->onRecv = CC_CALLBACK_2(OnlineGameScene::onReceive, this);
	client->onDisconnect = CC_CALLBACK_0(OnlineGameScene::onDisconnect, this);
	/* �ϲ������ʱ��������ip��ַ�ĳ�127.0.0.1���ܱ��ص����ˣ�Ϊ��ȷ���Ƿ�ɹ���һ��������Ƿ���error */
	if (!client->connectServer("103.46.128.49", 17047))
	{
		CCLOG("%s", "Client connect error");
	}
	uid = rand() % 100000; /* ����һ�������uid�������ڴ������ */
	SocketData data(uid, KEYCODESEND::FIRSTCONNECT);
	client->sendMessage((char*)(&data), sizeof(SocketData));

#pragma endregion



#pragma region ��Ӽ�����

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(OnlineGameScene::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(OnlineGameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(OnlineGameScene::onConcactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(OnlineGameScene::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

#pragma endregion

#pragma region ��Ӷ�ʱ��

	schedule(schedule_selector(OnlineGameScene::update), 0.0f, kRepeatForever, 0);
	schedule(schedule_selector(OnlineGameScene::hit), 0.0f, kRepeatForever, 0); /* �����ж� */
	schedule(schedule_selector(OnlineGameScene::isCharge), 1.0f, kRepeatForever, 0);
	schedule(schedule_selector(OnlineGameScene::updateHP_MP), 0.1f, kRepeatForever, 0);

#pragma endregion

#pragma region ���Զ����ð�ť------����˶

	auto label = Label::createWithTTF("hit", "fonts/arial.ttf", 24);

	auto changeItem = MenuItemLabel::create(label, CC_CALLBACK_1(OnlineGameScene::hitTest, this));
	auto menu = Menu::create(changeItem, NULL);
	menu->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	menu->setVisible(false);
	addChild(menu, 2);

	auto label2 = Label::createWithTTF("dead", "fonts/arial.ttf", 24);

	auto changeItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(OnlineGameScene::deadTest, this));
	auto menu2 = Menu::create(changeItem2, NULL);
	menu2->setPosition(visibleSize.width / 2 + 50, visibleSize.height / 2);
	menu2->setVisible(false);
	addChild(menu2, 2);

#pragma endregion

    return true;
}

/* ��ײ�������� */
bool OnlineGameScene::onConcactBegin(PhysicsContact & contact)
{
	return true;
}


/* ��ײ�����������뿪ʱ��Ӧ���� */
bool OnlineGameScene::onContactSeparate(PhysicsContact & contact)
{
	/* �뿪��ʱ���Ƴ��ٶ� */
	if (physicPlayer1->getPhysicsBody()->getVelocity().x != -250 || physicPlayer1->getPhysicsBody()->getVelocity().x == 250) {
		physicPlayer1->getPhysicsBody()->setVelocity(Vec2::ZERO);
	}
	if (physicPlayer2->getPhysicsBody()->getVelocity().x != -250 || physicPlayer2->getPhysicsBody()->getVelocity().x == 250) {
		physicPlayer2->getPhysicsBody()->setVelocity(Vec2::ZERO);
	}
	return true;
}


#pragma region ��������¼�

/* ���¼��� */
void OnlineGameScene::onKeyPressed(EventKeyboard::KeyCode code, Event* event)
{
	SocketData data(uid, KEYCODESEND::LEFT);
	if (chargeEffect1 != NULL) {
		chargeEffect1->removeFromParentAndCleanup(true);
		chargeEffect1 = NULL;
	}
	if (chargeEffect2 != NULL) {
		chargeEffect2->removeFromParentAndCleanup(true);
		chargeEffect2 = NULL;
	}
	switch (code) {
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (event == nullptr) {
			LeftKeyPressed();
			LeftKeyState = true;
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (event == nullptr) {
			RightKeyPressed();
			RightKeyState = true;
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		if (event == nullptr) {
			player1->jump();
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		if (event == nullptr) {
			player1->defend();
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_1:
		if (event == nullptr) {
			if (player1->getActionByTag(6) == nullptr) {
				One_KeyPressed();
				player1LastHit = time(NULL);
			}
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_2:
		if (event == nullptr) {
			createRangedBall(player1, true);
			player1->rangedAttack();
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_3:
		if (event == nullptr) {
			createUltimateBall(player1, true);
			player1->ultimate();
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_5:
		if (event == nullptr) {
			chargeEffect1 = createChargeEffect(player1);
			player1->charge();
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		A_KeyPressed();
		A_KeyState = true;
		client->sendMessage((char*)(&data), sizeof(SocketData));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		data.codeSend = KEYCODESEND::RIGHT;
		client->sendMessage((char*)(&data), sizeof(SocketData));
		D_KeyPressed();
		D_KeyState = true;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		player2->jump();
		data.codeSend = KEYCODESEND::UP;
		client->sendMessage((char*)(&data), sizeof(SocketData));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_G:
		if (player2->getActionByTag(6) == nullptr) {
			player2LastHit = time(NULL);
			G_KeyPressed();
		}
		data.codeSend = KEYCODESEND::G;
		client->sendMessage((char*)(&data), sizeof(SocketData));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_H:
		createRangedBall(player2, false);
		player2->rangedAttack();
		data.codeSend = KEYCODESEND::H;
		client->sendMessage((char*)(&data), sizeof(SocketData));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_Y:
		chargeEffect2 = createChargeEffect(player2);
		player2->charge();
		data.codeSend = KEYCODESEND::Y;
		client->sendMessage((char*)(&data), sizeof(SocketData));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_J:
		createUltimateBall(player2, false);
		player2->ultimate();
		data.codeSend = KEYCODESEND::J;
		client->sendMessage((char*)(&data), sizeof(SocketData));
		break;
	default:
		break;
	}
}

/* �ͷŰ��� */
void OnlineGameScene::onKeyReleased(EventKeyboard::KeyCode code, Event* event)
{
	SocketData data(uid, KEYCODESEND::UPRELEASE);	
	switch (code) {
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (event == nullptr) {
			player1->isMove = false;
			player1->stopActionByTag(1);
			if (physicPlayer1->getPhysicsBody()->getVelocity().x < 0) {
				physicPlayer1->getPhysicsBody()->setVelocity(Vec2(0, 0));
			}
			/* �����Ȱ�1��2������1����� */
			if (player1->getActionByTag(2) == nullptr) {
				player1->idle();
			}
			LeftKeyState = false;
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (event == nullptr) {
			player1->isMove = false;
			player1->stopActionByTag(2);
			if (physicPlayer1->getPhysicsBody()->getVelocity().x > 0) {
				physicPlayer1->getPhysicsBody()->setVelocity(Vec2(0, 0));
			}
			if (player1->getActionByTag(1) == nullptr) {
				player1->idle();
			}
			RightKeyState = false;
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		if (event == nullptr) {
			player1->stopActionByTag(11);
			player1->idle();
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_1:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_2:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_3:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_5:
		if (event == nullptr) {
			if (player1->getActionByTag(12) != nullptr) {
				player1->stopActionByTag(12);
				if (chargeEffect1 != NULL) {
					chargeEffect1->removeFromParentAndCleanup(true);
					chargeEffect1 = NULL;
				}
				player1->idle();
			}
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		player2->isMove = false;
		player2->stopActionByTag(1);
		if (physicPlayer2->getPhysicsBody()->getVelocity().x < 0)
		{
			physicPlayer2->getPhysicsBody()->setVelocity(Vec2(0, 0));
		}
		if (player2->getActionByTag(2) == nullptr) {
			player2->idle();
		}
		A_KeyState = false;
		data.codeSend = KEYCODESEND::LEFTRELEASE;
		client->sendMessage((char*)(&data), sizeof(SocketData));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		player2->isMove = false;
		player2->stopActionByTag(2);
		if (physicPlayer2->getPhysicsBody()->getVelocity().x > 0)
		{
			physicPlayer2->getPhysicsBody()->setVelocity(Vec2(0, 0));
		}
		if (player2->getActionByTag(1) == nullptr) {
			player2->idle();
		}
		D_KeyState = false;
		data.codeSend = KEYCODESEND::RIGHTRELEASE;
		client->sendMessage((char*)(&data), sizeof(SocketData));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		client->sendMessage((char*)(&data), sizeof(SocketData));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_G:
		data.codeSend = KEYCODESEND::G_RELEASE;
		client->sendMessage((char*)(&data), sizeof(SocketData));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_H:
		data.codeSend = KEYCODESEND::H_RELEASE;
		client->sendMessage((char*)(&data), sizeof(SocketData));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_J:
		data.codeSend = KEYCODESEND::J_RELEASE;
		client->sendMessage((char*)(&data), sizeof(SocketData));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_Y:
		data.codeSend = KEYCODESEND::Y_RELEASE;
		client->sendMessage((char*)(&data), sizeof(SocketData));
		if (player2->getActionByTag(12) != nullptr) {
			player2->stopActionByTag(12);
			if (chargeEffect2 != NULL) {
				chargeEffect2->removeFromParentAndCleanup(true);
				chargeEffect2 = NULL;
			}
			player2->idle();
		}
		break;
	default:
		break;
	}
}
#pragma endregion


void OnlineGameScene::update(float delay)
{
	/* ����Ǳ���ɵ�״̬����ô�ø���;����λ����ͬ */
	if (player1->getActionByTag(6) == nullptr) {
		player1->setPositionX(physicPlayer1->getPositionX());
	}
	else
	{
		/* ������ǣ���ô�ƶ�����ʵ���������ƶ����壬��˽�����͸����λ�ñ���һ�� */
		physicPlayer1->setPosition(player1->getPosition());
	}
	if (player2->getActionByTag(6) == nullptr) {
		player2->setPositionX(physicPlayer2->getPositionX());
	}
	else {
		physicPlayer2->setPosition(player2->getPosition());
	}
	


#pragma region �ƶ�����ж�
	/* ����ɿ��������ʱ���ŵ�Ϊ�����ƶ��Ķ���������ͣ������ͬ�� */
	if (LeftKeyState == false && (player1->getActionByTag(13) != nullptr || player1->getActionByTag(1) != nullptr)) {
		firstPressL = false;
		player1->stopAllActions();
		player1->idle();
	}
	else if (LeftKeyState == true && (player1->getActionByTag(0) != nullptr)) {
		player1->stopActionByTag(0);
		player1->moveLeft();
	}

	if (RightKeyState == false && (player1->getActionByTag(14) != nullptr || player1->getActionByTag(2) != nullptr)) {
		firstPressR = false;
		player1->stopAllActions();
		player1->idle();
	}
	else if (RightKeyState == true && (player1->getActionByTag(0) != nullptr)) {
		player1->stopActionByTag(0);
		player1->moveRight();
	}
	if (A_KeyState == false && (player2->getActionByTag(13) != nullptr || player2->getActionByTag(1) != nullptr)) {
		firstPressA = false;
		player2->stopAllActions();
		player2->idle();
	}
	else if (A_KeyState == true && (player2->getActionByTag(0) != nullptr)) {
		player2->stopActionByTag(0);
		player2->moveLeft();
	}
	if (D_KeyState == false && (player2->getActionByTag(14) != nullptr || player2->getActionByTag(2) != nullptr)) {
		firstPressD = false;
		player2->stopAllActions();
		player2->idle();
	}
	else if (D_KeyState == true && (player2->getActionByTag(0) != nullptr)) {
		player2->stopActionByTag(0);
		player2->moveRight();
	}
#pragma endregion

}

/* Todo: ˫�˶�ս��������ⲿ�ֵĴ��� */
void OnlineGameScene::gameOver()
{
	
}

/* ����״̬ */
void OnlineGameScene::isCharge(float dt)
{
	if (player1->getActionByTag(12) != nullptr) {
		player1->setMp(player1->getMp() + 5);
	}
	if (player2->getActionByTag(12) != nullptr) {
		player2->setMp(player2->getMp() + 5);
	}
}

/* ����hp��mp */
void OnlineGameScene::updateHP_MP(float delay)
{
	if (player1->getHp() != player1Hp->getPercentage()) {
		player1Hp->runAction(CCProgressFromTo::create(0.25f, player1Hp->getPercentage(), player1->getHp() * 1.0));
	}
	if (player2->getHp() != player2Hp->getPercentage()) {
		player2Hp->runAction(CCProgressFromTo::create(0.25f, player2Hp->getPercentage(), player2->getHp() * 1.0));
	}
	if (player1->getMp() != player1Mp->getPercentage()) {
		player1Mp->runAction(CCProgressFromTo::create(0.25f, player1Mp->getPercentage(), player1->getMp() * 1.0));
	}
	if (player2->getMp() != player2Mp->getPercentage()) {
		player2Mp->runAction(CCProgressFromTo::create(0.25f, player2Mp->getPercentage(), player2->getMp() * 1.0));
	}
	/* �ж���Ϸ���� */
	if (player1->getHp() <= 0 || player2->getHp() <= 0) {
		gameOver();
	}
}


/* TODO:����ĶԴ��߼�����һ��С���⣬��ʱ�����������˻��������� */
void OnlineGameScene::hit(float dt)
{
	bool flag = false;
	if (isFreiza) {
		flag = abs(physicPlayer1->getPositionX() - physicPlayer2->getPositionX()) < physicPlayer1->getContentSize().width + physicPlayer2->getContentSize().width - 50;
	}
	else {
		flag = abs(player1->getPositionX() - player2->getPositionX()) < 100;
	}
	if (flag) {
		bool player1FirstAttack = false,bothIdle = false;
		if (player1->isHitting && player2->isHitting) {
			player1FirstAttack = player1LastHit > player2LastHit;
		}
		else if (player1->isHitting) {
			player1FirstAttack = true;
		}
		else if (player2->isHitting) {
			player1FirstAttack = false;
		}
		else {
			bothIdle = true;
		}
		if (player1FirstAttack &&
			((player1->isFlippedX() && player1->getPositionX() < player2->getPositionX()) ||
			(!player1->isFlippedX() && player1->getPositionX() > player2->getPositionX()))) {
			player2->setFlippedX(!player1->isFlippedX());
			if (player2->isHitted == false) {
				shareInstance->opponentFlipx = player1->isFlippedX();
				createHitEffect(player2);
			}
			if (player2->getActionByTag(6) == nullptr) {
				player2->hit();
			}
		}
		else if (!player1FirstAttack && !bothIdle && 
			((player2->isFlippedX() && player1->getPositionX() > player2->getPositionX()) ||
			(!player2->isFlippedX() && player1->getPositionX() < player2->getPositionX()))) {
			player1->setFlippedX(!player2->isFlippedX());
			if (player1->isHitted == false) {
				shareInstance->opponentFlipx = player2->isFlippedX();
				createHitEffect(player1);
			}
			if (player1->getActionByTag(6) == nullptr) {
				player1->hit();
			}
		}
	}
#pragma region �ж��Ƿ�Զ�̹�������

	for (Sprite* ball : player1RangedBalls)
	{
		if (ball->getPositionX() > 1100 || ball->getPositionX() < 40) {
			ball->removeFromParentAndCleanup(true);
			player1RangedBalls.remove(ball);
			break;
		}
		else if (abs(player2->getPositionX() - ball->getPositionX()) < 80 && player2->getPositionY() < 120) {
			player2->setFlippedX(!player1->isFlippedX());
			if (player2->isHitted == false) {
				shareInstance->opponentFlipx = player1->isFlippedX();
				createHitEffect(player2);
			}
			player2->hit();
			ball->removeFromParentAndCleanup(true);
			player1RangedBalls.remove(ball);
			break;
		}
	}
	for (Sprite* ball : player2RangedBalls)
	{
		if (ball->getPositionX() > 1100 || ball->getPositionX() < 40) {
			ball->removeFromParentAndCleanup(true);
			player2RangedBalls.remove(ball);
			break;
		}
		else if (abs(player1->getPositionX() - ball->getPositionX()) < 80 && player1->getPositionY() < 120) {
			player1->setFlippedX(!player2->isFlippedX());
			if (player1->isHitted == false) {
				shareInstance->opponentFlipx = player2->isFlippedX();
				createHitEffect(player1);
			}
			player1->hit();
			ball->removeFromParentAndCleanup(true);
			player2RangedBalls.remove(ball);
			break;
		}
	}

#pragma endregion

}

/* �����ť��������״̬�������ڲ��Դ��� */
void OnlineGameScene::hitTest(Ref* sender)
{
	if (!player2->isDouble) {
		player2->hittedCount = 0;
		scheduleOnce(schedule_selector(OnlineGameScene::hittedCounter), 2.0f);
		player2->isDouble = true;
	}
	else {
		player2->hittedCount++;
	}
	player2->hit();
	createHitEffect(player2);
}


/* �����ť��������״̬�������ڲ��Դ��� */
void OnlineGameScene::deadTest(Ref* sender)
{
	if(!player2->isDead)
		player2->dead();
}

/* �����һ�ΰ���ʱ��Ӧ */
void OnlineGameScene::LeftKeyPressed()
{
	if (firstPressL) {
		/* ����ǵ�һ�ΰ��£�firstPressL��Ϊfalse, �����ƶ���Ȼ����ʱ0.3�뽫firstPressL������Ϊtrue */
		player1->moveLeft();
		scheduleOnce(schedule_selector(OnlineGameScene::LeftKeyPressed), 0.30f);
		firstPressL = false;
	}
	else
	{
		/* ��firstPressLΪtrue��˵����0.3f���ڣ��൱��dash */
		player1->dashLeft(player2->getPosition());
		firstPressL = true;
	}

}

/* ��ʱ0.3�뽫firstPressL������Ϊtrue */
void OnlineGameScene::LeftKeyPressed(float t)
{
	firstPressL = true;
}

/* �Ҽ���һ�ΰ���ʱ��Ӧ */
void OnlineGameScene::RightKeyPressed()
{
	if (firstPressR) {
		player1->moveRight();
		scheduleOnce(schedule_selector(OnlineGameScene::RightKeyPressed), 0.30f);
		firstPressR = false;
	}
	else
	{
		player1->dashRight(player2->getPosition());
		firstPressR = true;
	}
}
/* ��ʱ0.3�뽫firstPressR������Ϊtrue */
void OnlineGameScene::RightKeyPressed(float t)
{
	firstPressR = true;
}

/* A����һ�ΰ���ʱ��Ӧ */
void OnlineGameScene::A_KeyPressed()
{
	if (firstPressA) {
		player2->moveLeft();
		scheduleOnce(schedule_selector(OnlineGameScene::A_KeyPressed), 0.30f);
		firstPressA = false;
	}
	else
	{
		player2->dashLeft(player1->getPosition());
		firstPressA = true;
	}
}

/* ��ʱ0.3�뽫firstPressA������Ϊtrue */
void OnlineGameScene::A_KeyPressed(float t)
{
	firstPressA = true;
}

/* D����һ�ΰ���ʱ��Ӧ */
void OnlineGameScene::D_KeyPressed()
{
	if (firstPressD) {
		player2->moveRight();
		scheduleOnce(schedule_selector(OnlineGameScene::D_KeyPressed), 0.30f);
		firstPressD = false;
	}
	else
	{
		player2->dashRight(player1->getPosition());
		firstPressD = true;
	}
}
/* ��ʱ0.3�뽫firstPressD������Ϊtrue */
void OnlineGameScene::D_KeyPressed(float t)
{
	firstPressD = true;
}

/* ��ʱ�жϹ������ͣ���ȭ����ȭ+�Ϲ�ȭ����ȭ+�Ϲ�ȭ+���� */
void OnlineGameScene::One_KeyPressed()
{
	if (secondPress1) {
		player1->meleeAttack2();
		scheduleOnce(schedule_selector(OnlineGameScene::One_KeyPressed), 1.8f);
		secondPress1 = false;
		firstPress1 = false;
	}
	else if (firstPress1) {
		player1->meleeAttack1();
		scheduleOnce(schedule_selector(OnlineGameScene::One_KeyPressed), 1.5f);
		firstPress1 = false;
		secondPress1 = true;
	}
	else
	{
		player1->meleeAttack3();
		firstPress1 = true;
		secondPress1 = false;
	}
}
void OnlineGameScene::One_KeyPressed(float t)
{
	firstPress1 = true;
	secondPress1 = false;
}

/* ��ʱ�жϹ������ͣ���ȭ����ȭ+�Ϲ�ȭ����ȭ+�Ϲ�ȭ+���� */
void OnlineGameScene::G_KeyPressed()
{
	if (secondPressG) {
		player2->meleeAttack2();
		scheduleOnce(schedule_selector(OnlineGameScene::G_KeyPressed), 1.8f);
		secondPressG = false;
		firstPressG = false;
	}
	else if (firstPressG) {
		player2->meleeAttack1();
		scheduleOnce(schedule_selector(OnlineGameScene::G_KeyPressed), 1.5f);
		firstPressG = false;
		secondPressG = true;
	}
	else
	{
		player2->meleeAttack3();
		firstPressG = true;
		secondPressG = false;
	}
}
void OnlineGameScene::G_KeyPressed(float t)
{
	firstPressG = true;
	secondPressG = false;
}

void OnlineGameScene::hittedCounter(float t)
{
	player1->isDouble = false;
}

/*���ɴ��е���ע������û��remove�����ڱ������б�ʱ����remove*/
void OnlineGameScene::createUltimateBall(PlayerSprite* player, bool isPlayer1) {
	if (player->isRun || player->getMp() < 50) return;
	Sprite* Ball = Sprite::createWithSpriteFrame(player->ultimateBallVector.back());
	Ball->setVisible(false);
	Ball->setScale(3.0f);
	PlayerSprite* opponent;
	if (isPlayer1) {
		player1UltimateBalls.push_back(Ball);
		opponent = player2;
	}
	else
	{
		player2UltimateBalls.push_back(Ball);
		opponent = player1;
	}

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
	}), animateBall, shootBall,CallFuncN::create([Ball, player, opponent, this](Ref* sender) {
		/*��ը*/
		Sprite* explosion = Sprite::createWithSpriteFrame(player->explosionVector.front());
		explosion->setPosition(Ball->getPosition());
		explosion->setScale(4.0f);
		auto exploseAnimation = Animation::createWithSpriteFrames(player->explosionVector, 0.06f);
		auto explose = Animate::create(exploseAnimation);
		auto seq = Sequence::create(explose, CallFuncN::create([explosion](Ref* sender) {
			explosion->removeFromParentAndCleanup(true);
		}), NULL);
		if (Ball->getBoundingBox().containsPoint(opponent->getPosition())) {
			opponent->hitByUltimate();
		}
		explose->setTag(1);
		addChild(explosion, 3);
		explosion->runAction(seq);
		Ball->removeFromParentAndCleanup(true);
	}), NULL);
	Ball->runAction(seqBall);
}

/* ����Զ�̹�������ע������û��remove�����ڱ������б�ʱ����remove */
void OnlineGameScene::createRangedBall(PlayerSprite* player,bool isPlayer1) {
	if (player->isRun || player->getMp() < 10) return;
	Sprite* Ball = Sprite::createWithSpriteFrame(player->rangedBallVector.back());
	Ball->setFlippedX(!player->isFlippedX());
	Ball->setVisible(false);
	/*������ķ���*/
	int direction = 1;
	if (!player->isFlippedX()) direction = -1;
	Ball->setPosition(player->getPositionX() + 70 * direction, player->getPositionY() + 20);
	if (isPlayer1) {
		player1RangedBalls.push_back(Ball);
	}
	else
	{
		player2RangedBalls.push_back(Ball);
	}
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
	}), moveTo, NULL);
	Ball->runAction(seqBall);
}

/* ��������Ч�� */
Sprite* OnlineGameScene::createChargeEffect(PlayerSprite* player) {
	if (player->isRun ||player->isMove ) return NULL;
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

/* ���ɱ�����Ч������hitTest�ﱻ���� */
void OnlineGameScene::createHitEffect(PlayerSprite* player) {
	Sprite* hitEffect = Sprite::createWithSpriteFrame(player->hitEffectVector.front());
	hitEffect->setPosition(player->getPosition());
	addChild(hitEffect, 3);
	auto hitEffectAnimation = Animation::createWithSpriteFrames(player->hitEffectVector, 0.04f);
	auto hitEffectAnimate = Animate::create(hitEffectAnimation);
	auto seq = Sequence::create(hitEffectAnimate, CallFuncN::create([hitEffect](Ref* sender) {
		hitEffect->removeFromParentAndCleanup(true);
	}),NULL);
	hitEffect->runAction(seq);
}

/* ������ͣ �ص�*/
void OnlineGameScene::VoicePauseSelectedCallback(Ref * pSender)
{
	/*������ť�л��Լ���������*/
	if (voiceState) {
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		SimpleAudioEngine::getInstance()->pauseAllEffects();
		voiceState = 0;
		voiceItem->setNormalImage(Sprite::create("button/SoundOff.png"));
	}
	else {
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		SimpleAudioEngine::getInstance()->resumeAllEffects();
		voiceState = 1;
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);
		voiceItem->setNormalImage(Sprite::create("button/SoundOn.png"));	
	}
}

/*��Ϸ��ͣ��������ͣ�����Ļص�����*/
void OnlineGameScene::playOrPauseCallback(Object * pSender)
{
	/*�õ����ڵĴ�С*/
	Size visibleSize = Director::sharedDirector()->getVisibleSize();
	RenderTexture *renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);

	/*������ǰ��������ӽڵ���Ϣ������renderTexture�С�
	�������ƽ�ͼ��*/
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	/*����Ϸ������ͣ��ѹ�볡����ջ�����л���GamePauseScene����*/
	Director::sharedDirector()->pushScene(GamePauseScene::CreateScene(renderTexture));
	
	log(" to game pause scene");

	/* ������ͣ��ť�л�*/
	if (playOrPauseState) {
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);
		playOrPauseState = 0;
		//Director::getInstance()->set
		playOrPauseItem->setNormalImage(Sprite::create("button/pause.png"));
	}
	else {
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);
		playOrPauseState = 1;
		playOrPauseItem->setNormalImage(Sprite::create("button/play.png"));
	}
}

#pragma region �������ش���

/* �������Է���˵����� */
void OnlineGameScene::onReceive(const char * data, int count)
{
	SocketData* revData = (SocketData*)data;
	if (revData->uid != uid) {
		switch (revData->codeSend)
		{
			/* ���ﲻ֪��Ϊʲô������KEYCODESEND::LEFT�����ҼǴ��ˣ���������ֻ���ú��Ѽǵ������� */
			case 0:
				onKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW, nullptr);
				break;
			case 1:
				onKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW, nullptr);
				break;
			case 2:
				onKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW, nullptr);
				break;
			case 3:
				onKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW, nullptr);
				break;
			case 4:
				onKeyPressed(EventKeyboard::KeyCode::KEY_1, nullptr);
				break;
			case 5:
				onKeyPressed(EventKeyboard::KeyCode::KEY_2, nullptr);
				break;
			case 6:
				onKeyPressed(EventKeyboard::KeyCode::KEY_5, nullptr);
				break;
			case 7:
				onKeyPressed(EventKeyboard::KeyCode::KEY_3, nullptr);
				break;
			case 8:
				onKeyReleased(EventKeyboard::KeyCode::KEY_LEFT_ARROW, nullptr);
				break;
			case 9:
				onKeyReleased(EventKeyboard::KeyCode::KEY_RIGHT_ARROW, nullptr);
				break;
			case 10:
				onKeyReleased(EventKeyboard::KeyCode::KEY_UP_ARROW, nullptr);
				break;
			case 11:
				onKeyReleased(EventKeyboard::KeyCode::KEY_DOWN_ARROW, nullptr);
				break;
			case 12:
				onKeyReleased(EventKeyboard::KeyCode::KEY_1, nullptr);
				break;
			case 13:
				onKeyReleased(EventKeyboard::KeyCode::KEY_2, nullptr);
				break;
			case 14:
				onKeyReleased(EventKeyboard::KeyCode::KEY_5, nullptr);
				break;
			case 15:
				onKeyReleased(EventKeyboard::KeyCode::KEY_3, nullptr);
				break;
			case 17:
				transfer();
				break;
			default:
				break;
		}
	}
}

/* �Ͽ����� */
void OnlineGameScene::onDisconnect()
{
	CCLOG("%s", "onDisconnect");
}


#pragma endregion


void OnlineGameScene::transfer()
{
	PlayerSprite* temp = player1;
	player1 = player2;
	player2 = temp;
	Sprite* temp2 = physicPlayer1;
	physicPlayer1 = physicPlayer2;
	physicPlayer2 = temp2;
	ProgressTimer* temp3 = player1Hp;
	player1Hp = player2Hp;
	player2Hp = temp3;
	temp3 = player1Mp;
	player1Mp = player2Mp;
	player2Mp = temp3;
}