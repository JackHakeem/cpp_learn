#include "SCMD316.h"


#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/formation/FormationMediator.h"
#include "control/AppFacade.h"
#include "view/skill/UpSkillMediator.h"

bool	SCMD316::Read()
{  
	 a_isOk = readByte();
	 b_passiveId = readShort() ;
	 c_passiveLel = readByte() ;

	 /*FormationMediator* form=(FormationMediator*)g_pFacade->retrieveMediator(AppFacade_FORMATION_PROXY_CHANGE);
	 form->sockFormationActive( a_isOk, b_startId, c_stopId);*/
	 return true;
}

int32 	SCMD316::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD316Handler::Execute(this) ;
}


uint32 SCMD316Handler::Execute(SCMD316* pPacket)
{
	if (!pPacket) return 1;



	//add code here
	CCLog("UPSkill:upgrade skill response received SCMD316");
	UpSkillMediator * skillm = (UpSkillMediator*)g_pFacade->retrieveMediator(AppFacade_SKILL_COMMAND);
	skillm->skillUpgradeListener((char *)pPacket);


	return 0;
}

