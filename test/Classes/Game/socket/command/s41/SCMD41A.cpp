#include "SCMD41A.h"
#include "model/battle/FightProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "manager/GlobalManage.h"
#include "manager/BattleManager.h"
#include "manager/LangManager.h"
#include "manager/LayerManager.h"
#include "view/dungeonEntrys/components/DungeonGuaView.h"
#include "view/dungeonEntrys/components/ChallengeGuaView.h"

bool SCMD41A::Read()
{
	_battleIndex = readByte();
	_monsterGroupId = readUint();


	int16 rewardCount = readShort();
	for(int16 i=0; i<rewardCount; ++i)
	{
		SCMD41ANode node;
		node._goodsId = readInt();
		node._goodsNum = readInt();
		_rewards.push_back(node);
	}

	int16 expCount = readShort();
	for(int16 i=0; i<expCount; ++i)
	{
		SCMD41ANode2 node;
		node._id = readInt();
		node._plusExp = readInt();
		node._isUpgrade = readByte();
		_exps.push_back(node);
	}

	return true;
}

int32 SCMD41A::Execute()
{
	if (!Read())
	{
		return 1;
	}
	return SCMD41AHandler::Execute(this) ;
}

uint32 SCMD41AHandler::Execute(SCMD41A* pPacket)
{
	if (!pPacket) return 1;
	//此协议服务器暂时不会下发，全部客户端所需展示内容由SCMD3B7完成

	return 0;
}

