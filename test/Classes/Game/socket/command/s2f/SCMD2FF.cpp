#include "SCMD2FF.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/figure/FigureMediator.h"

bool	SCMD2FF::Read()
{
	a_mercId1 = readInt();
	b_skill1 = readShort();
	c_mercId2 = readInt();
	d_skill2 = readShort();

	return true;
}

int32 	SCMD2FF::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2FFHandler::Execute(this) ;
}


uint32 SCMD2FFHandler::Execute(SCMD2FF* pPacket)
{
	if (!pPacket) return 1;

	CCLog("skill3:merch exchange skill response received.SCMD2FF");
	FigureMediator* _figureMediator = (FigureMediator*)g_pFacade->retrieveMediator(AppFacade_FIGURE_MEDIATOR);
	_figureMediator->sockMercSkillExchange((char*)pPacket);
	return 0;

	return 0;
}