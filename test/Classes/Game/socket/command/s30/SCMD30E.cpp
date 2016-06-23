#include "SCMD30E.h"
#include "socket/network/GameServerSocket.h"
#include "view/figure/FigureMediator.h"
bool	SCMD30E::Read()
{
	a_isSucceed = readByte();
	b_merId = readInt();
	c_skillRank = readByte();
	d_skillId = readShort();
	e_exSkillId = readShort();
	
	return true;
}

int32 	SCMD30E::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD30EHandler::Execute(this) ;
}


uint32 SCMD30EHandler::Execute(SCMD30E* pPacket)
{
	if (!pPacket) return 1;
	
	CCLog("skill3:passive skill changed response received SCMD30E");
	FigureMediator* _figureMediator = (FigureMediator*)g_pFacade->retrieveMediator(AppFacade_FIGURE_MEDIATOR);
	_figureMediator->sockEqipSkillUpdate((char*)pPacket);

	return 0;
}