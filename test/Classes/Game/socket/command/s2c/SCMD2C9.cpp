#include "SCMD2C9.h"
#include "view/worldBoss/WorldBossMediator.h"

bool	SCMD2C9::Read()
{
	a_currentHP = readUint();
	b_maxHP = readUint();
	c_totalDamage_low = readUint();
	c_totalDamage_high = readUint();

	int count = readUshort();
	for (int i =0 ;i < count ; i++)
	{
		SCMD2C9Node node;
		node.a_rank = readUbyte();
		node.b_name = readString();
		node.c_damage = readUint();
		d_damageRankList.push_back(node);
	}

	return true;
}

int32 	SCMD2C9::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2C9Handler::Execute(this) ;
}


uint32 SCMD2C9Handler::Execute(SCMD2C9* pPacket)
{
	if (!pPacket) return 1;

	WorldBossMediator * pMediator = (WorldBossMediator *)g_pFacade->retrieveMediator(AppFacade_WorldBoss_Mediator);
	if (pMediator)
	{
		pMediator->sockBossInfo(pPacket);
	}

	return 0;
}