#include "SCMD279.h"

bool	SCMD279::Read()
{
	a_fbId = readUshort();
	b_teamId = readUshort();
	c_ret = readUbyte();

	return true;
}

int32 	SCMD279::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD279Handler::Execute(this) ;
}


uint32 SCMD279Handler::Execute(SCMD279* pPacket)
{
	if (!pPacket) return 1;


	return 0;
}