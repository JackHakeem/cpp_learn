#ifndef __TIMER_H__
#define __TIMER_H__
/****************************************************************************
Timer 
****************************************************************************/

//#include <windows.h>
#include "cocos2d.h"
#include "platform.h"
using namespace cocos2d;

//using namespace util;

typedef unsigned long DWORD;
typedef /*time_t*/long long Number;

//namespace util
//{
class Timer
{
public: 
	Timer():m_dwExpireTime(0),m_dwIntervalTime(0),m_bCheckTime(false) {}
	~Timer(){}

public: 
	//External call common interface
	inline void setTimer( time_t dwIntervalTime )
	{
		m_dwIntervalTime	= dwIntervalTime;
		reset();
	}

	//The current time (ms)
	static inline time_t millisecondNow()
	{
		//struct cc_timeval tNow;
		//CCTime::gettimeofdayCocos2d(&tNow, NULL);
		//return (tNow.tv_sec * 1000 + tNow.tv_usec / 1000);
		struct cc_timeval tNow;
		CCTime::gettimeofdayCocos2d(&tNow, NULL);
		time_t dt = (time_t)tNow.tv_sec;
		dt *= 1000;
		time_t dv = (time_t)tNow.tv_usec;
		dv /= 1000;
		time_t t = dt + dv;
		return t;
	} 
	
	//Set up and get the default timer intervals
	inline time_t getIntervalTime() { return m_dwIntervalTime;	}
    inline void setIntervalTime(time_t dwTime){ m_dwIntervalTime = dwTime;}
	// iRate The time interval between incremental (percentage)
	inline void reset(int iRate = 0)
	{
        time_t dwCurTime = millisecondNow();//GetTickCount();
		m_dwExpireTime		= dwCurTime + (time_t)(m_dwIntervalTime*(1.0f+iRate*0.0001f));
		enableCheckTime();
	}
	// Open timer
	inline void enableCheckTime()
	{
		m_bCheckTime = true;
	}

	// Off timer
	inline void disableCheckTime()
	{
		m_bCheckTime = false;
	}

	//// Get executive progress
	// float getProgressRatio()
	//{		
	//	time_t dwProgressTime = millisecondNow() - (m_dwExpireTime - m_dwIntervalTime);
	//	return min(1.0f,((float)dwProgressTime / (float)m_dwIntervalTime));
	//}

	// Timing is due
	inline bool isExpired( bool bReset=true )
	{
		time_t dwCurTime;
		if( m_bCheckTime && ( dwCurTime = millisecondNow() ) >= m_dwExpireTime ) //GetTickCount()
		{
			if( bReset )
			{
				m_dwExpireTime = dwCurTime + m_dwIntervalTime;
			}
			m_bIsReset = false;
			return true;
		}
		else 
			return false;
	}

	// Whether the timer expires, if expire, the need for open next time
	inline bool isExpiredManual( bool bReset=true )
	{
		time_t dwCurTime;
		if( m_bCheckTime && ( dwCurTime = millisecondNow() ) >= m_dwExpireTime ) 
		{
			if( bReset )
			{
				m_dwExpireTime = dwCurTime + m_dwIntervalTime;
			}
			disableCheckTime();
			m_bIsReset = false;
			return true;
		}
		else 
			return false;
	}

	//Time to
	void initCoolTime()
	{
		m_dwExpireTime = 0;
	}

	inline time_t getExpireTime()	{ return m_dwExpireTime; }
	
	void setIsReset(bool bIsReset)	{ m_bIsReset = bIsReset; }
	bool getIsReset(void)			{ return m_bIsReset; }
    bool isCheckTime()              { return m_bCheckTime; }
private: 
	bool		m_bCheckTime;			//switch
	time_t		m_dwExpireTime;			//Due time
	time_t		m_dwIntervalTime;		//Time interval between

	bool		m_bIsReset;				// IF reset
};

//}//End of namespace util


#endif //__TIMER_H__

