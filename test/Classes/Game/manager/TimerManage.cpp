#include "TimerManage.h"
#include <time.h>
#include "ViewManager.h"

TimerManage::TimerManage()
{

}

TimerManage::~TimerManage()
{

}

/**
* add a timer listener 
* @param delay
* @param pfnSelector callback function
* @param param:callback param
*/		
void TimerManage::add( float delay, SEL_SCHEDULE pfnSelector, CCObject *pTarget )
{
	CCScheduler::sharedScheduler()->scheduleSelector( pfnSelector, pTarget, delay, false);
}

void TimerManage::remove( SEL_SCHEDULE pfnSelector, CCObject *pTarget )
{
	CCScheduler::sharedScheduler()->unscheduleSelector( pfnSelector, pTarget );
}


string TimerManage::formatData( Number timer1, Number serTimer )
{
 	if ( timer1 < serTimer )
 	{
 		return "00:00:00";
 	}
	Number num = ( timer1 - serTimer ) * 0.001;  // second

	num = num > 0 ? (num) : ((-1) * num);

	int hour = num/3600;
	int minute = ( num/60 )%60;
	int second = num%60;

	char timeStr[28];
	sprintf( timeStr, "%d", hour );
	string sHour = formatTime( timeStr );

	sprintf( timeStr, "%d", minute );
	string sMinute = formatTime( timeStr );

	sprintf( timeStr, "%d", second );
	string sSecond = formatTime( timeStr );

	return sHour.append( ":" ).append( sMinute ).append( ":" ).append( sSecond );
}

string TimerManage::formatTime( string s )
{
	string withZero = "0";
	return s.length() == 1 ? ( withZero.append( s ) ) : s;
}

string TimerManage::formatServerTimeToDate( Number timer1 )
{
	time_t pTimeT = (time_t)timer1;
	struct tm* pTm = localtime(&pTimeT);
	//struct tm* pTm = gmtime(  &pTimeT  );	// UTC Time

	if ( !pTm )
	{
		return "";
	}
	
	int year = pTm->tm_year + 1900;	//Local time
	int month = pTm->tm_mon + 1;
	int day = pTm->tm_mday;
	int hour = pTm->tm_hour;
	int minute = pTm->tm_min;
	int second = pTm->tm_sec;

	char timeStr[28];

	sprintf( timeStr, "%d", year );
	string sYear = timeStr;

	sprintf( timeStr, "%d", month );
	string sMonth = timeStr;

	sprintf( timeStr, "%d", day );
	string sDay = formatTime( timeStr );

	sprintf( timeStr, "%d", hour );
	string sHour = formatTime( timeStr );

	sprintf( timeStr, "%d", minute );
	string sMinute = formatTime( timeStr );

	sprintf( timeStr, "%d", second );
	string sSecond = formatTime( timeStr );

	string sTemp = sYear.append(" ").append( sMonth ).append( " " ).append( sDay );
	return sTemp.append( " " ).append( sHour ).append( ":" ).append( sMinute ).append( ":" ).append( sSecond );
}

uint32 TimerManage::getSeconds( Number timer1, Number serTimer )
{	
	Number num = ( timer1 - serTimer ) /** 0.001*/; 
	num = num > 0 ? (num) : ((-1) * num);
	return num;
}