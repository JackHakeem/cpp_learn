#pragma once


#include "BaseListPanel.h"
#include "model/guild/vo/MemberVo.h"
#include "CommonList.h"
class GuildDispatcher;
class PageNav;
class MemberPanel:public BaseListPanel
{
public:
	enum
	{
		ListMenu_Member = 1,//更改职务 -> 会员
		ListMenu_Officer = 2,//更改职务 -> 官员
		ListMenu_ViceLeader = 3,//更改职务 -> 副会长
		ListMenu_ShiftLeader = 4,
		
		ListMenu_ExpelledMember,//开除会员
		ListMenu_ViewInformation,	//查看信息
		ListMenu_PrivateChat,		//发起私聊
		ListMenu_AddFriend,				//添加好友
		ListMenu_InviteToTeam,		//邀请组队
		ListMenu_CopyName,			//复制名称
	};
public:
	MemberPanel();
	~MemberPanel();

	bool init();
	void initBody();
	void onPageChange(CCNode* pSender, void* data);
	void initBackground();
	void setPage(int max, int index);
	void onFuncClick(CCObject* pSender);
	void onListItemClick(CCObject* pSender);
	int dutyToId(std::string duty);
	void expelledMember();
	void confirmExpelledMember(CCObject* pSender);
	void confirmExpelledMemberCancel(CCObject* pSender);
	void ChangeDuty(int duty);
	void confirmChangeDuty(CCObject* pSender);
	void confirmChangeDutyCancel(CCObject* pSender);
public:
	void updateList(std::list<GuildVoBase*>& listDatas);
	
	CommonList* _memberList;
	GuildDispatcher* _guildDispatcher;
	PageNav* _pageNav;

	MemberVo _currentMember;
	int m_tmp_duty2CCMD1B9;
};