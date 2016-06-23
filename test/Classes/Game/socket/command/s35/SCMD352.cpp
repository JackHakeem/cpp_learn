#include "socket/network/GameServerSocket.h"
#include "SCMD352.h"
#include "view/train/TrainViewMediator.h"
#include "manager/GlobalManage.h"

bool	SCMD352::Read()
{
	a_goldPrice = readShort();

	int16 SCMD352NodeNum = readShort();	//Action number
	for(  int k = 0; k < (int)SCMD352NodeNum; k++  )
	{

		SCMD352Node newnode;
		newnode.a_playerId = readInt();
		newnode.b_mode = readByte();
		newnode.c_time = readInt();
		b_players.push_back(newnode);
	}


	return true;
}

int32 	SCMD352::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD352Handler::Execute(this) ;
}


uint32 SCMD352Handler::Execute( SCMD352* pPacket )
{
	if (!pPacket) return 1;

	TrainViewMediator* pMediator = ( TrainViewMediator* )g_pFacade->retrieveMediator( AppFacade_TRAIN_PROXY_CHANGE );
	pMediator->trainListListener( (char*)pPacket );

	g_pGlobalManage->loadOneProgress( 2 );
	return 0;
}