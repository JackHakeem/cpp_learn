#include "SCMD3CB.h"
#include "view/tower/TowerMediator.h"

bool SCMD3CB::Read()
{
	a_page = readShort();
	b_maxFloor = readByte();
	c_curFloor = readByte();
	d_myRank = readByte();
	d_nRestCount = readByte();
	d_oLastRank = readByte();

	int16 cnt = readUshort();
	for(int i=0;i < cnt; ++i)
	{
		SCMD3CBNode node;		
		node.a_rank = readByte();
		node.b_floor = readByte();
		node.c_name = readString();
		node.d_guild = readString();
		node.e_lev = readByte();
		node.f_date = readInt();
		e_rankList.push_back(node);
	}

	return true;
}

int32 SCMD3CB::Execute()
{
	if(!Read())
	{
		return 1;
	}

	return SCMD3CBHandler::Execute(this);
}

uint32 SCMD3CBHandler::Execute( SCMD3CB *pPacket )
{
	if(!pPacket)
	{
		return 1;
	}

	g_pTowerMediator->cmdTowerRanking(pPacket);

	return 0;
}
