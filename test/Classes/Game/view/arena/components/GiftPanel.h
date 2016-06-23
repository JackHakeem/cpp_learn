#pragma once

#include "BaseType.h"

class ArenaUI;
class SCMD285;
struct CfgRankVo;

class GiftPanel:public LayerNode
{
public:
	enum
	{
		GiftPanelZ_bg1,
		GiftPanelZ_bg2,
		GiftPanelZ_closebtn,
		GiftPanelZ_getbtn,
		GiftPanelZ_boxOpen,
		GiftPanelZ_boxRank0,
		GiftPanelZ_boxRank1,
		GiftPanelZ_boxRank2,
		GiftPanelZ_boxRank3,
		GiftPanelZ_txtReward,
		GiftPanelZ_txtReward_title,
		GiftPanelZ_rank,
		GiftPanelZ_rank_title,
		GiftPanelZ_str0,
	};

	enum
	{
		GiftPanelTAG_bg1,
		GiftPanelTAG_bg2,
		GiftPanelTAG_closebtn,
		GiftPanelTAG_getbtn,
		GiftPanelTAG_boxOpen,
		GiftPanelTAG_boxRank0,
		GiftPanelTAG_boxRank1,
		GiftPanelTAG_boxRank2,
		GiftPanelTAG_boxRank3,
		GiftPanelTAG_txtReward,
		GiftPanelTAG_txtReward_title,
		GiftPanelTAG_rank,
		GiftPanelTAG_rank_title,
		GiftPanelTAG_str0,
	};

	GiftPanel();
	~GiftPanel();

	bool initWithParam(ArenaUI* pContainer);

	void clickClose(CCObject* pSender);
	void clickGet(CCObject* pSender);

	void update(SCMD285* data, ArenaUI* pContainer);
	void setRankingTip(int rank);
	void setGiftOpt(bool value);
public:
	ArenaUI* _pContainer;
	CCMenuItemSprite *_btnGet;
	CfgRankVo* _cfgRankVo;
	CCLabelTTF* pBtnGetLabel;
};