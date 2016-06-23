#include "SCMD42B.h"
#include "manager/LangManager.h"
#include "model/dailyTaskEx/DailyTaskExProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD42B::Read()
{
	a_result = readByte();
	return true;
}

int32 SCMD42B::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD42BHandler::Execute(this);
}

uint32 SCMD42BHandler::Execute( SCMD42B* pPacket )
{
    
	DailyTaskExProxy* pProxy = (DailyTaskExProxy *) g_pFacade->retrieveProxy(AppFacade_DAILY_TASK_EX_PROXY);
	pProxy->onDailyTaskExGiveup(pPacket);
	return 0;
}
