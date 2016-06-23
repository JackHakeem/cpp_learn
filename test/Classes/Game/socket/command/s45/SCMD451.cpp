#include "SCMD451.h"
//#include "control/campFight/campFightCommand.h"
#include "view/campFight/CampFightMediator.h"

bool SCMD451::Read()
{
	a_res = readInt();
	return true;
}

int32 SCMD451::Execute()
{
	if (!Read())
	{
		return 1;
	}
	return SCMD451Handler::Execute(this);
}

uint32 SCMD451Handler::Execute(SCMD451* pPacket)
{
	if (! pPacket)
		return 1;
	CampFightMediator* p = (CampFightMediator*)g_pFacade->retrieveMediator(AppFacade_CampFight_Mediator);
	if (p)
		p->OpenCampFightView(pPacket->a_res);
		//p->Update(pPacket);
	//sendNotification(Facade_Command, AppFacade_Ranking_Proxy_Change, (char*)pPacket, CampFightCommand::UPDATE_CAMPFIGHT_INFO);
	return 0;
}