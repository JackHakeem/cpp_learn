#include "SCMD150.h"
#include "view/login/LoginMediator.h"



int32 SCMD150::Execute()
{
	if(!Read())
	{
		return 1;
	}

	return SCMD150Handler::Execute(this);
}

bool SCMD150::Read()
{
	_taskProcess.clear();
	int16 length = readShort();
	for(int i=0; i<length; ++i)
	{
		int32 temp = readInt();
		_taskProcess.push_back(temp);
	}
	return true;
}

uint32 SCMD150Handler::Execute( SCMD150 *pPacket )
{
	if(!pPacket)
	{
		return 1;
	}
	LoginMediator *loginMediator = (LoginMediator *) g_pFacade->retrieveMediator(AppFacade_LOGIN_MEDIATOR);
	loginMediator->taskProcess((char *)pPacket);
	return 0;
}
