#include "SCMD31A.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "mvc/Facade.h"
#include "control/skill/SkillCommand.h"
#include "view/skill/UpSkillMediator.h"

bool	SCMD31A::Read()
{  
	  a_passiveId = readShort() ;
      b_passiveLel = readByte() ;
	 

	return true;
}

int32 	SCMD31A::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD31AHandler::Execute(this) ;
}


uint32 SCMD31AHandler::Execute(SCMD31A* pPacket)
{
	if (!pPacket) return 1;



	//add code here
	CCLog("UPSkill:skill add response received,SCMD31A");
//  	SkillCommand* skillCmd = (SkillCommand*)g_pFacade->retrieveController(AppFacade_SKILL_COMMAND);
//  	skillCmd->initSkillDic((char *)pPacket);
 	UpSkillMediator * skillm = (UpSkillMediator*)g_pFacade->retrieveMediator(AppFacade_SKILL_COMMAND);
 	skillm->skillAddedListener((char *)pPacket);
	return 0;
}