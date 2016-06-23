#include "SCMD361.h"
#include "model/arena/ArenaProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool	SCMD361::Read()
{
	a_state = readByte();
	b_rank = readUint();
	c_maxRank = readUint();
	d_winstreak = readUint();
	e_cd = readUint();
	l_refreshcd = readUint();//hwj
	f_quota = readUint();
	g_price = readUint();
	h_buyed = readUint();

	int SCMD361NodeNum = readShort();
	for (int i = 0; i < SCMD361NodeNum; i++)
	{
		SCMD361Node newnode;
		newnode.a_rank = readInt();
		newnode.b_accountId = readInt();
		newnode.c_name = readString();
		newnode.d_level = readInt();
		newnode.e_mercid = readShort();
		newnode.f_win = readByte();//hwj
		i_challengeArr.push_back(newnode);
	}

	int intNum = readShort();
	for (int i = 0; i < intNum; i++)
	{
		int newnode = readInt();
		j_resultArr.push_back(newnode);
	}

	int SCMD361Node2Num = readShort();
	for (int i = 0; i < SCMD361Node2Num; i++)
	{
		SCMD361Node2 newnode;
		newnode.a_time = readUint();
		newnode.b_name = readString();
		newnode.c_position = readByte();
		newnode.d_result = readByte();
		newnode.e_trend = readByte();
		newnode.f_report1 = readUint();
		newnode.g_report2 = readUint();

		k_reportArr.push_back(newnode);
	}

	return true;
}

int32 	SCMD361::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD361Handler::Execute(this) ;
}


uint32 SCMD361Handler::Execute(SCMD361* pPacket)
{
	if (!pPacket) return 1;

	ArenaProxy* _arenaProxy = (ArenaProxy*)g_pFacade->retrieveProxy(AppFacade_ARENA_PROXY);
	if (_arenaProxy)
		_arenaProxy->doArenaInfo(pPacket);

	return 0;
}