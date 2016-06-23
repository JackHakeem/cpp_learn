#include "SCMD158.h"
#include "view/task/TaskListenerMediator.h"

int32 SCMD158::Execute()
{
	if(!Read())
	{
		return 1;
	}

	return SCMD158Handler::Execute(this);
}

bool SCMD158::Read()
{
	_id = readShort();
	readShort();
	_taskTip._id = readInt();
	_taskTip._nowCount = readShort();
	
	return true;
}

uint32 SCMD158Handler::Execute( SCMD158 *pPacket )
{
	if(!pPacket)
	{
		return 1;
	}
	TaskListenerMediator *taskListenerMediator = (TaskListenerMediator *)g_pFacade->retrieveMediator(AppFacade_TASK_LISTENER_MEDIATOR);
	taskListenerMediator->updateTaskHandler((char *)pPacket);
	return 0;
}
