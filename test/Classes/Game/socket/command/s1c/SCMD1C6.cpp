#include "SCMD1C6.h"
#include "view/guild/GuildListenerMediator.h"

bool	SCMD1C6::Read()
{
	a_total = readShort();
	b_page = readShort();
	c_defaultId = readShort();

	int16 SCMDNodeNum = readShort();	//Action number
	for(  int k = 0; k < (int)SCMDNodeNum; k++  )
	{
		SCMD1C6Node newnode;
		newnode.a_scienceId = readShort();
		newnode.b_scienceLevel = readShort();
		newnode.c_requrieYB = readInt();
		newnode.d_hasYB = readInt();
		d_scienceArr.push_back(newnode);
	}

	return true;
}

int32 	SCMD1C6::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD1C6Handler::Execute(this) ;
}

uint32 SCMD1C6Handler::Execute(SCMD1C6* pPacket)
{
	if (!pPacket) return 1;

	g_pGuildListenerMediator->getTEListHandler(pPacket);

	return 0;
}