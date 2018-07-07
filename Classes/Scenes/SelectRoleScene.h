/**************************************************************************

* Copyright: 

* Author: LittleFish

* Date: 2018-06-17

* Description: 选择游戏角色界面

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
    
    /* 返回欢迎界面 */
    void menuBackCallback(cocos2d::Ref* pSender);

	/* 选择角色 */
	void roleSelectedCallback(Ref * pSender, char option);

	virtual bool onTouchBegan(Touch * touch, Event * unused_event);

	/* 隐藏所有的角色大图 */
	void invisibleRolesBig();
	/* 确定角色 */
	void confirmCallback(Ref * pSender, char option);

    
	/* implement the "static create()" method manually */
    CREATE_FUNC(SelectRoleScene);

private:
	/* 玩家1是否已经选择好游戏角色，如果是，下一次点击将为玩家2选择角色 */
	bool player1Selected = false;  
	/* 可选角色1-4 */
	MenuItemImage* roleItem1,* roleItem2, *roleItem3, *roleItem4;
	/* 确定按钮和返回按钮 */
	MenuItemImage* player1ConfirmItem, *player2ConfirmItem, *backItem;
	/* 角色1-4的大图，选中时显示 */
	Sprite *roleItem1_big, *roleItem2_big, *roleItem3_big, *roleItem4_big;
	/* player1 和 player2 的标签，选中时显示 */
	Sprite *p1Sprite, *p2Sprite;
	/* 已经被选择的角色 */
	int alreadySelected = 0;

	std::string player1Name, player2Name;

	/*提示游戏角色已选中*/
	Sprite* role1Selected;
	Sprite* role2Selected;
};

#endif
