#include "SCMD46E.h"
#include "manager/LangManager.h"
#include "control/AppFacade.h"
#include "socket/network/GameServerSocket.h"
#include "view/zx/ZXMediator.h"
#include "view/zx/components/ZXView.h"

bool SCMD46E::Read()
{
	a_ZXerFreeCountToday = readUint();
	return true;
}

int32 SCMD46E::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD46EHandler::Execute(this);
}

uint32 SCMD46EHandler::Execute( SCMD46E* pPacket )
{

	ZXView* pZXView = (ZXView*)LayerManager::intervalLayer->getChildByTag( IntervalLayer::IntervalLayerTAG_ZX);
	if (pZXView)
	{
		pZXView->updateZXerFreeCountToday(pPacket->a_ZXerFreeCountToday);
	}

	return 0;
}
