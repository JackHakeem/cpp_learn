#ifndef _RANKINGVIEW_H_
#define _RANKINGVIEW_H_

#include "PopContainer.h"
#include "model/ranking/vo/RankItemVo.h"
#include "model/ranking/vo/EquipItemVo.h"

class RankingPanel;

class RankingView : public PopContainer
{
public:
	enum
	{
		REQUEST_RANKING_LIST,
		REQUEST_EQUIP_INFO,
	};
    RankingView();
    ~RankingView();

public:
    virtual bool init();
	virtual void clickCloseHandler(CCObject* pSender);
	void popUpView();

	void updateRankList(const std::vector<RankItemVo>& array);
	void updateEquipments(const std::vector<EquipItemVo>& array);
	void updateMyRank(int rank);
	virtual void removeDataObjectChild();
private:
	enum
	{
		TAG_RENOWN_BTN = 0,
		TAG_CAPACITY_BTN,
		
		MAX_BTN_NUM,
	};

	CCMenuItem* _pButtons[MAX_BTN_NUM];

	bool initTopButtons();
	void onTabHandler(CCObject* pSender);
	void onListItemSelected(CCNode* node, void* data);
	int _curTab;
private:
	void showPanel(int tag);
	void closePanel(int tag);
	

    CCLayer* _pContainer;

	RankingPanel* _rankingPanel[MAX_BTN_NUM];
};

#endif
