#include "GamePauseScene.h"
#include "cocos2d.h"
#include "WelcomeScene.h"
#include "SimpleAudioEngine.h"
#include "ShareSingleton.h"
using namespace CocosDenshion;

/*暂停页面的创建 ，将当前游戏场景截图作为纹理传入暂停场景，然后出现菜单按钮*/
cocos2d::Scene * GamePauseScene::CreateScene(RenderTexture * sqr)
{
	Scene *scene = Scene::create();
	GamePauseScene *layer = GamePauseScene::create();
	scene->addChild(layer, 1);
	/*增加部分：使用Game界面中截图的sqr纹理图片创建Sprite
	并将Sprite添加到GamePauseScene场景层中
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

bool GamePauseScene::init()
{
#pragma region Cocos2dx自动生成的内容：一些基本配置

	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

#pragma endregion

#pragma region  游戏暂停标签
	auto GamePauseImage = CCMenuItemImage::create("label/GamePause.png", "button/GamePause/png");
	GamePauseImage->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 + 150));

#pragma endregion


#pragma region 继续游戏按钮
	/*继续游戏按钮*/
	ContinueGameItem = CCMenuItemImage::create(
		"button/continue-normal.png",
		"button/continue-selected.png",
		this,
		menu_selector(GamePauseScene::ContinueGameCallback)
	);
	ContinueGameItem->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 + 70));

#pragma endregion 


#pragma region 退出游戏按钮
	/*退出游戏按钮*/
	QuiteGameItem = CCMenuItemImage::create(
		"button/close-normal.png",
		"button/close-selected.png",
		this,
		menu_selector(GamePauseScene::QuiteGameCallback)
	);
	QuiteGameItem->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 - 70));

#pragma endregion


#pragma region 返回菜单按钮

	/*返回菜单按钮*/
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

/* 继续游戏按钮的回调*/
void GamePauseScene::ContinueGameCallback(Object * pSender)
{
	if (ShareSingleton::GetInstance()->controlVoice)
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);
	ShareSingleton::GetInstance()->controlPause = true;  // 图标按钮需要恢复为播放状态
	Director::sharedDirector()->popScene();
}

/*返回菜单按钮的回调*/
void GamePauseScene::ReturnToMenuSceneCallback(Object * pSender)
{
	if (ShareSingleton::GetInstance()->controlVoice)
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);
	float t = 1.0f;
	auto newScene = WelcomeScene::createScene();
	auto replacesense = TransitionFade::create(t, newScene);
	Director::sharedDirector()->replaceScene(replacesense);
}

/*结束游戏的回调*/
void GamePauseScene::QuiteGameCallback(Object * pSender)
{
	if (ShareSingleton::GetInstance()->controlVoice)
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);
	Director::sharedDirector()->end();
}


