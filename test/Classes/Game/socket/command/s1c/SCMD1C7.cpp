#include "view/guild/GuildListenerMediator.h"
#include "SCMD1C7.h"

bool	SCMD1C7::Read()
{
	a = readByte();

	return true;
}

int32 	SCMD1C7::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD1C7Handler::Execute(this) ;
}

uint32 SCMD1C7Handler::Execute(SCMD1C7* pPacket)
{
	if (!pPacket) return 1;

	g_pGuildListenerMediator->oprateHandler(pPacket);

	return 0;
}