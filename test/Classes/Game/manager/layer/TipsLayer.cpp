#include "TipsLayer.h"
#include "view/backpack/components/BagView.h"
#include "view/backpack/components/BagCreate.h"
#include "view/bank/components/BankView.h"

#include "view/shop/components/ShopView.h"

#include "manager/OverPanelManage.h"
#include "manager/PopEventName.h"
#include "utils/TipsEquipCanvas.h"
#include "TextInputConfirm.h"
#include "TextFieldTTF.h"
#include "view/friend/components/FItemCheck.h"
#include "manager/TouchLayerEnum.h"
#include "view/arena/components/GiftPanel.h"
#include "view/arena/components/HeroRankView.h"
#include "Confirm.h"
#include "view/chat/components/ChannelBtnClickLayer.h"
#include "utils/ScaleUtil.h"
#include "view/zx/components/ZXDuiView.h"
//#include "NewEAlert.h"

USING_NS_CC;



TipsLayer::TipsLayer()
{
	//使可被触控
	this->setIsTouchEnabled(true);

	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::TipsLayer, true);
	setLastItemGID(NONEINT);
}

TipsLayer::~TipsLayer()
{}

//CC_PROPERTY(int32, _lastItemGID, LastItemGID)
int32 TipsLayer::getLastItemGID()
{
	return _lastItemGID;
}

void TipsLayer::setLastItemGID(int32 var)
{
	_lastItemGID = var;
}

//begin

void TipsLayer::registerWithTouchDispatcher()
{
	this->setIsTouchEnabled (true);
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::TipsLayer, true);
}

