#include "SCMD172.h"
#include "socket/network/GameServerSocket.h"
#include "view/figure/FigureMediator.h"
bool	SCMD172::Read()
{
	a_figureId = readInt();
	b_sitGrid = readByte();
	c_eqpId = readInt();
	d_eqpGoodsId = readShort();
	
	return true;
}

int32 	SCMD172::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD172Handler::Execute(this) ;
}


uint32 SCMD172Handler::Execute(SCMD172* pPacket)
{
	if (!pPacket) return 1;
	CCLog("Role:Role equipment update response received SCMD172");
	FigureMediator* _figureMediator = (FigureMediator*)g_pFacade->retrieveMediator(AppFacade_FIGURE_MEDIATOR);
	_figureMediator->sockEquipItemUpdate((char*)pPacket);
	return 0;
}