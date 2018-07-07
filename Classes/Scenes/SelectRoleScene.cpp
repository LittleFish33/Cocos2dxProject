#include "SelectRoleScene.h"
#include "SimpleAudioEngine.h"
#include "WelcomeScene.h"
#include "ShareSingleton.h"
#include "SelectBackgroundScene.h"
#include <stdlib.h>

using namespace CocosDenshion;


Scene* SelectRoleScene::createScene()
{
    return SelectRoleScene::create();
}

/* ���ļ�������ʱ����ӡ���õĴ�����Ϣ�����Ƿֶδ��� */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SelectRoleSceneScene.cpp\n");
}

/* ��ʼ���������� */
bool SelectRoleScene::init()
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
	/* ����Ľ�ɫ�ı�����������Ϊ�˻�����ܵĹ���������ѡ�ý�ɫ֮���滻��Щ������ */
	/*��Ϸ����*/
	auto bg = Sprite::create("bg/selectRoleSceneBackground.png");
	bg->setPosition(visibleSize / 2);
	addChild(bg, 0);
	
	/* ��ѡ��ɫ1 */
	roleItem1 = MenuItemImage::create(
		"role/role1-Goku.png",
		"role/role1-Goku.png",
		CC_CALLBACK_1(SelectRoleScene::roleSelectedCallback, this, '1'));
	roleItem1->setPosition(Vec2(400, 500));
	/* ��ѡ��ɫ2 */
	roleItem2 = MenuItemImage::create(
		"role/role2-Vegeta.png",
		"role/role2-Vegeta.png",
		CC_CALLBACK_1(SelectRoleScene::roleSelectedCallback, this, '2'));
	roleItem2->setPosition(Vec2(600, 500));
	/* ��ѡ��ɫ3 */
	roleItem3 = MenuItemImage::create(
		"role/role3-Kid_Buu.png",
		"role/role3-Kid_Buu.png",
		CC_CALLBACK_1(SelectRoleScene::roleSelectedCallback, this, '3'));
	roleItem3->setPosition(Vec2(400, 300));
	/* ��ѡ��ɫ4 */
	roleItem4 = MenuItemImage::create(
		"role/role4-Frieza.png",
		"role/role4-Frieza.png",
		CC_CALLBACK_1(SelectRoleScene::roleSelectedCallback, this, '4'));
	roleItem4->setPosition(Vec2(600, 300));
	
	/* ȷ����ť */
	player1ConfirmItem = MenuItemImage::create(
		"button/confirm-normal.png",
		"button/confirm-selected.png",
		CC_CALLBACK_1(SelectRoleScene::confirmCallback, this, '1'));
	player1ConfirmItem->setPosition(Vec2(850, 100));
	player1ConfirmItem->setVisible(false);

	player2ConfirmItem = MenuItemImage::create(
		"button/confirm-normal.png",
		"button/confirm-selected.png",
		CC_CALLBACK_1(SelectRoleScene::confirmCallback, this, '2'));
	player2ConfirmItem->setPosition(Vec2(150, 100));
	player2ConfirmItem->setVisible(false);

	/* �ص����˵���Ŧ */
	backItem = MenuItemImage::create(
		"button/back-normal.png",
		"button/back-selected.png",
		CC_CALLBACK_1(SelectRoleScene::menuBackCallback, this));
	backItem->setPosition(Vec2(500, 100));

	/*xѡ���ɫ����*/
	auto chooseRole = Sprite::create("label/ChooseRole.png");
	chooseRole->setPosition(Vec2(512, 680));
	this->addChild(chooseRole, 0);

	auto menu = Menu::create(roleItem1, roleItem2, roleItem3, roleItem4, backItem, player1ConfirmItem, player2ConfirmItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/*�����ǽ�ɫ1,2��ͼƬ*/
	auto role1 = Sprite::create("role/role-1.png");
	auto role2 = Sprite::create("role/role-2.png");
	role1->setPosition(Vec2(850, 500));
	role2->setPosition(Vec2(150, 500));
	addChild(role1, 1);
	addChild(role2, 1);

	/* ����Ϸ��ɫȷ���� ������ʾѡ��*/
    role1Selected = Sprite::create("role/roleSelected.png");
	role1Selected->setPosition(Vec2(850, 300));
	role1Selected->setVisible(false);
	this->addChild(role1Selected, 2);
	
    role2Selected = Sprite::create("role/roleSelected.png");
	role2Selected->setPosition(Vec2(150, 300));
	role2Selected->setVisible(false);
	this->addChild(role2Selected, 2);

	/* ����ѡ����һ����ɫ֮�󣬽�����ʾ���ý�ɫ�Ĵ�ͼ�����½ǻ����½ǣ��ڴ�֮ǰ��ͼƬ�ǲ��ɼ��� */
	/* ��ѡ��ɫ1 */
	roleItem1_big = Sprite::create("role/role1-big-Goku.png");
	roleItem1_big->setPosition(Vec2(0, 0));
	roleItem1_big->setVisible(false);
	this->addChild(roleItem1_big, 0);

	roleItem2_big = Sprite::create("role/role2-big-Vegeta.png");
	roleItem2_big->setPosition(Vec2(0, 0));
	roleItem2_big->setVisible(false);
	this->addChild(roleItem2_big, 0);

	roleItem3_big = Sprite::create("role/role3-big-Kid_Buu.png");
	roleItem3_big->setPosition(Vec2(150, 300));
	roleItem3_big->setVisible(false);
	this->addChild(roleItem3_big, 0);

	roleItem4_big = Sprite::create("role/role4-big-Frieza.png");
	roleItem4_big->setPosition(Vec2(850, 300));
	roleItem4_big->setVisible(false);
	this->addChild(roleItem4_big, 0);

	/* P1��ǩ��P2��ǩ����δѡ��״̬�ǲ��ɼ��� */
	p1Sprite = Sprite::create("role/p1.png");
	p1Sprite->setPosition(Vec2(0, 0));
	p1Sprite->setOpacity(200);
	p1Sprite->setVisible(false);
	this->addChild(p1Sprite, 2);

	p2Sprite = Sprite::create("role/p2.png");
	p2Sprite->setPosition(Vec2(400, 500));
	p2Sprite->setOpacity(200);
	p2Sprite->setVisible(false);
	this->addChild(p2Sprite, 2);
	
#pragma endregion

	/* �������Ӧ������Ϊ�˷��㿪��ʱʹ�ã�ʵ��û������*/
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(SelectRoleScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

/* ���ػ�ӭ���� */
void SelectRoleScene::menuBackCallback(Ref* pSender)
{
	float t = 1.2f;
	if (ShareSingleton::GetInstance()->controlVoice)
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);
	auto newScene = WelcomeScene::createScene();
	auto replacesense = CCTransitionFade::create(t, newScene);
	Director::sharedDirector()->replaceScene(replacesense);
}

/* ѡ���ɫ */
void SelectRoleScene::roleSelectedCallback(Ref* pSender, char option)
{
	if (ShareSingleton::GetInstance()->controlVoice)
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);

	if (!player1Selected) { /* ��ǰ��Ϊplayer1ѡ���ɫ */
		invisibleRolesBig();
		switch (option) /* �ж�ѡ�������һ����ɫ */
		{
		case '1':
			p1Sprite->setPosition(400, 500);	/* ����p1��ǩ��λ�� */
			roleItem1_big->setPosition(850, 300); /* ������ѡ��ɫ�Ĵ�ͼ��λ�� */
			roleItem1_big->setVisible(true);
			roleItem2_big->setVisible(false);
			roleItem3_big->setVisible(false);
			roleItem4_big->setVisible(false);

			/////////////////////////////////////////////// qiuyihao
			player1Name = "Goku";    /*��¼ѡ��Ľ�ɫ��*/

			alreadySelected = 1;  /* �����Ѿ�ѡ��Ľ�ɫ��ţ�������һ�����ѡ����ͬ���Ľ�ɫ */
			break;
		case '2':
			p1Sprite->setPosition(600, 500);
			roleItem2_big->setPosition(850, 300);
			roleItem1_big->setVisible(false);
			roleItem2_big->setVisible(true);
			roleItem3_big->setVisible(false);
			roleItem4_big->setVisible(false);

			player1Name = "Vegeta";
			alreadySelected = 2;
			break;
		case '3':
			p1Sprite->setPosition(400, 300);
			roleItem3_big->setPosition(850, 300);
			roleItem1_big->setVisible(false);
			roleItem2_big->setVisible(false);
			roleItem3_big->setVisible(true);
			roleItem4_big->setVisible(false);

			player1Name = "Kid_Buu";

			alreadySelected = 3;
			break;
		case '4':
			p1Sprite->setPosition(600, 300);
			roleItem4_big->setPosition(850, 300);
			roleItem1_big->setVisible(false);
			roleItem2_big->setVisible(false);
			roleItem3_big->setVisible(false);
			roleItem4_big->setVisible(true);

			player1Name = "Frieza";

			alreadySelected = 4;
			break;
		default:
			break;
		}
		p1Sprite->setVisible(true); /* ���ñ�ǩ�ɼ� */
		player1ConfirmItem->setVisible(true); /* ����ȷ����ť�ɼ� */
	}
	else { /* ��ǰ��Ϊplayer2ѡ���ɫ */
		if (option - '0' == alreadySelected) { /* �ж�player1��player2�ǲ���ѡ������ͬ��������ɫ */
			return;
		}
		invisibleRolesBig();
		switch (option)/* �ж�ѡ�������һ����ɫ */
		{
		case '1':
			p2Sprite->setPosition(400, 500);  /* ����p2��ǩ��λ�� */
			roleItem1_big->setPosition(150, 300); /* ������ѡ��ɫ�Ĵ�ͼ��λ�� */
			roleItem1_big->setVisible(true);
			player2Name = "Goku";
			break;
		case '2':
			p2Sprite->setPosition(600, 500);
			roleItem2_big->setPosition(150, 300);
			roleItem2_big->setVisible(true);
			player2Name = "Vegeta";
			break;
		case '3':
			p2Sprite->setPosition(400, 300);
			roleItem3_big->setPosition(150, 300);
			roleItem3_big->setVisible(true);
			player2Name = "Kid_Buu";
			break;
		case '4':
			p2Sprite->setPosition(600, 300);
			roleItem4_big->setPosition(150, 300);
			roleItem4_big->setVisible(true);
			player2Name = "Frieza";
			break;
		default:
			break;
		}
		p2Sprite->setVisible(true);
		player2ConfirmItem->setVisible(true);
	}
}

