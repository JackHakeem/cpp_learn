#include "SCMD465.h"
#include "manager/LangManager.h"
#include "control/AppFacade.h"
#include "socket/network/GameServerSocket.h"
#include "view/zx/components/ZXView.h"
#include "view/zx/ZXMediator.h"

bool SCMD465::Read()
{
	int16 SCMD464_465NodeNum = readShort();	//动作次数
	for(int k = 0; k < (int)SCMD464_465NodeNum; k++)
	{

		SCMD464_465Node newnode;
		newnode.a_sitGrid		= readByte();	
		newnode.b_id			= readUint();	
		newnode.c_goodId		= readInt();		
		newnode.d_lv			= readByte();
		//newnode.f_isnew			= readByte();

		a_XHList.push_back(newnode);
	}
	return true;
}

int32 SCMD465::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD465Handler::Execute(this);
}

uint32 SCMD465Handler::Execute( SCMD465* pPacket )
{
	ZXView* pZXView = (ZXView*)LayerManager::intervalLayer->getChildByTag( IntervalLayer::IntervalLayerTAG_ZX);
	if (pZXView)
	{
		pZXView->buildBankXH(pPacket->a_XHList);
	}
	

	return 0;
}
