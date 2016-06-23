#include "SCMD462.h"
#include "manager/LangManager.h"
#include "control/AppFacade.h"
#include "socket/network/GameServerSocket.h"
#include "view/zx/components/ZXView.h"

bool SCMD462::Read()
{
	a_ZXerState = readInt();
	return true;
}

int32 SCMD462::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD462Handler::Execute(this);
}

uint32 SCMD462Handler::Execute( SCMD462* pPacket )
{
	ZXView* pZXView = (ZXView*)LayerManager::intervalLayer->getChildByTag( IntervalLayer::IntervalLayerTAG_ZX);
	if (pZXView)
	{
		pZXView->updateZXerState(pPacket->a_ZXerState);
	}
	
	return 0;
}
