#include "SelectBackgroundScene.h"
#include "SimpleAudioEngine.h"
#include "ExampleGameScene.h"
#include "../ShareSingleton.h"
using namespace CocosDenshion;

Scene* SelectBackgroundScene::createScene()
{
    return SelectBackgroundScene::create();
}

/* ���ļ�������ʱ����ӡ���õĴ�����Ϣ�����Ƿֶδ��� */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SelectBackgroundSceneScene.cpp\n");
}

/* ��ʼ���������� */
bool SelectBackgroundScene::init()
{
#pragma region Cocos2dx�Զ����ɵ����ݣ�һЩ��������

	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

#pragma endregion


#pragma region UI����

	/* Todo��������Ա�뽫�����ͼƬ�滻Ϊ��ѡ���زĺͰ������Ҫ����λ�� */
	/*��Ϸ����*/
	auto bg = Sprite::create("bg/selectBackgroundSceneBackground.png");
	bg->setPosition(visibleSize / 2);
	addChild(bg, 0);

	/* ����ĳ����ı�����������Ϊ�˻�����ܵĹ���������ѡ�ó���֮���滻��Щ������ */
	/* ��ѡ����1 */
	bgItem1 = MenuItemImage::create(
		"bg/bg1-small.png",
		"bg/bg1-small.png",
		CC_CALLBACK_1(SelectBackgroundScene::bgSelectedCallback, this, 1));
	bgItem1->setPosition(Vec2(120, 500));
	/* ��ѡ����2 */
	bgItem2 = MenuItemImage::create(
		"bg/bg2-small.png",
		"bg/bg2-small.png",
		CC_CALLBACK_1(SelectBackgroundScene::bgSelectedCallback, this, 2));
	bgItem2->setPosition(Vec2(380, 500));
	/* ��ѡ����3 */
	bgItem3 = MenuItemImage::create(
		"bg/bg3-small.png",
		"bg/bg3-small.png",
		CC_CALLBACK_1(SelectBackgroundScene::bgSelectedCallback, this, 3));
	bgItem3->setPosition(Vec2(640, 500));
	/* ��ѡ����4 */
	bgItem4 = MenuItemImage::create(
		"bg/bg4-small.png",
		"bg/bg4-small.png",
		CC_CALLBACK_1(SelectBackgroundScene::bgSelectedCallback, this, 4));
	bgItem4->setPosition(Vec2(900, 500));
	/* ��ѡ����5 */
	bgItem5 = MenuItemImage::create(
		"bg/bg5-small.png",
		"bg/bg5-small.png",
		CC_CALLBACK_1(SelectBackgroundScene::bgSelectedCallback, this, 5));
	bgItem5->setPosition(Vec2(120, 300));
	/* ��ѡ����6 */
	bgItem6 = MenuItemImage::create(
		"bg/bg6-small.png",
		"bg/bg6-small.png",
		CC_CALLBACK_1(SelectBackgroundScene::bgSelectedCallback, this, 6));
	bgItem6->setPosition(Vec2(380, 300));
	/* ��ѡ����7 */
	bgItem7 = MenuItemImage::create(
		"bg/bg7-small.png",
		"bg/bg7-small.png",
		CC_CALLBACK_1(SelectBackgroundScene::bgSelectedCallback, this, 7));
	bgItem7->setPosition(Vec2(640, 300));
	/* ��ѡ����8 */
	bgItem8 = MenuItemImage::create(
		"bg/bg8-small.png",
		"bg/bg8-small.png",
		CC_CALLBACK_1(SelectBackgroundScene::bgSelectedCallback, this, 8));
	bgItem8->setPosition(Vec2(900, 300));


	/* ȷ����ť */
	confirmItem = MenuItemImage::create(
		"confirm-normal.png",
		"confirm-selected.png",
		CC_CALLBACK_1(SelectBackgroundScene::startGame, this));
	confirmItem->setPosition(Vec2(512, 200));

	/*ѡ���ͼ����*/
	auto chooseBg = Sprite::create("button/ChooseBackground.png");
	chooseBg->setPosition(Vec2(512, 680));
	this->addChild(chooseBg, 0);

	auto menu = Menu::create(bgItem1, bgItem2, bgItem3, bgItem4, bgItem5, bgItem6, bgItem7, bgItem8, confirmItem,  NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/* �����߿�ѡ��ʹ��ʾ */
	frame = Sprite::create("frame.png");
	frame->setPosition(Vec2(120, 495)); /* Ĭ�������ѡ�񳡾�1 */
	frame->setVisible(true); 
	this->addChild(frame, 1);

#pragma endregion

    return true;
}

/* ������ѡ�����Ϸ���� */
void SelectBackgroundScene::bgSelectedCallback(Ref* pSender, int option) 
{
	SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);
	log("%d option", option);
	switch (option)
	{
		case 1:
			frame->setPosition(Vec2(120, 495));
			selectedBackground = 1;
			break;
		case 2:
			frame->setPosition(Vec2(380, 495));
			selectedBackground = 2;
			break;
		case 3:
			frame->setPosition(Vec2(640, 495));
			selectedBackground = 3;
			break;
		case 4:
			frame->setPosition(Vec2(900, 495));
			selectedBackground = 4;
			break;
		case 5:
			frame->setPosition(Vec2(120, 300));
			selectedBackground = 5;
			break;
		case 6:
			frame->setPosition(Vec2(380, 300));
			selectedBackground = 6;
			break;
		case 7:
			frame->setPosition(Vec2(640, 300));
			selectedBackground = 7;
			break;
		case 8:
			frame->setPosition(Vec2(900, 300));
			selectedBackground = 8;
			break;
		default:
			break;
	}
	frame->setVisible(true);
}

/* ��ʼ��Ϸ */
void SelectBackgroundScene::startGame(Ref * pSender)
{
	float t = 1.2f;
	SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);
	ShareSingleton::GetInstance()->selectedBackground = this->selectedBackground;
	auto newScene = ExampleGameScene::createScene();
	auto replacesense = CCTransitionFade::create(t, newScene);
	Director::sharedDirector()->replaceScene(replacesense);

}
