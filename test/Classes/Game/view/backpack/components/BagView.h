#ifndef _BAGVIEW_H_
#define _BAGVIEW_H_

#include "PopContainer.h"
#include "LayerNode.h"
#include "FocusNode.h"
#include "utils/Timer.h"

class BagUIPartialScrollView;
class GoodsInfo;
class BagCreate;
class BagGoods;
class GameDispatcher;
#define BAGVIEW_TOUCH_STATE1_INTERVAL (0.3f)
#define BAGVIEW_TOUCH_DIAOTAX (2)

USING_NS_CC;
class BagView:public PopContainer
{
public:
	enum
	{
		RENDERZ_bagContainer = 0,
		RENDERZ_g_pBagCreate,
		RENDERZ_goldline,
		RENDERZ_buttonMenu,
		RENDERZ_select,
	};

	enum
	{
		RENDERTAG_select = 90,
	};

	enum
	{
		BAG_ADD_GRID_CLICK,
		BAG_SORT_CLICK,
	};
	BagView();
	virtual ~BagView();
	bool init();
	void OpenBag(std::map<int32, GoodsInfo*>& goodDic, int32 noEmpty, uint32 goodsNum);

	virtual int32 getSelfTag();
	void reinit();

	BagGoods* getCurSelectedBagGoods(CCPoint p);
	void updateGoods(char* arr, int32 noEmpty);
	
	void onClickFarBank(CCObject* pSender);
	void onClickFarShop(CCObject* pSender);
	void onClickSort(CCObject* pSender);
	void openFarBankOrShop(int32 type);
	void handleBuyCellConfirm(CCObject* pSender);
	void handleBuyCellCancel(CCObject* pSender);
	void addGrid(int32 num, int32 money);

	void onEnter();
	void onExit();
	virtual void backHandlerByCurrentUIStage();
	CCNode *getNewHandItem(int sitNum);

	virtual void removeDataObjectChild();

public:
//´¥¿Øbegin
	CCRect rect();

	bool containsTouchLocation(CCPoint touchPoint);

    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){};

	void onClickHandler(BagGoods* bagGoods);
	void step(ccTime dt);//´¥¿Ø¼ÆÊ±

	enum TouchStateEnum
	{
		TouchState_0 = 0,//No state, is not inspire the touch module
		TouchState_1, // points down, also didn't move, BAGVIEW_TOUCH_STATE1_INTERVAL seconds before
		TouchState_2, // BAGVIEW_TOUCH_STATE1_INTERVAL seconds after the
		TouchState_3, // backpack to scroll mode
		TouchState_4, // what nothing mode
		TouchState_5, // click selected operation mode props
		TouchState_6, // check props information model
	};
	/*
		 0
	   /   \
	   1   2
	  /     \
	 3       4
	*/

	CC_PROPERTY(int32, _TouchState, TouchState)	
	CC_PROPERTY(bool, _selectFrameShow, SelectFrameShow)
	ccTime m_fStepCounter;// timer

	CCPoint preTouchPoint;
    CCPoint currentTouchPoint;

//touch end
public:

	uint32 _capacity;
	uint32 _noEmpty;
	LayerNode* __container;

	BagUIPartialScrollView *scrollView;
	cocos2d::CCSize m_viewSize;
	BagGoods* m_pCurSelectedBagGoods;
	GameDispatcher* dispatcher;
	//int32 LayerManager::tipsLayer->getLastItemGID();

private:
	uint32 tmp_num;
	uint32 tmp_money;
	int32 tmp_sitNum;
	Number lastZhengliTime;
};

#endif