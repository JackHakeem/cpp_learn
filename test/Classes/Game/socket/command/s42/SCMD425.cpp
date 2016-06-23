#include "SCMD425.h"
#include "model/dailyTaskEx/DailyTaskExProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD425::Read()
{
	a_taskId = readByte();
	b_result = readByte();
	return true;
}

int32 SCMD425::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD425Handler::Execute(this);
}

uint32 SCMD425Handler::Execute( SCMD425* pPacket )
{
	DailyTaskExProxy* pProxy = (DailyTaskExProxy *) g_pFacade->retrieveProxy(AppFacade_DAILY_TASK_EX_PROXY);
	pProxy->onDailyTaskExSubmit(pPacket);
	return 0;
}
