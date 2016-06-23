#include "SCMD2B7.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD2B7::Read()
{
	a_eventType = readByte();
	b_awardType = readShort();
	c_awardNum = readInt();

	return true;
}


int32 	SCMD2B7::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2B7Handler::Execute(this) ;
}


uint32 SCMD2B7Handler::Execute(SCMD2B7* pPacket)
{
	if (!pPacket) return 1;

	//add code here

	return 0;
}