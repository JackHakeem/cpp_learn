#include "SCMD1CB.h"
#include "view/guild/GuildListenerMediator.h"

bool	SCMD1CB::Read()
{
	a_guildId = readInt();
	b_retNum = readByte();
	c_name = readString();

	return true;
}

int32 	SCMD1CB::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD1CBHandler::Execute(this) ;
}

uint32 SCMD1CBHandler::Execute(SCMD1CB* pPacket)
{
	if (!pPacket) return 1;

	g_pGuildListenerMediator->getApplyHandler( pPacket );

	return 0;
}