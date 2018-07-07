#include "GameOverScene.h"
#include "cocos2d.h"
#include "ExampleGameScene.h"
#include "SelectRoleScene.h"
#include "WelcomeScene.h"
#include "ShareSingleton.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

/*暂停页面的创建 ，将当前游戏场景截图作为纹理传入暂停场景，然后出现菜单按钮*/
cocos2d::Scene * GameOverScene::CreateScene(RenderTexture * sqr)
{
	Scene *scene = Scene::create();
	GameOverScene *layer = GameOverScene::create();
	scene->addChild(layer, 1);
	/*增加部分：使用Game界面中截图的sqr纹理图片创建Sprite
	并将Sprite添加到GameOverScene场景层中
	得到窗口的大小*/
	Size visibleSize = Director::sharedDirector()->getVisibleSize();
	Sprite *back_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	/*放置位置,这个相对于中心位置。*/
	back_spr->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	/* 翻转，因为UI坐标和OpenGL坐标不同*/
	back_spr->setFlipY(true);
	/*图片颜色变灰色*/
	back_spr->setColor(Color3B::GRAY);
	scene->addChild(back_spr);
	return scene;

}

bool GameOverScene::init()
{
#pragma region Cocos2dx自动生成的内容：一些基本配置

	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

#pragma endregion

#pragma region  游戏结束标签
	auto GameOverImage = CCMenuItemImage::create("label/GameOver.png", "button/GameOver/png");
	GameOverImage->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 + 150));

#pragma endregion




#pragma region 重新开始游戏按钮
	/*重新开始游戏按钮*/
	RestartGameItem = CCMenuItemImage::create(
		"button/restart-normal.png",
		"button/restart-selected.png",
		this,
		menu_selector(GameOverScene::RestartGameCallback)
	);
	RestartGameItem->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 3));

#pragma endregion


#pragma region 选择角色按钮
	/*选择角色按钮*/
	ChooseRoleSceneItem = CCMenuItemImage::create(
		"button/chooseRole-normal.png",
		"button/chooseRole-selected.png",
		this,
		menu_selector(GameOverScene::ReturnToChooseRoleSceneCallback)
	);
	ChooseRoleSceneItem->setPosition(Vec2(2 * visibleSize.width / 3, visibleSize.height / 3 ));

#pragma endregion

#pragma region 退出游戏按钮
	/*退出游戏按钮*/
	QuitGameItem = CCMenuItemImage::create(
		"button/close-normal.png",
		"button/close-selected.png",
		this,
		menu_selector(GameOverScene::QuiteGameCallback)
	);
	QuitGameItem->setPosition(ccp(visibleSize.width / 3, visibleSize.height / 3 - 70));

#pragma endregion


#pragma region 返回菜单按钮

	/*返回菜单按钮*/
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

/*返回菜单按钮的回调*/
void GameOverScene::ReturnToMenuSceneCallback(Object * pSender)
{
	if (ShareSingleton::GetInstance()->controlVoice)
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);

	float t = 1.0f;
	auto newScene = WelcomeScene::createScene();
	auto replacesense = TransitionFade::create(t, newScene);
	Director::sharedDirector()->replaceScene(replacesense);
}

/*结束游戏的回调*/
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


