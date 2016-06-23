#include "SCMD24B.h"
#include "control/vip/VipCommand.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"


bool SCMD24B::Read()
{
	a_roleErrorNum = readUshort();
	b_roleName = readString();
	return true;
}

int32 SCMD24B::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD24BHandler::Execute(this);
}

uint32 SCMD24BHandler::Execute( SCMD24B* pPacket )
{
	if (!pPacket) return 1;

	return 0;
}
