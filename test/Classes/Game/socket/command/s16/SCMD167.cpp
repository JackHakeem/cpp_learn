#include "SCMD167.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "control/AppFacade.h"
#include "view/backpack/BagMediator.h"
#include "view/bank/BankMediator.h"

bool	SCMD167::Read()
{
	int16 SCMD161_163_165_167NodeNum = readShort();	//Action times
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


	
	BankMediator* p = (BankMediator*)g_pFacade->retrieveMediator(AppFacade_BANK_PROXY_CHANGE);
	p->initWorldBank((char*)&a_goodsList);
	return true;
}

int32 	SCMD167::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD167Handler::Execute(this) ;
}


uint32 SCMD167Handler::Execute(SCMD167* pPacket)
{
	if (!pPacket) return 1;
	
	/*
	//Apply of battle
	CCMD11E* s = new CCMD11E();
	if (s)
	{
		s->a_monsterId = 1090;
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(s);
	}
	SAFE_DELETE(s);
	*/
	return 0;
}