#include "SCMD455.h"
#include "view/campFight/CampFightMediator.h"

bool SCMD455::Read()
{
	a_res = readByte();
	return true;
}

int32 SCMD455::Execute()
{
	if (!Read())
	{
		return 1;
	}
	return SCMD455Handler::Execute(this);
}

uint32 SCMD455Handler::Execute(SCMD455* pPacket)
{
	if (! pPacket)
		return 1;
	CampFightMediator* p = (CampFightMediator*)g_pFacade->retrieveMediator(AppFacade_CampFight_Mediator);
	if (p)
		p->Fight(pPacket->a_res);
	//sendNotification(Facade_Command, AppFacade_Ranking_Proxy_Change, (char*)pPacket, CampFightCommand::UPDATE_CAMPFIGHT_INFO);
	return 0;
}