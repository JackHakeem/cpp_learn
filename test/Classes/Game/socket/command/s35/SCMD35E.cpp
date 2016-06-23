#include "SCMD35E.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/figure/FigureMediator.h"

bool	SCMD35E::Read()
{
	a_mercId = readInt();
	b_att = readInt();

	return true;
}

int32 	SCMD35E::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD35EHandler::Execute(this) ;
}


uint32 SCMD35EHandler::Execute(SCMD35E* pPacket)
{
	if (!pPacket) return 1;

	FigureMediator* _figureMediator = (FigureMediator*)g_pFacade->retrieveMediator(AppFacade_FIGURE_MEDIATOR);
	_figureMediator->attPointChange((char*)pPacket);
	return 0;
}