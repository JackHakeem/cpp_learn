#include "WindowLayer.h"
#include "view/backpack/components/BagView.h"
#include "view/backpack/components/BagCreate.h"
#include "view/bank/components/BankView.h"

#include "view/shop/components/ShopView.h"

#include "manager/OverPanelManage.h"
#include "manager/PopEventName.h"
#include "view/figure/components/FigureMainView.h"
#include "manager/TouchLayerEnum.h"
#include "manager/PopManage.h"
#include "manager/GlobalManage.h"
#include "Confirm.h"

USING_NS_CC;

bool WindowLayer::init()
{
	if (!LayerNode::init())
	{
		return false;
	}

	this->setIsTouchEnabled (true);
	return true;
}

int WindowLayer::getCurNodeTag(CCPoint tarPoint)
{
	int rnttag = OVER_0_NONE;
	//
	BagView* bagView = (BagView*)this->getChildByTag(PopEventName::BAG);
	if (bagView && bagView->getisPop())
	{
		if (bagView->containsTouchLocation(tarPoint))
		{
			rnttag = OVER_7_BAG_ITEM;
			return rnttag;
		}
	}
	//
	BankView* bankView = (BankView*)this->getChildByTag(PopEventName::BANK);
	if (bankView && bankView->getisPop())
	{
		if (bankView->containsTouchLocation(tarPoint))
		{
			rnttag = OVER_8_BANK_ITEM;
			return rnttag;
		}
	}
	//
	ShopView* shopView = (ShopView*)this->getChildByTag(PopEventName::SHOP);
	if (shopView && shopView->getisPop())
	{
		if (shopView->containsTouchLocation(tarPoint))
		{
			rnttag = OVER_10_SHOP;
			return rnttag;
		}
	}
	//
	FigureMainView * figuerView = (FigureMainView*)this->getChildByTag(PopEventName::FIGURE);
	if (figuerView && figuerView->getisPop())
	{
		CCRect contentLayerRect = CCRectZero;
		contentLayerRect.origin = ccp(POSX(34), POSX(220));//figuerView->getPosition();
		contentLayerRect.size = CCSizeMake(POSX(454), POSX(300));////figuerView->m_viewSize;

		if (CCRect::CCRectContainsPoint(contentLayerRect, tarPoint))
		{
			rnttag = OVER_1_FIGURE;
			return rnttag;
		}
	}
	return rnttag;
}

void WindowLayer::registerWithTouchDispatcher()
{
	this->setIsTouchEnabled (true);
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer, true);
}

bool WindowLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	//CCLog("TLE::WindowLayer");

	if (g_pPopManage->getCurPopNum() > 0)
	{
		return true;
	}
	
	return false;
}

void WindowLayer::arenaWaitTime()
{//每次挑战后延迟5秒才可以继续挑战
	g_pGlobalManage->canOperate = true;
}

void WindowLayer::clickCancel(CCObject * pSender)
{
	Confirm * _confirmBuy = (Confirm *)this->getChildByTag(
		WindowLayer::WindowLayerTAG_confirmFrame);
	if (_confirmBuy&&_confirmBuy->getParent())
	{
		_confirmBuy->getParent()->removeChildByTag(WindowLayer::WindowLayerTAG_confirmFrame,true);
	}  
}