#include "SCMD27B.h"

bool	SCMD27B::Read()
{
	a_fbId = readUshort();
	b_teamId = readUshort();
	c_ret = readUbyte();

	return true;
}

int32 	SCMD27B::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD27BHandler::Execute(this) ;
}


uint32 SCMD27BHandler::Execute(SCMD27B* pPacket)
{
	if (!pPacket) return 1;


	return 0;
}