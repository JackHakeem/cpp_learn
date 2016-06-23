#include "SCMD45F.h"
#include "view/campFight/CampFightMediator.h"

bool SCMD45F::Read()
{
	//a_mod = readByte();
	b_res = readByte();
	c_harmInc = readByte();
	d_lifeInc = readByte();

	return true;
}

int32 SCMD45F::Execute()
{
	if (!Read())
	{
		return 1;
	}
	return SCMD45FHandler::Execute(this);
}

uint32 SCMD45FHandler::Execute(SCMD45F* pPacket)
{
	if (! pPacket)
		return 1;
	CampFightMediator* p = (CampFightMediator*)g_pFacade->retrieveMediator(AppFacade_CampFight_Mediator);
	if (p)
		p->UpdateInspire(pPacket);
	//sendNotification(Facade_Command, AppFacade_Ranking_Proxy_Change, (char*)pPacket, CampFightCommand::UPDATE_CAMPFIGHT_INFO);
	return 0;
}