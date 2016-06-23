#include "SCMD27D.h"

bool	SCMD27D::Read()
{
	a_fbId = readUshort();
	b_teamId = readUshort();
	c_ret = readUbyte();

	return true;
}

int32 	SCMD27D::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD27DHandler::Execute(this) ;
}


uint32 SCMD27DHandler::Execute(SCMD27D* pPacket)
{
	if (!pPacket) return 1;


	return 0;
}