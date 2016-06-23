#pragma once

#include "BaseType.h"
#include "socket/command/s28/SCMD285.h"

class ArenaUI;
class SCMD285;

class RankingInfo:public LayerNode
{
public:
	enum
	{
		RankingInfoZ_btnClose,
		RankingInfoZ_str0,
		RankingInfoZ_str1,
		RankingInfoZ_str2,
	};

	enum
	{
		RankingInfoTAG_btnClose,
		RankingInfoTAG_str0,
		RankingInfoTAG_str1,
		RankingInfoTAG_str2,
	};

	RankingInfo();
	~RankingInfo();

	bool initWithParam(ArenaUI* pContainer);
	void updateRanking(int rank);
	void clickBox(CCObject* pSender);
	void updatePackage(SCMD285* param);
public:
	ArenaUI* _pContainer;
	bool _canTake;   // 礼包是否可领取 

	int16	a_meRank;	uint32	b_time;
	std::vector<SCMD285Node1> c_rewards;
	std::vector<SCMD285Node> d_rankArr;
	CCMenuItemImage *_btnClose;
};