#include "SCMD105.h"
#include "LoginManage.h"
#include "../c24/CCMD24A.h"
#include "../../network/GateServerSocket.h"

bool	SCMD105::Read()
{
	a_result = readShort();

	return true;
}

int32 	SCMD105::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD105Handler::Execute(this) ;
}


uint32 SCMD105Handler::Execute(SCMD105* pPacket)
{
	if (!pPacket) return 1;
	
	if (g_pLoginManage)
	{
		g_pLoginManage->onCreateAccHandler((char *)pPacket);
	}

	return 0;
}