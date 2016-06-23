#include "SCMD318.h"


#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/formation/FormationMediator.h"
 
#include "control/AppFacade.h"
#include "view/skill/UpSkillMediator.h"
#include "manager/GlobalManage.h"

bool	SCMD318::Read()
{   
	 
	a_fomations.clear();

	SCMD318NodeNum=readUshort();
	for(int i=0;i<(int)SCMD318NodeNum;i++)
	{
		SCMD318Node node1;
		node1.a_formationId=readUshort();   
		node1.b_formationLel=readUbyte();
		node1.c_active=readUbyte();

		SCMD318Node2Num=readUshort();

		for(int j=0;j<(int)SCMD318Node2Num;j++){
			{
				SCMD318Node2 node2;
				node2.a_sitGrid=readUbyte();
				node2.b_figureId=readUint();

				node1.d_figures.push_back(node2);
			}
	}
		a_fomations.push_back(node1);
	 
}

// 	FormationMediator* form=(FormationMediator*)g_pFacade->retrieveMediator(AppFacade_FORMATION_PROXY_CHANGE);
// 	form->initFormationInfo((char*)&a_fomations );
	return true;
}

int32 	SCMD318::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD318Handler::Execute(this) ;
}


uint32 SCMD318Handler::Execute(SCMD318* pPacket)
{
	if (!pPacket) return 1;

	 CCLog("formation: formation info received SCMD318");
	//The simulated open formation panel, actual hair MainUI on the command SHOW_UI_FORMATION an open formation panel
	FormationMediator* form=(FormationMediator*)g_pFacade->retrieveMediator(AppFacade_FORMATION_PROXY_CHANGE);
	//form->openFormationView();	
	form->initFormationInfo((char*)&pPacket->a_fomations);

	CCLog("UPSkill:formation info received SCMD318");
	UpSkillMediator * skillm = (UpSkillMediator*)g_pFacade->retrieveMediator(AppFacade_SKILL_COMMAND);
	skillm->formationInfoListener((char *)pPacket);
	
	g_pGlobalManage->loadOneProgress( 2 );
	return 0;
}

