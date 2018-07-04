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

/* ���ļ�������ʱ����ӡ���õĴ�����Ϣ�����Ƿֶδ��� */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in WelcomeSceneScene.cpp\n");
}

/* ��ʼ���������� */
bool WelcomeScene::init()
{
#pragma region Cocos2dx�Զ����ɵ����ݣ�һЩ��������

	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

#pragma endregion


#pragma region UI���� ����ͼƬ
	
	auto bg = Sprite::create("bg/startSceneBackground.png");
	bg->setPosition(visibleSize / 2);
	addChild(bg, 0);

   /* ���������� */
	Sprite* wukong = Sprite::create("setting/SunWuKong.png");
	wukong->setPosition(Vec2(250, 200));
	addChild(wukong, 0);

	/* ��ӶԻ���*/
	auto welcomeDialogue = Sprite::create("setting/welcome-Dialogue.png");
	welcomeDialogue->setPosition(Vec2(450, 400));
	addChild(welcomeDialogue, 1);

#pragma endregion



#pragma region  Ԥ�����Ч�ͱ�������

	auto audio = SimpleAudioEngine::getInstance();
	/*Ԥ���ز�ѭ�����ű�������*/
	if(ShareSingleton::GetInstance()->controlVoice)
		audio->playBackgroundMusic("music/WelcomeSceneBgm.mp3", true);
	audio->setBackgroundMusicVolume(0.80);

	/*Ԥ������Ч*/
	audio->preloadEffect("music/ClickCamera.wav");
	audio->setEffectsVolume(0.80);

#pragma endregion


#pragma region ��ʼ��Ϸ��ť

	auto startItem = MenuItemImage::create(
		"button/start-normal.png",
		"button/start-selected.png",
		CC_CALLBACK_1(WelcomeScene::startGameCallback, this));

	//startItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3 + 20));
	startItem->setPosition(Vec2(800, 300));
	
#pragma endregion

#pragma region ��Ϸ���ð�ť

	auto settingItem = MenuItemImage::create(
		"button/setting-normal.png",
		"button/setting-selected.png",
		CC_CALLBACK_1(WelcomeScene::settingGameCallback, this)
	);
	//settingItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3 - 60));
	settingItem->setPosition(Vec2(800, 210));

#pragma endregion

#pragma region ������Ϸ��ť

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

/* �ر���Ϸ */
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






