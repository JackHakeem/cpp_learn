#ifndef _BAGGOODS_H_
#define _BAGGOODS_H_

#include "BaseType.h"
#include "utils/TipBase.h"

USING_NS_CC;

class TipHelps;
class GoodsInfo;
class GameDispatcher;
class BagGoods:public LayerNode, public TipBase//cocos2d::CCSprite, public CCTargetedTouchDelegate
{
public:
	enum
	{
		RENDERZ_unlock_lock = 0,
		RENDERZ_item,
		RENDERZ_qualityframe,
		RENDERZ_number,
		//RENDERZ_thisCopy,
	};
	enum
	{
		RENDERTAG_unlock_lock = 0,
		RENDERTAG_item,
		RENDERTAG_qualityframe,
		RENDERTAG_number,
		//RENDERTAG_thisCopy,
	};

	BagGoods();
	~BagGoods();

	bool initBagGoods(GoodsInfo* info, int32 sitNum, int32 page, bool lock=false);
	void reShowItemAndFrame(bool isShow);
	void onMouseDownHandler(CCPoint curTouchPoint);
	void onMouseMoveHnadler(CCPoint curTouchPoint);
	void onMouseUpHnadler(CCPoint curTouchPoint);

	void onRollOverHandler();

	virtual CCSize getSrcContentSize();
	void OnTimer(CCObject* pSender);

public:
	bool _lock;
	uint32 _mySitNum;
	int32 m_page;
	bool isHasCopy;
	bool isMove;
	

	TipHelps* myTip;
	GameDispatcher* _dispatcher;
	//LayerNode* thisCopy;
	
};

#endif