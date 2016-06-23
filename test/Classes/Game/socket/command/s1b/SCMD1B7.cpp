#include "SCMD1B7.h"
#include "view/guild/GuildListenerMediator.h"

bool	SCMD1B7::Read()
{
	a_guildId = readInt();
	b_guildName = readString();
	c_guildLimit = readShort();

	return true;
}

int32 	SCMD1B7::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD1B7Handler::Execute(this) ;
}

uint32 SCMD1B7Handler::Execute(SCMD1B7* pPacket)
{
	if (!pPacket) return 1;

	g_pGuildListenerMediator->newGuildSuccessHandler(pPacket);

	return 0;
}