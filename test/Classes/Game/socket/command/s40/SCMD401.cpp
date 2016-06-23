#include "SCMD401.h"
#include "socket/network/GameServerSocket.h"
#include "control/AppFacade.h"
#include "view/egg/EggMediator.h"

bool	SCMD401::Read()
{
	a_num = readByte();

	short SCMD401Node1Num = readShort();
	for (int i = 0; i < SCMD401Node1Num; i++)
	{
		SCMD401Node1 node;
		node.a_type = readByte();
		node.b_quality = readByte();
		node.c_state = readByte();
		node.d_goodsId = readInt();
		node.e_goodsNum = readInt();
		node.f_num = readInt();

		b_myReward.push_back(node);
	}

	short SCMD401Node2Num = readShort();
	for (int i = 0; i < SCMD401Node2Num; i++)
	{
		SCMD401Node2 node;
		node.a_name = readString();
		node.b_type = readByte();
		node.c_quality = readByte();
		node.d_state = readByte();
		node.e_goodsId = readInt();
		node.f_goodsNum = readInt();
		node.g_num = readInt();

		c_otherReward.push_back(node);
	}

	return true;
}

int32 	SCMD401::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD401Handler::Execute(this) ;
}


uint32 SCMD401Handler::Execute(SCMD401* pPacket)
{
	if (!pPacket) return 1;
	
	EggMediator* md = (EggMediator*)g_pFacade->retrieveMediator(AppFacade_EGG_CHANGE);
	if(md)
		md->cmdHistoryHandler(pPacket);
	
	return 0;
}