#include "SCMD15E.h"
#include "view/task/TaskListenerMediator.h"

int32 SCMD15E::Execute()
{
	if(!Read())
	{
		return 1;
	}

	return SCMD15EHandler::Execute(this);
}

bool SCMD15E::Read()
{
	_succ = readByte();
	return true;
}

uint32 SCMD15EHandler::Execute( SCMD15E *pPacket )
{
	if(!pPacket)
	{
		return 1;
	}

	TaskListenerMediator *taskListenerMediator = (TaskListenerMediator *)g_pFacade->retrieveMediator(AppFacade_TASK_LISTENER_MEDIATOR);
	taskListenerMediator->refTaskHandler((char *)pPacket);

	return 0;
}
