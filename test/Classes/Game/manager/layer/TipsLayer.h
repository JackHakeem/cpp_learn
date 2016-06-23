#ifndef _TIPSLAYER_H_
#define _TIPSLAYER_H_

#include "BaseType.h"
#include "FocusNode.h"
USING_NS_CC;
class TipsLayer:public LayerNode
{
public:
	enum
	{
		//TipsLayerZ_thisCopy = 100,
		TipsLayerZ_itemInfoShow = 100,
		TipsLayerZ_textInputConfirm,
		TipsLayerZ_friendCheck,
		TipsLayerZ_rankReward,
		TipsLayerZ_heroUi,
		TipsLayerZ_messageUi,
		TipsLayerZ_messageInfoBox,
		TipsLayerZ_NewEAlert,
		TipsLayerZ_LoadingPercent,
		TipsLayerZ_CurPercent,
		TipsLayerZ_popChannels,
		TipsLayerZ_msgInfoBox,
		TipsLayerZ_SysNotice,
		TipsLayerZ_confirmFrame,
		TipsLayerZ_confirmFrameTower,
		TipsLayerZ_egg_washPanel,
		TipsLayerZ_egg_NumSelectBox,
		TipsLayerZ_cdmanage,
		TipsLayerZ_tipHelpMelting,
		TipsLayerZ_ZXDuiView,


		WindowLayerZ_Loading,
	};
	enum
	{
		//TipsLayerTAG_thisCopy= 100, 
		TipsLayerTAG_itemInfoShow,
		TipsLayerTAG_textInputConfirm,
		TipsLayerTAG_friendCheck,
		TipsLayerTAG_rankReward,
		TipsLayerTAG_heroUi,
		TipsLayerTAG_messageUi,
		TipsLayerTAG_messageInfoBox,
		TipsLayerTAG_NewEAlert,
		TipsLayerTAG_LoadingPercent,
		TipsLayerTAG_CurPercent,
		TipsLayerTAG_popChannels,
		TipsLayerTAG_msgInfoBox,
		TipsLayerTAG_SysNotice,
		TipsLayerTAG_confirmFrame,
		TipsLayerTAG_confirmFrameTower,
		TipsLayerTAG_egg_washPanel,
		TipsLayerTAG_egg_NumSelectBox,
		TipsLayerTAG_cdmanage,
		TipsLayerTAG_tipHelpMelting,
		TipsLayerTAG_ZXDuiView,


		WindowLayerTAG_Loading,
	};

	TipsLayer();
	~TipsLayer();
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