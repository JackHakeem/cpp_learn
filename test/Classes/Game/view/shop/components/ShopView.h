#ifndef _SHOPVIEW_H_
#define _SHOPVIEW_H_

#include "PopContainer.h"
#include "LayerNode.h"

#include "model/shop/vo/ShopGoodsVo.h"

USING_NS_CC;

class ShopUIPartialScrollView;
class ShopGoods;
class GameDispatcher;
class ShopCreate;
class ShopView:public PopContainer
{
public:
	enum
	{
		RENDERZ_shopContainer = 0,
		RENDERZ_shopbg,
		RENDERZ_g_pShopCreate,
		RENDERZ_goldline,
		RENDERZ_buttonMenu,
		RENDERZ_select,
		RENDERZ_title,
	};
	enum
	{
		RENDERTAG_select = 0,
	};
public:
	ShopView();
	virtual ~ShopView();
	bool init();
	virtual void reinit(){};
	void createList(int32 shopId, int32 page=1);
	void resetPage(int32 page);

	void onEnter();
	void onExit();
	virtual void removeDataObjectChild();
public:
//touch begin
	CCRect rect();

	bool containsTouchLocation(CCPoint touchPoint);

    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){};

	//void step(ccTime dt);//touch counter
	/*
	enum TouchStateEnum
	{
		TouchState_0 = 0,//no state
		TouchState_1, //clicked£¬before mousemove, befor BAGVIEW_TOUCH_STATE1_INTERVAL 
		TouchState_2, //BAGVIEW_TOUCH_STATE1_INTERVAL no a do
		TouchState_3, //backpack pageview
		TouchState_4, //ignore model
		TouchState_5, //click and selected model
		TouchState_6, //check item info model
	};
	*/
	/*
		 0
	   /   \
	   1   2
	  /     \
	 3       4
	*/

	//CC_PROPERTY(int32, _TouchState, TouchState)	
	//ccTime m_fStepCounter;//timer

	CCPoint preTouchPoint;
    CCPoint currentTouchPoint;

//touch end

	ShopGoods* getCurSelectedShopGoods(CCPoint p);
	CC_PROPERTY(bool, _selectFrameShow, SelectFrameShow)
public:
	int32 _shopId;
	int32 _totalPage;
	int32 _pagesize;
	int32 _curPage;
	std::vector<ShopGoodsVo>* _shopGoods;

public:

	uint32 _capacity;
	uint32 _noEmpty;
	LayerNode* __container;

	ShopUIPartialScrollView *scrollView;
	cocos2d::CCSize m_viewSize;
	ShopGoods* m_pCurSelectedBagGoods;
	GameDispatcher* dispatcher;
	//int32 LayerManager::tipsLayer->getLastItemGID();
};

#endif