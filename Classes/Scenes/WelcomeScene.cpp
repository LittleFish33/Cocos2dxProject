#include "WelcomeScene.h"
#include "SimpleAudioEngine.h"
#include "GameSettingScene.h"
#include "ShareSingleton.h"
using namespace CocosDenshion;
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


#pragma region UI界面 背景图片
	
	auto bg = Sprite::create("bg/startSceneBackground.png");
	bg->setPosition(visibleSize / 2);
	addChild(bg, 0);

   /* 添加悟空人物 */
	Sprite* wukong = Sprite::create("setting/SunWuKong.png");
	wukong->setPosition(Vec2(250, 200));
	addChild(wukong, 0);

	/* 添加对话框*/
	auto welcomeDialogue = Sprite::create("setting/welcome-Dialogue.png");
	welcomeDialogue->setPosition(Vec2(450, 400));
	addChild(welcomeDialogue, 1);

#pragma endregion



#pragma region  预添加音效和背景音乐

	auto audio = SimpleAudioEngine::getInstance();
	/*预加载并循环播放背景音乐*/
	if(ShareSingleton::GetInstance()->controlVoice)
		audio->playBackgroundMusic("music/WelcomeSceneBgm.mp3", true);
	audio->setBackgroundMusicVolume(0.80);

	/*预加载音效*/
	audio->preloadEffect("music/ClickCamera.wav");
	audio->setEffectsVolume(0.80);

#pragma endregion


#pragma region 开始游戏按钮

	auto startItem = MenuItemImage::create(
		"button/start-normal.png",
		"button/start-selected.png",
		CC_CALLBACK_1(WelcomeScene::startGameCallback, this));

	//startItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3 + 20));
	startItem->setPosition(Vec2(800, 300));
	
#pragma endregion

#pragma region 游戏设置按钮

	auto settingItem = MenuItemImage::create(
		"button/setting-normal.png",
		"button/setting-selected.png",
		CC_CALLBACK_1(WelcomeScene::settingGameCallback, this)
	);
	//settingItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3 - 60));
	settingItem->setPosition(Vec2(800, 210));

#pragma endregion

#pragma region 结束游戏按钮

	auto closeItem = MenuItemImage::create(
		"button/close-normal.png",
		"button/close-selected.png",
		CC_CALLBACK_1(WelcomeScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3 - 140));
	closeItem->setPosition(Vec2(800, 120));

#pragma endregion

	auto menu = Menu::create(startItem, closeItem, settingItem,  NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
    return true;
}

/* 关闭游戏 */
void WelcomeScene::menuCloseCallback(Ref* pSender)
{
	if (ShareSingleton::GetInstance()->controlVoice)
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);
	Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
}

void WelcomeScene::startGameCallback(Ref* pSender)
{
	if (ShareSingleton::GetInstance()->controlVoice)
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);
	
	float t = 0.8f;
	auto newScene = SelectRoleScene::createScene();
	auto replacesense = CCTransitionFade::create(t, newScene);
	Director::sharedDirector()->replaceScene(replacesense);
}

void WelcomeScene::settingGameCallback(Ref * pSender)
{
	if (ShareSingleton::GetInstance()->controlVoice)
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);
	
	float t = 0.8f;
	auto newScene = GameSettingScene::createScene();
	auto replacescene = CCTransitionFade::create(t, newScene);
	Director::sharedDirector()->replaceScene(replacescene);

}






