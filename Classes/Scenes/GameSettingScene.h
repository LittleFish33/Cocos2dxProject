/**************************************************************************

* Copyright:

* Author: qiuyihao

* Date: 2018-06-27

* Description:   ��Ϸ���ý���

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

	/*����bgm�ص�����*/
	void controlVoiceCallback(Ref * pSender);
	/*��Ϸ��ʼ������ѡ���ɫѡ�����*/
	void startGameCallback(Ref * pSender);
	/*������Ϸ*/
	void aboutGameCallback(Ref * pSender);


	/* implement the "static create()" method manually */
	CREATE_FUNC(GameSettingScene);
private:
	/*Ϊtrue�����򿪣�Ϊfalse�����رգ�Ĭ��true*/
	bool openOrCloseVoiceState; //�����Դ���api����
	/* �˵���ť��*/
	MenuItemImage *bgmItem, *startGameItem, *aboutGameItem;
	/*�Ի�����*/
	Sprite *welcomeDialogue, *openBgmDialogue, *closeBgmDialogue, *aboutGameDialogue;
};

#endif