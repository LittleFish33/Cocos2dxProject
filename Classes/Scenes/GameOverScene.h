/**************************************************************************

* Copyright:

* Author: qiuyihao

* Date: 2018-07-02

* Description:  游戏主场景的结束界面

**************************************************************************/

#ifndef _GAMEOVERSCENE_H_
#define _GAMEOVERSCENE_H_
#include "cocos2d.h"

USING_NS_CC;

class GameOverScene : public cocos2d::Layer
{
public:
	virtual bool init();
	static cocos2d::Scene* CreateScene(RenderTexture* sqr);

	/*返回主界面*/
	void ReturnToMenuSceneCallback(Object* pSender);
	/*退出游戏*/
	void QuiteGameCallback(Object* pSender);
	/*进入选择角色界面*/
	void ReturnToChooseRoleSceneCallback(Object *pSender);
	/*重新开始游戏*/
	void RestartGameCallback(Object* pSender);

	/* implement the "static create()" method manually */
	CREATE_FUNC(GameOverScene);

private:
	/*结束游戏按钮*/
	MenuItemImage * QuitGameItem;
	/*返回菜单按钮*/
	MenuItemImage * ReturnToMenuSceneItem;
	/*重新开始按钮*/
	MenuItemImage * RestartGameItem;
	/*选择角色按钮*/
	MenuItemImage * ChooseRoleSceneItem;
};

#endif 