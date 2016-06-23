#include "SCMD45B.h"
//#include "control/campFight/campFightCommand.h"
#include "view/campFight/CampFightMediator.h"

bool SCMD45B::Read()
{
	a_type = readByte();
	b_score = readInt();
	c_num   = readShort();
	for(int i = 0; i < c_num; ++i)
	{
		SCMD45BNode node;
		node.a_playerId = readInt();
		node.b_name     = readString();
		node.c_contiWin = readShort();
		d_members.push_back(node);
	}
	e_type = readByte();
	f_score = readInt();
	g_num   = readShort();
	for(int i = 0; i < g_num; ++i)
	{
		SCMD45BNode node;
		node.a_playerId = readInt();
		node.b_name     = readString();
		node.c_contiWin = readShort();
		h_members.push_back(node);
	}
	return true;
}

int32 SCMD45B::Execute()
{
	if (!Read())
	{
		return 1;
	}
	return SCMD45BHandler::Execute(this);
}

uint32 SCMD45BHandler::Execute(SCMD45B* pPacket)
{
	if (! pPacket)
		return 1;
	CampFightMediator* p = (CampFightMediator*)g_pFacade->retrieveMediator(AppFacade_CampFight_Mediator);
	if (p)
		p->UpdateCampFightSceneInfo(pPacket);
	//sendNotification(Facade_Command, AppFacade_Ranking_Proxy_Change, (char*)pPacket, CampFightCommand::UPDATE_CAMPFIGHT_INFO);
	return 0;
}