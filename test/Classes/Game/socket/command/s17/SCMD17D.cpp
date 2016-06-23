#include "SCMD17D.h"
#include "socket/network/GameServerSocket.h"
#include "view/figure/FigureMediator.h"
#include "view/mainStreng/MainStrengMediator.h"

bool	SCMD17D::Read()
{
	a_Probability = readByte();
	b_Trend = readByte();

	return true;
}

int32 	SCMD17D::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD17DHandler::Execute(this) ;
}


uint32 SCMD17DHandler::Execute( SCMD17D* pPacket )
{
	if (!pPacket) return 1;

	if ( g_pMainStrengMediator )
	{
		g_pMainStrengMediator->sockStrengPROBchange( pPacket );
	}
	return 0;
}