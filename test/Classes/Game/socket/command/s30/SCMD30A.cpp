#include "SCMD30A.h"
#include "socket/network/GameServerSocket.h"
#include "view/login/LoginMediator.h"
#include "manager/GlobalManage.h"

bool	SCMD30A::Read()
{
	count = readShort();
	
	SCMD30ANode node;
	for(int i = 0; i < count; ++i)
	{
		node.a_figureId = readInt();
		node.b_sitGrid	= readByte();
		node.c_eqpId	= readInt();
		node.d_eqpGoodsId = readShort();
		node.e_superLv = readByte();
		node.f_stamina = readShort();			//The magic of the physical number of
		node.g_wrist = readShort();			//The number of magic of the wrist
		node.h_intellect = readShort();
		node.i_sp_stamina = readShort();
		node.j_sp_wrist = readShort();
		node.k_sp_intellect = readShort();
		node.l_blue = readByte();
		node.m_purple = readByte();
		node.n_red = readByte();

		a_eqpList.push_back(node);
	}

	return true;
}

int32 	SCMD30A::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD30AHandler::Execute(this) ;
}


uint32 SCMD30AHandler::Execute(SCMD30A* pPacket)
{
	if (!pPacket) return 1;

	CCLog("Mercenary:equip response received SCMD30A");
	//FigureMediator* _figureMediator = (FigureMediator*)g_pFacade->retrieveMediator(AppFacade_FIGURE_MEDIATOR);
	//_figureMediator->sockEquipInfo((char*)pPacket);
	LoginMediator* loginMediator = 
		(LoginMediator*)g_pFacade->retrieveMediator(AppFacade_LOGIN_MEDIATOR);
	loginMediator->sockEquipInfo(pPacket);

	g_pGlobalManage->loadOneProgress( 2 );
	return 0;
}