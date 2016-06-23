#include "socket/network/GameServerSocket.h"
#include "view/train/TrainViewMediator.h"
#include "SCMD358.h"

bool SCMD358::Read()
{
	a_playerId = readInt();
	b_result = readByte();
	return true;
}

int32 	SCMD358::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD358Handler::Execute(this) ;
}


uint32 SCMD358Handler::Execute( SCMD358* pPacket )
{
	if (!pPacket) return 1;

	TrainViewMediator* pMediator = ( TrainViewMediator* )g_pFacade->retrieveMediator( AppFacade_TRAIN_PROXY_CHANGE );
	pMediator->endTrainingListener( (char*)pPacket );
	return 0;
}