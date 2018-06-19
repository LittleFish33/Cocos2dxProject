#include "SelectRoleScene.h"
#include "SimpleAudioEngine.h"
#include "WelcomeScene.h"
#include "SelectBackgroundScene.h"
#include <stdlib.h>


Scene* SelectRoleScene::createScene()
{
    return SelectRoleScene::create();
}

/* 当文件不存在时，打印有用的错误消息而不是分段错误 */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SelectRoleSceneScene.cpp\n");
}

/* 初始化场景函数 */
bool SelectRoleScene::init()
{
#pragma region Cocos2dx自动生成的内容：一些基本配置

	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

#pragma endregion

#pragma region UI界面

	/* Todo：美工人员请将这里的图片替换为你选的素材和按你的需要设置位置 */
	/* 这里的角色的变量名仅仅是为了基本框架的构建，请在选好角色之后替换这些变量名 */
	/* 可选角色1 */
	roleItem1 = MenuItemImage::create(
		"role1.png",
		"role1.png",
		CC_CALLBACK_1(SelectRoleScene::roleSelectedCallback, this, '1'));
	roleItem1->setPosition(Vec2(400, 500));
	/* 可选角色2 */
	roleItem2 = MenuItemImage::create(
		"role2.png",
		"role2.png",
		CC_CALLBACK_1(SelectRoleScene::roleSelectedCallback, this, '2'));
	roleItem2->setPosition(Vec2(600, 500));
	/* 可选角色3 */
	roleItem3 = MenuItemImage::create(
		"role3.png",
		"role3.png",
		CC_CALLBACK_1(SelectRoleScene::roleSelectedCallback, this, '3'));
	roleItem3->setPosition(Vec2(400, 300));
	/* 可选角色4 */
	roleItem4 = MenuItemImage::create(
		"role4.png",
		"role4.png",
		CC_CALLBACK_1(SelectRoleScene::roleSelectedCallback, this, '4'));
	roleItem4->setPosition(Vec2(600, 300));
	
	/* 确定按钮 */
	player1ConfirmItem = MenuItemImage::create(
		"confirm.png",
		"confirm.png",
		CC_CALLBACK_1(SelectRoleScene::confirmCallback, this, '1'));
	player1ConfirmItem->setPosition(Vec2(150, 100));
	player1ConfirmItem->setVisible(false);

	player2ConfirmItem = MenuItemImage::create(
		"confirm.png",
		"confirm.png",
		CC_CALLBACK_1(SelectRoleScene::confirmCallback, this, '2'));
	player2ConfirmItem->setPosition(Vec2(850, 100));
	player2ConfirmItem->setVisible(false);

	/* 回到主菜单按纽 */
	backItem = MenuItemImage::create(
		"back.png",
		"back.png",
		CC_CALLBACK_1(SelectRoleScene::menuBackCallback, this));
	backItem->setPosition(Vec2(500, 100));

	auto menu = Menu::create(roleItem1, roleItem2, roleItem3, roleItem4, backItem, player1ConfirmItem, player2ConfirmItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/* 当你选择了一个角色之后，将会显示出该角色的大图在左下角或右下角，在此之前该图片是不可见的 */
	/* 已选角色1 */
	roleItem1_big = Sprite::create("role1-big.png");
	roleItem1_big->setPosition(Vec2(0, 0));
	roleItem1_big->setVisible(false);
	this->addChild(roleItem1_big, 0);

	roleItem2_big = Sprite::create("role2-big.png");
	roleItem2_big->setPosition(Vec2(0, 0));
	roleItem2_big->setVisible(false);
	this->addChild(roleItem2_big, 0);

	roleItem3_big = Sprite::create("role3-big.png");
	roleItem3_big->setPosition(Vec2(150, 300));
	roleItem3_big->setVisible(false);
	this->addChild(roleItem3_big, 0);

	roleItem4_big = Sprite::create("role4-big.png");
	roleItem4_big->setPosition(Vec2(850, 300));
	roleItem4_big->setVisible(false);
	this->addChild(roleItem4_big, 0);

	/* P1标签和P2标签：在未选中状态是不可见的 */
	p1Sprite = Sprite::create("p1.png");
	p1Sprite->setPosition(Vec2(400, 500));
	p1Sprite->setOpacity(200);
	p1Sprite->setVisible(false);
	this->addChild(p1Sprite, 2);

	p2Sprite = Sprite::create("p2.png");
	p2Sprite->setPosition(Vec2(0, 0));
	p2Sprite->setOpacity(200);
	p2Sprite->setVisible(false);
	this->addChild(p2Sprite, 2);
	
#pragma endregion

	/* 鼠标点击响应函数，为了方便开发时使用，实际没有作用*/
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(SelectRoleScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

/* 返回欢迎界面 */
void SelectRoleScene::menuBackCallback(Ref* pSender)
{
	float t = 1.2f;
	auto newScene = WelcomeScene::createScene();
	auto replacesense = CCTransitionPageTurn::create(t, newScene, false);
	Director::sharedDirector()->replaceScene(replacesense);
}

/* 选择角色 */
void SelectRoleScene::roleSelectedCallback(Ref* pSender, char option)
{
	if (!player1Selected) { /* 当前是为player1选择角色 */
		invisibleRolesBig();
		switch (option) /* 判断选择的是哪一个角色 */
		{
		case '1':
			p1Sprite->setPosition(400, 500);	/* 设置p1标签的位置 */
			roleItem1_big->setPosition(150, 300); /* 设置所选角色的大图的位置 */
			roleItem1_big->setVisible(true);
			alreadySelected = 1;  /* 设置已经选择的角色编号，避免另一个玩家选择了同样的角色 */
			break;
		case '2':
			p1Sprite->setPosition(600, 500);
			roleItem2_big->setPosition(150, 300);
			roleItem2_big->setVisible(true);
			alreadySelected = 2;
			break;
		case '3':
			p1Sprite->setPosition(400, 300);
			roleItem3_big->setPosition(150, 300);
			roleItem3_big->setVisible(true);
			alreadySelected = 3;
			break;
		case '4':
			p1Sprite->setPosition(600, 300);
			roleItem4_big->setPosition(150, 300);
			roleItem4_big->setVisible(true);
			alreadySelected = 4;
			break;
		default:
			break;
		}
		p1Sprite->setVisible(true); /* 设置标签可见 */
		player1ConfirmItem->setVisible(true); /* 设置确定按钮可见 */
	}
	else { /* 当前是为player2选择角色 */
		if (option - '0' == alreadySelected) { /* 判断player1和player2是不是选择了相同的两个角色 */
			return;
		}
		invisibleRolesBig();
		switch (option)/* 判断选择的是哪一个角色 */
		{
		case '1':
			p2Sprite->setPosition(400, 500);  /* 设置p2标签的位置 */
			roleItem1_big->setPosition(850, 300); /* 设置所选角色的大图的位置 */
			roleItem1_big->setVisible(true);
			break;
		case '2':
			p2Sprite->setPosition(600, 500);
			roleItem2_big->setPosition(850, 300);
			roleItem2_big->setVisible(true);
			break;
		case '3':
			p2Sprite->setPosition(400, 300);
			roleItem3_big->setPosition(850, 300);
			roleItem3_big->setVisible(true);
			break;
		case '4':
			p2Sprite->setPosition(600, 300);
			roleItem4_big->setPosition(850, 300);
			roleItem4_big->setVisible(true);
			break;
		default:
			break;
		}
		p2Sprite->setVisible(true);
		player2ConfirmItem->setVisible(true);
	}
}

/* 鼠标点击响应函数，为了方便开发时使用，实际没有作用*/
bool SelectRoleScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	CCLOG("%f %f\n", touch->getLocation().x, touch->getLocation().y);
	return true;
}


/* 隐藏，除了player1已经选好的角色的其他角色大图 */
void SelectRoleScene::invisibleRolesBig()
{
	switch (alreadySelected)
	{
		case 1:
			roleItem2_big->setVisible(false);
			roleItem3_big->setVisible(false);
			roleItem4_big->setVisible(false);
			break;
		case 2:
			roleItem1_big->setVisible(false);
			roleItem3_big->setVisible(false);
			roleItem4_big->setVisible(false);
			break;
		case 3:
			roleItem1_big->setVisible(false);
			roleItem2_big->setVisible(false);
			roleItem4_big->setVisible(false);
			break;
		case 4:
			roleItem1_big->setVisible(false);
			roleItem2_big->setVisible(false);
			roleItem3_big->setVisible(false);
			break;
		default:
			break;
	}
}


/* 确定角色 */
void SelectRoleScene::confirmCallback(Ref* pSender, char option)
{
	auto particle = ParticleFlower::create();
	switch (option)
	{
	case '1':
		player1Selected = true;
		/* Todo：这里只是我添加的一个简单粒子特效，美工人员请做更好的优化 */
		particle->setScale(3.0f);
		particle->setPosition(150,100);
		player1ConfirmItem->addChild(particle);
		particle->runAction(Sequence::create(DelayTime::create(1.0f), RemoveSelf::create(true), nullptr));
		return;
	case '2':
		break;
	default:
		return;
	}
	/* 如果play2也已经选择好角色了，那么进入游戏背景选择界面（这里试过了不能放在switch里，所以让case2 直接break） */
	float t = 1.2f;
	auto newScene = SelectBackgroundScene::createScene();
	auto replacesense = CCTransitionPageTurn::create(t, newScene, false);
	Director::sharedDirector()->replaceScene(replacesense);
}

