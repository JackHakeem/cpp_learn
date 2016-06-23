#include "SCMD411.h"
#include "manager/GlobalManage.h"
#include "manager/LangManager.h"
#include "manager/LayerManager.h"
#include "view/dungeonEntrys/components/DungeonGuaView.h"
bool SCMD411::Read()
{
	a_dunId = readUshort();
	return true;
}


int32 	SCMD411::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD411Handler::Execute(this) ;
}


uint32 SCMD411Handler::Execute(SCMD411* pPacket)
{
	if (!pPacket) return 1;

	//可以进入副本操作
	if (pPacket->a_dunId == g_pGlobalManage->getDunMapId())
	{
		DungeonGuaView* guaView = (DungeonGuaView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_dungeonGua);
		if (guaView)
		{
			g_pGlobalManage->setDunGUA(3); //可以开始挂机
		}

		
	}
	else
	{
		//挂机error over
		LangManager::msgShow("GUA012");
		g_pGlobalManage->setDunGUA(0); 
	}
	return 0;
}