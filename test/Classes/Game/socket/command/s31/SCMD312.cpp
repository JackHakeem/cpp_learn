#include "SCMD312.h"


#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/formation/FormationMediator.h"
#include "control/AppFacade.h"

bool	SCMD312::Read()
{  
	 a_isOk=readUbyte() ;
	 b_startId=readUshort() ;
	 c_stopId=readUshort() ;
	 return true;
}

int32 	SCMD312::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD312Handler::Execute(this) ;
}


uint32 SCMD312Handler::Execute(SCMD312* pPacket)
{
	if (!pPacket) return 1;



	//add code here
	FormationMediator* form=(FormationMediator*)g_pFacade->retrieveMediator(AppFacade_FORMATION_PROXY_CHANGE);
	form->sockFormationActive((char*)pPacket);

	return 0;
}

