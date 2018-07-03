/**************************************************************************

* Copyright:

* Author: LittleFish

* Date: 2018-06-25

* Description: 共享单例类，用于存放一些共享变量的值

**************************************************************************/
#ifndef SHARESINGLETON_H
#define SHARESINGLETON_H

using namespace std;
class ShareSingleton
{
private:
	ShareSingleton(){}
public:
	static ShareSingleton* GetInstance()
	{
		static ShareSingleton Instance;
		return &Instance;
	}
	bool opponentFlipx = false;
	
	/*代表选择地图序号*/
	int selectedBackground = 1;

	/*全局变量，用于确定音效是否需要关闭 qyh*/
	bool controlVoice = true;

	/*全局变量，主要用于确定暂停场景，暂停(继续）图标是否需要变化,
	为真，图标为播放状态，为假，图标为暂停状态*/
	bool controlPause = true; 

	/* 两个玩家名字 */
	string player1 = "NONE";
	string player2 = "NONE";

	string xmlPath = "C:/Users/Qiuyh/AppData/Local/HelloGame/UserDefault.xml";
};

#endif