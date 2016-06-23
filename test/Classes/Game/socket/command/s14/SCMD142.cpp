#include "SCMD142.h"
#include "socket/network/GameServerSocket.h"
#include "view/battle/SceneFightMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "view/honor/HonorMediator.h"

bool	SCMD142::Read()
{
	a_currentpoint = readInt();
	b_rolehononameid = readShort();

	int16 cnt = readShort();	//Action number
	for(  int k = 0; k < (int)cnt; k++  )
	{

		SCMD142Node1 newnode;
		newnode.a_honorid = readShort();
		newnode.b_completed = readByte();
		c_idlist.push_back(newnode);
	}
		
	cnt = readShort();	//Action number
	for(  int k = 0; k < (int)cnt; k++  )
	{

		SCMD142Node2 newnode;
		newnode.a_wardpoint = readShort();
		d_pointlist.push_back(newnode);
	}

	return true;
}

int32 	SCMD142::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD142Handler::Execute(this) ;
}


uint32 SCMD142Handler::Execute(SCMD142* pPacket)
{
	if (!pPacket) return 1;

	if ( g_pHonorMediator )
	{
		g_pHonorMediator->socketHasReachHonorList( pPacket );
	}

	return 0;
}