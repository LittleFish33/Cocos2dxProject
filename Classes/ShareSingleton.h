/**************************************************************************

* Copyright:

* Author: LittleFish

* Date: 2018-06-25

* Description: �������࣬���ڴ��һЩ���������ֵ

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
	
	/*����ѡ���ͼ���*/
	int selectedBackground = 1;

	/* ����������� */
	string player1 = "NONE";
	string player2 = "NONE";

	string xmlPath = "C:/Users/Zero/AppData/Local/HelloWorld/UserDefault.xml";
};

#endif