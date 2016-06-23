#include "SCMD36E.h"
#include "model/arena/ArenaProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool	SCMD36E::Read()
{
	a_result = readByte();
	b_id = readByte();

	int SCMD36ENodeNum = readShort();
	for (int i = 0; i < SCMD36ENodeNum; i++)
	{
		SCMD36ENode newnode;
		newnode.a_goodsId = readShort();
		newnode.b_count = readUint();

		c_rewards.push_back(newnode);
	}

	return true;
}

int32 	SCMD36E::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD36EHandler::Execute(this) ;
}


uint32 SCMD36EHandler::Execute(SCMD36E* pPacket)
{
	if (!pPacket) return 1;

	ArenaProxy* _arenaProxy = (ArenaProxy*)g_pFacade->retrieveProxy(AppFacade_ARENA_PROXY);
	if (_arenaProxy)
		_arenaProxy->doArenaAwardRes(pPacket);

	return 0;
}