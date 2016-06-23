#include "SCMD442.h"
#include "socket/network/GameServerSocket.h"
#include "view/mainUI/MainUIMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "manager/LangManager.h"

bool	SCMD442::Read()
{
	a_NextWorldBossTime = readUint();
	b_NextGongTime = readUint();
	c_NextSilverMineTime = readUint();

	return true;
}

int32 	SCMD442::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD442Handler::Execute(this) ;
}


uint32 SCMD442Handler::Execute(SCMD442* pPacket)
{
	if (!pPacket) return 1;

	//MainUIMediator * mUImediator = (MainUIMediator *)g_pFacade->retrieveMediator(AppFacade_MainUIMediator);
	//if (mUImediator)
	//	mUImediator->mineOpenTime(pPacket);
	
	{
		Number openTime = pPacket->a_NextWorldBossTime;

		time_t pTimeT = (time_t)openTime;
		struct tm* pTm = localtime(&pTimeT);

		if ( !pTm )
		{
			return 1;
		}
	
		int year = pTm->tm_year + 1900;	//Local time
		int month = pTm->tm_mon + 1;
		int day = pTm->tm_mday;
		int hour = pTm->tm_hour;
		int minute = pTm->tm_min;
		int second = pTm->tm_sec;
		char shows[150];
		sprintf(shows, "gong %d-%02d-%02d  %02d:%02d~%02d:%02d",  year, month, day, hour, minute,
			hour, minute+30);

		LangManager::msgStr(shows);
	}
	{
		Number openTime = pPacket->b_NextGongTime;

		time_t pTimeT = (time_t)openTime;
		struct tm* pTm = localtime(&pTimeT);

		if ( !pTm )
		{
			return 1;
		}
	
		int year = pTm->tm_year + 1900;	//Local time
		int month = pTm->tm_mon + 1;
		int day = pTm->tm_mday;
		int hour = pTm->tm_hour;
		int minute = pTm->tm_min;
		int second = pTm->tm_sec;
		char shows[150];
		sprintf(shows, "gong %d-%02d-%02d  %02d:%02d~%02d:%02d",  year, month, day, hour, minute,
			hour, minute+30);

		LangManager::msgStr(shows);
	}
	{
		Number openTime = pPacket->c_NextSilverMineTime;

		time_t pTimeT = (time_t)openTime;
		struct tm* pTm = localtime(&pTimeT);

		if ( !pTm )
		{
			return 1;
		}
	
		int year = pTm->tm_year + 1900;	//Local time
		int month = pTm->tm_mon + 1;
		int day = pTm->tm_mday;
		int hour = pTm->tm_hour;
		int minute = pTm->tm_min;
		int second = pTm->tm_sec;
		char shows[150];
		sprintf(shows, "gong %d-%02d-%02d  %02d:%02d~%02d:%02d",  year, month, day, hour, minute,
			hour, minute+30);

		LangManager::msgStr(shows);
	}
	return 0;
}