/* �������Ӧ������Ϊ�˷��㿪��ʱʹ�ã�ʵ��û������*/
bool SelectRoleScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	CCLOG("%f %f\n", touch->getLocation().x, touch->getLocation().y);
	return true;
}


/* ���أ�����player1�Ѿ�ѡ�õĽ�ɫ��������ɫ��ͼ */
void SelectRoleScene::invisibleRolesBig()
{
	switch (alreadySelected)
	{
		case 1:
			roleItem2_big->setVisible(false);
			roleItem3_big->setVisible(false);
			roleItem4_big->setVisible(false);
			break;
		case 2:
			roleItem1_big->setVisible(false);
			roleItem3_big->setVisible(false);
			roleItem4_big->setVisible(false);
			break;
		case 3:
			roleItem1_big->setVisible(false);
			roleItem2_big->setVisible(false);
			roleItem4_big->setVisible(false);
			break;
		case 4:
			roleItem1_big->setVisible(false);
			roleItem2_big->setVisible(false);
			roleItem3_big->setVisible(false);
			break;
		default:
			break;
	}
}


/* ȷ����ɫ */
void SelectRoleScene::confirmCallback(Ref* pSender, char option)
{
	auto particle = ParticleFlower::create();
	if (ShareSingleton::GetInstance()->controlVoice)
		SimpleAudioEngine::getInstance()->playEffect("music/ClickCamera.wav", false, 1.0f, 0.0f, 1.0f);
	switch (option)
	{
	case '1':
		player1Selected = true;
		role1Selected->setVisible(true);
		return;
	case '2':
		role2Selected->setVisible(true);
		break;
	default:
		return;
	}


	/*��ѡ��õĽ�ɫ�����빲����ShareSingleton */
	ShareSingleton::GetInstance()->player1 = player1Name;
	ShareSingleton::GetInstance()->player2 = player2Name;

	/* ���play2Ҳ�Ѿ�ѡ��ý�ɫ�ˣ���ô������Ϸ����ѡ����棨�����Թ��˲��ܷ���switch�������case2 ֱ��break�� */
	float t = 1.2f;
	auto newScene = SelectBackgroundScene::createScene();
	auto replacesense = CCTransitionFade::create(t, newScene);
	Director::sharedDirector()->replaceScene(replacesense);
}

