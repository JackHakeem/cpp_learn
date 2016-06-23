#include "SCMD29A.h"
#include "manager/LangManager.h"

bool	SCMD29A::Read()
{
	a_reward = readShort();

	return true;
}

int32 	SCMD29A::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD29AHandler::Execute(this) ;
}


uint32 SCMD29AHandler::Execute(SCMD29A* pPacket)
{
	if (!pPacket) return 1;

	if(pPacket->a_reward == -1)
	{
		LangManager::msgShow("VIP075");
	}
	return 0;
}