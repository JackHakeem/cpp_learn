#include "SCMD287.h"
#include "model/arena/ArenaProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD287::Read()
{
    a_ret = readByte();

	int SCMD287NodeNum = readShort();
	for (int i = 0; i < SCMD287NodeNum; i++)
	{
		SCMD287Node newnode;
		newnode.a_goodsId = readShort();
		newnode.b_num = readUint();

		b_rewards.push_back(newnode);
	}

	return true;
}

int32 	SCMD287::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD287Handler::Execute(this) ;
}

uint32 SCMD287Handler::Execute(SCMD287* pPacket)
{
	if (!pPacket) return 1;

	ArenaProxy* _arenaProxy = (ArenaProxy*)g_pFacade->retrieveProxy(AppFacade_ARENA_PROXY);
	if (_arenaProxy)
		_arenaProxy->doGiftPackage(pPacket);

	return 0;
}