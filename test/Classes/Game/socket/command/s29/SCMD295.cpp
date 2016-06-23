#include "SCMD295.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "mvc/Facade.h"
#include "view/recruit/RecruitMediator.h"
#include "control/AppFacade.h"
#include "view/figure/FigureMediator.h"

bool	SCMD295::Read()
{
	a_type = readUbyte();
	b_price = readUint();

	return true;
}

int32 	SCMD295::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD295Handler::Execute(this) ;
}


uint32 SCMD295Handler::Execute(SCMD295* pPacket)
{
	if (!pPacket) return 1;

	if (pPacket->a_type == 0) // wash
	{
		FigureMediator* _figureMediator = (FigureMediator*)g_pFacade->retrieveMediator(AppFacade_FIGURE_MEDIATOR);
		_figureMediator->sockPriceResult((char*)pPacket);
	}
	else if (pPacket->a_type == 1) // task
	{
		
	}
	
	return 0;
}