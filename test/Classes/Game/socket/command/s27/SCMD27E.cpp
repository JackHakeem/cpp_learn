#include "SCMD27E.h"

bool	SCMD27E::Read()
{
	a_fbId = readUshort();
	b_teamId = readUshort();

	return true;
}

int32 	SCMD27E::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD27EHandler::Execute(this) ;
}


uint32 SCMD27EHandler::Execute(SCMD27E* pPacket)
{
	if (!pPacket) return 1;


	return 0;
}