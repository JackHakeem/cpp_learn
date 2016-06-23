#pragma once

#include "BaseType.h"
#include "model/guild/vo/MemberVo.h"
#include "model/guild/vo/GuildInfoVo.h"
#include "cocos2d.h"
using namespace cocos2d;

class GuildItem:public LayerNode
{
public:
	enum
	{
		GuildItemZ_bg1,
	};
	enum
	{
		GuildItemTAG_bg1,
	};
	GuildItem();
	~GuildItem();

	bool init(GuildInfoVo guildVo);
	void initView();
	void onApplyBtnClick(CCObject* obj);
	void onExamineBtnClick(CCObject* obj);
	void canApply( bool flag );
public:
	//_item:MovieClip = null;				//整个Item元素
	//_rank:TextField = null;				//公会排名字段
	//_name:TextField = null;				//公会名称字段
	//_leader:TextField = null;			//公会会长字段
	//_level:TextField = null;			//公会等级字段
	//_count:TextField = null;			//公会成员数
	CCMenu* _btnApply;		//申请按钮
	CCMenu* _btnExamine;	//查看按钮
	//_introduce:String = "";				//公会介绍
	CCLabelTTF* _applyText;
	GuildInfoVo _guildVo;		//公会信息对象
};