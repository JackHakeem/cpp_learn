#include "socket/network/GameServerSocket.h"
#include "SCMD35C.h"
#include "view/train/TrainViewMediator.h"

bool	SCMD35C::Read()
{
	a_playerId = readInt();
	b_rapidExp = readInt();
	c_goldPrice = readShort();
	d_critExp = readInt();
	return true;
}

int32 	SCMD35C::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD35CHandler::Execute(this) ;
}


uint32 SCMD35CHandler::Execute( SCMD35C* pPacket )
{
	if (!pPacket) return 1;

	TrainViewMediator* pMediator = ( TrainViewMediator* )g_pFacade->retrieveMediator( AppFacade_TRAIN_PROXY_CHANGE );
	pMediator->rapicLeapListener( (char*)pPacket );
	return 0;
}