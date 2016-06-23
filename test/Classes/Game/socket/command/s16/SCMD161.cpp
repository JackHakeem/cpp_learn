#include "SCMD161.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "control/AppFacade.h"
#include "view/backpack/BagMediator.h"

bool	SCMD161::Read()
{
	int16 SCMD161_163_165_167NodeNum = readShort();	//动作次数
	for(int k = 0; k < (int)SCMD161_163_165_167NodeNum; k++)
	{

		SCMD161_163_165_167Node newnode;
		newnode.a_sitGrid		= readByte();	
		newnode.b_id			= readUint();	
		newnode.c_goodId		= readShort();	
		newnode.d_number		= readByte();	
		newnode.e_superLv		= readByte();	
		newnode.f_stamina		= readShort();	
		newnode.g_wrist			= readShort();	
		newnode.h_intellect		= readShort();

		newnode.i_sp_stamina	= readShort();
		newnode.j_sp_wrist		= readShort();
		newnode.k_sp_intellect	= readShort();
		newnode.l_blue			= readByte();
		newnode.m_purple		= readByte();
		newnode.n_red			= readByte();

		a_goodsList.push_back(newnode);
	}



	return true;
}

int32 	SCMD161::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD161Handler::Execute(this) ;
}


uint32 SCMD161Handler::Execute(SCMD161* pPacket)
{
	if (!pPacket) return 1;
	BagMediator* p = (BagMediator*)g_pFacade->retrieveMediator(AppFacade_BAG_PROXY_CHANGE);
	p->sockBagItemUpdate(&(pPacket->a_goodsList));
	return 0;
}