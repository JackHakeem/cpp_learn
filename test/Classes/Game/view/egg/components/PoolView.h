#pragma once

#include "PopContainer.h"
#include "BaseType.h"
#include "model/egg/vo/EggInfo.h"

class TipHelps;
class GameDispatcher;
class RewardPanel;
class ShowItem;

class PoolView:public PopContainer
{
public:
	PoolView();
	~PoolView();

	bool init();
	void setTab(bool b);
	void setGold(int num);
	void showBg(int type);
	void payHandler(CCObject* pSender);
	void setPrizeContainer(int type);
	void updateEggNumInDepot(int num);
	void updatePrize();
	void close(CCObject* pSender);
	void plegeHandler(CCObject* pSender);
	void bagHandler(CCObject* pSender);
	void updateOtherReward(std::vector<EggInfo> arr);
	void updateMyReward(std::vector<EggInfo> arr);
	void touchItem(CCObject* pSender);
public:
	LayerNode* _pContainer;
	/** tab的tips */
	TipHelps* _tabTips;
	/** 剩余金币*/
	CCLabelTTF* _txtGold;
	CCLabelTTF* _txtCapacity;
	SpriteNode* _lowPic;
	/** 许愿的类型（1精灵，2圣光） */
	int plegeType[2];
	/** 许愿的次数 */
	int plegeNum[3];
	std::string plegeCost[3];
	int total;
	int _type;
	ShowItem* _eggGridDic[10];
	GameDispatcher* _dispatcher;

	/** 自己获得的奖励信息面板 */
	RewardPanel* _myRewardPanel;
	/** 其他玩家获得的奖励信息面板 */
	RewardPanel* _otherRewardPanel;
};