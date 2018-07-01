/**************************************************************************

* Copyright:

* Author: LittleFish

* Date: 2018-06-25

* Description: 共享单例类，用于存放一些共享变量的值

**************************************************************************/
#ifndef SHARESINGLETON_H
#define SHARESINGLETON_H
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

};

#endif