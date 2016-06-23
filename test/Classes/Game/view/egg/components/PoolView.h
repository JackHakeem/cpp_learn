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
	/** tab��tips */
	TipHelps* _tabTips;
	/** ʣ����*/
	CCLabelTTF* _txtGold;
	CCLabelTTF* _txtCapacity;
	SpriteNode* _lowPic;
	/** ��Ը�����ͣ�1���飬2ʥ�⣩ */
	int plegeType[2];
	/** ��Ը�Ĵ��� */
	int plegeNum[3];
	std::string plegeCost[3];
	int total;
	int _type;
	ShowItem* _eggGridDic[10];
	GameDispatcher* _dispatcher;

	/** �Լ���õĽ�����Ϣ��� */
	RewardPanel* _myRewardPanel;
	/** ������һ�õĽ�����Ϣ��� */
	RewardPanel* _otherRewardPanel;
};