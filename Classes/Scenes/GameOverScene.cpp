#include "GameOverScene.h"
#include "cocos2d.h"
#include "ExampleGameScene.h"
#include "SelectRoleScene.h"
#include "WelcomeScene.h"
#include "ShareSingleton.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

/*��ͣҳ��Ĵ��� ������ǰ��Ϸ������ͼ��Ϊ��������ͣ������Ȼ����ֲ˵���ť*/
cocos2d::Scene * GameOverScene::CreateScene(RenderTexture * sqr)
{
	Scene *scene = Scene::create();
	GameOverScene *layer = GameOverScene::create();
	scene->addChild(layer, 1);
	/*���Ӳ��֣�ʹ��Game�����н�ͼ��sqr����ͼƬ����Sprite
	����Sprite��ӵ�GameOverScene��������
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

bool GameOverScene::init()
{
#pragma region Cocos2dx�Զ����ɵ����ݣ�һЩ��������

	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

#pragma endregion

#pragma region  ��Ϸ������ǩ
	auto GameOverImage = CCMenuItemImage::create("label/GameOver.png", "button/GameOver/png");
	GameOverImage->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 + 150));

#pragma endregion




#pragma region ���¿�ʼ��Ϸ��ť
	/*���¿�ʼ��Ϸ��ť*/
	RestartGameItem = CCMenuItemImage::create(
		"button/restart-normal.png",
		"button/restart-selected.png",
		this,
		menu_selector(GameOverScene::RestartGameCallback)
	);
	RestartGameItem->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 3));

#pragma endregion


#pragma region ѡ���ɫ��ť
	/*ѡ���ɫ��ť*/
	ChooseRoleSceneItem = CCMenuItemImage::create(
		"button/chooseRole-normal.png",
		"button/chooseRole-selected.png",
		this,
		menu_selector(GameOverScene::ReturnToChooseRoleSceneCallback)
	);
	ChooseRoleSceneItem->setPosition(Vec2(2 * visibleSize.width / 3, visibleSize.height / 3 ));

#pragma endregion

#pragma region �˳���Ϸ��ť
	/*�˳���Ϸ��ť*/
	QuitGameItem = CCMenuItemImage::create(
		"button/close-normal.png",
		"button/close-selected.png",
		this,
		menu_selector(GameOverScene::QuiteGameCallback)
	);
	QuitGameItem->setPosition(ccp(visibleSize.width / 3, visibleSize.height / 3 - 70));

#pragma endregion


#pragma region ���ز˵���ť

	/*���ز˵���ť*/
	ReturnToMenuSceneItem = CCMenuItemImage::create(
		"button/back2-normal.png",
		"button/back2-selected.png",
		this,
		menu_selector(GameOverScene::ReturnToMenuSceneCallback)
	);
	ReturnToMenuSceneItem->setPosition(Vec2(2 * visibleSize.width / 3, visibleSize.height / 3 - 70));

	Menu* pMenu = Menu::create(GameOverImage,ChooseRoleSceneItem, RestartGameItem, QuitGameItem, ReturnToMenuSceneItem, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 2);

#pragma endregion


	return true;
}

/*���ز˵���ť�Ļص�*/
void GameOverScene::ReturnToMenuSceneCallback(Object * pSender)
{
	if (ShareSingleton::GetInstance()->controlVoice)
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);

	float t = 1.0f;
	auto newScene = WelcomeScene::createScene();
	auto replacesense = TransitionFade::create(t, newScene);
	Director::sharedDirector()->replaceScene(replacesense);
}

/*������Ϸ�Ļص�*/
void GameOverScene::QuiteGameCallback(Object * pSender)
{
	if (ShareSingleton::GetInstance()->controlVoice)
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);

	Director::sharedDirector()->end();
}

void GameOverScene::ReturnToChooseRoleSceneCallback(Object * pSender)
{
	float t = 1.0f;
	auto newScene = SelectRoleScene::createScene();
	auto replacesense = TransitionFade::create(t, newScene);
	Director::sharedDirector()->replaceScene(replacesense);
}

void GameOverScene::RestartGameCallback(Object * pSender)
{
	float t = 1.0f;
	if (ShareSingleton::GetInstance()->controlVoice)
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);

	auto newScene = ExampleGameScene::createScene();
	auto replacesense = TransitionFade::create(t, newScene);
	Director::sharedDirector()->replaceScene(replacesense);
}


