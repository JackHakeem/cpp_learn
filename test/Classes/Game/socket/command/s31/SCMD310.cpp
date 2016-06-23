#include "SCMD310.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/formation/FormationMediator.h"
#include "control/AppFacade.h"
#include "model/skill/SkillProxy.h"
#include "../c31/CCMD317.h"

bool	SCMD310::Read()
{  
	 a_isSuccess=readUbyte() ;         //Whether to replace successful
	 b_formationId= readUshort() ;   //Formation ID
	 c_srcId=readUint();                   //Operating mercenary unique ID
	 d_srcPos=readUbyte() ;               //Operating mercenary-for-to
	 e_destId=readUint();                 //Replacement of the unique ID of the position of the mercenary
	 f_destPos=readUbyte() ;             //Mercenary was traded to the location of

	return true;
}

int32 	SCMD310::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD310Handler::Execute(this) ;
}


uint32 SCMD310Handler::Execute(SCMD310* pPacket)
{
	if (!pPacket) return 1;

	 
	 
	// add code here
	FormationMediator* form=(FormationMediator*)g_pFacade->retrieveMediator(AppFacade_FORMATION_PROXY_CHANGE);
	form->sockMemberChange((char *)pPacket);
	
	return 0;
}