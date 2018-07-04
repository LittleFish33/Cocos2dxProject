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

	/* 两个玩家名字 */
	string player1 = "NONE";
	string player2 = "NONE";

	string xmlPath = "C:/Users/Zero/AppData/Local/HelloWorld/UserDefault.xml";
};

#endif