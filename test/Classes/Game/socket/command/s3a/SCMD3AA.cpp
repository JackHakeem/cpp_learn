#include "SCMD3AA.h"


#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/formation/FormationMediator.h"
#include "control/AppFacade.h"

bool	SCMD3AA::Read()
{  
	 a_tltId = readShort();
	 b_tltLv = readByte() ;
	 return true;
}

int32 	SCMD3AA::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD3AAHandler::Execute(this) ;
}


uint32 SCMD3AAHandler::Execute(SCMD3AA* pPacket)
{
	if (!pPacket) return 1;



	//add code here


	return 0;
}

