#include "SCMD131.h"
 
#include "view/scene/layer/BattleLayer.h"
#include "model/battle/BattleProxy.h"
#include "control/AppFacade.h"
#include "model/battle/FightProxy.h"
#include "view/scene/components/BattlePlay.h"
#include "view/scene/SceneListenerMediator.h"
#include "manager/GlobalManage.h"
#include "manager/LangManager.h"

//Here changes in the 2012.3.14 data directly to a SCMD131
bool	SCMD131::Read()
{
	if (g_pGlobalManage->m_canSCMD133Enable != 0)
		g_pGlobalManage->m_canSCMD133Enable = 9;
	else
		g_pGlobalManage->m_canSCMD133Enable = 1;
    //剧情副本挂机
	if (g_pGlobalManage->getDunGUA() > 0)
	{
		return true;
	}

	d_SCMD131Node.clear();
	a_BattleId = readInt();
	b_GroupId = readInt();

	cocos2d::CCLog("GroupId is %d",b_GroupId);
	c_formationId = readShort();
	d_SCMD131NodeNum = readShort();
	 
	for (int i = 0; i < d_SCMD131NodeNum; i++)
	{
      
		SCMD131Node newnode;
		newnode.a_id = readShort();		
		newnode.b_station = readByte();
       // CCLog("------------b_station:%d", newnode.b_station);
		newnode.c_lev = readByte();
		newnode.d_hp = readInt();
		newnode.e_skill1 = readShort();
		newnode.f_skill2 = readShort();
		newnode.g_skill3 = readShort();
		newnode.h_name = readString();
		newnode.i_cloth = readString();

		newnode.j_maxHp = readInt();//hwj 2012-12-26
		newnode.k_startEP = readShort();

		d_SCMD131Node.push_back(newnode);
	}
    
	 
    e_playerId = readShort();
	return true;
    
}

int32 	SCMD131::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD131Handler::Execute(this) ;
}

uint32 SCMD131Handler::Execute(SCMD131* pPacket)
{
	if (!pPacket) return 1;

	//剧情副本挂机
	if (g_pGlobalManage->getDunGUA() > 0)
	{
//		LangManager::msgStr(" LOG:SCMD131  ");
		return 0;
	}

	if (g_pGlobalManage->getTowerGUA() != 0)
		return 1;

	LayerManager::loadingPic->socketWait( WMSG_WORLD_BATTLE_FINISH, BattlePlay::getInstance(), callfuncND_selector(BattlePlay::waitSCMD133Timeout));
	SceneListenerMediator* m = (SceneListenerMediator*)g_pFacade->retrieveMediator(AppFacade_SCENELISTENER_MEDIATOR);
	if(m)
	{
		m->pveFightStart(pPacket);
	}

	//BattlePlay::getInstance()->playBattleStart();   //Play "Start battle" animation

	return 0;
}

