#include "FirstPurchaseView.h"
#include "manager/PopEventName.h"
#include "utils/ScaleUtil.h"
#include "CCMenuItem.h"
#include "CCMenu.h"
#include "manager/TouchLayerEnum.h"
#include "CCUIBackground.h"
#include "LoginManage.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "jni/slcq/JniManager.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import "Connect91Handler.h"
#endif
const int TAG_PARENT = 1001;
const int TAG_BUTTON_GO_TO_PURCHASE = 1002;
const int TAG_BUTTON_CLOSE = 1003;

FirstPurchaseView::FirstPurchaseView()
{
	this->key = PopEventName::FIRST_PURCHASE;
	this->setNeedBg(0);
}

bool FirstPurchaseView::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    //this->setIsTouchEnabled(true);

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    this->setPosition(CCPointZero);
    this->setContentSize(winSize);
    this->setPopContentSize(this->getContentSize());

    CCLayer *pParentLayer = new CCLayer();
    if(!pParentLayer || !pParentLayer->init())
    {
        return false;
    }
    CCPoint innerLayerPosition = POS(ccp(0, 70), ScaleUtil::CENTER_TOP);
    pParentLayer->setAnchorPoint(CCPointZero);
    //pInnerLayer->initWithColor(ccc4(255, 128, 128, 100));
    pParentLayer->setPosition(innerLayerPosition);
    pParentLayer->setIsRelativeAnchorPoint(true);
    pParentLayer->setContentSize(winSize);
    this->addChild(pParentLayer, 0, TAG_PARENT);
    pParentLayer->release();


    CCUIBackground *pBackground1 = new CCUIBackground();
    pBackground1->initWithSpriteFrame("ui.png", ccp((winSize.width - POSX(610)) / 2 + POSX(10), 0), ccp(POSX(6), POSX(7)), CCSizeMake(POSX(640), POSX(/*350*/510)));
    pParentLayer->addChild(pBackground1);
    pBackground1->release();

    CCUIBackground *pBackground2 = new CCUIBackground();
    pBackground2->initWithSpriteFrame("ui2.png", ccp((winSize.width - POSX(590)) / 2 + POSX(10), POSX(10)), CCPointZero, CCSizeMake(POSX(620), POSX(/*270*/490)));
    pParentLayer->addChild(pBackground2);
    pBackground2->release();

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/purchase/res_purchase_first.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/purchase/res_purchase_act.plist");

    CCSprite *pFirstPurchaseImage = CCSprite::spriteWithSpriteFrameName("res_purchase_first.png");
    if(pFirstPurchaseImage)
    {
        pFirstPurchaseImage->setAnchorPoint(CCPointZero);
        pFirstPurchaseImage->setPosition(ccp(POSX(20), POSX(0)));
        pParentLayer->addChild(pFirstPurchaseImage);
    }
	

	CCSprite *pPurNormalSprite = CCSprite::spriteWithSpriteFrameName("purchase/btn_purchase_normal.png");
	CCSprite *pPurPressedSprite = CCSprite::spriteWithSpriteFrameName("purchase/btn_purchase_pressed.png");
	if(pPurNormalSprite && pPurPressedSprite)
	{
		CCMenuItemSprite *pPurchaseMenuImage = CCMenuItemSprite::itemFromNormalSprite(
			pPurNormalSprite,
			pPurPressedSprite,
			this,
			menu_selector(FirstPurchaseView::onBuyButtonClick));

		pPurchaseMenuImage->setPosition(ccpAdd(pBackground1->getPosition(), ccp(POSX(390), POSX(80))));
		pPurchaseMenuImage->setTag(TAG_BUTTON_GO_TO_PURCHASE);
		CCMenu *pPurchaseMenu = CCMenu::menuWithItem(pPurchaseMenuImage);
		if(pPurchaseMenu)
		{
			pPurchaseMenu->setTouchLayer(TLE::WindowLayer_PurchaseView);
			pPurchaseMenu->setPosition(CCPointZero);
			pParentLayer->addChild(pPurchaseMenu);
		}
	}


	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_normal.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_pressed.png");
	CCMenuItemSprite *pColseMenuImage = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite,
		pPressedSprite,
        this,
        menu_selector(FirstPurchaseView::onBuyButtonClick));
    pColseMenuImage->setPosition(ccpAdd(pBackground1->getPosition(), ccp(POSX(640), POSX(/*350*/510))));
    pColseMenuImage->setTag(TAG_BUTTON_CLOSE);
    CCMenu *pCloseMenu = CCMenu::menuWithItem(pColseMenuImage);
    if(pCloseMenu)
    {
        pCloseMenu->setTouchLayer(TLE::WindowLayer_PurchaseView);
        pCloseMenu->setPosition(CCPointZero);
        pParentLayer->addChild(pCloseMenu);
    }

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/purchase/res_purchase_first.plist");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/purchase/res_purchase_first.pvr.ccz");

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/purchase/res_purchase_act.plist");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/purchase/res_purchase_act.pvr.ccz");
}

void FirstPurchaseView::onBuyButtonClick( CCObject* pSender )
{
	CCMenu *pMenu = (CCMenu *) pSender;
	if(!pMenu)
	{
		return;
	}

	switch(pMenu->getTag())
	{
	case TAG_BUTTON_CLOSE:
		{
			this->setisPop(false);
		}
		break;
		
	case TAG_BUTTON_GO_TO_PURCHASE:
		{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		    callExcharge("1000", g_pLoginManage->getExchargeServerId().c_str());
#endif
            

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
         [[Connect91Handler sharedTo91] buyGold:1000];   
#endif
		}
		break;
	}
}
