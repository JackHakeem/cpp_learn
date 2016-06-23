#include "SCMD30C.h"
#include "socket/network/GameServerSocket.h"
#include "view/figure/FigureMediator.h"
bool	SCMD30C::Read()
{
	a_result = readByte();
	b_figureId = readInt();
	c_rebornNum = readByte();
	return true;
}

int32 	SCMD30C::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD30CHandler::Execute(this) ;
}


uint32 SCMD30CHandler::Execute(SCMD30C* pPacket)
{
	if (!pPacket) return 1;
	
	CCLog("Peiyang:reborn result received SCMD30C");
	FigureMediator * fm = (FigureMediator *)g_pFacade->retrieveMediator(AppFacade_FIGURE_MEDIATOR);
	fm->sockRebornResult((char *)pPacket);

	return 0;
}