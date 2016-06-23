#include "SCMD464.h"
#include "manager/LangManager.h"
#include "control/AppFacade.h"
#include "socket/network/GameServerSocket.h"
#include "view/zx/ZXMediator.h"
#include "view/zx/components/XHView.h"

bool SCMD464::Read()
{
	int16 SCMD464_465NodeNum = readShort();	//动作次数
	for(int k = 0; k < (int)SCMD464_465NodeNum; k++)
	{

		SCMD464_465Node newnode;
		newnode.a_sitGrid		= readByte();	
		newnode.b_id			= readUint();	
		newnode.c_goodId		= readInt();
		newnode.d_lv			= readByte();
		newnode.e_curexp		= readUint();

		a_XHList.push_back(newnode);
	}
	return true;
}

int32 SCMD464::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD464Handler::Execute(this);
}

uint32 SCMD464Handler::Execute( SCMD464* pPacket )
{

	ZXMediator * pZXMediator = (ZXMediator *)g_pFacade->retrieveMediator(AppFacade_ZX);
	if (pZXMediator)
	{
		pZXMediator->m_pXHView->buildBagXH(pPacket->a_XHList);
	}			
	return 0;
}
