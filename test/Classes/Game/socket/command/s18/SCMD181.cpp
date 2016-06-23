#include "SCMD181.h"
#include "view/mainStreng/MainStrengMediator.h"


bool	SCMD181::Read()
{  
	a_isSuccess = readByte();
	b_typeSit = readByte();
	c_sit = readByte();
	d_isVIP = readByte();
	e_probability = readByte();
	f_strengChange = readByte();
	g_roleID = readInt();
	h_strengLevle = readByte();

	return true;
}

int32 	SCMD181::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD181Handler::Execute(this) ;
}


uint32 SCMD181Handler::Execute(SCMD181* pPacket)
{
	if (!pPacket) return 1;

	//add code here
	g_pMainStrengMediator->sockStrengInfo( pPacket );

	return 0;
}