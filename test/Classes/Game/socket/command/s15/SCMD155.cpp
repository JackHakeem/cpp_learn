#include "SCMD155.h"
#include "view/task/TaskListenerMediator.h"


int32 SCMD155::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD155Handler::Execute(this);
}

bool SCMD155::Read()
{
	_id = readShort();
	_succ = readByte();
	return true;
}

uint32 SCMD155Handler::Execute( SCMD155 *pPacket )
{
	if(!pPacket)
	{
		return 1;
	}

	TaskListenerMediator *taskListenerMediator = (TaskListenerMediator *)g_pFacade->retrieveMediator(AppFacade_TASK_LISTENER_MEDIATOR);
	taskListenerMediator->recTaskHandler((char *)pPacket);
	return 0;
}
