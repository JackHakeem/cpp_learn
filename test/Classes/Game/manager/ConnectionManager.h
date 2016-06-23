#ifndef __Connection_Manage_H__
#define __Connection_Manage_H__
#include "utils/Singleton.h"
#include "cocos2d.h"

USING_NS_CC;

/*
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
typedef unsigned long long socket_type;
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
typedef int socket_type;
#endif
*/

class ConnectionManager : public Singleton<ConnectionManager>, public CCObject
{
public:
	ConnectionManager();
	virtual ~ConnectionManager(){}

	void CheckStep(ccTime dt);
	int ConnectionCheck(int millisecond);
	void ReConnect(CCObject * pSender);
	void onDisConnectMenuClick(CCObject * pSender);
	void didDisConnet();
	void run();
	void stop();
public:
	CC_SYNTHESIZE(int, _GateSocket, GateSocket)
	CC_SYNTHESIZE(int, _GameSocket, GameSocket)
	CC_SYNTHESIZE(bool, _isConnect, IsConnect)
	
	int _nCount;
	int _nCountDisCon;
};

#endif