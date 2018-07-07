#include "GamePauseScene.h"
#include "cocos2d.h"
#include "WelcomeScene.h"
#include "SimpleAudioEngine.h"
#include "ShareSingleton.h"
using namespace CocosDenshion;

/*��ͣҳ��Ĵ��� ������ǰ��Ϸ������ͼ��Ϊ��������ͣ������Ȼ����ֲ˵���ť*/
cocos2d::Scene * GamePauseScene::CreateScene(RenderTexture * sqr)
{
	Scene *scene = Scene::create();
	GamePauseScene *layer = GamePauseScene::create();
	scene->addChild(layer, 1);
	/*���Ӳ��֣�ʹ��Game�����н�ͼ��sqr����ͼƬ����Sprite
	����Sprite��ӵ�GamePauseScene��������
	�õ����ڵĴ�С*/
	Size visibleSize = Director::sharedDirector()->getVisibleSize();
	Sprite *back_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	/*����λ��,������������λ�á�*/
	back_spr->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	/* ��ת����ΪUI�����OpenGL���겻ͬ*/
	back_spr->setFlipY(true);
	/*ͼƬ��ɫ���ɫ*/
	back_spr->setColor(Color3B::GRAY);
	scene->addChild(back_spr);
	return scene;

}

bool GamePauseScene::init()
{
#pragma region Cocos2dx�Զ����ɵ����ݣ�һЩ��������

	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

#pragma endregion

#pragma region  ��Ϸ��ͣ��ǩ
	auto GamePauseImage = CCMenuItemImage::create("label/GamePause.png", "button/GamePause/png");
	GamePauseImage->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 + 150));

#pragma endregion


#pragma region ������Ϸ��ť
	/*������Ϸ��ť*/
	ContinueGameItem = CCMenuItemImage::create(
		"button/continue-normal.png",
		"button/continue-selected.png",
		this,
		menu_selector(GamePauseScene::ContinueGameCallback)
	);
	ContinueGameItem->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 + 70));

#pragma endregion 


#pragma region �˳���Ϸ��ť
	/*�˳���Ϸ��ť*/
	QuiteGameItem = CCMenuItemImage::create(
		"button/close-normal.png",
		"button/close-selected.png",
		this,
		menu_selector(GamePauseScene::QuiteGameCallback)
	);
	QuiteGameItem->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 - 70));

#pragma endregion


#pragma region ���ز˵���ť

	/*���ز˵���ť*/
	ReturnToMenuSceneItem = CCMenuItemImage::create(
		"button/back2-normal.png",
		"button/back2-selected.png",
		this,
		menu_selector(GamePauseScene::ReturnToMenuSceneCallback)
	);
	ReturnToMenuSceneItem->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));

	Menu* pMenu = Menu::create(GamePauseImage,ContinueGameItem, QuiteGameItem, ReturnToMenuSceneItem, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 2);

#pragma endregion

	
	return true;
}

/* ������Ϸ��ť�Ļص�*/
void GamePauseScene::ContinueGameCallback(Object * pSender)
{
	if (ShareSingleton::GetInstance()->controlVoice)
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);
	ShareSingleton::GetInstance()->controlPause = true;  // ͼ�갴ť��Ҫ�ָ�Ϊ����״̬
	Director::sharedDirector()->popScene();
}

/*���ز˵���ť�Ļص�*/
void GamePauseScene::ReturnToMenuSceneCallback(Object * pSender)
{
	if (ShareSingleton::GetInstance()->controlVoice)
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);
	float t = 1.0f;
	auto newScene = WelcomeScene::createScene();
	auto replacesense = TransitionFade::create(t, newScene);
	Director::sharedDirector()->replaceScene(replacesense);
}

/*������Ϸ�Ļص�*/
void GamePauseScene::QuiteGameCallback(Object * pSender)
{
	if (ShareSingleton::GetInstance()->controlVoice)
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);
	Director::sharedDirector()->end();
}


