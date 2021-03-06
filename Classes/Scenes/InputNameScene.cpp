#include "InputNameScene.h"
#include "SimpleAudioEngine.h"
#include "GameSettingScene.h"
#include "ExampleGameScene.h"
#include "../ShareSingleton.h"
using namespace CocosDenshion;
USING_NS_CC;

Scene* InputNameScene::createScene()
{
    return InputNameScene::create();
}

/* 当文件不存在时，打印有用的错误消息而不是分段错误 */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in InputNameSceneScene.cpp\n");
}

/* 初始化场景函数 */
bool InputNameScene::init()
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

#pragma endregion

#pragma region  预添加音效和背景音乐

	auto audio = SimpleAudioEngine::getInstance();
	/*预加载并循环播放背景音乐*/
	audio->playBackgroundMusic("music/InputNameSceneBgm.mp3", true);
	audio->setBackgroundMusicVolume(0.80);

	/*预加载音效*/
	audio->preloadEffect("music/ClickCamera.wav");
	audio->setEffectsVolume(0.80);

#pragma endregion

#pragma region 文本输入
	/* VS */
	vs = Label::createWithTTF("VS", "fonts/comicsansms.ttf", 60);
	vs->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	vs->setColor(Color3B(255, 255, 0));
	addChild(vs, 1);

	/* 两个编辑框 */
	Size boxSize = CCSizeMake(100, 45);	

	editBox1 = EditBox::create(boxSize, "green.png");
	editBox2 = EditBox::create(boxSize, "green.png");
	editBox1->setPosition(Vec2(visibleSize.width / 2 + 200, visibleSize.height / 2));
	editBox2->setPosition(Vec2(visibleSize.width / 2 - 200, visibleSize.height / 2));

	// 默认字体相关
	editBox1->setPlaceHolder("Player1");
	editBox2->setPlaceHolder("Player2");
	editBox1->setPlaceholderFontName("comicsansms");
	editBox2->setPlaceholderFontName("comicsansms");
	editBox1->setPlaceholderFontColor(Color3B::RED);
	editBox2->setPlaceholderFontColor(Color3B::RED);
	editBox1->setPlaceholderFontSize(32);
	editBox2->setPlaceholderFontSize(32);

	// 编辑框文本相关
	editBox1->setFontName("comicsansms");
	editBox2->setFontName("comicsansms");
	editBox1->setFontColor(Color3B::RED);
	editBox2->setFontColor(Color3B::RED);
	editBox1->setFontSize(36);
	editBox2->setFontSize(36);

	this->addChild(editBox1, 2);
	this->addChild(editBox2, 2);
#pragma endregion

#pragma region 确认按钮
	/* 确定按钮 */
	nameConfirmItem = MenuItemImage::create(
		"button/confirm-normal.png",
		"button/confirm-selected.png",
		CC_CALLBACK_1(InputNameScene::confirmCallback, this));

	nameConfirmItem->setPosition(Vec2(512, 250));
	//addChild(nameConfirmItem);
	auto menu = Menu::create(nameConfirmItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
#pragma endregion

    return true;
}

/* 确定角色名称 */
void InputNameScene::confirmCallback(Ref* pSender)
{
	CCLOG("yiingxuanzhong");
	auto particle = ParticleFlower::create();
	SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);

	ShareSingleton::GetInstance()->player1 = editBox1->getText();
	ShareSingleton::GetInstance()->player2 = editBox2->getText();

	float t = 1.2f;
	auto newScene = ExampleGameScene::createScene();
	auto replacesense = CCTransitionFade::create(t, newScene);
	Director::sharedDirector()->replaceScene(replacesense);
	return;
}
