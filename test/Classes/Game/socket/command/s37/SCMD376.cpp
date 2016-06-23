#include "SCMD376.h"
#include "socket/network/GameServerSocket.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "manager/GlobalManage.h"
#include "manager/BattleManager.h"
#include "manager/LangManager.h"
#include "manager/LayerManager.h"
#include "view/dungeonEntrys/components/ChallengeGuaView.h"
#include "model/backpack/GoodsManager.h"
#include "utils/ColorUtil.h"

bool	SCMD376::Read()
{

	a_mapId = readShort();
	b_rank = readByte();
	c_silver = readInt();
	d_gold = readInt();
	e_good1 = readInt();
	f_good2 =  readInt();

	return true;
}

int32 	SCMD376::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD376Handler::Execute(this) ;
}


uint32 SCMD376Handler::Execute(SCMD376* pPacket)
{
	if (!pPacket) return 1;

	//���鸱���һ�
	if (g_pGlobalManage->getDunGUA() != 0)
	{
		g_pGlobalManage->setDunGUA(7);
		//���¹һ������Ϣ
		ChallengeGuaView* guaView = (ChallengeGuaView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_dungeonGua);
		if (guaView)
		{
			bool hasAwardItem = false;
			
			//����ͨ�ؽ���
			{
				char str[40] = {0};
				std::string strvalue = ValuesUtil::Instance()->getString("GUA024");
				sprintf(str, strvalue.c_str());
				guaView->addStrRecords(str, ccc3(234, 239, 33));
			}
			//c_silver
			{
				char str[40];
				std::string strvalue = ValuesUtil::Instance()->getString("GUA031");
				sprintf(str, strvalue.c_str(), pPacket->c_silver);
				guaView->addStrRecords(str, ccc3(255,255,255));
			}
			//��Ʒö��
			//if (pPacket->d_gold > 0)
			//{
			//	GoodsBasic* goodBasic = g_pGoodsManager->getBasicGood( pPacket->d_gold );
			//	if (goodBasic)
			//	{
			{
				char str[40];
				std::string strvalue = ValuesUtil::Instance()->getString("GUA033");
				sprintf(str, strvalue.c_str(), pPacket->d_gold);
				guaView->addStrRecords(str, ccc3(255,255,255));
			}
			//hasAwardItem = true;
			//	}			
			//}
			if (pPacket->e_good1 > 0)
			{
				GoodsBasic* goodBasic = g_pGoodsManager->getBasicGood( pPacket->e_good1 );
				if (goodBasic)
				{
					char str[40] = {0};
					std::string strvalue = ValuesUtil::Instance()->getString("GUA018");
					sprintf(str, strvalue.c_str(), goodBasic->goodName.c_str());
					guaView->addStrRecords(str, ColorUtil::getGoodColor(goodBasic->quality));
					hasAwardItem = true;
				}			
			}
			if (pPacket->f_good2 > 0)
			{
				GoodsBasic* goodBasic = g_pGoodsManager->getBasicGood( pPacket->f_good2 );
				if (goodBasic)
				{
					char str[40] = {0};
					std::string strvalue = ValuesUtil::Instance()->getString("GUA018");
					sprintf(str, strvalue.c_str(), goodBasic->goodName.c_str());
					guaView->addStrRecords(str, ColorUtil::getGoodColor(goodBasic->quality));
					hasAwardItem = true;
				}			
			}
			//����Ʒ
			if (hasAwardItem == false)
			{
				char str[20] = {0};
				std::string strvalue = ValuesUtil::Instance()->getString("GUA023");
				sprintf(str, strvalue.c_str());
				guaView->addStrRecords(str, ccc3(255, 255, 255));
			}
		}


		//
		//LangManager::msgStr(" LOG:SCMD13D ");
		return 0;
	}
	return 0;
}