#include "SCMD275.h"

bool	SCMD275::Read()
{
	a_fbId = readUshort();
	b_ret = readUbyte();
	c_teamId = readUshort();

	return true;
}

int32 	SCMD275::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD275Handler::Execute(this) ;
}


uint32 SCMD275Handler::Execute(SCMD275* pPacket)
{
	if (!pPacket) return 1;


	return 0;
}