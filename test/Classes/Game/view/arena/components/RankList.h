#pragma once

#include "BaseType.h"
class ArenaUI;
class AccountInfoVo;
class SCMD361;
class RankItem;
class CustomCD;
class RankList:public LayerNode
{
public:
	enum
	{
		RankListZ_item_0,
		RankListZ_item_1,
		RankListZ_item_2,
		RankListZ_item_3,
		RankListZ_item_4,
		RankListZ_quota,
		RankListZ_quota_value,
		RankListZ_quota_btn,
		RankListZ_cd_title,
		RankListZ_cd,
		RankListZ_cd2,
		RankListZ_reset,
		RankListZ_cd_title2,
	};

	enum
	{
		RankListTAG_item_0,
		RankListTAG_item_1,
		RankListTAG_item_2,
		RankListTAG_item_3,
		RankListTAG_item_4,
		RankListTAG_quota,
		RankListTAG_quota_value,
		RankListTAG_quota_btn,
		RankListTAG_cd_title,
		RankListTAG_cd,
		RankListTAG_cd2,
		RankListTAG_reset,
		RankListTAG_cd_title2,
	};

	RankList();
	~RankList();

	bool initWithParam(ArenaUI* pContainer);
	void update(SCMD361* param);
	void clickHandler(CCObject* pSender);
	void handleBuyArena(CCObject* pSender);
	void handleBuyArenaCancel(CCObject* pSender);
	void handleResetOpps(CCObject* pSender);
public:
	std::vector<RankItem*> _itemDic;

	ArenaUI* _pContainer;
	AccountInfoVo* _accountInfo;

	uint32 _cdvalue; // cd时间
	int32 _price;  // 购买竞技挑战次数的金币价格
	CustomCD* _suiteCD;

	CustomCD* _refreshCD;
	uint32 _refreshValue;
	CCMenuItemSprite *m_btnReset;
public:
	void tmpClearCD(CCObject* pSender);


};