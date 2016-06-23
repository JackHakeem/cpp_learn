#include "SCMD2A7.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD2A7::Read()
{
	

	return true;
}

int32 SCMD2A7::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD2A7Handler::Execute(this);
}

uint32 SCMD2A7Handler::Execute( SCMD2A7* pPacket )
{
	if (!pPacket)
	{
		return 1;
	}
}
