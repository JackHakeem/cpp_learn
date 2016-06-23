#include "SCMD31F.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/figure/FigureMediator.h"

bool	SCMD31F::Read()
{
	a_isSuccess = readByte();
	b_figureId = readInt();
	c_strength = readShort();
	d_stamina = readShort();
	e_intellect = readShort();

	return true;
}

int32 	SCMD31F::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD31FHandler::Execute(this) ;
}


uint32 SCMD31FHandler::Execute(SCMD31F* pPacket)
{
	if (!pPacket) return 1;

	FigureMediator* _figureMediator = (FigureMediator*)g_pFacade->retrieveMediator(AppFacade_FIGURE_MEDIATOR);
	_figureMediator->sockRefreshWashValue((char*)pPacket);
	return 0;
}