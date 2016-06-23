#include "SCMD1B8.h"
#include "view/guild/GuildListenerMediator.h"

bool	SCMD1B8::Read()
{
	a_type = readByte();
	b_operator = readString();
	c_target = readString();
	d_param1 = readInt();
	e_param2 = readInt();

	return true;
}

int32 	SCMD1B8::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD1B8Handler::Execute(this) ;
}

uint32 SCMD1B8Handler::Execute(SCMD1B8* pPacket)
{
	if (!pPacket) return 1;

	g_pGuildListenerMediator->showGuildTip( pPacket );

	return 0;
}