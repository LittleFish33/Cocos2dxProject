#include "ExampleGameScene.h"
#include "SimpleAudioEngine.h"
#include "GamePauseScene.h"
#include "GameOverScene.h"
#include "../configuration.h"
#include "../ShareSingleton.h"
#include "../Players/PlayerSprite.h"
#include <iostream>
#include <cmath>
#include <ctime>
#define database UserDefault::getInstance()
using namespace CocosDenshion;
USING_NS_CC;
/*
*  tag    动画
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
#pragma region 设置物理环境

	srand((unsigned)time(NULL));
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, -1000.0f));
	scene->getPhysicsWorld()->setAutoStep(true);
	auto layer = ExampleGameScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;

#pragma endregion
}


/* 当文件不存在时，打印有用的错误消息而不是分段错误 */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in ExampleGameSceneScene.cpp\n");
}

/* 初始化场景函数 */
bool ExampleGameScene::init()
{
#pragma region Cocos2dx自动生成的内容：一些基本配置

	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto edgeSp = Sprite::create();  //创建边界
	auto boundBody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(1000.0f, 1.0f, 0.0f), 3);
	boundBody->setCategoryBitmask(0xFFFFFFFF);
	boundBody->setCollisionBitmask(0xFFFFFFFF);
	boundBody->setContactTestBitmask(0xFFFFFFFF);
	edgeSp->setPosition(visibleSize.width / 2, visibleSize.height / 2);  //位置设置在屏幕中央
	edgeSp->setPhysicsBody(boundBody);
	addChild(edgeSp);

#pragma endregion

#pragma region 创建场景
	int selectedBg = ShareSingleton::GetInstance()->selectedBackground;
	char bgName[20];
	sprintf(bgName, "bg/bg%d.png", selectedBg);
	auto bgSprite = Sprite::create(bgName);
	bgSprite->setPosition(visibleSize / 2);
	bgSprite->setScale(visibleSize.width / bgSprite->getContentSize().width, visibleSize.height / bgSprite->getContentSize().height);
	this->addChild(bgSprite, 0);
	
	/* 添加地面 */
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
	
#pragma region 创建精灵
	isFreiza = false;
	/*注 player1 在右边，使用数字键盘； player2 在左边，使用字母键盘*/

	string Player1Name = ShareSingleton::GetInstance()->player1;
	string Player2Name = ShareSingleton::GetInstance()->player2;

	player1 = new PlayerSprite();

	/* 添加player1的物理刚体 */
	if (Player1Name == "Frieza") {
		/* 弗利萨的尾巴问题，所以得换个刚体绑定 */
		physicPlayer1 = Sprite::create("physicplayerForFrieza.png");
		isFreiza = true;
	}
	else {
		physicPlayer1 = Sprite::create("physicplayer.png");
	}
	physicPlayer1->setPosition(Vec2(visibleSize.width / 4 * 3, visibleSize.height / 2 - 300));
	auto player1Body = PhysicsBody::createBox(physicPlayer1->getContentSize(), PhysicsMaterial(10000.0f, 0.0f, 0.0f));
	player1Body->setCategoryBitmask(0xFFFFFFFF);
	player1Body->setContactTestBitmask(0xFFFFFFFF);
	player1Body->setContactTestBitmask(0xFFFFFFFF);
	player1Body->setDynamic(true);
	physicPlayer1->setPhysicsBody(player1Body);
	physicPlayer1->setVisible(true);
	physicPlayer1->setScale(1.2f);
	addChild(physicPlayer1, 3);

	player1->initSprite(Player1Name, physicPlayer1);
	player1->initAnimateFrame();
	player1->setPosition(Vec2(visibleSize.width / 4 * 3, visibleSize.height / 2 - 300));
	player1->setFlippedX(false);
	player1->setVisible(true);
	addChild(player1, 3);
	player1->idle();

	player2 = new PlayerSprite();
	/* 添加player2的物理刚体 */
	if (Player2Name == "Frieza") {
		/* 弗利萨的尾巴问题，所以得换个刚体绑定 */
		physicPlayer2 = Sprite::create("physicplayerForFrieza.png");
		isFreiza = true;
	}
	else {
		physicPlayer2 = Sprite::create("physicplayer.png");
	}
	//physicPlayer2 = Sprite::create("physicplayer.png");
	physicPlayer2->setPosition(Vec2(visibleSize.width / 4, visibleSize.height / 2 - 300));
	auto player2Body = PhysicsBody::createBox(physicPlayer2->getContentSize(), PhysicsMaterial(10000.0f, 0.0f, 0.0f));
	player2Body->setCategoryBitmask(0xFFFFFFFF);
	player2Body->setContactTestBitmask(0xFFFFFFFF);
	player2Body->setContactTestBitmask(0xFFFFFFFF);
	player2Body->setDynamic(true);
	physicPlayer2->setPhysicsBody(player2Body);
	physicPlayer2->setVisible(true);
	physicPlayer2->setScale(1.2f);
	addChild(physicPlayer2, 3);

	player2->initSprite(Player2Name, physicPlayer2);
	player2->initAnimateFrame();
	player2->setPosition(Vec2(visibleSize.width / 4, visibleSize.height / 2 - 300));
	player2->setFlippedX(true);
	player2->setVisible(true);
	addChild(player2, 3);
	player2->idle();

	
#pragma endregion

