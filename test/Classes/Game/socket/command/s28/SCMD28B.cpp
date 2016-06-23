#include "SCMD28B.h"
#include "view/broadcast/BroadcastMediator.h"
#include "control/AppFacade.h"

bool SCMD28B::Read()
{
	int nodeNum = readUshort();

	for (int i = 0;i < nodeNum; i++)
	{
		SCMD28BNode node;
		node.a_id = readInt();
		node.b_name = readString();
		heros.push_back(node);
	}

	return true;
}


int32 	SCMD28B::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD28BHandler::Execute(this);
}


uint32 SCMD28BHandler::Execute(SCMD28B* pPacket)
{
	if (!pPacket) return 1;

	BroadcastMediator * pBroadCastMediator = (BroadcastMediator *)g_pFacade->retrieveMediator(AppFacade_BroadCast_Mediator);
	if (pBroadCastMediator)
	{
		pBroadCastMediator->sockHeroNoticeRecived(pPacket);
	}

	return 0;
}