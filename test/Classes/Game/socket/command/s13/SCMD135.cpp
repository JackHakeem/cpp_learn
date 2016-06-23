#include "SCMD135.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/scene/SceneListenerMediator.h"



bool	SCMD135::Read()
{
	a_BattleId = readInt();
	b_GroupId = readInt();
	c_formationId = readShort();

	int16 d_SCMD135NodeNum = readShort();
	for (int i = 0; i < d_SCMD135NodeNum; i++)
	{
		SCMD135Node newnode;
		newnode.a_id = readShort();		
		newnode.b_station = readByte();
		newnode.c_lev = readByte();
		newnode.d_hp = readInt();
		newnode.e_skill1 = readShort();
		newnode.f_skill2 = readShort();
		newnode.g_skill3 = readShort();
		newnode.h_name = readString();
		newnode.i_cloth = readString();
		d_SCMD135Node.push_back(newnode);
	}

	e_playerId = readInt();

	return true;
}

int32 	SCMD135::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD135Handler::Execute(this) ;
}


uint32 SCMD135Handler::Execute(SCMD135* pPacket)
{
	if (!pPacket) return 1;

	////Apply for battle
	//CCMD11E* s = new CCMD11E();
	//if (s)
	//{
	//	s->a_monsterId = 1071;
	//	GameServerSocket* pSocket = GameServerSocket::getInstance();
	//	if (pSocket)
	//		pSocket->sendMessage(s);
	//}
	//SAFE_DELETE(s);

	SceneListenerMediator* md = (SceneListenerMediator*)g_pFacade->retrieveMediator(AppFacade_SCENELISTENER_MEDIATOR);
	md->pveReportFightStart(pPacket);

	return 0;
}