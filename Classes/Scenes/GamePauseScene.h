/**************************************************************************

* Copyright:

* Author: qiuyihao

* Date: 2018-06-27

* Description:  游戏主场景的暂停界面

**************************************************************************/

#ifndef _GAMEPAUSESCENE_H_
#define _GAMEPAUSESCENE_H_
#include "cocos2d.h"

USING_NS_CC;

class GamePauseScene : public cocos2d::Layer
{
public:
	virtual bool init();
	static cocos2d::Scene* CreateScene(RenderTexture* sqr);

	/*继续游戏*/
	void ContinueGameCallback(Object* pSender);
	/*返回主界面*/
	void ReturnToMenuSceneCallback(Object* pSender);
	/*退出游戏*/
	void QuiteGameCallback(Object* pSender);

	/* implement the "static create()" method manually */
	CREATE_FUNC(GamePauseScene);

private:
	/*继续游戏按钮*/
	MenuItemImage * ContinueGameItem;
	/*结束游戏按钮*/
	MenuItemImage * QuiteGameItem;
	/*返回菜单按钮*/
	MenuItemImage * ReturnToMenuSceneItem;
};

#endif 