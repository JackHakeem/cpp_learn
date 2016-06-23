#include "SCMD1ED.h"
#include "view/onlineReward/RewardMediator.h"

bool SCMD1ED::Read()
{
	a_presentValue = readUshort();
	b_addValue = readUshort();

	uint16 num = readUshort();
	for (int i = 0 ; i < num ; i++)
	{
		SCMD1EDNode node;
		node.a_goodsId = readUshort();
		node.b_goodsNum = readInt();
		c_goodsArray.push_back(node);
	}

	return true;
}

int32 SCMD1ED::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD1EDHandler::Execute(this) ;
}


uint32 SCMD1EDHandler::Execute(SCMD1ED* pPacket)
{
	if (!pPacket) return 1;

	RewardMediator * pRewardM = (RewardMediator *)g_pFacade->retrieveMediator(AppFacade_OnlineReward_Mediator);
	if (pRewardM)
	{
		pRewardM->sockADInfo((char *)pPacket);
	}

	return 0;
}