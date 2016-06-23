#include "SCMD139.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/scene/SceneListenerMediator.h"



bool	SCMD139::Read()
{
	int16 cnt = readShort();
	for (int i = 0; i < cnt; i++)
	{
		SCMD139Node node;
		node.a_roleId = readInt();
		node.b_maxHP = readInt();
		node.c_hp = readInt();
		node.d_exp = readInt();
		node.e_lev = readByte();
		roles.push_back(node);
	}

	return true;
}

int32 	SCMD139::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD139Handler::Execute(this) ;
}


uint32 SCMD139Handler::Execute(SCMD139* pPacket)
{
	if (!pPacket) return 1;


	SceneListenerMediator* md = (SceneListenerMediator*)g_pFacade->retrieveMediator(AppFacade_SCENELISTENER_MEDIATOR);
	md->updateRole(pPacket);

	return 0;
}