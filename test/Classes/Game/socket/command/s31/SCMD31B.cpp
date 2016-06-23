#include "SCMD31B.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/skill/UpSkillMediator.h"

bool	SCMD31B::Read()
{  
	  a_formationId=readUshort() ;
      b_formationLel=readUbyte() ;
      c_roleSit=readUbyte() ;
	 

	return true;
}

int32 	SCMD31B::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD31BHandler::Execute(this) ;
}


uint32 SCMD31BHandler::Execute(SCMD31B* pPacket)
{
	if (!pPacket) return 1;



	//add code here
	CCLog("UPSkill:formation add response received,SCMD31B");
	UpSkillMediator * skillm = (UpSkillMediator*)g_pFacade->retrieveMediator(AppFacade_SKILL_COMMAND);
	skillm->formationAddedListener((char *)pPacket);



	return 0;
}