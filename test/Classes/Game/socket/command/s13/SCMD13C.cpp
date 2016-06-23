#include "SCMD13C.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/scene/SceneListenerMediator.h"
#include "view/scene/components/BattlePlay.h"
#include "manager/GlobalManage.h"



bool SCMD13C::Read()
{
	if (g_pGlobalManage->m_canSCMD133Enable != 0)
		g_pGlobalManage->m_canSCMD133Enable = 9;
	else
		g_pGlobalManage->m_canSCMD133Enable = 1;

	a_BattleId = readInt();
	if (a_BattleId==0)
	{
		a_BattleId = 999;
	}
	
	b_attackFid = readShort();
	c_defendFid = readShort();

	int16 d_SCMD13CNodeNum = readShort();
	for (int i = 0; i < d_SCMD13CNodeNum; i++)
	{
		SCMD131Node newnode;
		newnode.a_id = readShort();		
		newnode.b_station = readByte();
		newnode.c_lev = readByte();
		newnode.d_hp = readInt();
		newnode.e_skill1 = readShort();
		newnode.f_skill2 = readShort();
		newnode.g_skill3 = readShort();
		newnode.h_name = readString();
		newnode.i_cloth = readString();
		newnode.j_maxHp = readInt();
		newnode.k_startEP = readShort();
		d_players.push_back(newnode);
	}


	return true;
}

int32 	SCMD13C::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD13CHandler::Execute(this) ;
}


uint32 SCMD13CHandler::Execute(SCMD13C* pPacket)
{
	if (!pPacket) return 1;

	LayerManager::loadingPic->socketWait( WMSG_WORLD_BATTLE_FINISH, BattlePlay::getInstance(), callfuncND_selector(BattlePlay::waitSCMD133Timeout));
	SceneListenerMediator* md = (SceneListenerMediator*)g_pFacade->retrieveMediator(AppFacade_SCENELISTENER_MEDIATOR);
	if (md)
	{
		md->pvpFightStart(pPacket);
	}

	
//	BattlePlay::getInstance()->playBattleStart();kevinchange0817
	return 0;
}