#pragma region hp条和mp条

	/* Player1的Hp， 右边 */
	Sprite* player1hpAndmpBorder = Sprite::create("Player2Border.png");
	Sprite* player1hpContent = Sprite::create("hp-new.png");
	/* Player1的Mp */
	Sprite* player1mpContent = Sprite::create("mp-new.png");
	player1Hp = ProgressTimer::create(player1hpContent);
	player1Hp->setScaleX(90);
	player1Hp->setAnchorPoint(Vec2(1, 0));
	player1Hp->setType(ProgressTimerType::BAR);
	player1Hp->setBarChangeRate(Point(1, 0));
	player1Hp->setMidpoint(Point(1, 0));
	player1Hp->setPercentage(50);
	player1Hp->setPosition(Vec2(935, 642));
	addChild(player1Hp, 1);
	player1hpAndmpBorder->setAnchorPoint(Vec2(1, 0));
	player1hpAndmpBorder->setPosition(Vec2(1025, 614));
	addChild(player1hpAndmpBorder, 0);

	player1Mp = ProgressTimer::create(player1mpContent);
	player1Mp->setScaleX(90);
	player1Mp->setAnchorPoint(Vec2(1, 0));
	player1Mp->setType(ProgressTimerType::BAR);
	player1Mp->setBarChangeRate(Point(1, 0));
	player1Mp->setMidpoint(Point(1, 0));
	player1Mp->setPercentage(60);
	player1Mp->setPosition(Vec2(935, 625));
	addChild(player1Mp, 1);


	/* Player2的Hp */
	Sprite* player2hpAndmpBorder = Sprite::create("Player1Border.png");
	Sprite* player2hpContent = Sprite::create("hp-new.png");
	/* Player2的Mp */
	Sprite* player2mpContent = Sprite::create("mp-new.png");
	player2Hp = ProgressTimer::create(player2hpContent);
	player2Hp->setScaleX(90);
	player2Hp->setAnchorPoint(Vec2(0, 0));
	player2Hp->setType(ProgressTimerType::BAR);
	player2Hp->setBarChangeRate(Point(1, 0));
	player2Hp->setMidpoint(Point(0, 1));
	player2Hp->setPercentage(10);
	player2Hp->setPosition(Vec2(90, 642));
	addChild(player2Hp, 1);
	player2hpAndmpBorder->setAnchorPoint(Vec2(0, 0));
	player2hpAndmpBorder->setPosition(Vec2(0, 614));
	addChild(player2hpAndmpBorder, 0);

	player2Mp = ProgressTimer::create(player2mpContent);
	player2Mp->setScaleX(90);
	player2Mp->setAnchorPoint(Vec2(0, 0));
	player2Mp->setType(ProgressTimerType::BAR);
	player2Mp->setBarChangeRate(Point(1, 0));
	player2Mp->setMidpoint(Point(0, 1));  ///  从左到右显示进度条
	player2Mp->setPercentage(20);
	player2Mp->setPosition(Vec2(90, 625));
	//player1Mp->setPosition(Vec2(origin.x + 14 * player1Mp->getContentSize().width + 500, origin.y + visibleSize.height - 2 * player1Mp->getContentSize().height - 100));
	addChild(player2Mp, 1);

#pragma endregion

#pragma region  添加游戏人物头像到信息框，以及显示人物姓名

	auto player1Icon = Sprite::create("role/" + Player1Name + "-icon.png");
	auto player2Icon = Sprite::create("role/" + Player2Name + "-icon.png");

	player1Icon->setAnchorPoint(Vec2(1, 0));
	player2Icon->setAnchorPoint(Vec2(0, 0));
	player1Icon->setPosition(Vec2(1012, 631));
	player2Icon->setPosition(Vec2(12, 631));

	addChild(player1Icon, 0);
	addChild(player2Icon, 0);


	player1Name = Label::createWithTTF(ShareSingleton::GetInstance()->user1.c_str(), "fonts/comicsansms.ttf", 20);
	player1Name->setAnchorPoint(Vec2(1, 0));
	player1Name->setPosition(Vec2(935, 660));
	player1Name->setColor(Color3B(0, 0, 0));
	addChild(player1Name, 1);
	player2Name = Label::createWithTTF(ShareSingleton::GetInstance()->user2.c_str(), "fonts/comicsansms.ttf", 20);
	player2Name->setAnchorPoint(Vec2(0, 0));
	player2Name->setPosition(Vec2(90, 660));
	player2Name->setColor(Color3B(0, 0, 0));
	addChild(player2Name, 1);

	vs = Label::createWithTTF("VS", "fonts/comicsansms.ttf", 60);
	vs->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 200);
	vs->setColor(Color3B(255, 255, 0));

#pragma endregion


#pragma region 音乐

	auto audio = SimpleAudioEngine::getInstance();
	/*预加载并循环播放背景音乐*/
	//	audio->preloadBackgroundMusic("music/WelcomeSceneBackground.mp3");  
	if (ShareSingleton::GetInstance()->controlVoice) {
		audio->playBackgroundMusic("music/MainGameSceneBgm.mp3", true);
		audio->setBackgroundMusicVolume(0.80);

		/*预加载点击音效*/
		audio->preloadEffect("music/ClickCamera.wav");
		audio->setEffectsVolume(0.80);

		/*加载并播放 3 2 1 开始 音乐*/
		audio->playEffect("music/321.mp3", false, 1.0f, 0.0f, 1.0f);
	}

#pragma endregion


