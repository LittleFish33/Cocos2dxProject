/**************************************************************************

* Copyright:

* Author: qiuyihao

* Date: 2018-07-02

* Description:  ��Ϸ�������Ľ�������

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

	/*����������*/
	void ReturnToMenuSceneCallback(Object* pSender);
	/*�˳���Ϸ*/
	void QuiteGameCallback(Object* pSender);
	/*����ѡ���ɫ����*/
	void ReturnToChooseRoleSceneCallback(Object *pSender);
	/*���¿�ʼ��Ϸ*/
	void RestartGameCallback(Object* pSender);

	/* implement the "static create()" method manually */
	CREATE_FUNC(GameOverScene);

private:
	/*������Ϸ��ť*/
	MenuItemImage * QuitGameItem;
	/*���ز˵���ť*/
	MenuItemImage * ReturnToMenuSceneItem;
	/*���¿�ʼ��ť*/
	MenuItemImage * RestartGameItem;
	/*ѡ���ɫ��ť*/
	MenuItemImage * ChooseRoleSceneItem;
};

#endif 