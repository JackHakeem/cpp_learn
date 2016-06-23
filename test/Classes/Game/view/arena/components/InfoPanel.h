#pragma once

#include "BaseType.h"

class AccountInfoVo;
class RoleManage;
class GameDispatcher;
class ArenaUI;
class SCMD361;
class InfoPanel:public LayerNode
{
public:
	enum
	{
		InfoPanelZ_name,
		InfoPanelZ_rank,//ÅÅÃû
		InfoPanelZ_title_title,//³ÆºÅ
		InfoPanelZ_title,
		InfoPanelZ_rank_title,
		InfoPanelZ_Straight,//Á¬Ê¤
		InfoPanelZ_Straight_title,
		InfoPanelZ_HeroRankBtn,
		InfoPanelZ_Renown,//ÃûÉù
		InfoPanelZ_Renown_title,
	};

	enum
	{
		InfoPanelTAG_name,
		InfoPanelTAG_rank,
		InfoPanelTAG_title_title,
		InfoPanelTAG_title,
		InfoPanelTAG_rank_title,
		InfoPanelTAG_Straight,
		InfoPanelTAG_Straight_title,
		InfoPanelTAG_HeroRankBtn,
		InfoPanelTAG_Renown,
		InfoPanelTAG_Renown_title,
	};

	InfoPanel();
	~InfoPanel();

	bool initWithParam(ArenaUI* pContainer);
	void update(SCMD361* data);
	void clickHeroRank(CCObject* pSender);
public:

	RoleManage* _roleManage;
	GameDispatcher* _dispatcher;
	AccountInfoVo* _accountInfo;
	ArenaUI* _pContainer;
};