#include "SCMD1C3.h"
#include "view/guild/GuildListenerMediator.h"

bool	SCMD1C3::Read()
{
	a_total = readShort();
	b_page = readShort();

	int16 SCMDNodeNum = readShort();	//Action number
	for(  int k = 0; k < (int)SCMDNodeNum; k++  )
	{
		SCMD1C3Node newnode;
		newnode.a_position = readByte();
		newnode.b_pID = readInt();
		newnode.c_pName = readString();
		newnode.d_pLevel = readShort();
		newnode.e_emblem = readInt();
		newnode.g_pState = readString();
		c_nodeArr.push_back(newnode);
	}

	return true;
}

int32 	SCMD1C3::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD1C3Handler::Execute(this) ;
}

uint32 SCMD1C3Handler::Execute(SCMD1C3* pPacket)
{
	if (!pPacket) return 1;

	g_pGuildListenerMediator->getMBInfoHandler( pPacket );

	return 0;
}