#include "SCMD459.h"
//#include "control/campFight/campFightCommand.h"
#include "view/campFight/CampFightMediator.h"

bool SCMD459::Read()
{
	a_score = readShort();
	b_hisContiWinTms = readShort();
	c_sumPop = readShort();
	d_sumSilver = readInt();
	e_state = readShort();

	return true;
}

int32 SCMD459::Execute()
{
	if (!Read())
	{
		return 1;
	}
	return SCMD459Handler::Execute(this);
}

uint32 SCMD459Handler::Execute(SCMD459* pPacket)
{
	if (! pPacket)
		return 1;
	CampFightMediator* p = (CampFightMediator*)g_pFacade->retrieveMediator(AppFacade_CampFight_Mediator);
	if (p)
		//p->Update(pPacket);
	//sendNotification(Facade_Command, AppFacade_Ranking_Proxy_Change, (char*)pPacket, CampFightCommand::UPDATE_CAMPFIGHT_INFO);
	return 0;
}