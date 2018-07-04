#include "GameSettingScene.h"
#include "SimpleAudioEngine.h"
#include "SelectRoleScene.h"
#include "../ShareSingleton.h"
using namespace CocosDenshion;

cocos2d::Scene * GameSettingScene::createScene()
{
	log("create setting scene");
	return GameSettingScene::create();
}

/*  初始化场景元素 */
bool GameSettingScene::init()
{

#pragma region Cocos2dx自动生成的内容：一些基本配置

	if (!Scene::init())
	{
		log("setting scene wrong");

		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	log("setting scene");

#pragma endregion

#pragma region 背景图片
	auto bg = Sprite::create("bg/GameSettingSceneBackground.png");
	bg->setPosition(visibleSize / 2);
	addChild(bg, 0);
#pragma endregion 

#pragma region 创建控制背景音乐按钮以及添加回调
	openOrCloseVoiceState = true;
	bgmItem = MenuItemImage::create(
		"setting/closeBgm-normal.png",
		"setting/closeBgm-selected.png",
		CC_CALLBACK_1(GameSettingScene::controlVoiceCallback, this)
	);
	bgmItem->setPosition(Vec2(200, 300));

#pragma endregion


#pragma region 直接开始游戏，进入选择游戏界面
	
	startGameItem = MenuItemImage::create(
		"setting/setting-start-normal.png",
		"setting/setting-start-selected.png",
		CC_CALLBACK_1(GameSettingScene::startGameCallback, this)
	);
	startGameItem->setPosition(Vec2(200, 240));

#pragma endregion


#pragma region 关于游戏
	
	aboutGameItem = MenuItemImage::create(
		"setting/aboutGame-normal.png",
		"setting/aboutGame-selected.png",
		CC_CALLBACK_1(GameSettingScene::aboutGameCallback, this)
	);
	aboutGameItem->setPosition(Vec2(200, 180));

#pragma endregion


#pragma region 创建点击菜单

	auto settingMenu = Menu::create(bgmItem, startGameItem, aboutGameItem, NULL);
	settingMenu->setPosition(Vec2::ZERO);
	addChild(settingMenu, 0);

#pragma endregion


#pragma region 添加悟空人物
	Sprite* wukong = Sprite::create("setting/SunWuKong.png");
	wukong->setPosition(Vec2(500, 200));
	addChild(wukong, 0);
#pragma endregion 


#pragma region  添加对话框

	welcomeDialogue = Sprite::create("setting/setting-welcome-Dialogue.png");
	welcomeDialogue->setPosition(Vec2(700, 400));
	addChild(welcomeDialogue, 1);

	closeBgmDialogue = Sprite::create("setting/closeBgm-Dialogue.png");
	closeBgmDialogue->setPosition(Vec2(700, 400));
	closeBgmDialogue->setVisible(false);
	addChild(closeBgmDialogue, 1);

	openBgmDialogue = Sprite::create("setting/openBgm-Dialogue.png");
	openBgmDialogue->setPosition(Vec2(700, 400));
	openBgmDialogue->setVisible(false);
	addChild(openBgmDialogue, 1);

	aboutGameDialogue = Sprite::create("setting/aboutGame-Dialogue.png");
	aboutGameDialogue->setPosition(Vec2(700, 400));
	aboutGameDialogue->setVisible(false);
	addChild(aboutGameDialogue, 1);
	
#pragma endregion


	return true;
}


/*控制背景音乐回调函数，打开或者关闭 */
void GameSettingScene::controlVoiceCallback(Ref * pSender)
{
	if (ShareSingleton::GetInstance()->controlVoice)
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);

	auto audio = SimpleAudioEngine::getInstance();
	/*即将关闭背景音乐*/
	if (openOrCloseVoiceState) {
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		SimpleAudioEngine::getInstance()->pauseAllEffects();
		ShareSingleton::GetInstance()->controlVoice = false;
		bgmItem->setNormalImage(Sprite::create("setting/openBgm-normal.png"));
		bgmItem->setSelectedImage(Sprite::create("setting/openBgm-selected.png"));
		openOrCloseVoiceState = false;

		openBgmDialogue->setVisible(false);
		closeBgmDialogue->setVisible(true);
		aboutGameDialogue->setVisible(false);
		welcomeDialogue->setVisible(false);
		
	}
	/*即将打开背景音乐*/
	else {
		/*预加载并循环播放背景音乐*/
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		SimpleAudioEngine::getInstance()->resumeAllEffects();
		ShareSingleton::GetInstance()->controlVoice = true;  //修改全局变量，以便页面间声音控制保持一致 
		bgmItem->setNormalImage(Sprite::create("setting/closeBgm-normal.png"));
		bgmItem->setSelectedImage(Sprite::create("setting/closeBgm-selected.png"));

		openOrCloseVoiceState = true;

		openBgmDialogue->setVisible(true);
		closeBgmDialogue->setVisible(false);
		aboutGameDialogue->setVisible(false);
		welcomeDialogue->setVisible(false);
	}
}
/*开始游戏，进入选择角色界面*/
void GameSettingScene::startGameCallback(Ref * pSender)
{
	float t = 0.8f;
	if (ShareSingleton::GetInstance()->controlVoice)
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);
	auto newScene = SelectRoleScene::createScene();
	auto replacesense = CCTransitionFade::create(t, newScene);

	Director::sharedDirector()->replaceScene(replacesense);
}

/*关于游戏，修改对话框*/
void GameSettingScene::aboutGameCallback(Ref * pSender)
{
	if (ShareSingleton::GetInstance()->controlVoice)
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);
	openBgmDialogue->setVisible(false);
	closeBgmDialogue->setVisible(false);
	aboutGameDialogue->setVisible(true);
	welcomeDialogue->setVisible(false);

}
