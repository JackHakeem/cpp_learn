#include "SCMD446.h"
#include "socket/network/GameServerSocket.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "manager/LangManager.h"
#include "view/gong/GongMediator.h"

bool	SCMD446::Read()
{
	a_wave = readUint();

	short b_rankingNum = readShort();
	for (int i = 0; i < b_rankingNum; i++)
	{
		GongRanking newnode;
		newnode.name = readString();
		newnode.killed = readUint();
		b_ranking.push_back(newnode);
	}

	return true;
}

int32 	SCMD446::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD446Handler::Execute(this) ;
}


uint32 SCMD446Handler::Execute(SCMD446* pPacket)
{
	if (!pPacket) return 1;

	GongMediator* p = (GongMediator*)g_pFacade->retrieveMediator(AppFacade_GONG);
	if (p)
		p->updateRankingView(pPacket);
	
	return 0;
}