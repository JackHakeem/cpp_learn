#include "SCMD18B.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "view/figure/FigureMediator.h"


bool	SCMD18B::Read()
{  
	a_figure = readInt();
	b_maxHp = readInt();
	c_difference = readInt();

	return true;
}

int32 SCMD18B::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD18BHandler::Execute(this) ;
}


uint32 SCMD18BHandler::Execute(SCMD18B * pPacket)
{
	if (!pPacket) return 1;

	CCLog("MainUI:HP changed info received SCMD18B");

	return 0;
}