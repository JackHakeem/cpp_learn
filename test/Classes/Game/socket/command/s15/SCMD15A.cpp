#include "SCMD15A.h"
#include "view/task/TaskListenerMediator.h"

int32 SCMD15A::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD15AHandler::Execute(this);
}

bool SCMD15A::Read()
{
	_id = readShort();
	_succ = readByte();
	return true;
}


uint32 SCMD15AHandler::Execute( SCMD15A *pPacket )
{
	if(!pPacket)
	{
		return 1;
	}

	TaskListenerMediator *taskListenerMediator = (TaskListenerMediator *)g_pFacade->retrieveMediator(AppFacade_TASK_LISTENER_MEDIATOR);
	taskListenerMediator->submitTaskHandler((char *)pPacket);
	return 0;
}
