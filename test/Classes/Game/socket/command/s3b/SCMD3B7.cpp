#include "SCMD3B7.h"
#include "view/tower/TowerMediator.h"
#include "view/tower/components/FightPanel.h"
#include "view/tower/components/TowerView.h"
#include "manager/BattleManager.h"
#include "manager/GlobalManage.h"
#include "events/GameDispatcher.h"

bool SCMD3B7::Read()
{
	a_isWin = readByte();
	b_isLottery = readByte();
	c_numFree = readByte();
	d_numPay = readByte();
	e_beforeFloor = readByte();
	f_afterFloor = readByte();
	if (f_afterFloor == 100 || f_afterFloor == 81)
	{
		int a = 0;
		a = 1;
		
	}
	CCLog("f_afterFloor %d", f_afterFloor);
	g_maxFloor = readByte();
	h_curMonsterId = readInt();

	int16 cnt = readUshort();
	for(int i=0;i < cnt; ++i)
	{
		SCMD3B5Node node;
		node.a_rewardId = readInt();   
		node.b_rewardNum = readInt();
		i_curRewards.push_back(node);
	}

	j_showCurBoss = readByte();
	k_nextMonsterId = readInt();

	cnt = readUshort();
	for(int i=0;i < cnt; ++i)
	{
		SCMD3B5Node node;
		node.a_rewardId = readInt();   
		node.b_rewardNum = readInt();
		l_nextRewards.push_back(node);
	}


	m_showNextBoss = readByte();
	n_inspire = readByte();
	o_inspirePrac = readInt(); 

	return true;
}

int32 SCMD3B7::Execute()
{
	if(!Read())
	{
		return 1;
	}

	return SCMD3B7Handler::Execute(this);
}

uint32 SCMD3B7Handler::Execute( SCMD3B7 *pPacket )
{
	if(!pPacket)
	{
		return 1;
	}

	if (g_pGlobalManage->getTowerGUA() != 0)
		g_pGlobalManage->setTowerGUA(3);

	if (g_pGlobalManage->getTowerGUA() != 0 && pPacket->f_afterFloor == pPacket->g_maxFloor)
	{
		g_pGlobalManage->setTowerGUA(9);
	}

	if (g_pGlobalManage->getTowerGUA() != 0)
	{
		int type = pPacket->a_isWin >= 0 ? 1 : 0;  // add by LH 0731
		g_pBattleManager->sendBattleStopHandler(type);	

		
	}

	g_pTowerMediator->cmdTowerFightResult(pPacket);

	if (g_pGlobalManage->getTowerGUA() != 0)//没有挂机这里怎么会进？检查一下这里就行
	{
		GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::BATTLE_CALLBACK, 0 );
	}

	if (g_pGlobalManage->getTowerGUA() == 9 && g_pTowerMediator->_towerView && g_pTowerMediator->_towerView->_panelFight)
	{
		g_pTowerMediator->_towerView->_panelFight->unGUA(0);
	}

	return 0;
}
