/**************************************************************************

* Copyright: 

* Author: WJH

* Date: 2018-07-02

* Description: �����ս���ƽ���

**************************************************************************/

#ifndef __InputNameScene_SCENE_H__
#define __InputNameScene_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;
#include "base\CCTouch.h"
USING_NS_CC;

class InputNameScene : public cocos2d::Scene
{
private:
	/* �༭�� */
	EditBox * editBox1;
	EditBox * editBox2;
	MenuItemImage* nameConfirmItem;
	cocos2d::Label* vs;
public:

    static cocos2d::Scene* createScene();

    virtual bool init();

	/* ȷ����ɫ���� */
	void confirmCallback(cocos2d::Ref * pSender);

	/* implement the "static create()" method manually */
    CREATE_FUNC(InputNameScene);
};

#endif /* __InputNameScene_SCENE_H__ */
