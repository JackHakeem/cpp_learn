#include "SCMD3C2.h"
#include "view/tower/TowerMediator.h"

bool	SCMD3C2::Read()
{  
	a_isSuccess = readInt();
	b_type = readByte();
	c_resultNo = readByte();

	return true;
}

int32 	SCMD3C2::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD3C2Handler::Execute(this) ;
}


uint32 SCMD3C2Handler::Execute(SCMD3C2* pPacket)
{
	if (!pPacket) return 1;

	//add code here
	if ( g_pTowerMediator )
		g_pTowerMediator->takeAwardListener( pPacket );

	return 0;
}