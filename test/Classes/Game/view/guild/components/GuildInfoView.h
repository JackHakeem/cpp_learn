#pragma once

#include "BaseType.h"
#include "model/guild/vo/GuildInfoVo.h"
class GuildInfoView:public LayerNode
{
public:
	GuildInfoView(GuildInfoVo guildVo);
	~GuildInfoView();

	bool init();
	void dispear(CCObject* pSender);
	void registerWithTouchDispatcher( void );
	bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
public:
	LayerNode* _container;


	//__skin:MovieClip = null;	//公会信息面板
	//_icon:MovieClip = null;	//公会图标
	//_level:TextField = null;		//公会等级
	//_name:TextField = null;			//公会名称
	//_leader:TextField = null;		//公会会长
	//_count:TextField = null;		//公会人数
	//_introduce:TextField = null;	//公会介绍
	//_closeBtn:SimpleButton = null;	//“关闭”按钮
	GuildInfoVo _guildVo;
};