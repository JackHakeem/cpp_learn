#ifndef _IntervalLayer_H_
#define _IntervalLayer_H_

#include "BaseType.h"
#include "FocusNode.h"
USING_NS_CC;
class IntervalLayer:public LayerNode
{
public:
	enum
	{
		IntervalLayerZ_eqdrop = 100,
		IntervalLayerZ_GuildPre,
		IntervalLayerZ_guild_editView,
		IntervalLayerZ_guild_memberListMenu,
		IntervalLayerZ_guild_creatGuild,
		IntervalLayerZ_guild_info,
		IntervalLayerZ_guild_donateview,
		IntervalLayerZ_guild_silverMineRank,
		IntervalLayerZ_guild_silverMineTips,
		IntervalLayerZ_towerRank,
		IntervalLayerZ_EndBtnTips,
		IntervalLayerZ_reserveDepot,
		IntervalLayerZ_dungeonGua,
		IntervalLayerZ_chatView,
		IntervalLayerZ_chatBtn,
		IntervalLayerZ_chat,//¥ÛΩÁ√Ê
		IntervalLayerZ_ore_plant,
		IntervalLayerZ_ore_help,
		IntervalLayerZ_ZX,
		
	};
	enum
	{
		IntervalLayerTAG_eqdrop,
		IntervalLayerTAG_GuildPre,
		IntervalLayerTAG_guild_editView,
		IntervalLayerTAG_guild_memberListMenu,
		IntervalLayerTAG_guild_createGuild,
		IntervalLayerTAG_guild_info,
		IntervalLayerTAG_guild_donateview,
		IntervalLayerTAG_guild_silverMineRank,
		IntervalLayerTAG_guild_silverMineTips,
		IntervalLayerTAG_towerRank,
		IntervalLayerTAG_EndBtnTips,
		IntervalLayerTAG_reserveDepot,
		IntervalLayerTAG_dungeonGua,
		IntervalLayerTAG_chat,
		IntervalLayerTAG_chatView,
		IntervalLayerTAG_chatBtn,
		IntervalLayerTAG_ore_plant,
		IntervalLayerTAG_ore_help,
		IntervalLayerTAG_ZX,
	};

	IntervalLayer();
	~IntervalLayer();
public:
	virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
public:
	CCPoint preTouchPoint;
    CCPoint currentTouchPoint;

	CC_PROPERTY(int32, _lastItemGID, LastItemGID)
};

#endif