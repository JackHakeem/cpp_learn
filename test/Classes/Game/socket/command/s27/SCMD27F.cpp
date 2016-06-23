#include "SCMD27F.h"

bool	SCMD27F::Read()
{
	a_fbId = readUshort();
	b_teamId = readUshort();
	c_result = readUbyte();
	d_prac = readInt();
	e_silver = readInt();
	f_goodId = readInt();

	return true;
}

int32 	SCMD27F::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD27FHandler::Execute(this) ;
}


uint32 SCMD27FHandler::Execute(SCMD27F* pPacket)
{
	if (!pPacket) return 1;


	return 0;
}