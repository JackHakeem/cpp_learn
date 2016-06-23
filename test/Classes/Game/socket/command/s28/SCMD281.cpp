#include "SCMD281.h"

bool	SCMD281::Read()
{
	a_fbId = readUshort();
	b_teamId = readUshort();
	c_playerId = readInt();
	d_ret = readUbyte();

	return true;
}

int32 	SCMD281::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD281Handler::Execute(this) ;
}


uint32 SCMD281Handler::Execute(SCMD281* pPacket)
{
	if (!pPacket) return 1;


	return 0;
}