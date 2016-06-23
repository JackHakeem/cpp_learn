#include "SCMD1C1.h"
#include "view/guild/GuildListenerMediator.h"

bool	SCMD1C1::Read()
{
	a_total = readShort();
	b_page = readShort();

	int16 SCMDNodeNum = readShort();	//Action number
	for(  int k = 0; k < (int)SCMDNodeNum; k++  )
	{
		SCMD1C1Node newnode;
		newnode.a_position = readByte();
		newnode.b_pID = readInt();
		newnode.c_pName = readString();
		newnode.d_pLevel = readShort();
		newnode.e_emblem = readInt();
		newnode.g_pState = readString();
		newnode.h_con = readInt();
		c_pArr.push_back(newnode);
	}

	return true;
}

int32 	SCMD1C1::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD1C1Handler::Execute(this) ;
}

uint32 SCMD1C1Handler::Execute(SCMD1C1* pPacket)
{
	if (!pPacket) return 1;

	g_pGuildListenerMediator->getMBListHandler( pPacket );

	return 0;
}