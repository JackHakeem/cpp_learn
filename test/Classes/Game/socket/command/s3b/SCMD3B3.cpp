#include "SCMD3B3.h"
#include "view/tower/TowerMediator.h"

bool SCMD3B3::Read()
{
	a_numFree = readByte(); 
	b_numPay = readByte(); 
	c_lastFloor = readByte(); 
	d_maxFloor = readByte(); 
	e_myRank = readByte(); 

	int16 cnt = readUshort();
	for(int i=0;i < cnt; ++i)
	{
		SCMD3B3Node node;
		node.a_name = readString();   
		node.b_time = readInt();
		f_topRank.push_back(node);
	}

	return true;
}

int32 SCMD3B3::Execute()
{
	if(!Read())
	{
		return 1;
	}

	return SCMD3B3Handler::Execute(this);
}

uint32 SCMD3B3Handler::Execute( SCMD3B3 *pPacket )
{
	if(!pPacket)
	{
		return 1;
	}

	g_pTowerMediator->cmdInitTower(pPacket);

	return 0;
}
