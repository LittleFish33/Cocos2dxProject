#include "WelcomeScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* WelcomeScene::createScene()
{
    return WelcomeScene::create();
}

/* 当文件不存在时，打印有用的错误消息而不是分段错误 */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in WelcomeSceneScene.cpp\n");
}

/* 初始化场景函数 */
bool WelcomeScene::init()
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

	/* Todo：美工人员请在这里添加为WelcomeScene添加UI界面的美化 */

#pragma endregion


#pragma region 开始游戏按钮

	/* Todo：美工人员请将这里的图片替换为你选的素材和按你的需要设置位置 */
	auto startItem = MenuItemImage::create(
		"start-normal.png",
		"start-selected.png",
		CC_CALLBACK_1(WelcomeScene::startGameCallback, this));

	startItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 100));
	
	
#pragma endregion


#pragma region 结束游戏按钮

	/* Todo：美工人员请将这里的图片替换为你选的素材和按你的需要设置位置 */
	auto closeItem = MenuItemImage::create(
		"close-normal.png",
		"close-selected.png",
		CC_CALLBACK_1(WelcomeScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

#pragma endregion

	auto menu = Menu::create(startItem, closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
    return true;
}

/* 关闭游戏 */
void WelcomeScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
}

void WelcomeScene::startGameCallback(Ref* pSender)
{
	float t = 1.2f;
	auto newScene = SelectRoleScene::createScene();
	auto replacesense = CCTransitionPageTurn::create(t, newScene, false);
	Director::sharedDirector()->replaceScene(replacesense);
}





