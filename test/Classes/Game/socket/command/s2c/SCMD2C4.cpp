#include "SCMD2C4.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD2C4::Read()
{
	a_id = readInt();
	b_result = readByte();
	c_doubleType = readByte();
	d_silver = readInt();

	return true;
}


int32 	SCMD2C4::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2C4Handler::Execute(this) ;
}


uint32 SCMD2C4Handler::Execute(SCMD2C4* pPacket)
{
	if (!pPacket) return 1;

	//add code here

	return 0;
}