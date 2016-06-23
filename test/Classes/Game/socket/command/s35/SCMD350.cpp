#include "SCMD350.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/figure/FigureMediator.h"

bool	SCMD350::Read()
{
	a_figureId = readInt();
	b_isReborn = readByte();
	c_exp = readInt();
	d_lev = readByte();
	e_isUpgrade = readByte();

	return true;
}

int32 	SCMD350::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD350Handler::Execute(this) ;
}


uint32 SCMD350Handler::Execute(SCMD350* pPacket)
{
	if (!pPacket) return 1;

	FigureMediator* _figureMediator = (FigureMediator*)g_pFacade->retrieveMediator(AppFacade_FIGURE_MEDIATOR);
	_figureMediator->sockUpdateExp((char*)pPacket);
	return 0;

}