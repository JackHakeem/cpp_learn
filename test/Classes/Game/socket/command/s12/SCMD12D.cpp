#include "SCMD12D.h"
#include "socket/network/GameServerSocket.h"
#include "view/scene/SceneListenerMediator.h"

bool	SCMD12D::Read()
{
	//a_AccountId = readInt();
	//b_startX = readShort();
	//c_startY = readShort();
	//int16 cnt = readShort();
	//for(int16 i = 0; i < cnt; ++i)
	//{
	//	SCMD111Node node;
	//	node.a_x = readShort();
	//	node.b_y = readShort();
	//	d_path.push_back(node);
	//}

	a_node.a_AccountId = readInt();
	a_node.b_RoleName =readString();
	a_node.c_x = readShort();
	a_node.d_y = readShort();
	a_node.e_guildName = readString();
	a_node.f_maxHp = readInt();
	a_node.g_hp = readInt();
	a_node.h_energy = readShort();
	a_node.i_mercId = readShort();
	a_node.j_roleLev = readByte();
	a_node.k_avatar = readInt();

	int path_cnt = readShort();
	for(int j = 0; j < path_cnt; ++j)
	{
		SCMD111Node node111;
		node111.a_x = readShort();
		node111.b_y = readShort();
		a_node.l_path.push_back(node111);
	}

	a_node.m_weiXie = readShort();
	a_node.n_title = readShort();

	return true;
}

int32 	SCMD12D::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD12DHandler::Execute(this) ;
}


uint32 SCMD12DHandler::Execute(SCMD12D* pPacket)
{
	if (!pPacket) return 1;

	SceneListenerMediator* md = (SceneListenerMediator*)g_pFacade->retrieveMediator(AppFacade_SCENELISTENER_MEDIATOR);
	if(md)
		md->creatTradeHandler(pPacket);

	return 0;
}