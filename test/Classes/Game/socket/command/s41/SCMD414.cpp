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

	//���鸱���һ�
	if (g_pGlobalManage->getDunGUA() == 0)
	{
		//���¹һ������Ϣ
		ChallengeGuaView* guaView = (ChallengeGuaView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_dungeonGua);
		if (guaView)
		{
			guaView->updateNeedVigour(pPacket);
			//g_pGlobalManage->setDunGUA(1);
		}
		
		//LangManager::msgStr(" LOG:SCMD13D ");
		//return 0;
	}

	////���Խ��븱������
	//if (pPacket->a_is2GUA == 1)
	//{
	//	g_pGlobalManage->setDunGUA(1); //���Կ�ʼ�һ�
	//updateNeedVigour
	//}
	//else
	//{
	//	//error
	//}
	return 0;
}