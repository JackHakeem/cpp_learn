#include "SCMD2A1.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD2A1::Read()
{
	a_isSuc = readUbyte();
	b_gridNum = readUbyte();

	return true;
}

int32 SCMD2A1::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD2A1Handler::Execute(this);
}

uint32 SCMD2A1Handler::Execute( SCMD2A1* pPacket )
{
	if (!pPacket)
	{
		return 1;
	}
}
