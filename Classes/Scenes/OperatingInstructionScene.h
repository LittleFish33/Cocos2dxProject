/**************************************************************************

* Copyright:

* Author: qiuyihao

* Date: 2018-07-07

* Description:  操作说明界面

**************************************************************************/

#ifndef _OPERATINGINSTRUCTION_SCENE_H_
#define _OPERATINGiNSTRUCTION_SCENE_H_
#include "cocos2d.h"

USING_NS_CC;

class OperatingInstructionScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	/*返回游戏菜单游戏*/
	void WelcomeSceneCallback(Ref * pSender);


	/* implement the "static create()" method manually */
	CREATE_FUNC(OperatingInstructionScene);
	
};

#endif