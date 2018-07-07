#include "OperatingInstructionScene.h"
#include "SimpleAudioEngine.h"
#include "SelectRoleScene.h"
#include "../ShareSingleton.h"
#include "WelcomeScene.h"
using namespace CocosDenshion;

cocos2d::Scene * OperatingInstructionScene::createScene()
{
	log("create setting scene");
	return OperatingInstructionScene::create();
}

/*  初始化场景元素 */
bool OperatingInstructionScene::init()
{

#pragma region Cocos2dx自动生成的内容：一些基本配置

	if (!Scene::init())
	{
		log("Operating InstructionScene wrong");

		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	log("setting scene");

#pragma endregion

#pragma region 背景图片
	auto bg = Sprite::create("bg/OperatingInstructionSceneBackground.png");
	bg->setPosition(visibleSize / 2);
	addChild(bg, 0);
#pragma endregion 

#pragma region 创建 返回按钮以及添加回调
	
	auto returnItem = MenuItemImage::create(
		"button/return-normal.png",
		"button/return-selected.png",
		CC_CALLBACK_1(OperatingInstructionScene::WelcomeSceneCallback, this)
	);
	returnItem->setPosition(Vec2(900, 200));

#pragma endregion

	auto Menu = Menu::create(returnItem, NULL);
	Menu->setPosition(Vec2::ZERO);
	addChild(Menu, 0);

	return true;
}

void OperatingInstructionScene::WelcomeSceneCallback(Ref * pSender)
{
	float t = 0.8f;
	if (ShareSingleton::GetInstance()->controlVoice)
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);
	auto newScene = WelcomeScene::createScene();
	auto replacesense = CCTransitionFade::create(t, newScene);

	Director::sharedDirector()->replaceScene(replacesense);
}

