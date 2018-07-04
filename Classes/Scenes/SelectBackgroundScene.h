/**************************************************************************

* Copyright: 

* Author: LittleFish

* Date: 2018-06-18

* Description: 选择游戏背景界面

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

	/* 设置游戏的场景 */
	void bgSelectedCallback(Ref * pSender, int option);
     
	/* 开始游戏 */
	void startGame(Ref * pSender);

	/* implement the "static create()" method manually */
    CREATE_FUNC(SelectBackgroundScene);



private:
	/* 可选场景1-4 */
	MenuItemImage * bgItem1, *bgItem2, *bgItem3, *bgItem4, *bgItem5, *bgItem6, *bgItem7, *bgItem8;
	/* 一个边框，用于高亮已经选择的场景 */
	Sprite * frame;
	/* 确定按钮，点击进入游戏界面 */
	MenuItemImage* confirmItem;
	/* 选择的场景 */
	int selectedBackground = 1;
};

#endif /* __SelectBackgroundScene_SCENE_H__ */
