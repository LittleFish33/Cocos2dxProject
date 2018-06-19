#include "ExampleGameScene.h"
#include "SimpleAudioEngine.h"
#include <cmath>

USING_NS_CC;

void ExampleGameScene::setPhysicsWorld(PhysicsWorld* world) { m_world = world; }

Scene* ExampleGameScene::createScene()
{
#pragma region 设置物理环境

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
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

#pragma endregion

#pragma region 创建场景
	/* Todo：美工 */

	/* 添加背景图片 */
	auto bgSprite = Sprite::create("exampleBackground.png");
	bgSprite->setPosition(visibleSize / 2);
	bgSprite->setScale(visibleSize.width / bgSprite->getContentSize().width, visibleSize.height / bgSprite->getContentSize().height);
	this->addChild(bgSprite, 0);

	/* 添加地面 */
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

#pragma region 创建精灵
	/* Todo：创建精灵的人需要修改一下这里的初始帧 */
	/* 创建一张贴图，使用贴图创建精灵 */
	auto texture = Director::getInstance()->getTextureCache()->addImage("$lucia_2.png");
	auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 113, 113)));
	player1 = new ExamplePlayerSprite();
	player1->initWithSpriteFrame(frame0);
	player1->initSprite();
	player1->initAnimateFrame();
	player1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 300));
	addChild(player1, 3);
	/* Todo：负责双人对战的人完成另一个精灵的建立 */
	
#pragma endregion

#pragma region hp条和mp条

	/* Todo：请美工在这里添加剩下的hp条和mp条 */
	Sprite* sp0 = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
	Sprite* sp = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(610, 362, 4, 16)));

	/* 使用hp条设置progressBar */
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

#pragma region 游戏界面的菜单项

	/* Todo: 美工人员请在这里添加游戏界面的菜单项，如暂停游戏，设置，声音开关 */

#pragma endregion

#pragma region 音乐

	/* Todo: 美工人员请在这里添加音乐的相关代码 */

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

	schedule(schedule_selector(ExampleGameScene::update), 0.1f, kRepeatForever, 0);
	schedule(schedule_selector(ExampleGameScene::hit), 0.0f, kRepeatForever, 0);
	schedule(schedule_selector(ExampleGameScene::gameOver), 0.0f, kRepeatForever, 0);

#pragma endregion

    return true;
}

/* 碰撞发生函数 */
bool ExampleGameScene::onConcactBegin(PhysicsContact & contact)
{
	return true;
}


/* 碰撞的两个物体离开时响应函数 */
bool ExampleGameScene::onContactSeparate(PhysicsContact & contact)
{
	return true;
}


#pragma region 键盘相关事件

/* 按下键盘 */
/* Todo：这里只绑定了第一个玩家的动作，请完成双人对战的人完成第二个玩家动作的绑定 */
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

/* 释放按键 */
/* Todo：这里只绑定了第一个玩家的动作，请完成双人对战的人完成第二个玩家动作的绑定 */
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
	/* 更新玩家的状态 */
	updatePlayer1Status();
	updatePlayer2Status();

	/* Todo：更新HP和MP的值，合并代码的人请完成这部分内容 */
	
}

/* Todo：更新玩家1的状态（这里还缺少了被攻击动画和死亡动画，请完成第一个精灵的人完成这部分的内容） */
void ExampleGameScene::updatePlayer1Status()
{	
	/*
	*  tag    动画
	*  0      idle
	*  1      moveLeft
	*  2      moveRight
	*  3      jump
	*  4      meleeAttack
	*  5      rangeAttack
	*/
	/* 判断是不是近攻的状态 */
	if (player1->stopMeleeAttack && !player1->isRun) { /* 键盘已释放，停止近攻，等待isRun为false（即之前的动画已播放完毕） */
		player1->stopAllActionsByTag(4); /* 停止所有的近攻动画 */
	}
	else { /* 键盘未释放，且此时没有播放其他动画 */
		player1->meleeAttack();  /* 播放近攻动画 */
		return;
	}

	/* 判断是不是远攻的状态 */
	if (player1->stopRangedAttack && !player1->isRun) {
		player1->stopAllActionsByTag(5);
	}
	else {
		player1->rangedAttack();
		return;
	}

	/* 判断是不是向左移动的状态 */
	if (player1->stopLeftMove && !player1->isRun) {
		player1->stopAllActionsByTag(1);
	}
	else {
		player1->moveLeft();
		return;
	}

	/* 判断是不是向右移动的状态 */
	if (player1->stopRightMove && !player1->isRun) {
		player1->stopAllActionsByTag(2);
	}
	else {
		player1->moveRight();
		return;
	}

	/* 判断是不是跳跃的状态 */
	if (player1->stopJump && !player1->isRun) {
		player1->stopAllActionsByTag(3);
	}
	else {
		player1->jump();
		return;
	}

	/* 此时并没有播放任何其他动作，则判断是不是运行idle动画，如果不是，则重复播放idle动画 */
	if (player1->getActionByTag(0) == nullptr) {
		player1->idle();
	}
}

/* Todo：更新玩家2的状态，负责双人对战的人请完成这部分代码 */
void ExampleGameScene::updatePlayer2Status()
{

}

/* Todo：游戏结束：负责双人对战的人完成这部分的代码 */
void ExampleGameScene::gameOver(float delay)
{

}


/* Todo：被攻击，负责双人对战的人完成这部分的代码*/
void ExampleGameScene::hit(float dt)
{
	
}
