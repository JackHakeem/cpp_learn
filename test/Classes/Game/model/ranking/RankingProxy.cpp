#include "RankingProxy.h"
#include "control/AppFacade.h"
#include "view/ranking/RankingMediator.h"

#define MAX_LIST_ITEM_SIZE 50
RankingProxy::RankingProxy()
{
	rankType = CAPACITY_RANKING;
	RankItemVo vo;
	for (int i = 0; i < MAX_RANKING_TYPE; ++i)
	{
		rankItems[i].clear();
	}
}

RankingProxy::~RankingProxy()
{
    for (int i = 0; i < (int)MAX_RANKING_TYPE; ++i)
    {
        rankItems[i].clear();
        equipments[i].clear();
    }
}

void RankingProxy::updateRankList()
{
	sendNotification(Facade_Mediator, AppFacade_Ranking_Mediator, (char*)(&rankItems[(int)rankType]), RankingMediator::UPDATE_RANK_LIST);
	int rank = myRank[rankType];
	sendNotification(Facade_Mediator, AppFacade_Ranking_Mediator, (char*)(&rank), RankingMediator::UPDATE_MY_RANK);
}

void RankingProxy::updateEquipments(int rankType, int playerId, const vector<EquipItemVo>& vo)
{
	if (rankType < 0 || rankType >= MAX_RANKING_TYPE)
		return;
	else
		equipments[rankType][playerId] = vo;

	sendNotification(Facade_Mediator, AppFacade_Ranking_Mediator, (char*)(&equipments[rankType][playerId]), RankingMediator::UPDATE_EQUIPMENTS);
}

//void RankingProxy::updateMyRank()
//{
//	int rank = myRank[rankType];
//	sendNotification(Facade_Mediator, AppFacade_Ranking_Mediator, (char*)(&rank), RankingMediator::UPDATE_MY_RANK);
//}

//void RankingProxy::setSelectedItem(int position)
//{
//	if (position < rankList[rankType].size())
//	{
//		_curSelected = position;
//		RankItemVo vo = rankList[rankType][position];
//		sendNotification(Facade_Mediator, AppFacade_Ranking_Mediator, (char*)&vo, RankingMediator::UPDATE_FIGURE_DATA);
//	}
//}