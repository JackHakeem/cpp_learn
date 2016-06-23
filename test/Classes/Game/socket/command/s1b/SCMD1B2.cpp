#include "SCMD1B2.h"
#include "view/guild/GuildListenerMediator.h"

bool	SCMD1B2::Read()
{
	a_total = readShort();
	b_page = readShort();

	int16 SCMDNodeNum = readShort();	//Action number
	for(  int k = 0; k < (int)SCMDNodeNum; k++  )
	{
		SCMD1B2Node newnode;
		newnode.a_rank = readShort();
		newnode.b_guildName = readString();
		newnode.c_leadName = readString();
		newnode.d_emblemLevel = readShort();
		newnode.e_memberNum = readShort();
		newnode.f_memberLimit = readShort();
		newnode.g_guildIntr = readString();
		newnode.h_flag = readByte();
		e_guildArr.push_back(newnode);
	}

	return true;
}

int32 	SCMD1B2::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD1B2Handler::Execute(this) ;
}

uint32 SCMD1B2Handler::Execute(SCMD1B2* pPacket)
{
	if (!pPacket) return 1;

	g_pGuildListenerMediator->getGListHandler(pPacket);

	return 0;
}