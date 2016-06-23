#ifndef _RANKINGPROXY_H_
#define _RANKINGPROXY_H_

#include "mvc/Proxy.h"
#include <vector>
#include "model/ranking/vo/RankItemVo.h"
#include "model/ranking/vo/EquipItemVo.h"
#include "BaseType.h"

class RankingProxy : public Proxy
{
public:
    enum
    {
		EQUIP_RANKING = 0,
		RENOWN_RANKING,
        CAPACITY_RANKING,
        PROCESS_RANKING,
        MAX_RANKING_TYPE,
    };
    RankingProxy();
    ~RankingProxy();

	void updateRankList();
	void updateEquipments(int rankType, int playerId, const std::vector<EquipItemVo>& vo);

	int rankType;
    std::vector<RankItemVo> rankItems[MAX_RANKING_TYPE];
    std::map<int, std::vector<EquipItemVo> > equipments[MAX_RANKING_TYPE];
	int myRank[MAX_RANKING_TYPE];
};

#endif
