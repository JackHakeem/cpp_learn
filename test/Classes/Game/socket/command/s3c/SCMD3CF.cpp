#include "SCMD3CF.h"
#include "view/tower/TowerMediator.h"

bool SCMD3CF::Read()
{
	int16 cnt = readUshort();
	for(int i=0;i < cnt; i++)
	{
		SCMD3CFNode node;
		node.a_floor = readByte();
		node.b_id = readByte();
		node.c_num = readInt();

		int16 SCMD3B5Nodecnt = readUshort();

		for(int i=0;i < SCMD3B5Nodecnt; i++)
		{
			SCMD3B5Node n;
			n.a_rewardId = readInt();
			n.b_rewardNum = readInt();

			node.d_floorReward.push_back(n);
		}
		a_rewards.push_back(node);
	}

	return true;
}

int32 SCMD3CF::Execute()
{
	if(!Read())
	{
		return 1;
	}

	return SCMD3CFHandler::Execute(this);
}

uint32 SCMD3CFHandler::Execute( SCMD3CF *pPacket )
{
	if(!pPacket)
	{
		return 1;
	}

	g_pTowerMediator->cmdBoxTip(pPacket);

	return 0;
}
