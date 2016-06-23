#ifndef __CDManage_H__
#define __CDManage_H__
/****************************************************************************
Copyright (c) 2012.3.7
system cd
CDManage::Instance() get instance£»
****************************************************************************/

#include "utils/Singleton.h"
#include "utils/Timer.h"
#include "BaseType.h"
#include "socket/command/s17/SCMD17F.h"
#include "cocos2d.h"
#include "utils/flash/CCIEventDispatcher.h"

using namespace cocos2d;

class GameDispatcher;

class Alert;
class CustomCD;
class CDManage:public Singleton<CDManage>, public CCObject, public CCIEventDispatcher
{
public:
	CDManage();
	~CDManage();

	// interface
public:
	enum CDEventName
	{
		OUT_GUILD	= 0,		//leave union 
		FIGHT,					//combat 
		AREA,					//covers an area of 
		BLESSING,				//blessing 
		COLLECTION,				//collection 
		TRAINING,				//training 
		STRENGTHEN,				//strengthen 
		ONLINE_AWARD,			//online award 
		CRYSTAL_0,				//crystal 0 (0 and 1 for ordinary player default crystal CD queue, other VIP level according to open)
		CRYSTAL_1,				//crystal 1 
		CRYSTAL_2,				//crystal 2 
		CRYSTAL_3,				//crystal 3 
		CRYSTAL_4,				//crystal 4 
		CRYSTAL_5,				//crystal 5 
		APPOINT,				//appointed 
		BUY_CRYSTAL,			//buying crystalline queue 
		BUY_TRAINING=16,			//buy training queue 
		SILVERMINE_MOVE=17,
		SILVERMINE_DIG=18,
		ARENA_CD = 19,
		ARENA_OPPS_CD = 20,     //hwj

		ORE_0 = 22,
		ORE_1 = 23,
		ORE_2 = 24,
		ORE_3 = 25,
		ORE_4 = 26,
		RobTraderCD = 27,


		WorldBoss_moveCD = 50,
		WorldBoss_battleCD = 51,
		WorldBoss_activityCD = 52,

		CampFight_CountDown = 60,
		TIMER_MAX

	};	

	enum
	{
		CDCHANGED = 500,
	};

	struct CDNode
	{
		int8 lock;
		Number time;
	};

	//Timer* getTimer( CDEventName iTimer );
	//void setTimer( CDEventName iTimer, DWORD dwIntervalTime );
	void serverTimer( Number value );
	void setTimeoffset( Number sTimer );
	Number getTimeoffset();
	Number getServerTime();
	void initAllCD( vector<SCMD17F::SCMD17FNode>& array );
	void updateCD( int type,int lock, Number time );
	void clearCD( uint type, uint state );
	Number getCDTimeBytype( uint type );
	int getLockBytype( uint type );
	void step( ccTime ct );
	void addTimerHandle( SEL_SCHEDULE pfnSelector, CCObject *pTarget );
	void removeTimerHandle( SEL_SCHEDULE pfnSelector, CCObject *pTarget );
	void timeStep( ccTime dt );

	void addCustomCD( int type, CustomCD* pCustomCD );
	void deleteCustomCD( int type );
	CustomCD* getCustomCD( int type );

	bool getCDReady( int cdType );
	void addNewCD(int type , int  time);
	int getTagByMinOreCD();
	int getNoCDOreNum();

private:
	Timer* m_TimerArray[ TIMER_MAX ];

	//Alert* m_alert;
	map<int, CDNode*> _cdDic;

	Number _serverTimer;

	//Number _timeoffset;
	Number _timeoffset;
	Number _clientTimer; // +1000 
	std::map<int, CustomCD*> customCDDic;

public:
	map<int, int> freeDic;
	static int BUY_LIST_VIPLEV[6];// = {0, 0, 0, 1, 4, 8};
	static int BUY_LIST_GOLD[6];// = {0, 0, 100, 200, 300, 400};
	/*static */string CDlockTimeName[TIMER_MAX];
	//std::map<int, CustomCD*> _CrystalCDDic;

	Number m_nLastTick;
};
#endif //__TIMERMANAGER_H__