#include "SCMD31D.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/figure/FigureMediator.h"

bool	SCMD31D::Read()
{
	a_isSuccess = readByte();
	b_figureId = readInt();
	c_strength = readShort();
	d_stamina = readShort();
	e_intellect = readShort();

	return true;
}

int32 	SCMD31D::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD31DHandler::Execute(this) ;
}


uint32 SCMD31DHandler::Execute(SCMD31D* pPacket)
{
	if (!pPacket) return 1;

	FigureMediator* _figureMediator = (FigureMediator*)g_pFacade->retrieveMediator(AppFacade_FIGURE_MEDIATOR);

	_figureMediator->sockSaveWashValue((char*)pPacket);
	return 0;
}