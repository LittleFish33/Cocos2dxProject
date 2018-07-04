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

/*  ��ʼ������Ԫ�� */
bool GameSettingScene::init()
{

#pragma region Cocos2dx�Զ����ɵ����ݣ�һЩ��������

	if (!Scene::init())
	{
		log("setting scene wrong");

		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	log("setting scene");

#pragma endregion

#pragma region ����ͼƬ
	auto bg = Sprite::create("bg/GameSettingSceneBackground.png");
	bg->setPosition(visibleSize / 2);
	addChild(bg, 0);
#pragma endregion 

#pragma region �������Ʊ������ְ�ť�Լ���ӻص�
	openOrCloseVoiceState = true;
	bgmItem = MenuItemImage::create(
		"setting/closeBgm-normal.png",
		"setting/closeBgm-selected.png",
		CC_CALLBACK_1(GameSettingScene::controlVoiceCallback, this)
	);
	bgmItem->setPosition(Vec2(200, 300));

#pragma endregion


#pragma region ֱ�ӿ�ʼ��Ϸ������ѡ����Ϸ����
	
	startGameItem = MenuItemImage::create(
		"setting/setting-start-normal.png",
		"setting/setting-start-selected.png",
		CC_CALLBACK_1(GameSettingScene::startGameCallback, this)
	);
	startGameItem->setPosition(Vec2(200, 240));

#pragma endregion


#pragma region ������Ϸ
	
	aboutGameItem = MenuItemImage::create(
		"setting/aboutGame-normal.png",
		"setting/aboutGame-selected.png",
		CC_CALLBACK_1(GameSettingScene::aboutGameCallback, this)
	);
	aboutGameItem->setPosition(Vec2(200, 180));

#pragma endregion


#pragma region ��������˵�

	auto settingMenu = Menu::create(bgmItem, startGameItem, aboutGameItem, NULL);
	settingMenu->setPosition(Vec2::ZERO);
	addChild(settingMenu, 0);

#pragma endregion


#pragma region ����������
	Sprite* wukong = Sprite::create("setting/SunWuKong.png");
	wukong->setPosition(Vec2(500, 200));
	addChild(wukong, 0);
#pragma endregion 


#pragma region  ��ӶԻ���

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


/*���Ʊ������ֻص��������򿪻��߹ر� */
void GameSettingScene::controlVoiceCallback(Ref * pSender)
{
	if (ShareSingleton::GetInstance()->controlVoice)
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);

	auto audio = SimpleAudioEngine::getInstance();
	/*�����رձ�������*/
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
	/*�����򿪱�������*/
	else {
		/*Ԥ���ز�ѭ�����ű�������*/
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		SimpleAudioEngine::getInstance()->resumeAllEffects();
		ShareSingleton::GetInstance()->controlVoice = true;  //�޸�ȫ�ֱ������Ա�ҳ����������Ʊ���һ�� 
		bgmItem->setNormalImage(Sprite::create("setting/closeBgm-normal.png"));
		bgmItem->setSelectedImage(Sprite::create("setting/closeBgm-selected.png"));

		openOrCloseVoiceState = true;

		openBgmDialogue->setVisible(true);
		closeBgmDialogue->setVisible(false);
		aboutGameDialogue->setVisible(false);
		welcomeDialogue->setVisible(false);
	}
}
/*��ʼ��Ϸ������ѡ���ɫ����*/
void GameSettingScene::startGameCallback(Ref * pSender)
{
	float t = 0.8f;
	if (ShareSingleton::GetInstance()->controlVoice)
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);
	auto newScene = SelectRoleScene::createScene();
	auto replacesense = CCTransitionFade::create(t, newScene);

	Director::sharedDirector()->replaceScene(replacesense);
}

/*������Ϸ���޸ĶԻ���*/
void GameSettingScene::aboutGameCallback(Ref * pSender)
{
	if (ShareSingleton::GetInstance()->controlVoice)
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);
	openBgmDialogue->setVisible(false);
	closeBgmDialogue->setVisible(false);
	aboutGameDialogue->setVisible(true);
	welcomeDialogue->setVisible(false);

}
