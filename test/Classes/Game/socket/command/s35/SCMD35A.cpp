#include "socket/network/GameServerSocket.h"
#include "SCMD35A.h"
#include "view/train/TrainViewMediator.h"

bool	SCMD35A::Read()
{
	a_playerId = readInt();
	b_time = readInt();
	return true;
}

int32 	SCMD35A::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD35AHandler::Execute(this) ;
}


uint32 SCMD35AHandler::Execute( SCMD35A* pPacket )
{
	if (!pPacket) return 1;

	TrainViewMediator* pMediator = ( TrainViewMediator* )g_pFacade->retrieveMediator( AppFacade_TRAIN_PROXY_CHANGE );
	pMediator->startTrainingListener( pPacket );
	return 0;
}