#pragma region 游戏界面的菜单项

	/* Todo: 美工人员请在这里添加游戏界面的菜单项，如暂停游戏，设置，声音开关 */
	/*声音开关,默认打开 voiceState == true*/
	voiceState = 1;
	voiceItem = MenuItemImage::create(
		"button/SoundOn.png",
		"button/SoundOff.png",
		CC_CALLBACK_1(ExampleGameScene::VoicePauseSelectedCallback, this)
	);
	voiceItem->setPosition(ccp(visibleSize.width - voiceItem->getContentSize().width / 2,
		visibleSize.height / 2 - voiceItem->getContentSize().height / 2 - 60));
	auto VoiceMenu = Menu::create(voiceItem, NULL);
	VoiceMenu->setPosition(Vec2::ZERO);
	addChild(VoiceMenu, 0);

	/*游戏暂停按钮 */
	playOrPauseState = 1;
	playOrPauseItem = MenuItemImage::create(
		"button/play.png",
		"button/pause.png",
		CC_CALLBACK_1(ExampleGameScene::playOrPauseCallback, this)
	);
	playOrPauseItem->setPosition(ccp(visibleSize.width - playOrPauseItem->getContentSize().width / 2,
		visibleSize.height / 2 - playOrPauseItem->getContentSize().height / 2));
	//playOrPauseItem->setPosition(Vec2(480, 70));
	auto playOrPauseMenu = Menu::create(playOrPauseItem, NULL);
	playOrPauseMenu->setPosition(Vec2::ZERO);
	addChild(playOrPauseMenu, 0);

#pragma endregion


