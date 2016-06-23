#include "SCMD2C5.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "view/trader/CityTraderMediator.h"

bool SCMD2C5::Read()
{
	a_id = readUint();
	b_name = readString();
	c_result = readByte();
	d_lostNum = readShort();
	e_reportId_1 = readUint();
	f_reportId_2 = readUint();

	return true;
}


int32 	SCMD2C5::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2C5Handler::Execute(this) ;
}


uint32 SCMD2C5Handler::Execute(SCMD2C5* pPacket)
{
	if (!pPacket) return 1;

	//add code here
	g_pCityTraderMediator->robNoteHandler(pPacket);
	return 0;
}