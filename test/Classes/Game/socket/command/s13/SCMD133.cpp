//#include "Include.h"
#include "BaseType.h"
#include "SCMD133.h"
#include "model/battle/BattleProxy.h"
#include "view/scene/components/BattlePlay.h"
#include "control/AppFacade.h"
#include "model/battle/FightProxy.h"
#include "view/battle/SceneFightMediator.h"
#include "view/scene/SceneListenerMediator.h"
#include "view/scene/SceneWorldMediator.h"
#include "manager/GlobalManage.h"
#include "manager/BattleManager.h"
#include "manager/LangManager.h"
#include "view/dungeonEntrys/components/DungeonGuaView.h"
#include "utils/ValuesUtil.h"
#include "manager/LayerManager.h"
#include "view/dungeonEntrys/components/DungeonGuaView.h"
#include "view/dungeonEntrys/components/ChallengeGuaView.h"

bool	SCMD133::Read()
{
  
	f_members.clear();
    a_BattleId	= readInt();	// Battle scenes ID	

	if (a_BattleId==0)
	{
		a_BattleId = 999;
	}
	b_type		= readByte();	//	Fighting type
	c_win		= readByte();	// Changed to have signed a Byte> = wins
	d_damage	= readInt();	// The total injured
	e_round		= readByte();	// The number of turns

	int16 SCMD133NodeNum = readShort();
 
	for (int i = 0; i <  SCMD133NodeNum; i++)
	{
       
		SCMD133Node newnode;
		newnode.a_station	= readByte();
		newnode.b_hp		= readInt();
        
	 
		f_members.push_back(newnode);
	}

	return true;
}
int32 	SCMD133::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD133Handler::Execute(this) ;
}

uint32 SCMD133Handler::Execute(SCMD133* pPacket)
{
	if (!pPacket) return 1;

	bool isGuaing = false;
	if (g_pGlobalManage->getDunMapId() >= 1201 && 
		g_pGlobalManage->getDunMapId() <= 1209 && 
		g_pGlobalManage->getDunMapId() != 1208)
	{
		ChallengeGuaView* guaView = (ChallengeGuaView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_dungeonGua);
		if (guaView)
		{
			isGuaing = true;
		}	
	}
	else
	{
		DungeonGuaView* guaView = (DungeonGuaView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_dungeonGua);
		if (guaView)
		{
			isGuaing = true;
		}	
	}

	//更新挂机面板信息
	if (isGuaing && pPacket->c_win < 0)
	{
		ChallengeGuaView* guaView = (ChallengeGuaView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_dungeonGua);
		if (guaView)
		{
			char str[40];
			sprintf(str, "%s", ValuesUtil::Instance()->getString( "GUA036" ).c_str());
			guaView->addStrRecords(str, ccc3(250, 254, 200));
		}		
	}

	//剧情副本挂机
	if (isGuaing)
	{
		//上发战斗结束协议
	
		int type = pPacket->c_win >= 0 ? 1 : 0;  // add by LH 0731

		g_pBattleManager->sendBattleStopHandler(type);	
		//
		ChallengeGuaView* guaView = (ChallengeGuaView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_dungeonGua);
		if (guaView)
		{
			g_pGlobalManage->setDunGUA(3); //可以开始挂机
		}
		return 0;
	}
	
	if (g_pGlobalManage->getTowerGUA() != 0)
		return 1;


	SceneListenerMediator* mm = (SceneListenerMediator*)g_pFacade->retrieveMediator(AppFacade_SCENELISTENER_MEDIATOR);
	if(mm)
	{
		mm->sendNotification(Facade_Mediator, AppFacade_SCENEWORLD_MEDIATOR, NULL, SceneWorldMediator::REMOVE_WORLD_SCENE);
	}


	BattlePlay::getInstance()->playBattleStart();  

	//kevinchange0817

	SceneFightMediator* m = (SceneFightMediator*)g_pFacade->retrieveMediator(AppFacade_FIGHT_PROXY_CHANGE);
	if(m)
		m->addBattleFinish((char*)pPacket);
	return 0;
}

