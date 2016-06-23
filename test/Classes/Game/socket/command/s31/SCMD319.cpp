#include "SCMD319.h"


#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/formation/FormationMediator.h"
 
#include "control/AppFacade.h"
#include "control/skill/SkillCommand.h"
#include "view/skill/UpSkillMediator.h"
#include "manager/GlobalManage.h"

bool	SCMD319::Read()
{   
	 
	a_skills.clear();

	int16 cnt = readUshort();
	for(int i=0;i < cnt; ++i)
	{
		SCMD319Node node;
		node.a_skillId = readShort();   
		node.b_skillLel = readByte();
		node.c_active = readByte();
		a_skills.push_back(node);
	}
	return true;
}

int32 	SCMD319::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD319Handler::Execute(this) ;
}


uint32 SCMD319Handler::Execute(SCMD319* pPacket)
{
	if (!pPacket) return 1;

	CCLog("Skill3:passive skill response received,SCMD319");
 	UpSkillMediator * skillm = (UpSkillMediator*)g_pFacade->retrieveMediator(AppFacade_SKILL_COMMAND);
 	skillm->UpSkillInfoListener((char*)pPacket);
// 	SkillCommand* skillCmd = (SkillCommand*)g_pFacade->retrieveController(AppFacade_SKILL_COMMAND);
// 	skillCmd->initSkillDic((char *)pPacket);

	g_pGlobalManage->loadOneProgress( 2 );
	return 0;
}

