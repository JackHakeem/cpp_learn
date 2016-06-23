#include "SCMD1BC.h"
#include "view/guild/GuildListenerMediator.h"

bool	SCMD1BC::Read()
{
	a_total = readShort();
	b_page = readShort();

	int16 SCMDNodeNum = readShort();	//Action number
	for(  int k = 0; k < (int)SCMDNodeNum; k++  )
	{
		SCMD1BCNode newnode;
		newnode.a_pName = readString();
		newnode.b_pLevel = readShort();
		newnode.c_prestige = readInt();
		newnode.d_applyDate = readString();
		c_applyArr.push_back(newnode);
	}

	return true;
}

int32 	SCMD1BC::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD1BCHandler::Execute(this) ;
}

uint32 SCMD1BCHandler::Execute(SCMD1BC* pPacket)
{
	if (!pPacket) return 1;

	g_pGuildListenerMediator->getApListHandler(pPacket);

	return 0;
}