#include "SCMD157.h"
#include "view/task/TaskListenerMediator.h"

int32 SCMD157::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD157Handler::Execute(this);
}

bool SCMD157::Read()
{
	_id = readShort();
	_succ = readByte();
	return true;
}

uint32 SCMD157Handler::Execute( SCMD157 *pPacket )
{
	if(!pPacket)
	{
		return 1;
	}

	TaskListenerMediator *taskListenerMediator = (TaskListenerMediator *)g_pFacade->retrieveMediator(AppFacade_TASK_LISTENER_MEDIATOR);
	taskListenerMediator->finishTaskHandler((char *)pPacket);
	
	return 0;
}
