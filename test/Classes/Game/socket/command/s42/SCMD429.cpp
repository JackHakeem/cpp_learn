#include "SCMD429.h"
#include "manager/LangManager.h"

bool SCMD429::Read()
{
	a_result = readByte();
	return true;
}

int32 SCMD429::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD429Handler::Execute(this);
}

uint32 SCMD429Handler::Execute( SCMD429* pPacket )
{
	if(!pPacket || pPacket->a_result == 0)
	{
		LangManager::msgShow("DTE202");
	}
	else
	{
		//LangManager::msgShow("DTE201");
	}

	return 0;
}