#pragma region 添加监听器

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(ExampleGameScene::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(ExampleGameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(ExampleGameScene::onConcactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(ExampleGameScene::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

#pragma endregion

#pragma region 添加定时器

	schedule(schedule_selector(ExampleGameScene::update), 0.0f, kRepeatForever, 0);
	schedule(schedule_selector(ExampleGameScene::hit), 0.0f, kRepeatForever, 0); /* 被打判断 */
	schedule(schedule_selector(ExampleGameScene::isCharge), 1.0f, kRepeatForever, 0);
	schedule(schedule_selector(ExampleGameScene::updateHP_MP), 0.1f, kRepeatForever, 0);

#pragma endregion

#pragma region 测试动画用按钮------邵梓硕

	/*auto label = Label::createWithTTF("win", "fonts/arial.ttf", 24);

	auto changeItem = MenuItemLabel::create(label, CC_CALLBACK_1(ExampleGameScene::hitTest, this));
	auto menu = Menu::create(changeItem, NULL);
	menu->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	menu->setVisible(true);
	addChild(menu, 2);*/

	/*auto label2 = Label::createWithTTF("dead", "fonts/arial.ttf", 24);

	auto changeItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(ExampleGameScene::deadTest, this));
	auto menu2 = Menu::create(changeItem2, NULL);
	menu2->setPosition(visibleSize.width / 2 + 50, visibleSize.height / 2);
	menu2->setVisible(false);
	addChild(menu2, 2);*/

#pragma endregion

	//--------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma region 创建倒计时
	totalTime = 122;
	schedule(schedule_selector(ExampleGameScene::updateCountDown), 1);

#pragma endregion

#pragma region 三秒回合图标和123倒计时
	bothCanmove = false;
	round1 = Sprite::create("round1.png");
	round1->setPosition(Vec2(origin.x + 14 * player2Mp->getContentSize().width + 455,
		origin.y + visibleSize.height - 2 * player2Mp->getContentSize().height - 20));
	addChild(round1, 3);
	three = Sprite::create("3.png");
	three->setPosition(Vec2(origin.x + 14 * player2Mp->getContentSize().width + 455
		, origin.y + visibleSize.height - 2 * player2Mp->getContentSize().height - 200));
	addChild(three, 3);
	isBreak = false;
#pragma endregion

	yIsBreak = false;
	fiveIsBreak = false;
	/* 爆裂帧动画 */
	explosion();


	//addChild(vs, 1);
	//--------------------------------------------------------------------------------------------------------------------------------------------------------


    return true;
}

/* 碰撞发生函数 */
bool ExampleGameScene::onConcactBegin(PhysicsContact & contact)
{
	if (player1->getActionByTag(12) != nullptr) {
		player1->stopActionByTag(12);
		if (chargeEffect1 != NULL) {
			chargeEffect1->removeFromParentAndCleanup(true);
			chargeEffect1 = NULL;
		}
		player1->idle();
	}
	if (player2->getActionByTag(12) != nullptr) {
		player2->stopActionByTag(12);
		if (chargeEffect2 != NULL) {
			chargeEffect2->removeFromParentAndCleanup(true);
			chargeEffect2 = NULL;
		}
		player2->idle();
	}
	return true;
}


/* 碰撞的两个物体离开时响应函数 */
bool ExampleGameScene::onContactSeparate(PhysicsContact & contact)
{
	/* 离开的时候移除速度 */
	if (physicPlayer1->getPhysicsBody()->getVelocity().x != -250 || physicPlayer1->getPhysicsBody()->getVelocity().x == 250) {
		physicPlayer1->getPhysicsBody()->setVelocity(Vec2::ZERO);
	}
	if (physicPlayer2->getPhysicsBody()->getVelocity().x != -250 || physicPlayer2->getPhysicsBody()->getVelocity().x == 250) {
		physicPlayer2->getPhysicsBody()->setVelocity(Vec2::ZERO);
	}
	return true;
}


#pragma region 键盘相关事件

/* 按下键盘 */
void ExampleGameScene::onKeyPressed(EventKeyboard::KeyCode code, Event* event)
{

	if (bothCanmove) {
		switch (code) {
		case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			if (fiveIsBreak == false) {
				if (player1->getActionByTag(12) != nullptr) {
					player1->stopActionByTag(12);
					if (chargeEffect1 != NULL) {
						chargeEffect1->removeFromParentAndCleanup(true);
						chargeEffect1 = NULL;
					}
				}
			}
			fiveIsBreak = true;
			LeftKeyPressed();
			LeftKeyState = true;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			if (fiveIsBreak == false) {
				if (player1->getActionByTag(12) != nullptr) {
					player1->stopActionByTag(12);
					if (chargeEffect1 != NULL) {
						chargeEffect1->removeFromParentAndCleanup(true);
						chargeEffect1 = NULL;
					}
				}
			}
			fiveIsBreak = true;
			RightKeyPressed();
			RightKeyState = true;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
			if (fiveIsBreak == false) {
				if (player1->getActionByTag(12) != nullptr) {
					player1->stopActionByTag(12);
					if (chargeEffect1 != NULL) {
						chargeEffect1->removeFromParentAndCleanup(true);
						chargeEffect1 = NULL;
					}
				}
			}
			fiveIsBreak = true;
			player1->jump();
			UPKeyState = true;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			if (FIVEKeyState) {
				player1->stopActionByTag(12);
				if (chargeEffect1 != NULL) {
					chargeEffect1->removeFromParentAndCleanup(true);
					chargeEffect1 = NULL;
				}
				FIVEKeyState = false;
			}
			if (fiveIsBreak == false) {
				if (player1->getActionByTag(12) != nullptr) {
					player1->stopActionByTag(12);
					if (chargeEffect1 != NULL) {
						chargeEffect1->removeFromParentAndCleanup(true);
						chargeEffect1 = NULL;
					}
				}
			}
			fiveIsBreak = false;
			player1->defend();
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_1:
			if (fiveIsBreak == false) {
				if (player1->getActionByTag(12) != nullptr) {
					player1->stopActionByTag(12);
					if (chargeEffect1 != NULL) {
						chargeEffect1->removeFromParentAndCleanup(true);
						chargeEffect1 = NULL;
					}
				}
			}
			fiveIsBreak = true;
			if (player1->getActionByTag(6) == nullptr && !player1->isHitted && !player2->isHitting) {
				player1LastHit = time(NULL);
				One_KeyPressed();
			}
			DOWNKeyState = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_2:
			if (fiveIsBreak == false) {
				if (player1->getActionByTag(12) != nullptr) {
					player1->stopActionByTag(12);
					if (chargeEffect1 != NULL) {
						chargeEffect1->removeFromParentAndCleanup(true);
						chargeEffect1 = NULL;
					}
				}
			}
			fiveIsBreak = true;
			createRangedBall(player1, true);
			player1->rangedAttack();
			DOWNKeyState = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_3:
			if (fiveIsBreak == false) {
				if (player1->getActionByTag(12) != nullptr) {
					player1->stopActionByTag(12);
					if (chargeEffect1 != NULL) {
						chargeEffect1->removeFromParentAndCleanup(true);
						chargeEffect1 = NULL;
					}
				}
			}
			fiveIsBreak = true;
			createUltimateBall(player1, true);
			if (!player1->ishitByUltimate) {
				player1->ultimate();
			}
			DOWNKeyState = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_5:
			if (DOWNKeyState) {
				player1->stopActionByTag(11);
				//CCLOG("SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS");
				DOWNKeyState = false;
			}
			if (fiveIsBreak == false) {
				chargeEffect1 = createChargeEffect(player1);
				player1->charge();
			}
			FIVEKeyState = true;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_A:
			if (yIsBreak == false) {
				if (player2->getActionByTag(12) != nullptr) {
					player2->stopActionByTag(12);
					if (chargeEffect2 != NULL) {
						chargeEffect2->removeFromParentAndCleanup(true);
						chargeEffect2 = NULL;
					}
				}
			}
			yIsBreak = true;
			A_KeyPressed();
			A_KeyState = true;
			S_KeyState = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_D:
			if (yIsBreak == false) {
				if (player2->getActionByTag(12) != nullptr) {
					player2->stopActionByTag(12);
					if (chargeEffect2 != NULL) {
						chargeEffect2->removeFromParentAndCleanup(true);
						chargeEffect2 = NULL;
					}
				}
			}
			yIsBreak = true;
			D_KeyPressed();
			D_KeyState = true;
			S_KeyState = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_W:
			if (yIsBreak == false) {
				if (player2->getActionByTag(12) != nullptr) {
					player2->stopActionByTag(12);
					if (chargeEffect2 != NULL) {
						chargeEffect2->removeFromParentAndCleanup(true);
						chargeEffect2 = NULL;
					}
				}
			}
			yIsBreak = true;
			W_KeyState = true;
			player2->jump();
			S_KeyState = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_S:
			if (yIsBreak == false) {
				if (player2->getActionByTag(12) != nullptr) {
					player2->stopActionByTag(12);
					if (chargeEffect2 != NULL) {
						chargeEffect2->removeFromParentAndCleanup(true);
						chargeEffect2 = NULL;
					}
				}
			}
			yIsBreak = true;
			player2->defend();
			S_KeyState = true;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_G:
			if (yIsBreak == false) {
				if (player2->getActionByTag(12) != nullptr) {
					player2->stopActionByTag(12);
					if (chargeEffect2 != NULL) {
						chargeEffect2->removeFromParentAndCleanup(true);
						chargeEffect2 = NULL;
					}
				}
			}
			yIsBreak = true;
			if (player2->getActionByTag(6) == nullptr && !player2->isHitted && !player2->isHitting) {
				player2LastHit = time(NULL);
				G_KeyPressed();
			}
			S_KeyState = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_H:
			if (yIsBreak == false) {
				if (player2->getActionByTag(12) != nullptr) {
					player2->stopActionByTag(12);
					if (chargeEffect2 != NULL) {
						chargeEffect2->removeFromParentAndCleanup(true);
						chargeEffect2 = NULL;
					}
				}
			}
			yIsBreak = true;
			createRangedBall(player2, false);
			player2->rangedAttack();
			S_KeyState = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_Y:
			if (yIsBreak == false) {
				chargeEffect2 = createChargeEffect(player2);
				player2->charge();
			}
			S_KeyState = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_J:
			if (yIsBreak == false) {
				if (player2->getActionByTag(12) != nullptr) {
					player2->stopActionByTag(12);
					if (chargeEffect2 != NULL) {
						chargeEffect2->removeFromParentAndCleanup(true);
						chargeEffect2 = NULL;
					}
				}
			}
			yIsBreak = true;
			createUltimateBall(player2, false);
			if (!player2->ishitByUltimate) {
				player2->ultimate();
			}
			S_KeyState = false;
			break;
		default:
			break;
		}
	}
}

/* 释放按键 */
void ExampleGameScene::onKeyReleased(EventKeyboard::KeyCode code, Event* event)
{
	if (bothCanmove) {
		switch (code) {
		case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			player1->isMove = false;
			player1->stopActionByTag(1);
			if (physicPlayer1->getPhysicsBody()->getVelocity().x < 0) {
				physicPlayer1->getPhysicsBody()->setVelocity(Vec2(0, 0));
			}
			/* 考虑先按1后按2，先松1的情况 */
			if (player1->getActionByTag(2) == nullptr) {
				player1->idle();
			}
			LeftKeyState = false;
			fiveIsBreak = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			player1->isMove = false;
			player1->stopActionByTag(2);
			if (physicPlayer1->getPhysicsBody()->getVelocity().x > 0) {
				physicPlayer1->getPhysicsBody()->setVelocity(Vec2(0, 0));
			}
			if (player1->getActionByTag(1) == nullptr) {
				player1->idle();
			}
			RightKeyState = false;
			fiveIsBreak = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
			UPKeyState = false;
			fiveIsBreak = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			player1->stopActionByTag(11);
			player1->idle();
			fiveIsBreak = false;
			DOWNKeyState = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_1:
			fiveIsBreak = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_2:
			fiveIsBreak = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_3:
			fiveIsBreak = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_5:
			if (player1->getActionByTag(12) != nullptr) {
				player1->stopActionByTag(12);
				if (chargeEffect1 != NULL) {
					chargeEffect1->removeFromParentAndCleanup(true);
					chargeEffect1 = NULL;
				}
				player1->idle();
			}
			FIVEKeyState = false;
			fiveIsBreak = false;
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
			yIsBreak = false;
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
			yIsBreak = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_W:
			yIsBreak = false;
			W_KeyState = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_S:
			player2->stopActionByTag(11);
			player2->idle();
			yIsBreak = false;
			S_KeyState = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_G:
			yIsBreak = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_H:
			yIsBreak = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_J:
			yIsBreak = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_Y:
			if (player2->getActionByTag(12) != nullptr) {
				player2->stopActionByTag(12);
				if (chargeEffect2 != NULL) {
					chargeEffect2->removeFromParentAndCleanup(true);
					chargeEffect2 = NULL;
				}
				player2->idle();
			}
			yIsBreak = false;
			break;
		default:
			break;
		}
	}
}
#pragma endregion


void ExampleGameScene::update(float delay)
{
	if (W_KeyState) {
		player2->jump();
	}
	else if (A_KeyState) {

	}
	else if (D_KeyState) {

	}
	else {
		if (S_KeyState)
			player2->defend();
	}

	if (UPKeyState) {
		player1->jump();
	}
	else if (LeftKeyState) {

	}
	else if (RightKeyState) {

	}
	else if (FIVEKeyState) {

	}
	else {
		if (DOWNKeyState) {
			//CCLOG("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx");
			player1->defend();
		}
	}
	////////////////qyh, 修复从暂停场景回退时，播放按钮没有从暂停状态恢复
	if (ShareSingleton::GetInstance()->controlPause) {
		playOrPauseState = 1;
		playOrPauseItem->setNormalImage(Sprite::create("button/play.png"));
	}
	/* 如果是被打飞的状态，那么让刚体和精灵的位置相同 */
	if (player1->getActionByTag(6) == nullptr) {
		player1->setPositionX(physicPlayer1->getPositionX());
	}
	else
	{
		/* 如果不是，那么移动动作实际上是在移动刚体，因此将精灵和刚体的位置保持一致 */
		physicPlayer1->setPosition(player1->getPosition());
	}
	if (player2->getActionByTag(6) == nullptr) {
		player2->setPositionX(physicPlayer2->getPositionX());
	}
	else {
		physicPlayer2->setPosition(player2->getPosition());
	}
	


#pragma region 移动冲刺判断
	/* 左键松开，如果此时播放的为向左移动的动画，则暂停；下面同理 */
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

void ExampleGameScene::updateCountDown(float delay)
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	if (totalTime == 122) {
		three->removeFromParent();
		two = Sprite::create("2.png");
		two->setPosition(Vec2(origin.x + 14 * player2Mp->getContentSize().width + 455
			, origin.y + visibleSize.height - 2 * player2Mp->getContentSize().height - 200));
		addChild(two, 3);
	}
	else if (totalTime == 121) {
		two->removeFromParent();
		one = Sprite::create("1.png");
		one->setPosition(Vec2(origin.x + 14 * player2Mp->getContentSize().width + 455
			, origin.y + visibleSize.height - 2 * player2Mp->getContentSize().height - 200));
		addChild(one, 3);
	}
	else if (totalTime == 120) {
		one->removeFromParent();
		bothCanmove = true;

		countDown = Label::createWithTTF("120", "fonts/comicsansms.ttf", 48);
		countDown->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 250);
		countDown->setColor(Color3B(0, 255, 0));
		countDown->enableShadow();
		addChild(countDown, 3);
	}
	else if (totalTime < 120) {
		char str[10];
		sprintf(str, "%d", totalTime); /* 将int类型转化为字符串char*类型 */
		countDown->setString(str);
	}
	if (totalTime > 0)
		totalTime--;
	else if (totalTime == 0)
		gameOver();
}

void ExampleGameScene::gameOver()
{
	_eventDispatcher->removeAllEventListeners();
	float delay = 3.0f;
	/* 停止所有计时器操作 */
	this->unscheduleAllSelectors();
	string name1 = ShareSingleton::GetInstance()->user1;
	string name2 = ShareSingleton::GetInstance()->user2;
	int score1 = 0, score2 = 0;

#pragma region WinLabel
	winLabel = Label::createWithTTF("", "fonts/comicsansms.ttf", 108);
	winLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	winLabel->setColor(Color3B(255, 255, 255));
	addChild(winLabel, 2);

	//bothCanmove = false;
	if (player1->getHp() > player2->getHp()) {
		player1->win();
		player2->dead();
		winLabel->setString(name1 + " Win");
		score1 += 1;
		score2 -= 1;
	}
	else if (player1->getHp() < player2->getHp()) {
		player2->win();
		player1->dead();
		winLabel->setString(name2 + " Win");
		score1 -= 1;
		score2 += 1;
	}
	else if (player1->getHp() == player2->getHp()) {
		delay = 1.0f;
		winLabel->setString("Draw!");
	}
#pragma endregion

#pragma region 数据存储

	if (!database->getBoolForKey("isExist")) {
		database->setBoolForKey("isExist", true);
	}
	int one = database->getIntegerForKey(name1.c_str(), 0);
	int two = database->getIntegerForKey(name2.c_str(), 0);
	/*CCLOG("SSS%d", one);
	CCLOG("TTT%d", two);*/

	score1 = score1 + one;
	score2 = score2 + two;
	database->setIntegerForKey(name1.c_str(), score1);
	database->setIntegerForKey(name2.c_str(), score2);

	database->flush();
	ShareSingleton::GetInstance()->xmlPath = FileUtils::getInstance()->getWritablePath() + "UserDefault.xml";
	//log("%s", ShareSingleton::GetInstance()->xmlPath);

#pragma endregion

	/*弹出游戏结束界面,  需要延迟1s*/
	scheduleOnce(schedule_selector(ExampleGameScene::CallGameOverScene), delay);
}

/* 集气状态 */
void ExampleGameScene::isCharge(float dt)
{
	if (player1->getActionByTag(12) != nullptr) {
		player1->setMp(player1->getMp() + 10);
	}
	else {
		if (chargeEffect1 != NULL) {
			chargeEffect1->removeFromParentAndCleanup(true);
			chargeEffect1 = NULL;
		}
	}
	if (player2->getActionByTag(12) != nullptr) {
		player2->setMp(player2->getMp() + 10);
	}
	else {
		if (chargeEffect2 != NULL) {
			chargeEffect2->removeFromParentAndCleanup(true);
			chargeEffect2 = NULL;
		}
	}
}

/* 更新hp和mp */
void ExampleGameScene::updateHP_MP(float delay)
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
	/* 判断游戏结束 */
	if (player1->getHp() <= 0 || player2->getHp() <= 0) {
		gameOver();
	}
}

void ExampleGameScene::CallGameOverScene(float dt)
{

#pragma region 弹出结束游戏场景

	/*得到窗口的大小*/
	Size visibleSize = Director::sharedDirector()->getVisibleSize();
	RenderTexture *renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);

	/*遍历当前类的所有子节点信息，画入renderTexture中。
	这里类似截图。*/
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	auto newScene = GameOverScene::CreateScene(renderTexture);
	/*结束游戏界面，压入场景堆栈。并切换到GameOverScene界面*/
	Director::sharedDirector()->pushScene(newScene);

#pragma endregion
}


