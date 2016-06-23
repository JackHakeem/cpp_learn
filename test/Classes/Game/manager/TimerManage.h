#ifndef _MIMERMANAGE_H_
#define _MIMERMANAGE_H_

/**
 *  Timer manager
 *  manage all system timer
 */
#include "cocos2d.h"
#include "utils/Singleton.h"
#include "utils/Timer.h"
#include "BaseType.h"
using namespace cocos2d;

class TimerManage : public Singleton<TimerManage>
{
public:
	TimerManage();
	~TimerManage();

public:
	void add( float delay, SEL_SCHEDULE pfnSelector, CCObject *pTarget );
	void remove( SEL_SCHEDULE pfnSelector, CCObject *pTarget );
	static string formatData( Number timer1, Number serTimer );
	static string formatTime( string s );
	static string formatServerTimeToDate( Number timer1 );
	static uint32 getSeconds( Number timer1, Number serTimer );
};

#endif