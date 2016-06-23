#include "SCMD277.h"

bool	SCMD277::Read()
{
	a_fbId = readUshort();
	b_teamId = readUshort();
	c_ret = readUbyte();

	return true;
}

int32 	SCMD277::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD277Handler::Execute(this) ;
}


uint32 SCMD277Handler::Execute(SCMD277* pPacket)
{
	if (!pPacket) return 1;


	return 0;
}