#include "SCMD3AC.h"


#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/formation/FormationMediator.h"
#include "control/AppFacade.h"

bool	SCMD3AC::Read()
{  
	 a_isSuccess = readByte();
	 b_tltId = readShort() ;
	 c_newLv = readByte() ;
	 return true;
}

int32 	SCMD3AC::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD3ACHandler::Execute(this) ;
}


uint32 SCMD3ACHandler::Execute(SCMD3AC* pPacket)
{
	if (!pPacket) return 1;



	//add code here


	return 0;
}

