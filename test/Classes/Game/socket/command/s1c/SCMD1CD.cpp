#include "SCMD1CD.h"
#include "view/guild/GuildListenerMediator.h"

bool	SCMD1CD::Read()
{
	a_flag = readByte();

	return true;
}

int32 	SCMD1CD::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD1CDHandler::Execute(this) ;
}

uint32 SCMD1CDHandler::Execute(SCMD1CD* pPacket)
{
	if (!pPacket) return 1;

	g_pGuildListenerMediator->exitGuildReturnHandler( pPacket );

	return 0;
}