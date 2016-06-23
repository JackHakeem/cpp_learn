#pragma once

#include "BaseType.h"
#include "model/guild/vo/MemberVo.h"

class MemberPanel;
class TechPanel;
class VerifyPanel;
class GuildView;
class GameDispatcher;
class GuildDispatcher;
class BaseListPanel;

class GuildTabPanel:public LayerNode
{
public:
	enum
	{
		GuildTabPanelZ_tabbtn,
	};
	enum
	{
		GuildTabPanelTAG_tabbtn,
	};
public:
	GuildTabPanel();
	~GuildTabPanel();

	bool init();
	void initView();
	void onTabChange(CCObject* pSender);
	void popOutPreView();
	int getinitEventConst();
	int getpanelIndex();
	BaseListPanel* getcurrentPanel();
	void eventON();

	CC_PROPERTY(MemberVo, _myMemberInfo, myMemberInfo)
public:
	MemberPanel* _memberPanel;
	TechPanel* _techPanel;
	VerifyPanel* _verifyPanel;
	GuildView* guildView;
	CCMenuItemSprite* _curTab;
	BaseListPanel* _curPanel;
	GameDispatcher* _dispatcher;
	uint _panelIndex;
	GuildDispatcher* _guildDispatcher;

};