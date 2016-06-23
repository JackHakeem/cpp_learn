#include "socket/network/GameServerSocket.h"
#include "SCMD354.h"
#include "view/train/TrainViewMediator.h"

bool	SCMD354::Read()
{
	a_result = readByte();
	b_posiNum = readByte();
	return true;
}

int32 	SCMD354::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD354Handler::Execute(this) ;
}


uint32 SCMD354Handler::Execute( SCMD354* pPacket )
{
	if (!pPacket) return 1;

	TrainViewMediator* pMediator = ( TrainViewMediator* )g_pFacade->retrieveMediator( AppFacade_TRAIN_PROXY_CHANGE );
	pMediator->buyPositionListener( pPacket );
	return 0;
}