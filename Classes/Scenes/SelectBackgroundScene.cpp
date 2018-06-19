#include "SelectBackgroundScene.h"
#include "SimpleAudioEngine.h"
#include "ExampleGameScene.h"

Scene* SelectBackgroundScene::createScene()
{
    return SelectBackgroundScene::create();
}

/* 当文件不存在时，打印有用的错误消息而不是分段错误 */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SelectBackgroundSceneScene.cpp\n");
}

/* 初始化场景函数 */
bool SelectBackgroundScene::init()
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
	/* 这里的场景的变量名仅仅是为了基本框架的构建，请在选好场景之后替换这些变量名 */
	/* 可选场景1 */
	bgItem1 = MenuItemImage::create(
		"bg1.jpg",
		"bg1.jpg",
		CC_CALLBACK_1(SelectBackgroundScene::bgSelectedCallback, this, 1));
	bgItem1->setPosition(Vec2(200, 500));
	/* 可选场景2 */
	bgItem2 = MenuItemImage::create(
		"bg2.jpg",
		"bg2.jpg",
		CC_CALLBACK_1(SelectBackgroundScene::bgSelectedCallback, this, 2));
	bgItem2->setPosition(Vec2(700, 500));
	/* 可选场景3 */
	bgItem3 = MenuItemImage::create(
		"bg3.jpg",
		"bg3.jpg",
		CC_CALLBACK_1(SelectBackgroundScene::bgSelectedCallback, this, 3));
	bgItem3->setPosition(Vec2(200, 200));
	/* 可选场景4 */
	bgItem4 = MenuItemImage::create(
		"bg4.jpg",
		"bg4.jpg",
		CC_CALLBACK_1(SelectBackgroundScene::bgSelectedCallback, this, 4));
	bgItem4->setPosition(Vec2(700, 200));
	
	/* 确定按钮 */
	confirmItem = MenuItemImage::create(
		"confirm.png",
		"confirm.png",
		CC_CALLBACK_1(SelectBackgroundScene::startGame, this));
	confirmItem->setPosition(Vec2(500, 100));
	
	auto menu = Menu::create(bgItem1, bgItem2, bgItem3, bgItem4, confirmItem,  NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/* 场景边框：选中使显示 */
	frame = Sprite::create("frame.png");
	frame->setPosition(Vec2(200, 500)); /* 默认情况下选择场景1 */
	frame->setVisible(true); 
	this->addChild(frame, 0);

#pragma endregion

    return true;
}

/* 高亮被选择的游戏场景 */
void SelectBackgroundScene::bgSelectedCallback(Ref* pSender, int option) 
{
	switch (option)
	{
		case 1:
			frame->setPosition(Vec2(200, 500));
			break;
		case 2:
			frame->setPosition(Vec2(700, 500));
			break;
		case 3:
			frame->setPosition(Vec2(200, 200));
			break;
		case 4:
			frame->setPosition(Vec2(700, 200));
			break;
		default:
			break;
	}
	frame->setVisible(true);
}

/* 开始游戏 */
void SelectBackgroundScene::startGame(Ref * pSender)
{
	/* Todo：美工人员请替换这里的转场特效 */
	float t = 1.2f;
	auto newScene = ExampleGameScene::createScene();
	auto replacesense = CCTransitionPageTurn::create(t, newScene, false);
	Director::sharedDirector()->replaceScene(replacesense);
}
