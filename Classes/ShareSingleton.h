/**************************************************************************

* Copyright:

* Author: LittleFish

* Date: 2018-06-25

* Description: �������࣬���ڴ��һЩ���������ֵ

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
	
	/*����ѡ���ͼ���*/
	int selectedBackground = 1;

};

#endif