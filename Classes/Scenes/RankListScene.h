/**************************************************************************

* Copyright: 

* Author: WJH

* Date: 2018-07-02

* Description: 游戏排行榜界面

**************************************************************************/

#ifndef __RankLisScene_SCENE_H__
#define __RankLisScene_SCENE_H__

#include "cocos2d.h"
using namespace std;
#include <vector>

class RankListScene : public cocos2d::Scene
{
private:
	list<cocos2d::Label*> ranks;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void handleRankList();
	/* implement the "static create()" method manually */
    CREATE_FUNC(RankListScene);
};

#endif /* __RankLisScene_SCENE_H__ */
