#ifndef _WINDOWLAYER_H_
#define _WINDOWLAYER_H_

#include "BaseType.h"
#include "FocusNode.h"
USING_NS_CC;

class WindowLayer:public LayerNode
{
public:
	enum
	{
		WindowLayerZ_PopUIBg,
		WindowLayerZ_thisCopy = 100,
		WindowLayerZ_confirmFrame = WindowLayerZ_thisCopy,
		WindowLayerZ_textInputConfirm,
		WindowLayerZ_RecvTaskEffect,
		WindowLayerZ_FinTaskEffect,

		WindowLayerZ_Broadcast_Notice = 1000,
		WindowLayerZ_Newhand_Help,
		
	};
	enum
	{
		WindowLayerTAG_PopUIBg,
		WindowLayerTAG_thisCopy= 100, 
		WindowLayerTAG_confirmFrame,
		WindowLayerTAG_textInputConfirm,
		WindowLayerTag_RecvTaskEffect,
		WindowLayerTag_FinTaskEffect,

		WindowLayerTag_Broadcast_Notice = 1000,
		WindowLayerTag_Newhand_Help,
	
	};
public:
	bool init();
	int getCurNodeTag(CCPoint tarPoint);

	 
	void registerWithTouchDispatcher();
	bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	void arenaWaitTime();
	void clickCancel(CCObject * pSender);
};

#endif