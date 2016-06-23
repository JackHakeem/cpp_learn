#include "PurchaseMediator.h"
#include "manager/ViewManager.h"
#include "manager/PopEventName.h"


void PurchaseMediator::openPurchaseView()
{
	if(!_pPurchaseView)
	{
		this->createPurchaseView();
	}
	this->openPurchaseViewHandler();
}

void PurchaseMediator::createPurchaseView()
{
	_pPurchaseView = PurchaseView::initView();
	ViewManager::getInstance()->purchaseView = _pPurchaseView;
	if (_pPurchaseView)
		_pPurchaseView->addEventListener(PopContainer::CLOSE_CONTAINER, this, callfuncND_selector(PurchaseMediator::closePurchaseView));
}

void PurchaseMediator::openPurchaseViewHandler()
{
	if(!_pPurchaseView) 
	{
		return;
	}
	if(_pPurchaseView->getisPop())
	{
		_pPurchaseView->setisPop(false);
	}
	else
	{
		_pPurchaseView->setisPop(true);
	}
}

PurchaseMediator::PurchaseMediator()
{
	_pPurchaseView = 0;
	_pFirstPurchaseView = 0;
	GameDispatcher::getInstance()->addEventListener(PopEventName::SHOW_UI_FIRST_PURCHASE,
		this,
		callfuncND_selector(PurchaseMediator::showFirstPurchaseView));
	GameDispatcher::getInstance()->addEventListener(PopEventName::SHOW_UI_PURCHASE,
		this,
		callfuncND_selector(PurchaseMediator::showPurchaseView));
}

void PurchaseMediator::showFirstPurchaseView( CCNode *pNode, void *pData )
{
	if(!_pFirstPurchaseView)
	{
		_pFirstPurchaseView = new FirstPurchaseView();
		_pFirstPurchaseView->init();
		_pFirstPurchaseView->addEventListener(PopContainer::CLOSE_CONTAINER, this, callfuncND_selector(PurchaseMediator::closeFirstPurchaseView));
	}
	_pFirstPurchaseView->setisPop(true);
}

void PurchaseMediator::showPurchaseView( CCNode *pNode, void *pData )
{
	openPurchaseView();
}

//Kenfly 20130123
void PurchaseMediator::closePurchaseView(CCNode* pNode, void* pData)
{
	if (_pPurchaseView)
	{
		_pPurchaseView->removeEventListener(PopContainer::CLOSE_CONTAINER, this, callfuncND_selector(PurchaseMediator::closePurchaseView));
		if (_pPurchaseView->getisPop())
			_pPurchaseView->setisPop(false);
		assert(_pPurchaseView->retainCount() == 1);
		ViewManager::getInstance()->purchaseView = NULL;
		CC_SAFE_RELEASE_NULL(_pPurchaseView);
	}
}

void PurchaseMediator::closeFirstPurchaseView(CCNode* pNode, void* pData)
{
	if (_pFirstPurchaseView)
	{
		_pFirstPurchaseView->removeEventListener(PopContainer::CLOSE_CONTAINER, this, callfuncND_selector(PurchaseMediator::closeFirstPurchaseView));
		if (_pFirstPurchaseView->getisPop())
			_pFirstPurchaseView->setisPop(false);
		assert(_pFirstPurchaseView->retainCount() == 1);
		CC_SAFE_RELEASE_NULL(_pFirstPurchaseView);
	}
}
