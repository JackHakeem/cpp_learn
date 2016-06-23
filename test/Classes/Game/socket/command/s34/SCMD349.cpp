#include "SCMD349.h"


#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/formation/FormationMediator.h"
 
#include "control/AppFacade.h"
#include "view/skill/UpSkillMediator.h"

bool	SCMD349::Read()
{
	d_MercList.clear();
	a_blue = readInt();
	b_purple = readInt();
	c_red = readInt();
	int cnt1 = readShort();
	for(int i = 0; i < cnt1; ++i)
	{
		SCMD349node1 node1;
		node1.a_mercId = readInt();
		node1.b_merOId = readShort();
		node1.c_jadeId = readInt();
		node1.d_jadeOId = readShort();
		int cnt2 = readShort();
		for(int j = 0; i < cnt2; ++j)
		{
			SCMD349node2 node2;
			node2.a_spType = readByte();
			node2.b_spLv = readShort();
			node2.c_exp = readInt();
			node2.d_lvUpExp = readInt();
			node1.e_spList.push_back(node2);
		}
		d_MercList.push_back(node1);
	}

	return true;
}

int32 	SCMD349::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD349Handler::Execute(this) ;
}


uint32 SCMD349Handler::Execute(SCMD349* pPacket)
{
	if (!pPacket) return 1;

	return 0;
}

