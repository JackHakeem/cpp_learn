#ifndef _RANKINGPANEL_H_
#define _RANKINGPANEL_H_

#include "LayerNode.h"
#include "model/ranking/vo/RankItemVo.h"
#include "model/ranking/vo/EquipItemVo.h"

class RankingPanel : public LayerNode
{
public:
	enum
	{
		RANK_ITEM_SELECTED,
	};
	virtual bool init() { return CCLayer::init(); }
    virtual void updateRankList(const std::vector<RankItemVo>& array) = 0;
	virtual void updateMyRank(int rank) {};
	virtual void updateFigureData(const RankItemVo& data) {};
	virtual void updateEquipments(const std::vector<EquipItemVo>& array) {};
	virtual int getRankType() = 0;
};
#endif
