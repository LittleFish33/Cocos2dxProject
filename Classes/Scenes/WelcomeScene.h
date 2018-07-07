/**************************************************************************

* Copyright: 

* Author: LittleFish

* Date: 2018-06-17

* Description: ��Ϸ��ӭ���棬��������ֱ�ӽ���Ľ���

**************************************************************************/

#ifndef __WelcomeScene_SCENE_H__
#define __WelcomeScene_SCENE_H__

#include "cocos2d.h"
#include "SelectRoleScene.h"

class WelcomeScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    /* �ر���Ϸ��ť����¼� */
    void menuCloseCallback(cocos2d::Ref* pSender);

	void startGameCallback(Ref * pSender);
    
	void settingGameCallback(Ref* pSender);

	void rankListCallback(Ref* pSender);

	void onlineCallback(Ref* pSender);

	void operatingInstructionSceneCallback(Ref* pSender);

	/* implement the "static create()" method manually */
    CREATE_FUNC(WelcomeScene);
};

#endif /* __WelcomeScene_SCENE_H__ */
