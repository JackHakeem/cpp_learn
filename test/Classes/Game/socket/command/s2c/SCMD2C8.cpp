#include "SCMD2C8.h"
#include "view/worldBoss/WorldBossMediator.h"

bool	SCMD2C8::Read()
{
	a_movingCD = readUint();
	b_battleCD = readUint();
	c_boostNum = readUbyte();
	d_damage = readUint();

	int count = readUshort();
	for (int i =0 ;i < count ; i++)
	{
		SCMD2C8Node node;
		node.a_id = readUint();
		node.b_num = readUint();
		e_awardList.push_back(node);
	}

	return true;
}

int32 	SCMD2C8::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2C8Handler::Execute(this) ;
}


uint32 SCMD2C8Handler::Execute(SCMD2C8* pPacket)
{
	if (!pPacket) return 1;

	WorldBossMediator * pMediator = (WorldBossMediator *)g_pFacade->retrieveMediator(AppFacade_WorldBoss_Mediator);
	if (pMediator)
	{
		pMediator->sockPlayerInfo(pPacket);
	}

	return 0;
}