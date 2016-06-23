#include "SCMD16D.h"
#include "socket/network/GameServerSocket.h"
#include "view/backpack/BagMediator.h"
//#include "LoginManage.h"
#include "control/AppFacade.h"
//#include "view/backpack/BagMediator.h"

bool	SCMD16D::Read()
{
	a_from = readByte();
	b_goodsId = readShort();
	c_num = readByte();
	d_sitGrid = readByte();

	return true;
}

int32 	SCMD16D::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD16DHandler::Execute(this) ;
}


uint32 SCMD16DHandler::Execute(SCMD16D* pPacket)
{
	if (!pPacket) return 1;
	
	BagMediator* p = (BagMediator*)g_pFacade->retrieveMediator(AppFacade_BAG_PROXY_CHANGE);
	p->onSpecialItemAdd(pPacket);
	return 0;
}