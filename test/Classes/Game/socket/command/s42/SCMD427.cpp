#include "SCMD427.h"
#include "model/dailyTaskEx/DailyTaskExProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD427::Read()
{
	a_taskId = readByte();
	b_finishCount = readByte();
	c_count = readByte();
	return true;
}

int32 SCMD427::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD427Handler::Execute(this);
}

uint32 SCMD427Handler::Execute( SCMD427* pPacket )
{
	DailyTaskExProxy* pProxy = (DailyTaskExProxy *) g_pFacade->retrieveProxy(AppFacade_DAILY_TASK_EX_PROXY);
	pProxy->onDailyTaskExProgress(pPacket);
	return 0;
}
