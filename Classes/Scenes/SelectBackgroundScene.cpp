#include "SelectBackgroundScene.h"
#include "SimpleAudioEngine.h"
#include "ExampleGameScene.h"

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
	/* ����ĳ����ı�����������Ϊ�˻�����ܵĹ���������ѡ�ó���֮���滻��Щ������ */
	/* ��ѡ����1 */
	bgItem1 = MenuItemImage::create(
		"bg1.jpg",
		"bg1.jpg",
		CC_CALLBACK_1(SelectBackgroundScene::bgSelectedCallback, this, 1));
	bgItem1->setPosition(Vec2(200, 500));
	/* ��ѡ����2 */
	bgItem2 = MenuItemImage::create(
		"bg2.jpg",
		"bg2.jpg",
		CC_CALLBACK_1(SelectBackgroundScene::bgSelectedCallback, this, 2));
	bgItem2->setPosition(Vec2(700, 500));
	/* ��ѡ����3 */
	bgItem3 = MenuItemImage::create(
		"bg3.jpg",
		"bg3.jpg",
		CC_CALLBACK_1(SelectBackgroundScene::bgSelectedCallback, this, 3));
	bgItem3->setPosition(Vec2(200, 200));
	/* ��ѡ����4 */
	bgItem4 = MenuItemImage::create(
		"bg4.jpg",
		"bg4.jpg",
		CC_CALLBACK_1(SelectBackgroundScene::bgSelectedCallback, this, 4));
	bgItem4->setPosition(Vec2(700, 200));
	
	/* ȷ����ť */
	confirmItem = MenuItemImage::create(
		"confirm.png",
		"confirm.png",
		CC_CALLBACK_1(SelectBackgroundScene::startGame, this));
	confirmItem->setPosition(Vec2(500, 100));
	
	auto menu = Menu::create(bgItem1, bgItem2, bgItem3, bgItem4, confirmItem,  NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/* �����߿�ѡ��ʹ��ʾ */
	frame = Sprite::create("frame.png");
	frame->setPosition(Vec2(200, 500)); /* Ĭ�������ѡ�񳡾�1 */
	frame->setVisible(true); 
	this->addChild(frame, 0);

#pragma endregion

    return true;
}

/* ������ѡ�����Ϸ���� */
void SelectBackgroundScene::bgSelectedCallback(Ref* pSender, int option) 
{
	switch (option)
	{
		case 1:
			frame->setPosition(Vec2(200, 500));
			break;
		case 2:
			frame->setPosition(Vec2(700, 500));
			break;
		case 3:
			frame->setPosition(Vec2(200, 200));
			break;
		case 4:
			frame->setPosition(Vec2(700, 200));
			break;
		default:
			break;
	}
	frame->setVisible(true);
}

/* ��ʼ��Ϸ */
void SelectBackgroundScene::startGame(Ref * pSender)
{
	/* Todo��������Ա���滻�����ת����Ч */
	float t = 1.2f;
	auto newScene = ExampleGameScene::createScene();
	auto replacesense = CCTransitionPageTurn::create(t, newScene, false);
	Director::sharedDirector()->replaceScene(replacesense);
}
