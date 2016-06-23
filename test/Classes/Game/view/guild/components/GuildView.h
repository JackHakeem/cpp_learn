#ifndef _GuildView_H_
#define _GuildView_H_

#include "PopContainer.h"
#include "BaseType.h"
#include "model/guild/vo/GuildInfoVo.h"
#include "model/guild/vo/MemberVo.h"

class GuildTabPanel;
class GuildView : public PopContainer
{
public:
	enum
	{
		GuildViewZ_bg1,
		GuildViewZ_bg2,
		GuildViewZ_bg3,
		GuildViewZ_icon,
		GuildViewZ_junhuidengji_name,
		GuildViewZ_btnClose,
		GuildViewZ_fmMedal,
		GuildViewZ_btUpgrade,
		GuildViewZ_txt,
		GuildViewZ_tabPanel,
		GuildViewZ_btnEditInfo,
		GuildViewZ_btnAbort,
		GuildViewZ_btnCancelAbort,
		GuildViewZ_btnQuit,
	};
	enum
	{
		GuildViewTAG_bg1,
		GuildViewTAG_bg2,
		GuildViewTAG_bg3,
		GuildViewTAG_icon,
		GuildViewTAG_junhuidengji_name,
		GuildViewTAG_btnClose,
		GuildViewTAG_fmMedal,
		GuildViewTAG_btUpgrade,
		GuildViewTAG_txtLevel,
		GuildViewTAG_txtName,
		GuildViewTAG_txtID,
		GuildViewTAG_txtRank,
		GuildViewTAG_txtOnline,//成员上限
		GuildViewTAG_txtTime,
		GuildViewTAG_txtQQ,
		GuildViewTAG_txtPost,
		GuildViewTAG_btnModify,
		GuildViewTAG_tabPanel,
		GuildViewTAG_btnEditInfo,
		GuildViewTAG_btnAbort,
		GuildViewTAG_btnCancelAbort,
		GuildViewTAG_btnQuit,
	};

public:
	GuildView();
	~GuildView();

public:

	bool init();
public:
	void initView();
	void registerWithTouchDispatcher( void );
	bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
	void updateEmblemDispatcher(CCObject* pSender);
	void setguildInfo(GuildInfoVo& info);
	CCLabelTTF* getLabel(int tag);
	void changeIcon(int emblemGrade);
	void updateButton();
	void setmyMemberInfo(MemberVo& info);
	MemberVo getmyMemberInfo();
	int getpanelIndex();
	void updateList(std::list<GuildVoBase*> datas);
	void eventON();
    void setPage(int max, int index);
	void editGuildInfo(CCObject* pSender);
	void abortGuildDispatcher(CCObject* pSender);
	void sureAbortGuild(CCObject* pSender);
	void sureAbortGuildCancel(CCObject* pSender);
	void abortCancelDispatcher(CCObject* pSender);
	void okFunction(CCObject* pSender);
	void okFunctionCancel(CCObject* pSender);
	void exitGuildDispatcher(CCObject* pSender);
	void sureExitGuild(CCObject* pSender);
	void sureExitGuildCancel(CCObject* pSender);
	CCNode * getNewHandItem(int id);

public:
	LayerNode* _container;
	GuildInfoVo _guildInfo; //自身公会信息;
	MemberVo _myMemberInfo;//自身成员信息
	CC_PROPERTY(bool, _hasInit, hasInit)
	GuildTabPanel* _tabPanel;
};

#endif