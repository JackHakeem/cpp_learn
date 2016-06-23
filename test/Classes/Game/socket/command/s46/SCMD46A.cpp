#include "SCMD46A.h"
#include "manager/LangManager.h"
#include "control/AppFacade.h"
#include "socket/network/GameServerSocket.h"
#include "view/zx/ZXMediator.h"
#include "view/zx/components/XHView.h"

bool SCMD46A::Read()
{
	int16 SCMD46ANodeNum = readShort();	//动作次数
	for(int k = 0; k < (int)SCMD46ANodeNum; k++)
	{

		SCMD46ANode newnode;
		newnode.a_roldId		= readUint();
		newnode.b_sitGrid		= readByte();	
		newnode.c_id			= readUint();	
		newnode.d_goodId		= readInt();		
		newnode.e_lv			= readByte();
		newnode.f_curexp		= readUint();

		a_XHEquipList.push_back(newnode);
	}
	return true;
}

int32 SCMD46A::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD46AHandler::Execute(this);
}

uint32 SCMD46AHandler::Execute( SCMD46A* pPacket )
{
	ZXMediator * pZXMediator = (ZXMediator *)g_pFacade->retrieveMediator(AppFacade_ZX);
	if (pZXMediator)
	{
		pZXMediator->m_pXHView->buildEquipXH(pPacket->a_XHEquipList);
	}	
	

	return 0;
}
