#include "SCMD40B.h"
#include "socket/network/GameServerSocket.h"
#include "control/AppFacade.h"
#include "view/egg/EggMediator.h"

bool	SCMD40B::Read()
{
	short SCMD40BNodeNum = readShort();

	for (int i = 0; i < SCMD40BNodeNum; i++)
	{
		SCMD40BNode node;
		node.a_type = readByte();
		node.b_quailty = readByte();
		node.c_state = readByte();
		node.d_goodsId = readInt();
		node.e_goodsNum = readInt();
		node.f_num = readInt();

		a_eggs.push_back(node);
	}

	return true;
}

int32 	SCMD40B::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD40BHandler::Execute(this) ;
}


uint32 SCMD40BHandler::Execute(SCMD40B* pPacket)
{
	if (!pPacket) return 1;
	
	EggMediator* md = (EggMediator*)g_pFacade->retrieveMediator(AppFacade_EGG_CHANGE);
	if(md)
		md->cmdDepotHandler(pPacket);
	
	return 0;
}