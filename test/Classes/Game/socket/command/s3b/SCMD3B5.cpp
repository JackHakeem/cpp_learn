#include "SCMD3B5.h"
#include "view/tower/TowerMediator.h"

bool SCMD3B5::Read()
{
	a_numFree = readByte();
	b_numPay = readByte();
	c_curFloor = readByte();
	d_maxFloor = readByte();
	e_curMonsterId = readInt();

	int16 cnt = readUshort();
	for(int i=0;i < cnt; ++i)
	{
		SCMD3B5Node node;
		node.a_rewardId = readInt();   
		node.b_rewardNum = readInt();
		f_curRewards.push_back(node);
	}

	g_showCurBoss = readByte();
	h_nextMonsterId = readInt();

	cnt = readUshort();
	for(int i=0;i < cnt; ++i)
	{
		SCMD3B5Node node;
		node.a_rewardId = readInt();   
		node.b_rewardNum = readInt();
		i_nextRewards.push_back(node);
	}

	j_showNextBoss = readByte();
	k_inspire = readByte();
	l_inspirePrac = readInt();

	return true;
}

int32 SCMD3B5::Execute()
{
	if(!Read())
	{
		return 1;
	}

	return SCMD3B5Handler::Execute(this);
}

uint32 SCMD3B5Handler::Execute( SCMD3B5 *pPacket )
{
	if(!pPacket)
	{
		return 1;
	}

	g_pTowerMediator->cmdUpdateTowerInfo(pPacket);

	return 0;
}
