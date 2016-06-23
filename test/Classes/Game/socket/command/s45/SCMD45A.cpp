#include "SCMD45A.h"
#include "view/campFight/CampFightMediator.h"

bool SCMD45A::Read()
{
	a_msg = readString();

	return true;
}

int32 SCMD45A::Execute()
{
	if (!Read())
	{
		return 1;
	}
	return SCMD45AHandler::Execute(this);
}

uint32 SCMD45AHandler::Execute(SCMD45A* pPacket)
{
	if (! pPacket)
		return 1;
	CampFightMediator* p = (CampFightMediator*)g_pFacade->retrieveMediator(AppFacade_CampFight_Mediator);
	if (p)
		p->UpdateLiveMsg(pPacket);
	//sendNotification(Facade_Command, AppFacade_Ranking_Proxy_Change, (char*)pPacket, CampFightCommand::UPDATE_CAMPFIGHT_INFO);
	return 0;
}