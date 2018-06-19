#include "WelcomeScene.h"
#include "SimpleAudioEngine.h"

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


#pragma region UI����

	/* Todo��������Ա�����������ΪWelcomeScene���UI��������� */

#pragma endregion


#pragma region ��ʼ��Ϸ��ť

	/* Todo��������Ա�뽫�����ͼƬ�滻Ϊ��ѡ���زĺͰ������Ҫ����λ�� */
	auto startItem = MenuItemImage::create(
		"start-normal.png",
		"start-selected.png",
		CC_CALLBACK_1(WelcomeScene::startGameCallback, this));

	startItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 100));
	
	
#pragma endregion


#pragma region ������Ϸ��ť

	/* Todo��������Ա�뽫�����ͼƬ�滻Ϊ��ѡ���زĺͰ������Ҫ����λ�� */
	auto closeItem = MenuItemImage::create(
		"close-normal.png",
		"close-selected.png",
		CC_CALLBACK_1(WelcomeScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

#pragma endregion

	auto menu = Menu::create(startItem, closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
    return true;
}

/* �ر���Ϸ */
void WelcomeScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
}

void WelcomeScene::startGameCallback(Ref* pSender)
{
	float t = 1.2f;
	auto newScene = SelectRoleScene::createScene();
	auto replacesense = CCTransitionPageTurn::create(t, newScene, false);
	Director::sharedDirector()->replaceScene(replacesense);
}





