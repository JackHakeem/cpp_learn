#include "SCMD1BF.h"
#include "view/guild/GuildListenerMediator.h"

bool	SCMD1BF::Read()
{
	a_guildName = readString();
	b_leaderName = readString();
	c_emblemLevel = readShort();
	d_guildLevel = readShort();
	e_guildRank = readShort();
	f_memberNum = readShort();
	g_memberLimit = readShort();
	h_createDate = readString();
	i_qqGN = readString();
	j_notice = readString();
	l_intro = readString();
	m_state = readByte();
	n_abortTime = readInt();

	return true;
}

int32 	SCMD1BF::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD1BFHandler::Execute(this) ;
}

uint32 SCMD1BFHandler::Execute(SCMD1BF* pPacket)
{
	if (!pPacket) return 1;

	g_pGuildListenerMediator->getGInfoHandler(pPacket);

	return 0;
}