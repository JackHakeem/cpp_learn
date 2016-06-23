#include "SCMD271.h"

bool	SCMD271::Read()
{
	a_fbId = readUshort();
	int num = readUshort();
	for (int i = 0; i < num ; i++)
	{
		SCMD271Node node;
		node.a_teamId = readUshort();
		node.b_captain = readString();
		node.c_type = readUbyte();
		node.d_currNum = readUbyte();
		node.e_guildId = readUint();
		node.f_guildName = readString();
		node.g_auto = readByte();
		b_teams.push_back(node);
	}
	
	return true;
}

int32 	SCMD271::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD271Handler::Execute(this) ;
}


uint32 SCMD271Handler::Execute(SCMD271* pPacket)
{
	if (!pPacket) return 1;


	return 0;
}