#include "SCMD285.h"
#include "model/arena/ArenaProxy.h"
#include "control/AppFacade.h"

bool SCMD285::Read()
{
	a_meRank = readShort();	b_time = readUint();
	int16 SCMD285Node1Num = readShort();
	for (int i = 0; i < SCMD285Node1Num; i++)
	{
		SCMD285Node1 newnode;
		newnode.a_goodsId = readShort();
		newnode.b_num = readUint();

		c_rewards.push_back(newnode);
	}

	int16 SCMD285NodeNum = readShort();
	for (int i=0; i < SCMD285NodeNum; i++)
	{
		SCMD285Node newnode;
		newnode.a_rank = readShort();
		newnode.b_playerId = readInt();
		newnode.c_playerName = readString();
		newnode.d_level = readUint();

		d_rankArr.push_back(newnode);
	}

	return true;
}

int32 	SCMD285::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD285Handler::Execute(this) ;
}

uint32 SCMD285Handler::Execute(SCMD285* pPacket)
{
	if (!pPacket) return 1;

	ArenaProxy* _arenaProxy = (ArenaProxy*)g_pFacade->retrieveProxy(AppFacade_ARENA_PROXY);
	if (_arenaProxy)
		_arenaProxy->doHeroInfo(pPacket);
				
	return 0;
}