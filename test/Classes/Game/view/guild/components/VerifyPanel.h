#pragma once


#include "BaseListPanel.h"
#include "model/guild/vo/MemberVo.h"
#include "CommonList.h"
class GuildDispatcher;
class PageNav;
class VerifyPanel:public BaseListPanel
{
public:
	enum
	{
		VerifyPanelZ_btnyes,
	};
	enum
	{
		VerifyPanelTAG_btnyes,
	};
public:
	VerifyPanel();
	~VerifyPanel();

	bool init();
	void initBody();
	void onPageChange(CCNode* pSender, void* data);
	void initBackground();
	void setPage(int max, int index);
	void onYesBtnClick(CCObject* pSender);
public:
	void updateList(std::list<GuildVoBase*>& listDatas);
	CC_PROPERTY(MemberVo, _myMemberInfo, myMemberInfo)
	CommonList* _verifyList;
	GuildDispatcher* _guildDispatcher;
	PageNav* _pageNav;
	std::string _name;
};