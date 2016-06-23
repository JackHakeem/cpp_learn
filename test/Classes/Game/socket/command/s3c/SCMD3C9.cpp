#include "SCMD3C9.h"


#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/formation/FormationMediator.h"
 
#include "control/AppFacade.h"
#include "control/skill/SkillCommand.h"
#include "manager/GlobalManage.h"

bool	SCMD3C9::Read()
{   
	 
	a_TalentArr.clear();

	int16 cnt = readUshort();
	for(int i=0;i < cnt; ++i)
	{
		SCMD3C9Node node;
		node.a_talentId = readShort();   
		node.b_talentLv = readByte();
		a_TalentArr.push_back(node);
	}
	return true;
}

int32 	SCMD3C9::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD3C9Handler::Execute(this) ;
}


uint32 SCMD3C9Handler::Execute(SCMD3C9* pPacket)
{
	if (!pPacket) return 1;
	//SkillCommand* cmd = (SkillCommand*)g_pFacade->retrieveController(AppFacade_SKILL_COMMAND);


	g_pGlobalManage->loadOneProgress( 2 );
	return 0;
}

