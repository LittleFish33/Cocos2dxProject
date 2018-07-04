#pragma once
enum KEYCODESEND
{
	LEFT,RIGHT,UP,DOWN,G,H,Y,J,
	LEFTRELEASE, RIGHTRELEASE, UPRELEASE,DOWNRELEASE, G_RELEASE, H_RELEASE, Y_RELEASE, J_RELEASE,
	FIRSTCONNECT, TRANSFER
};
struct SocketData
{
	int uid;
	KEYCODESEND codeSend;
	SocketData(int u, KEYCODESEND k) {
		uid = u;
		codeSend = k;
	}
};