bool TipsLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	//CCLog("TLE::TipsLayer");
	//
	//setTouchState(TouchState_0);
	//
	bool rnt = false;

	CCPoint locationInView = touch->locationInView(touch->view());
    preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	TipsEquipCanvas* p_tec = (TipsEquipCanvas*)this->getChildByTag(TipsLayerTAG_itemInfoShow);
	if (p_tec)
	{
		CCRect contentLayerRect = CCRectZero;
		contentLayerRect.origin = p_tec->getPosition();
		contentLayerRect.size = p_tec->getContentSize();

		if (CCRect::CCRectContainsPoint(contentLayerRect, preTouchPoint))
		{
			rnt = true;
		}
		else
		{//删除道具TIPS显示
			this->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
		}
	}

	{
		CCObject* pConfirm = (CCObject*)this->getChildByTag(TipsLayerTAG_confirmFrame);
		if (pConfirm)
		{
			rnt = true;
		}
	}

	//TipsLayerTAG_cdmanage
	{
		CCObject* pConfirm = (CCObject*)this->getChildByTag(TipsLayerTAG_cdmanage);
		if (pConfirm)
		{
			rnt = true;
		}
	}
	
	TextInputConfirm* pTic = (TextInputConfirm*)this->getChildByTag(TipsLayerTAG_textInputConfirm);
	if (pTic)
	{
		TextFieldTTF* tf = (TextFieldTTF*)pTic->m_alert->getChildByTag(Alert::AlertTAG_CCTextFieldTTF);
		if (tf)
		{
			tf->ccTouchBegan(touch, event);
			rnt =  true;
			/*
			CCRect contentLayerRect = CCRectZero;
			contentLayerRect.origin = ccp(pTic->getPosition().x-pTic->getContentSize().width/2, 
				pTic->getPosition().y-pTic->getContentSize().height/2);
			contentLayerRect.size = pTic->getContentSize();
			if (CCRect::CCRectContainsPoint(contentLayerRect, preTouchPoint))
			{
			}
			else
			{
				//删除道具TIPS显示
				this->removeChildByTag(TipsLayerTAG_textInputConfirm, true);
				rnt =  true;
			}
		//	tf->ccTouchBegan(touch, event);
		*/
		}
	}
	
	FItemCheck* pFC = (FItemCheck*)this->getChildByTag(TipsLayerTAG_friendCheck);
	if (pFC)
	{
		
		rnt =  true;
	}
	//
	CCNode* pCF = (CCNode*)this->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pCF)
	{
		rnt =  true;
	}
	//TipsLayerTAG_egg_washPanel
	CCNode* p_egg_washPanel = (CCNode*)this->getChildByTag(TipsLayer::TipsLayerTAG_egg_washPanel);
	if (p_egg_washPanel)
	{
		rnt =  true;
	}
	//TipsLayerTAG_egg_NumSelectBox
	CCNode* p_egg_NumSelectBox = (CCNode*)this->getChildByTag(TipsLayer::TipsLayerTAG_egg_NumSelectBox);
	if (p_egg_NumSelectBox)
	{
		rnt =  true;
	}
	//
	GiftPanel* pGP = (GiftPanel*)this->getChildByTag(TipsLayer::TipsLayerTAG_rankReward);
	if (pGP && pGP->getIsVisible() == true)
	{
		CCRect contentLayerRect = CCRectZero;
		contentLayerRect.origin = pGP->getPosition();
		contentLayerRect.size = pGP->getContentSize();

		if (CCRect::CCRectContainsPoint(contentLayerRect, preTouchPoint))
		{
			rnt =  true;
		}
		else
		{//删除竞技场挑战奖励显示
			//this->removeChildByTag(TipsLayer::TipsLayerTAG_rankReward, true);
			pGP->setIsVisible(false);
			rnt =  true;
		}
	}
	//
	HeroRankView* pHRV = (HeroRankView*)this->getChildByTag(TipsLayer::TipsLayerTAG_heroUi);
	if (pHRV)
	{
		CCRect contentLayerRect = CCRectZero;
		contentLayerRect.origin = pHRV->getPosition();
		contentLayerRect.size = pHRV->getContentSize();

		if (CCRect::CCRectContainsPoint(contentLayerRect, preTouchPoint))
		{
			rnt =  true;
		}
		else
		{//删除竞技场挑战奖励显示
			this->removeChildByTag(TipsLayer::TipsLayerTAG_heroUi, true);
			rnt =  true;
		}
	}
	//
	LayerNode* pNEA = (LayerNode*)this->getChildByTag(TipsLayer::TipsLayerTAG_NewEAlert);
	if (pNEA)
	{
		rnt =  true;
		/*
		CCRect contentLayerRect = CCRectZero;
		contentLayerRect.origin = pNEA->getPosition();
		contentLayerRect.size = pNEA->getContentSize();

		if (CCRect::CCRectContainsPoint(contentLayerRect, preTouchPoint))
		{
			rnt =  true;
		}
		else
		{//删除装备新物品对话框、使用礼包显示
			this->removeChildByTag(TipsLayer::TipsLayerTAG_NewEAlert, true);
			rnt =  true;
		}
		*/
	}
	//
	ChannelBtnClickLayer* pCBCL = (ChannelBtnClickLayer*)this->getChildByTag(TipsLayer::TipsLayerTAG_popChannels);
	if (pCBCL)
	{
		CCRect contentLayerRect = CCRectZero;
		contentLayerRect.origin = ccp(POSX(96-123/2), POSX(40+56-55/2));
		contentLayerRect.size = CCSizeMake(123*2, 56*2);

		if (CCRect::CCRectContainsPoint(contentLayerRect, preTouchPoint))
		{
			rnt =  true;
		}
		else
		{//删除聊天选择频道界面
			this->removeChildByTag(TipsLayer::TipsLayerTAG_popChannels, true);
			rnt =  true;
		}
	}
	//
	ZXDuiView* pZXDuiView = (ZXDuiView*)this->getChildByTag(TipsLayer::TipsLayerTAG_ZXDuiView);
	if (pZXDuiView)
	{
		rnt =  true;
	}

	return rnt;
}

void TipsLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{	
	//setSelectFrameShow(false);
	////
	//CCPoint locationInView = touch->locationInView(touch->view());
 //   currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	//g_pShopCreate->ccTouchMoved(touch, event);

	//preTouchPoint = currentTouchPoint;
}

void TipsLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	TextInputConfirm* pTic = (TextInputConfirm*)this->getChildByTag(TipsLayerTAG_textInputConfirm);
	if (pTic)
	{
		TextFieldTTF* tf = (TextFieldTTF*)pTic->m_alert->getChildByTag(Alert::AlertTAG_CCTextFieldTTF);
		if (tf)
		{
			tf->ccTouchEnded(touch, event);
		}
		//return true;
	}
	//
	//if (LayerManager::tipsLayer->getLastItemGID() == -1)
	//{
	//	LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
	//}
	//else if (!g_pShopCreate->getIsTouchingMoving())//getSelectFrameShow()
	//{//显示道具信息框
	//	ShopGoods* shopGoods = getCurSelectedShopGoods(preTouchPoint);//touchbegan里面设置的preTouchPoint
	//	if (!shopGoods)
	//		return;

	//	shopGoods->myTip->rollOverHander();	
	//	//bagGoods->myTip->rollOverHander();				
	//}

	//CCPoint locationInView = touch->locationInView(touch->view());
 //   currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	//g_pShopCreate->ccTouchEnded(touch, event);
} 
