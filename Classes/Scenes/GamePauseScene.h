/**************************************************************************

* Copyright:

* Author: qiuyihao

* Date: 2018-06-27

* Description:  ��Ϸ����������ͣ����

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

	/*������Ϸ*/
	void ContinueGameCallback(Object* pSender);
	/*����������*/
	void ReturnToMenuSceneCallback(Object* pSender);
	/*�˳���Ϸ*/
	void QuiteGameCallback(Object* pSender);

	/* implement the "static create()" method manually */
	CREATE_FUNC(GamePauseScene);

private:
	/*������Ϸ��ť*/
	MenuItemImage * ContinueGameItem;
	/*������Ϸ��ť*/
	MenuItemImage * QuiteGameItem;
	/*���ز˵���ť*/
	MenuItemImage * ReturnToMenuSceneItem;
};

#endif 