/* TODO:这里的对打逻辑存在一点小问题，有时候会出现两个人互打的情况； */
void ExampleGameScene::hit(float dt)
{
	if (player2->isHitted || yIsBreak == true) {
		if (player2->getActionByTag(12) != nullptr) {
			player2->stopActionByTag(12);
			if (chargeEffect2 != NULL) {
				chargeEffect2->removeFromParentAndCleanup(true);
				chargeEffect2 = NULL;
			}
		}
		yIsBreak = true;
	}

	if (player1->isHitted || fiveIsBreak == true) {
		if (player1->getActionByTag(12) != nullptr) {
			player1->stopActionByTag(12);
			if (chargeEffect1 != NULL) {
				chargeEffect1->removeFromParentAndCleanup(true);
				chargeEffect1 = NULL;
			}
		}
		fiveIsBreak = true;
	}
	/* 因为弗利萨尾巴太长，所以判定距离的方法得区别开来 */
	bool flag = false;
	if (isFreiza) {
		flag = abs(physicPlayer1->getPositionX() - physicPlayer2->getPositionX()) < physicPlayer1->getContentSize().width + physicPlayer2->getContentSize().width - 50;
	}
	else {
		flag = abs(physicPlayer1->getPositionX() - physicPlayer2->getPositionX()) < physicPlayer1->getContentSize().width + physicPlayer2->getContentSize().width - 10;
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
#pragma region 判断是否被远程攻击击中

	for (Sprite* ball : player1RangedBalls)
	{
		if (ball->getPositionX() > 1100 || ball->getPositionX() < 40) {
			ball->removeFromParentAndCleanup(true);
			player1RangedBalls.remove(ball);
			break;
		}
		else if (abs(player2->getPositionX() - ball->getPositionX()) < 40 && player2->getPositionY() < 120) {
			player2->setFlippedX(!player1->isFlippedX());
			if (player2->isHitted == false) {
				shareInstance->opponentFlipx = player1->isFlippedX();
				if (chargeEffect2 != NULL) {
					chargeEffect2->removeFromParentAndCleanup(true);
					chargeEffect2 = NULL;
				}
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
		else if (abs(player1->getPositionX() - ball->getPositionX()) < 40 && player1->getPositionY() < 120) {
			player1->setFlippedX(!player2->isFlippedX());
			if (player1->isHitted == false) {
				shareInstance->opponentFlipx = player2->isFlippedX();
				if (player1->getActionByTag(12) != nullptr) {
					player1->stopActionByTag(12);
					if (chargeEffect1 != NULL) {
						chargeEffect1->removeFromParentAndCleanup(true);
						chargeEffect1 = NULL;
					}
				}
				createHitEffect(player1);
			}
			player1->hit();
			ball->removeFromParentAndCleanup(true);
			player2RangedBalls.remove(ball);
			break;
		}
	}

#pragma endregion

#pragma region 两球相撞动画
	bool end = false;
	for (Sprite* ball2 : player2RangedBalls) {
		for (Sprite* ball1 : player1RangedBalls) {
			if (abs(ball2->getPositionX() - ball1->getPositionX()) < 15) {
				auto explore_animation = Animation::createWithSpriteFrames(explore, 0.1f);
				AnimationCache::getInstance()->addAnimation(explore_animation, "exploreAnimation");
				auto exploreAnimation = Animate::create(AnimationCache::getInstance()->getAnimation("exploreAnimation"));
				SimpleAudioEngine::getInstance()->playEffect("music/explore.wav", false);

				Sprite* temp2 = ball2;
				// 先从队列中移除
				ball2->setPosition(Vec2(ball2->getPosition().x + 15, ball2->getPosition().y));
				ball2->stopAllActions();
				ball2->runAction(
					Sequence::create(
						exploreAnimation
						, CallFunc::create([temp2, this] {
					temp2->removeFromParentAndCleanup(true);
					player2RangedBalls.remove(temp2);
				})
						, nullptr
					)
				);

				/*ball2->removeFromParentAndCleanup(true);
				player2RangedBalls.remove(ball2);*/
				ball1->removeFromParentAndCleanup(true);
				player1RangedBalls.remove(ball1);
				end = true;
				break;
			}
		}
		if (end) {
			break;
		}
	}
#pragma endregion
}

/* 点击按钮发生被打状态，仅用于测试代码 */
void ExampleGameScene::hitTest(Ref* sender)
{
	player2->win();
}


/* 点击按钮发生死亡状态，仅用于测试代码 */
void ExampleGameScene::deadTest(Ref* sender)
{
	if(!player1->isDead)
		player1->dead();
}

/* 左键第一次按下时响应 */
void ExampleGameScene::LeftKeyPressed()
{
	if (firstPressL) {
		/* 如果是第一次按下，firstPressL设为false, 向左移动，然后延时0.3秒将firstPressL重新设为true */
		player1->moveLeft();
		scheduleOnce(schedule_selector(ExampleGameScene::LeftKeyPressed), 0.30f);
		firstPressL = false;
	}
	else
	{
		/* 若firstPressL为true，说明在0.3f以内，相当于dash */
		player1->dashLeft(player2->getPosition());
		firstPressL = true;
	}

}

/* 延时0.3秒将firstPressL重新设为true */
void ExampleGameScene::LeftKeyPressed(float t)
{
	firstPressL = true;
}

/* 右键第一次按下时响应 */
void ExampleGameScene::RightKeyPressed()
{
	if (firstPressR) {
		player1->moveRight();
		scheduleOnce(schedule_selector(ExampleGameScene::RightKeyPressed), 0.30f);
		firstPressR = false;
	}
	else
	{
		player1->dashRight(player2->getPosition());
		firstPressR = true;
	}
}
/* 延时0.3秒将firstPressR重新设为true */
void ExampleGameScene::RightKeyPressed(float t)
{
	firstPressR = true;
}

/* A键第一次按下时响应 */
void ExampleGameScene::A_KeyPressed()
{
	if (firstPressA) {
		player2->moveLeft();
		scheduleOnce(schedule_selector(ExampleGameScene::A_KeyPressed), 0.30f);
		firstPressA = false;
	}
	else
	{
		player2->dashLeft(player1->getPosition());
		firstPressA = true;
	}
}

/* 延时0.3秒将firstPressA重新设为true */
void ExampleGameScene::A_KeyPressed(float t)
{
	firstPressA = true;
}

/* D键第一次按下时响应 */
void ExampleGameScene::D_KeyPressed()
{
	if (firstPressD) {
		player2->moveRight();
		scheduleOnce(schedule_selector(ExampleGameScene::D_KeyPressed), 0.30f);
		firstPressD = false;
	}
	else
	{
		player2->dashRight(player1->getPosition());
		firstPressD = true;
	}
}
/* 延时0.3秒将firstPressD重新设为true */
void ExampleGameScene::D_KeyPressed(float t)
{
	firstPressD = true;
}

/* 延时判断攻击类型：出拳，出拳+上勾拳，出拳+上勾拳+飞踢 */
void ExampleGameScene::One_KeyPressed()
{
	if (secondPress1) {
		player1->meleeAttack2();
		scheduleOnce(schedule_selector(ExampleGameScene::One_KeyPressed), 1.8f);
		secondPress1 = false;
		firstPress1 = false;
	}
	else if (firstPress1) {
		player1->meleeAttack1();
		scheduleOnce(schedule_selector(ExampleGameScene::One_KeyPressed), 1.5f);
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
void ExampleGameScene::One_KeyPressed(float t)
{
	firstPress1 = true;
	secondPress1 = false;
}

/* 延时判断攻击类型：出拳，出拳+上勾拳，出拳+上勾拳+飞踢 */
void ExampleGameScene::G_KeyPressed()
{
	if (secondPressG) {
		player2->meleeAttack2();
		scheduleOnce(schedule_selector(ExampleGameScene::G_KeyPressed), 1.8f);
		secondPressG = false;
		firstPressG = false;
	}
	else if (firstPressG) {
		player2->meleeAttack1();
		scheduleOnce(schedule_selector(ExampleGameScene::G_KeyPressed), 1.5f);
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
void ExampleGameScene::G_KeyPressed(float t)
{
	firstPressG = true;
	secondPressG = false;
}

void ExampleGameScene::hittedCounter(float t)
{
	player1->isDouble = false;
}

/*生成大招的球，注意这里没有remove，请在遍历球列表时进行remove*/
void ExampleGameScene::createUltimateBall(PlayerSprite* player, bool isPlayer1) {
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
	/*设置球的方向*/
	int direction = 1;
	if (!player->isFlippedX()) direction = -1;
	auto shootBall = MoveTo::create(1.0f, Vec2(player->getPositionX() + 500 * direction, visibleSize.height / 2 - 300));
	/*球的动作：延迟，可见，动画，移动，爆炸，销毁*/
	auto seqBall = Sequence::create(DelayTime::create(1.0f), CallFuncN::create([Ball, player](Ref* sender) {
		Ball->setPosition(player->getPositionX(), player->getPositionY() + 300);
		Ball->setVisible(true);
	}), animateBall, shootBall,CallFuncN::create([Ball, player, opponent, this](Ref* sender) {
		/*爆炸*/
		Sprite* explosion = Sprite::createWithSpriteFrame(player->explosionVector.front());
		explosion->setPosition(Ball->getPosition());
		explosion->setScale(4.0f);
		auto exploseAnimation = Animation::createWithSpriteFrames(player->explosionVector, 0.06f);
		auto explose = Animate::create(exploseAnimation);
		auto seq = Sequence::create(explose, CallFuncN::create([explosion](Ref* sender) {
			explosion->removeFromParentAndCleanup(true);
		}), NULL);
		/* 这里判断是否被大招击中  */
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

/* 生成远程攻击的球，注意这里没有remove，请在遍历球列表时进行remove */
void ExampleGameScene::createRangedBall(PlayerSprite* player,bool isPlayer1) {
	if (player->isRun || player->getMp() < 10) return;
	Sprite* Ball = Sprite::createWithSpriteFrame(player->rangedBallVector.back());
	Ball->setFlippedX(!player->isFlippedX());
	Ball->setVisible(false);
	/*设置球的方向*/
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
	/*球的动作：延迟，可见，移动，销毁*/
	auto seqBall = Sequence::create(DelayTime::create(0.5f), CallFuncN::create([Ball](Ref* sender) {
		Ball->setVisible(true);
	}), moveTo, NULL);
	Ball->runAction(seqBall);
}

/* 生成蓄力效果 */
Sprite* ExampleGameScene::createChargeEffect(PlayerSprite* player) {
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

/* 生成被击打效果，在hitTest里被调用 */
void ExampleGameScene::createHitEffect(PlayerSprite* player) {
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

/* 声音暂停 回调*/
void ExampleGameScene::VoicePauseSelectedCallback(Ref * pSender)
{
	/*声音按钮切换以及声音控制*/
	if (voiceState) {
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		SimpleAudioEngine::getInstance()->pauseAllEffects();
		voiceState = 0;
		voiceItem->setNormalImage(Sprite::create("button/SoundOn.png"));
	}
	else {
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		SimpleAudioEngine::getInstance()->resumeAllEffects();
		voiceState = 1;
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);
		voiceItem->setNormalImage(Sprite::create("button/SoundOff.png"));	
	}
}

/*游戏暂停，弹出暂停场景的回调函数*/
void ExampleGameScene::playOrPauseCallback(Object * pSender)
{

	/*得到窗口的大小*/
	Size visibleSize = Director::sharedDirector()->getVisibleSize();
	RenderTexture *renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);

	/*遍历当前类的所有子节点信息，画入renderTexture中。
	这里类似截图。*/
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();
	float t = 0.5;
	auto replacesense = CCTransitionFade::create(t, GamePauseScene::CreateScene(renderTexture));

	/*将游戏界面暂停，压入场景堆栈。并切换到GamePauseScene界面*/
	Director::sharedDirector()->pushScene(GamePauseScene::CreateScene(renderTexture));
	
	log(" to game pause scene");

	/* 播放暂停按钮切换*/
	if (playOrPauseState) {
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);
		playOrPauseState = 0;
		ShareSingleton::GetInstance()->controlPause = false;
		playOrPauseItem->setNormalImage(Sprite::create("button/pause.png"));
	}
	else {
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);
		playOrPauseState = 1;
		playOrPauseItem->setNormalImage(Sprite::create("button/play.png"));
	}
}

void ExampleGameScene::explosion()
{
	auto texture = Director::getInstance()->getTextureCache()->addImage("explosion.png");
	explore.reserve(8);
	for (int i = 0; i < 5; i++) {
		auto frame = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(191 * i, 0, 191, 192)));
		explore.pushBack(frame);
	}
	for (int i = 0; i < 2; i++) {
		auto frame = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(191 * i, 192, 191, 192)));
	}
	auto explore_animation = Animation::createWithSpriteFrames(explore, 0.1f);
	AnimationCache::getInstance()->addAnimation(explore_animation, "exploreAnimation");
}
