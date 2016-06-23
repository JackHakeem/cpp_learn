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
		ListMenu_Member = 1,//����ְ�� -> ��Ա
		ListMenu_Officer = 2,//����ְ�� -> ��Ա
		ListMenu_ViceLeader = 3,//����ְ�� -> ���᳤
		ListMenu_ShiftLeader = 4,
		
		ListMenu_ExpelledMember,//������Ա
		ListMenu_ViewInformation,	//�鿴��Ϣ
		ListMenu_PrivateChat,		//����˽��
		ListMenu_AddFriend,				//��Ӻ���
		ListMenu_InviteToTeam,		//�������
		ListMenu_CopyName,			//��������
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