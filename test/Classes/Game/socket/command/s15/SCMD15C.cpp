#include "SCMD15C.h"
#include "view/task/TaskListenerMediator.h"

int32 SCMD15C::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD15CHandler::Execute(this);
}

bool SCMD15C::Read()
{
	_id = readShort();
	_succ = readByte();
	return true;
}

uint32 SCMD15CHandler::Execute( SCMD15C *pPacket )
{
	if(!pPacket)
	{
		return 1;
	}

	TaskListenerMediator *taskListenerMediator = (TaskListenerMediator *)g_pFacade->retrieveMediator(AppFacade_TASK_LISTENER_MEDIATOR);
	taskListenerMediator->giviUPTaskHandler((char *)pPacket);

	return 0;
}
