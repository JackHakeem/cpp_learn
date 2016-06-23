#ifndef _PURCHASE_MEDIATOR_H_
#define _PURCHASE_MEDIATOR_H_

#include "mvc/Mediator.h"
#include "components/PurchaseView.h"
#include "components/FirstPurchaseView.h"

class PurchaseMediator : public Mediator
{
public:
	PurchaseMediator();
	~PurchaseMediator(){}

	void openPurchaseView();
	void openPurchaseViewHandler();
	void createPurchaseView();
	void showFirstPurchaseView(CCNode *pNode, void *pData);
	void showPurchaseView(CCNode *pNode, void *pData);

private:
	void closePurchaseView(CCNode* pNode, void* pData);
	void closeFirstPurchaseView(CCNode* pNode, void* pData);

	PurchaseView *_pPurchaseView;
	FirstPurchaseView *_pFirstPurchaseView;
};
#endif