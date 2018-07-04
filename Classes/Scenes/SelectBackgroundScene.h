/**************************************************************************

* Copyright: 

* Author: LittleFish

* Date: 2018-06-18

* Description: ѡ����Ϸ��������

**************************************************************************/

#ifndef __SELECTBACKGROUND_SCENE_H__
#define __SELECTBACKGROUND_SCENE_H__

#include "cocos2d.h"
#include "SelectRoleScene.h"

USING_NS_CC;

class SelectBackgroundScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	/* ������Ϸ�ĳ��� */
	void bgSelectedCallback(Ref * pSender, int option);
     
	/* ��ʼ��Ϸ */
	void startGame(Ref * pSender);

	/* implement the "static create()" method manually */
    CREATE_FUNC(SelectBackgroundScene);



private:
	/* ��ѡ����1-4 */
	MenuItemImage * bgItem1, *bgItem2, *bgItem3, *bgItem4, *bgItem5, *bgItem6, *bgItem7, *bgItem8;
	/* һ���߿����ڸ����Ѿ�ѡ��ĳ��� */
	Sprite * frame;
	/* ȷ����ť�����������Ϸ���� */
	MenuItemImage* confirmItem;
	/* ѡ��ĳ��� */
	int selectedBackground = 1;
};

#endif /* __SelectBackgroundScene_SCENE_H__ */
