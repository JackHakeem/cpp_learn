#ifndef _HonorMediator_H_
#define _HonorMediator_H_

#include "mvc/Mediator.h"
#include "../BaseMediator.h"
#include "socket/command/s14/SCMD140.h"
#include "socket/command/s14/SCMD144.h"
#include "socket/command/s14/SCMD142.h"

class HonorMediator : public BaseMediator{

public:
	enum 
	{
		HONONR_POP,
		HONONR_CREAT_LIST,
		HONONR_COMPLETED,
		HONONR_TITLEUPDATE,
		HONONR_POINTAWARDUPDATE,
		HONONR_HONORAWARDUPDATE
		//				,
		//				FIGHT_FIRST,
		//				FIGHT_ENDS
	};


public:
public:
	virtual void handleNotification(int M2Vcmd, char* data);
	//void dungeonAward( SCMD376& param );
	void dungeonAward( SCMD140& param );
	void updateHonorAwardComplete( int honorId );
	void updateHonorReach( int honorId );
	void socketHonorHasReach( SCMD140* param );
	void socketHonorhasGetItem( SCMD144* param );
	void honorChangeClickHandler( int type );
	void socketHasReachHonorList( SCMD142* pPacket );
};

extern HonorMediator* g_pHonorMediator;

#endif