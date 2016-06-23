#ifndef _CAPACITYPANEL_H_
#define _CAPACITYPANEL_H_

#include "cocos2d.h"
#include "RankingPanel.h"
#include "model/ranking/vo/RankItemVo.h"
#include "model/ranking/vo/EquipItemVo.h"

class RankingListView;
class FigureItemView;

class CapacityPanel : public RankingPanel
{
public:
	CapacityPanel();
	~CapacityPanel();
	virtual bool init();

	virtual void updateRankList(const std::vector<RankItemVo>& array);
	virtual void updateMyRank(int rank);
	virtual void updateFigureData(const RankItemVo& data);
	virtual void updateEquipments(const std::vector<EquipItemVo>& array);
	virtual int getRankType() { return 2; }
private:
	void startListener();
	void stopListener();
	void onListItemSelected(cocos2d::CCNode* node, void* data);
private:

	RankingListView* _pListView;
	FigureItemView* _pFigureView;
	cocos2d::CCLabelTTF* _pMyRankLabel;

	const std::vector<RankItemVo>* _pListData;

	int _curSelectedItem;
};

#endif
