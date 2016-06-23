#include "SCMD419.h"
#include "model/battle/FightProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "manager/GlobalManage.h"
#include "manager/BattleManager.h"
#include "manager/LangManager.h"
#include "manager/LayerManager.h"
#include "view/dungeonEntrys/components/DungeonGuaView.h"
#include "view/dungeonEntrys/components/ChallengeGuaView.h"

bool SCMD419::Read()
{
	_battleIndex = readByte();
	_monsterGroupId = readUint();


	int16 rewardCount = readShort();
	for(int16 i=0; i<rewardCount; ++i)
	{
		SCMD419Node node;
		node._goodsId = readInt();
		node._goodsNum = readInt();
		_rewards.push_back(node);
	}

	int16 expCount = readShort();
	for(int16 i=0; i<expCount; ++i)
	{
		SCMD419Node2 node;
		node._id = readInt();
		node._plusExp = readInt();
		node._isUpgrade = readByte();
		_exps.push_back(node);
	}

	return true;
}

int32 SCMD419::Execute()
{
	if (!Read())
	{
		return 1;
	}
	return SCMD419Handler::Execute(this) ;
}

uint32 SCMD419Handler::Execute(SCMD419* pPacket)
{
	if (!pPacket) return 1;
	//更新挂机面板信息
	if (g_pGlobalManage->getDunMapId() >= 1201 && 
		g_pGlobalManage->getDunMapId() <= 1209 && 
		g_pGlobalManage->getDunMapId() != 1208)
	{
		ChallengeGuaView* guaView = (ChallengeGuaView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_dungeonGua);
		if (guaView)
		{
			guaView->addRecords(pPacket);
		}	
	}
	else
	{
		DungeonGuaView* guaView = (DungeonGuaView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_dungeonGua);
		if (guaView)
		{
			guaView->addRecords(pPacket);
		}	
	}

	return 0;
}

