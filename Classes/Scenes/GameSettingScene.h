/**************************************************************************

* Copyright:

* Author: qiuyihao

* Date: 2018-06-27

* Description:   游戏设置界面

**************************************************************************/

#ifndef _GAMESETTING_SCENE_H_
#define _GAMESETTING_SCENE_H_
#include "cocos2d.h"

USING_NS_CC;

class GameSettingScene : public cocos2d::Scene
{
public: 
	static cocos2d::Scene* createScene();

	virtual bool init();

	/*控制bgm回调函数*/
	void controlVoiceCallback(Ref * pSender);
	/*游戏开始，进入选择角色选择界面*/
	void startGameCallback(Ref * pSender);
	/*关于游戏*/
	void aboutGameCallback(Ref * pSender);


	/* implement the "static create()" method manually */
	CREATE_FUNC(GameSettingScene);
private:
	/*为true声音打开，为false声音关闭，默认true*/
	bool openOrCloseVoiceState; //额有自带的api。。
	/* 菜单按钮项*/
	MenuItemImage *bgmItem, *startGameItem, *aboutGameItem;
	/*对话框精灵*/
	Sprite *welcomeDialogue, *openBgmDialogue, *closeBgmDialogue, *aboutGameDialogue;
};

#endif