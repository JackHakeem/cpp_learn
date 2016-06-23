#include "SCMD1D6.h"
#include "view/guild/GuildListenerMediator.h"

bool	SCMD1D6::Read()
{
	a_limit = readInt();
	b_donate = readInt();

	return true;
}

int32 	SCMD1D6::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD1D6Handler::Execute(this) ;
}

uint32 SCMD1D6Handler::Execute(SCMD1D6* pPacket)
{
	if (!pPacket) return 1;

	g_pGuildListenerMediator->receiveDonateData( pPacket );

	return 0;
}