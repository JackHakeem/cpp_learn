#ifndef _GuildPreView_H_
#define _GuildPreView_H_

#include "BaseType.h"
#include "model/guild/vo/GuildInfoVo.h"
#include "model/guild/vo/MemberVo.h"
#include "model/guild/vo/GuildVoBase.h"
#include "CommonList.h"
#include "PageNav.h"

class GuildPreView : public LayerNode
{
public:
	enum
	{
		GuildPreViewZ_bg1,

	};
	enum
	{
		GuildPreViewTAG_bg1,
	};

public:
	GuildPreView();
	~GuildPreView();

public:

	bool init();
public:
	void initView();
	void registerWithTouchDispatcher( void );
	bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
public:
	LayerNode* _container;

	//private var __skin:MovieClip;
	//private var _txtInput:TextField;
	//private var _btnSearch:SimpleButton;
	CCMenu* _btnCreate;
	//private var _creatView:PopContainer;		//创建公会窗口
	//private var _infoView:GuildInfoView;		//公会信息窗口

	PageNav* _pageNav;
	//private var _checkIndex:uint = 0;
	CommonList* _guildList;
	CC_PROPERTY( bool, _hasInit, hasInit )
	CC_PROPERTY( bool, _hasGuild, hasGuild )
	void onInit();
	void updateList( std::list<GuildVoBase*> listDatas );
	void setPage( int max = 1, int index = 1 );
	void dispear(CCObject* pSender);
	void onPageChange(CCNode* pSender, void* data);
	void onCreatClick(CCObject* obj);
};

#endif