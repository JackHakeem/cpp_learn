#include "SCMD13D.h"
#include "model/battle/FightProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "manager/GlobalManage.h"
#include "manager/BattleManager.h"
#include "manager/LangManager.h"
#include "manager/LayerManager.h"
#include "view/dungeonEntrys/components/DungeonGuaView.h"
#include "view/dungeonEntrys/components/ChallengeGuaView.h"

bool SCMD13D::Read()
{
	_sceneId = readUint();//readInt();

	int16 rewardCount = readShort();
	for(int16 i=0; i<rewardCount; ++i)
	{
		SCMD13DNode node;
		node._goodsId = readInt();
		node._goodsNum = readInt();
		_rewards.push_back(node);
	}

	int16 expCount = readShort();
	for(int16 i=0; i<expCount; ++i)
	{
		SCMD13DNode2 node;
		node._id = readInt();
		node._plusExp = readInt();
		node._isUpgrade = readByte();
		_exps.push_back(node);
	}

	return true;
}

int32 SCMD13D::Execute()
{
	if (!Read())
	{
		return 1;
	}
	return SCMD13DHandler::Execute(this) ;
}

uint32 SCMD13DHandler::Execute(SCMD13D* pPacket)
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

	FightProxy *pFightProxy = (FightProxy *) g_pFacade->retrieveProxy(AppFacade_FIGHT_PROXY_CHANGE);
	pFightProxy->fightReward(pPacket);

	return 0;
}

