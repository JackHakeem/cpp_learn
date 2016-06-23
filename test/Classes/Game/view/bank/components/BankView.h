#ifndef _BANKVIEW_H_
#define _BANKVIEW_H_

#include "PopContainer.h"
#include "LayerNode.h"
#include "FocusNode.h"


class BankUIPartialScrollView;
class GoodsInfo;
class BankCreate;
class BankGoods;

#define BANKVIEW_TOUCH_STATE1_INTERVAL (0.3f)
#define BANKVIEW_TOUCH_DIAOTAX (2)

USING_NS_CC;
class BankView:public PopContainer
{
public:
	enum
	{
		RENDERZ_bankContainer = 0,
		RENDERZ_g_pBankCreate,
		RENDERZ_goldline,
		RENDERZ_buttonMenu,
		RENDERZ_select,
		RENDERZ_title,
	};
	
	enum
	{
		RENDERTAG_select = 0,
	};

	enum
	{
		BANK_ADD_GRID_CLICK,
	};

	BankView();
	virtual ~BankView();
	bool init();
	virtual void reinit();
	void OpenBank(std::map<int32, GoodsInfo*>& goodDic, int32 noEmpty, uint32 goodsNum);

	virtual int32 getSelfTag();

	BankGoods* getCurSelectedBankGoods(CCPoint p);
	void updateGoods(char* arr, int32 noEmpty);
	void handleBuyCellConfirm(CCObject* pSender);
	void handleBuyCellCancel(CCObject* pSender);
	void addGrid(int32 num, int32 money);

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

	void onClickHandler(BankGoods* bankGoods);
	void step(ccTime dt);//touch times 

	enum TouchStateEnum
	{
		TouchState_0 = 0, // no state, is not inspire the touch module
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
	ccTime m_fStepCounter;//timer

	CCPoint preTouchPoint;
    CCPoint currentTouchPoint;

//touch end
public:

	uint32 _capacity;
	uint32 _noEmpty;
	LayerNode* __container;

	BankUIPartialScrollView *scrollView;
	cocos2d::CCSize m_viewSize;
	BankGoods* m_pCurSelectedBankGoods;
	//int32 LayerManager::tipsLayer->getLastItemGID();
private:
	uint32 tmp_num;
	uint32 tmp_money;
	int32 tmp_sitNum;
};

#endif