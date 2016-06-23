#include "campFightCommand.h"
#include "model/campFight/vo/campFightVo.h"

CampFightCommand::CampFightCommand()
{
	m_pCampFightProxy = NULL;
	if (g_pFacade)
	{
		m_pCampFightProxy = 
			dynamic_cast<CampFightProxy*>(g_pFacade->retrieveProxy(AppFacade_CampFight_Proxy));
		//m_pCampFightMediator = 
			//dynamic_cast<CampFightMediator*>(g_pFacade->retrieveMediator(AppFacade_CampFight_Mediator));
	}
}
CampFightCommand::~CampFightCommand()
{

}
void CampFightCommand::execute(int32 command, char* data)
{
	switch(command)
	{
	case UPDATE_CAMPFIGHT_INFO:
		{
			UpdateCampFightInfo((SCMD45B*)data);
		}
		break;
	case UPDATE_MY_INFO:
		{
			UpdateMyInfo((SCMD459*)data);
		}
		break;
	default:
		break;
	}
}
void CampFightCommand::UpdateMyInfo(SCMD459* pPacket)
{
	TMyCampFightInfo myInfo;
	myInfo.score = pPacket->a_score;
	myInfo.hisConstiWinTims = pPacket->b_hisContiWinTms;
	myInfo.sumPop = pPacket->c_sumPop;
	myInfo.sumSilver = pPacket->d_sumSilver;
	myInfo.state = pPacket->e_state;
	m_pCampFightProxy->UpdateMyInfo(&myInfo);
}
void CampFightCommand::UpdateCampFightInfo(SCMD45B* pPacket)
{
	//translate data
	TCampInfo* iceCity = new TCampInfo();
	TCampInfo* fireCity = new TCampInfo();
	if (ICE_CAMP == pPacket->a_type)
	{
		iceCity->scores = pPacket->b_score;
		vecCFPlayerInfo memInfo;
		std::vector< SCMD45BNode > nodes = pPacket->d_members; 
		for (uint16 i = 0; i != pPacket->c_num; ++i)
		{
			SCMD45BNode node = nodes[i];
			TCFPlayerInfo* p = new TCFPlayerInfo(node.a_playerId,
				node.b_name,node.c_contiWin);
			memInfo.push_back(p);
		}
		iceCity->members = memInfo;
	}
	if (FIRE_CAMP == pPacket->e_type)
	{
		fireCity->scores = pPacket->f_score;
		vecCFPlayerInfo memInfo;
		std::vector< SCMD45BNode > nodes = pPacket->h_members; 
		for (uint16 i = 0; i != pPacket->g_num; ++i)
		{
			SCMD45BNode node = nodes[i];
			TCFPlayerInfo* p = new TCFPlayerInfo(node.a_playerId,
				node.b_name,node.c_contiWin);
			memInfo.push_back(p);
		}
		fireCity->members = memInfo;
	}
	//update proxy
	m_pCampFightProxy->UpdateCampFightInfo(iceCity, fireCity);	
}