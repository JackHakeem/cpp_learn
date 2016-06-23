#include "SCMD2B4.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD2B4::Read()
{
	a_historyItem1 = readByte();
	b_historyItem2 = readByte();
	c_historyItem3 = readByte();
	d_historyItem4 = readByte();
	e_historyItem5 = readByte();

	return true;
}


int32 	SCMD2B4::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2B4Handler::Execute(this) ;
}


uint32 SCMD2B4Handler::Execute(SCMD2B4* pPacket)
{
	if (!pPacket) return 1;

	//add code here

	return 0;
}