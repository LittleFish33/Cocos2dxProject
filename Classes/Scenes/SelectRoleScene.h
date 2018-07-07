/**************************************************************************

* Copyright: 

* Author: LittleFish

* Date: 2018-06-17

* Description: ѡ����Ϸ��ɫ����

**************************************************************************/

#ifndef __SELECTROLE_SCENE_H__
#define __SELECTROLE_SCENE_H__

#include "cocos2d.h"
#include "base\CCTouch.h"
USING_NS_CC;
class SelectRoleScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    /* ���ػ�ӭ���� */
    void menuBackCallback(cocos2d::Ref* pSender);

	/* ѡ���ɫ */
	void roleSelectedCallback(Ref * pSender, char option);

	virtual bool onTouchBegan(Touch * touch, Event * unused_event);

	/* �������еĽ�ɫ��ͼ */
	void invisibleRolesBig();
	/* ȷ����ɫ */
	void confirmCallback(Ref * pSender, char option);

    
	/* implement the "static create()" method manually */
    CREATE_FUNC(SelectRoleScene);

private:
	/* ���1�Ƿ��Ѿ�ѡ�����Ϸ��ɫ������ǣ���һ�ε����Ϊ���2ѡ���ɫ */
	bool player1Selected = false;  
	/* ��ѡ��ɫ1-4 */
	MenuItemImage* roleItem1,* roleItem2, *roleItem3, *roleItem4;
	/* ȷ����ť�ͷ��ذ�ť */
	MenuItemImage* player1ConfirmItem, *player2ConfirmItem, *backItem;
	/* ��ɫ1-4�Ĵ�ͼ��ѡ��ʱ��ʾ */
	Sprite *roleItem1_big, *roleItem2_big, *roleItem3_big, *roleItem4_big;
	/* player1 �� player2 �ı�ǩ��ѡ��ʱ��ʾ */
	Sprite *p1Sprite, *p2Sprite;
	/* �Ѿ���ѡ��Ľ�ɫ */
	int alreadySelected = 0;

	std::string player1Name, player2Name;

	/*��ʾ��Ϸ��ɫ��ѡ��*/
	Sprite* role1Selected;
	Sprite* role2Selected;
};

#endif
