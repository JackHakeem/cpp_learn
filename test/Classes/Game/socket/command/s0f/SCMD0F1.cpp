#include "SCMD0F1.h"
#include "socket/network/GameServerSocket.h"
#include "view/scene/SceneListenerMediator.h"
#include "manager/GlobalManage.h"

bool	SCMD0F1::Read()
{
	int16 cnt = readShort();
	for(int16 i = 0; i < cnt; ++i)
	{
		SCMD0F1Node node;
		node.a_AccountId = readInt();
		node.b_RoleName =readString();
		node.c_x = readShort();
		node.d_y = readShort();
		node.e_guildName = readString();
		node.f_maxHp = readInt();
		node.g_hp = readInt();
		node.h_energy = readShort();
		node.i_mercId = readShort();
		node.j_roleLev = readByte();
		node.k_avatar = readInt();

		int path_cnt = readShort();
		for(int j = 0; j < path_cnt; ++j)
		{
			SCMD111Node node111;
			node111.a_x = readShort();
			node111.b_y = readShort();
			node.l_path.push_back(node111);
		}

		node.m_weiXie = readShort();
		node.n_title = readShort();
		a_Accounts.push_back(node);
	}

	return true;
}

int32 	SCMD0F1::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD0F1Handler::Execute(this) ;
}
uint32 SCMD0F1Handler::Execute(SCMD0F1* pPacket)
{
	if (!pPacket) return 1;

	SceneListenerMediator* md = 
		(SceneListenerMediator*)g_pFacade->retrieveMediator(AppFacade_SCENELISTENER_MEDIATOR);
	md->tradeplayerViewGetHandler(pPacket);

	return 0;
}