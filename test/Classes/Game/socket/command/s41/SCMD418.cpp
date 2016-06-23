#include "SCMD418.h"
#include "manager/LangManager.h"
#include "control/AppFacade.h"
#include "socket/network/GameServerSocket.h"
#include "manager/GlobalManage.h"
#include "view/dungeonEntrys/components/ChallengeGuaView.h"
#include "view/dungeonEntrys/components/DungeonGuaView.h"

bool SCMD418::Read()
{
	a_flag = readUint();
	return true;
}

int32 SCMD418::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD418Handler::Execute(this);
}

uint32 SCMD418Handler::Execute( SCMD418* pPacket )
{
	char str[50];
	sprintf(str, "GUAMSG0%02d", pPacket->a_flag);
	LangManager::msgShow(str);



	switch (pPacket->a_flag)
	{
	case 0://��ͼ���ɽ���
	case 1://���޴�ͼ
	case 2://��ͼ��Ӧ�����б�����
	case 3://����buff�쳣��
	case 4://��������
	case 5://���ﲻ����
	case 7://��������
		{
			if (g_pGlobalManage->getDunGUA() != 0)
				g_pGlobalManage->setDunGUA(9);

			//DungeonGuaView* guaView = (DungeonGuaView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_dungeonGua);
			//if (guaView)
			//{//�����һ�

			//	char str[50];
			//	std::string strvalue = ValuesUtil::Instance()->getString("GUA025");
			//	sprintf(str, "%s", strvalue.c_str());
			//	guaView->addStrRecords(str, ccc3(255, 255, 255));

			//	guaView->onTAOFACancel(0);
			//}
		}
		break;
	case 10://�����۳�ʧ�� �һ�����
	case 11://û�н�������� �һ�����
		{
			if (g_pGlobalManage->getDunGUA() != 0)
				g_pGlobalManage->setDunGUA(9);

			//ChallengeGuaView* guaView = (ChallengeGuaView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_dungeonGua);
			//if (guaView)
			//{//�����һ�

			//	char str[50];
			//	std::string strvalue = ValuesUtil::Instance()->getString("GUA025");
			//	sprintf(str, "%s", strvalue.c_str());
			//	guaView->addStrRecords(str, ccc3(255, 255, 255));

			//	guaView->onTAOFACancel(0);
			//}
		}break;
	}
	return 0;
}
