#include "SCMD414.h"
#include "manager/GlobalManage.h"
#include "manager/BattleManager.h"
#include "manager/LangManager.h"
#include "manager/LayerManager.h"
#include "view/dungeonEntrys/components/ChallengeGuaView.h"

bool SCMD414::Read()
{
	a_canChaTimes = readByte();
	b_buyTimes    = readByte();
	//a_GUANeedVigour = readShort();
	//b_GUANeedVigour = readShort();
	//c_GUANeedVigour = readShort();
	d_GUANeedVigour = readShort();
	return true;
}


int32 	SCMD414::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD414Handler::Execute(this) ;
}


uint32 SCMD414Handler::Execute(SCMD414* pPacket)
{
	if (!pPacket) return 1;

	//剧情副本挂机
	if (g_pGlobalManage->getDunGUA() == 0)
	{
		//更新挂机面板信息
		ChallengeGuaView* guaView = (ChallengeGuaView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_dungeonGua);
		if (guaView)
		{
			guaView->updateNeedVigour(pPacket);
			//g_pGlobalManage->setDunGUA(1);
		}
		
		//LangManager::msgStr(" LOG:SCMD13D ");
		//return 0;
	}

	////可以进入副本操作
	//if (pPacket->a_is2GUA == 1)
	//{
	//	g_pGlobalManage->setDunGUA(1); //可以开始挂机
	//updateNeedVigour
	//}
	//else
	//{
	//	//error
	//}
	return 0;
}