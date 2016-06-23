#include "SCMD423.h"
#include "model/dailyTaskEx/DailyTaskExProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD423::Read()
{
	a_taskId = readByte();
	b_result = readByte();
	return true;
}

int32 SCMD423::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD423Handler::Execute(this);
}

uint32 SCMD423Handler::Execute( SCMD423* pPacket )
{
	DailyTaskExProxy* pProxy = (DailyTaskExProxy *) g_pFacade->retrieveProxy(AppFacade_DAILY_TASK_EX_PROXY);
	pProxy->onDailyTaskExAccept(pPacket);
	return 0;
}
