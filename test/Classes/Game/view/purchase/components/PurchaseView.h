#ifndef _PURCHASE_VIEW_H_
#define _PURCHASE_VIEW_H_

#include "cocos2d.h"
#include "PopContainer.h"
#include "BaseType.h"
#include "UIListView/CCUIListViewAdapter.h"
#include "UIListView/CCUIListView.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "IAPManagerCallback.h"

class PurchaseView : public PopContainer, CCUIListViewAdapter, IAPManagerCallback
#else
class PurchaseView : public PopContainer, CCUIListViewAdapter
#endif
{
public:
	static PurchaseView* initView();

	~PurchaseView(){}

	virtual bool init();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	//virtual void registerWithTouchDispatcher(void);

	virtual int getCount();
	virtual LayerNode * getView( int position );

	void closeButtonClick(CCObject* pSender);
	void onBuyButtonClick(CCObject* pSender);

	LayerNode *createListItem(int position);
	CCLayer *createListItemCell(const char* nameStr, const char* goldStr, const char* iconStr, const char* buyStr, int tag);

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    // iap about
    virtual void onBuyProductSuccess(const char *pProductIdentify);
    virtual void onBuyProductFailed(const char *pProductIdentify);
#endif
private:
    bool _isPaymentReturn;
	PurchaseView();
	CCUIListView *_pListView;
};
#endif
