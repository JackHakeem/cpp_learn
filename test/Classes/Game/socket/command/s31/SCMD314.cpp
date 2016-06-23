#include "SCMD314.h"


#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/formation/FormationMediator.h"
#include "control/AppFacade.h"
#include "view/skill/UpSkillMediator.h"

bool	SCMD314::Read()
{  
	 a_isOk = readByte();
	 b_formationId = readShort() ;
	 c_formationLel = readByte() ;

	 /*FormationMediator* form=(FormationMediator*)g_pFacade->retrieveMediator(AppFacade_FORMATION_PROXY_CHANGE);
	 form->sockFormationActive( a_isOk, b_startId, c_stopId);*/
	 return true;
}

int32 	SCMD314::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD314Handler::Execute(this) ;
}


uint32 SCMD314Handler::Execute(SCMD314* pPacket)
{
	if (!pPacket) return 1;



	//add code here
	CCLog("UPSkill:upgrade formation response received SCMD314");
	UpSkillMediator * skillm = (UpSkillMediator*)g_pFacade->retrieveMediator(AppFacade_SKILL_COMMAND);
	skillm->formationUpgradeListener((char *)pPacket);




	return 0;
}

