#include "SCMD453.h"
//#include "control/campFight/campFightCommand.h"
#include "view/campFight/CampFightMediator.h"

bool SCMD453::Read()
{
	a_res = readByte();
	return true;
}

int32 SCMD453::Execute()
{
	if (!Read())
	{
		return 1;
	}
	return SCMD453Handler::Execute(this);
}

uint32 SCMD453Handler::Execute(SCMD453* pPacket)
{
	if (! pPacket)
		return 1;
	CampFightMediator* p = (CampFightMediator*)g_pFacade->retrieveMediator(AppFacade_CampFight_Mediator);
	if (p)
		p->CloseCampFightView(pPacket->a_res);
	//sendNotification(Facade_Command, AppFacade_Ranking_Proxy_Change, (char*)pPacket, CampFightCommand::UPDATE_CAMPFIGHT_INFO);
	return 0;
}