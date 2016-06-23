#include "SCMD273.h"

bool	SCMD273::Read()
{
	a_fbId = readUshort();
	b_teamId = readUshort();
	c_auto = readByte();
	d_captainId = readInt();
	int num = readUshort();
	for (int i = 0; i < num ; i++)
	{
		SCMD273Node node;
		node.a_sitNum = readUbyte();
		node.b_playerId = readInt();
		node.c_mercId = readUshort();
		node.d_playerName = readString();
		node.e_cryLev = readUbyte();
		node.f_guildName = readString();
		e_members.push_back(node);
	}

	return true;
}

int32 	SCMD273::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD273Handler::Execute(this) ;
}


uint32 SCMD273Handler::Execute(SCMD273* pPacket)
{
	if (!pPacket) return 1;


	return 0;
}