#include "SCMD460.h"
#include "manager/LangManager.h"
#include "control/AppFacade.h"
#include "socket/network/GameServerSocket.h"
#include "view/zx/components/ZXView.h"

bool SCMD460::Read()
{
	a_flag = readUint();
	return true;
}

int32 SCMD460::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD460Handler::Execute(this);
}

uint32 SCMD460Handler::Execute( SCMD460* pPacket )
{
	switch (pPacket->a_flag)
	{
	case 3:
	case 4:
	case 10:
		{}
		break;
	case 22://ZXMSG022
		{
			ZXView* pZXView = (ZXView*)LayerManager::intervalLayer->getChildByTag( IntervalLayer::IntervalLayerTAG_ZX);
			if (pZXView)
			{
				pZXView->clickOneKeyZX(0);
			}
		}
		break;
	default:
		{
			char str[50];
			sprintf(str, "ZXMSG0%02d", pPacket->a_flag);
			LangManager::msgShow(str);		
		}
		break;
	}


	return 0;
}
