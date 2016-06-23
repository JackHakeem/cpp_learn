#include "VipView.h"
#include "manager/PopEventName.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"
#include "model/player/RoleManage.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ValuesUtil.h"
#include "../VipMediator.h"
#include "manager/LangManager.h"
#include "model/vip/VipManager.h"
#include "VipGiftView.h"
#include "model/vip/vo/VipGiftVo.h"
#include "LoginManage.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import "Connect91Handler.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "jni/slcq/JniManager.h"
#endif
#include "control/AppFacade.h"
const int TAG_LAYER_PARENT = 1001;
const int TAG_LAYER_INFO = 1002;
const int TAG_LABEL_PERCENT = 1011;
const int TAG_PROGRESS_BAR = 1012;
const int TAG_BUTTON_PURCHASE = 1013;
const int TAG_BUTTON_WELFARE = 1014;
const int TAG_LABEL_GOLD_TOTAL = 1015;
const int TAG_LABEL_VIP_NEXT = 1016;
const int TAG_LABEL_VIP_GIFT = 1017;
const int TAG_BUTTON_PRE_PAGE = 1018;
const int TAG_BUTTON_NEXT_PAGE = 1019;

const int TAG_ICON_VIP_GOODS = 1100;

VipView::VipView()
{
	key = PopEventName::VIP;

	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/streng/res_streng.plist");

	_pScrollView = 0;
	this->init();
	this->setContentSize(CCDirector::sharedDirector()->getWinSize());
	this->setPopContentSize(this->getContentSize());

	initPlayerInfo();

	initView();
}

VipView::~VipView()
{
	if(_pScrollView)
	{
		//_pScrollView->removeAllLayer();
		//_pScrollView->removeAllChildrenWithCleanup(true);
		_pScrollView = 0;
	}


	VipMediator * pM = (VipMediator *)g_pFacade->retrieveMediator(AppFacade_VIP_MEDIATOR);
	if (pM)
	{
		pM->_pVipView = 0;
	}

	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/streng/res_streng.plist");

	//CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/streng/res_streng.pvr.ccz");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/icon/res_icon.plist");
	//CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/icon/res_icon.pvr.ccz");
}

void VipView::removeDataObjectChild()
{
	VipMediator * pMediator = (VipMediator *)g_pFacade->retrieveMediator(AppFacade_VIP_MEDIATOR);
	if (pMediator)
	{
		pMediator->_pVipView = 0;
	}
	
}

void VipView::openVipView()
{
	if(!_pScrollView)
	{
		_pScrollView = VipScrollView::scrollViewWithRect(CCRectMake(POSX(28),
			POSX(102),
			POSX(902), 
			POSX(250)));
		
		_pScrollView->setScrollListener(this);

		CCLayerColor *pParentLayer = CCLayerColor::layerWithColorWidthHeight(ccc4(255, 128, 128, 0), 
			CCDirector::sharedDirector()->getWinSize().width,
			POSX(354));
		pParentLayer->setAnchorPoint(CCPointZero);
		pParentLayer->setPosition(POS(ccp(0, 36), ScaleUtil::CENTER_TOP));
		
		// Add infomation.
		// Doyang 20120712
		CCLayer *pBackLayer = buildInfomationView();
		pParentLayer->addChild(pBackLayer, 0, TAG_LAYER_INFO);
		pBackLayer->release();

		// Add scrollview.
		pParentLayer->addChild(_pScrollView);
		_pScrollView->release();
		_pScrollView->initData();

		// Add pre next button
		CCSprite* pNormal = CCSprite::spriteWithSpriteFrameName("streng/direct.png");
		CCSprite* pPress = CCSprite::spriteWithSpriteFrameName("streng/direct_pressed.png");
		CCMenuItemSprite *pPreItem = cocos2d::CCMenuItemImage::itemFromNormalSprite(
			pNormal,
			pPress,
			this,
			menu_selector(VipView::onPrePageItemClickListener) );
		pPreItem->setPosition( ccp(POSX(20), POSX(160)) );
		pPreItem->setAnchorPoint(CCPointZero);
		CCMenu* pPreMenu = CCMenu::menuWithItems(pPreItem, 0);
		pPreMenu->setTouchLayer( -2000 );
		pPreMenu->setPosition( CCPointZero );
		pParentLayer->addChild( pPreMenu, 0, TAG_BUTTON_PRE_PAGE );

		pNormal = CCSprite::spriteWithSpriteFrameName("streng/direct.png");
		pPress = CCSprite::spriteWithSpriteFrameName("streng/direct_pressed.png");
		CCMenuItemSprite *pNextItem = cocos2d::CCMenuItemImage::itemFromNormalSprite(
			pNormal,
			pPress,
			this,
			menu_selector(VipView::onNextPageItemClickListener) );
		pNextItem->setPosition( ccp(POSX(875), POSX(160)) );
		CCSprite* pS = (CCSprite*)pNextItem->getNormalImage();
		pS->setFlipX( true );
		pS = (CCSprite*)pNextItem->getSelectedImage();
		pS->setFlipX( true );
		pNextItem->setAnchorPoint(CCPointZero);
		CCMenu* pNextMenu = CCMenu::menuWithItems(pNextItem, 0);
		pNextMenu->setTouchLayer( -2000 );
		pNextMenu->setPosition( CCPointZero );
		pParentLayer->addChild( pNextMenu, 0, TAG_BUTTON_NEXT_PAGE );

		// Add vip gift
		CCLabelTTF *pGiftLabel = CCLabelTTF::labelWithString("", CCSizeMake(POSX(280), POSX(24)),
			CCTextAlignmentCenter, "Arial", POSX(24));
		if(pGiftLabel)
		{
			pGiftLabel->setPosition(ccp(POSX(44 + 125), POSX(34 + 12)));
			pParentLayer->addChild(pGiftLabel, 0, TAG_LABEL_VIP_GIFT);
		}

		// Add icon
		CCSprite *pIconSprite = CCSprite::spriteWithSpriteFrameName("vip/logo_vip.png");
		if(pIconSprite)
		{
			pIconSprite->setPosition(ccp(POSX(480),
				POSX(536)));
			pParentLayer->addChild(pIconSprite);
		}
		this->addChild(pParentLayer, 0, TAG_LAYER_PARENT);
		//pParentLayer->release(); //LH20130110

	}
	this->setisPop(true);

	release(); //LH20130110

	this->resetVipLev();
}

bool VipView::init()
{
	return true;
}

CCLayer * VipView::buildInfomationView()
{
	ValuesUtil *pValuesUtil = ValuesUtil::Instance();

	CCUIBackground* pBgLayer = new CCUIBackground();
	pBgLayer->initWithSpriteFrame("popuibg/bg2.png", 
		ccp(POSX(36), POSX(358)), 
		ccp(0,0), 
		CCSizeMake(POSX(890), POSX(150)));

	CCSprite *pIconSprite = CCSprite::spriteWithSpriteFrameName("vip/icon_vip.png");
	if(pIconSprite)
	{
		pIconSprite->setAnchorPoint(CCPointZero);
		pIconSprite->setPosition(ccp(POSX(0), POSX(0)));
		pBgLayer->addChild(pIconSprite);
	}

	CCSprite *pProgressBg = CCSprite::spriteWithSpriteFrameName("figure/exp_bg.png");
	if(pProgressBg)
	{
		pProgressBg->setPosition(ccp(POSX(420), POSX(75)));
		pBgLayer->addChild(pProgressBg);
	}

	CCProgressTimer *pProgressBar = new CCProgressTimer();
	if (pProgressBar)
	{	
		if (pProgressBar->initWithFile("assets/ui/figure/exp.png"))
		{
			pProgressBar->setPosition(ccp(POSX(420), POSX(75)));
			pProgressBar->getSprite()->setColor(ccc3(0, 255, 0));
			pProgressBar->setPercentage(0);
			pProgressBar->setType(CCProgressTimerType(2));
			/*CCProgressTo * pProgressTo = CCProgressTo::actionWithDuration(0.2f, 1.0f); 
			pProgressBar->runAction(pProgressTo);*/
			pBgLayer->addChild(pProgressBar, 0, TAG_PROGRESS_BAR);
			pProgressBar->release();
		}
	}

	CCLabelTTF *pPercentLabel = CCLabelTTF::labelWithString(
		"",
		CCSizeMake(POSX(400), POSX(20)),
		CCTextAlignmentCenter,
		"Arial",
		POSX(20));
	pPercentLabel->setPosition(ccp(POSX(420), POSX(75)));
	pBgLayer->addChild(pPercentLabel, 0, TAG_LABEL_PERCENT);
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		if(pNormalSprite && pPressedSprite)
		{
			CCMenuItemSprite *pPurchaseMenuItem = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this,
				menu_selector(VipView::onPurchaseItemClickListener));
			pPurchaseMenuItem->setAnchorPoint(CCPointZero);
			pPurchaseMenuItem->setPosition(ccp(POSX(730), POSX(50)));
			pPurchaseMenuItem->setTag(TAG_BUTTON_PURCHASE);
			CCMenu *pPurchaseMenu = CCMenu::menuWithItem(pPurchaseMenuItem);
			pPurchaseMenu->setTouchLayer(TLE::WindowLayer_VipView);
			pPurchaseMenu->setPosition(CCPointZero);
			pBgLayer->addChild(pPurchaseMenu);

			CCLabelTTF *pPurchaseLabel = CCLabelTTF::labelWithString(
				pValuesUtil->getString("VIP094").c_str(),
				CCSizeMake(POSX(400), POSX(20)),
				CCTextAlignmentCenter,
				"Arial",
				POSX(20));
			pPurchaseLabel->setPosition(ccpAdd(pPurchaseMenuItem->getPosition(),
				ccp(pPurchaseMenuItem->getContentSize().width / 2, pPurchaseMenuItem->getContentSize().height / 2)));
			pBgLayer->addChild(pPurchaseLabel);
		}
	}
	

	//Begin Kenfly 20121025 : modify ȥ����
	/*
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			CCMenuItemSprite *pWelfareMenuItem = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this,
				menu_selector(VipView::onPurchaseItemClickListener));
			pWelfareMenuItem->setAnchorPoint(CCPointZero);
			pWelfareMenuItem->setPosition(ccp(POSX(730), POSX(15)));
			pWelfareMenuItem->setTag(TAG_BUTTON_WELFARE);
			CCMenu *pWelfareMenu = CCMenu::menuWithItem(pWelfareMenuItem);
			pWelfareMenu->setTouchLayer(TLE::WindowLayer_VipView);
			pWelfareMenu->setPosition(CCPointZero);
			pBgLayer->addChild(pWelfareMenu, 0, TAG_BUTTON_WELFARE);

			CCLabelTTF *pWelfareLabel = CCLabelTTF::labelWithString(
				pValuesUtil->getString("VIP095").c_str(),
				CCSizeMake(POSX(400), POSX(20)),
				CCTextAlignmentCenter,
				"Arial",
				POSX(20));
			pWelfareLabel->setPosition(ccpAdd(pWelfareMenuItem->getPosition(),
				ccp(pWelfareMenuItem->getContentSize().width / 2, pWelfareMenuItem->getContentSize().height / 2)));
			pBgLayer->addChild(pWelfareLabel);
		}
	}
	*/
	//End Kenfly 20121025
	
	//current gold and next gold require
	CCLabelTTF *pTotalGoldPreLabel = CCLabelTTF::labelWithString(
		pValuesUtil->getString("VIP096").c_str(),
		CCSizeMake(POSX(300), POSX(24)),
		CCTextAlignmentLeft,
		"Arial",
		POSX(24));
	pTotalGoldPreLabel->setAnchorPoint(CCPointZero);
	pTotalGoldPreLabel->setPosition(ccp(POSX(230), POSX(95)));
	pBgLayer->addChild(pTotalGoldPreLabel);

	CCLabelTTF *pTotalGoldLabel = CCLabelTTF::labelWithString(
		"0",
		CCSizeMake(POSX(200), POSX(24)),
		CCTextAlignmentLeft,
		"Arial",
		POSX(24));
	pTotalGoldLabel->setAnchorPoint(CCPointZero);
	pTotalGoldLabel->setPosition(ccp(POSX(450), POSX(95)));
	pTotalGoldLabel->setColor(ccc3(5, 225, 13));
	pBgLayer->addChild(pTotalGoldLabel, 0, TAG_LABEL_GOLD_TOTAL);

	CCLabelTTF *pNextVipLabel = CCLabelTTF::labelWithString(
		"",
		CCSizeMake(POSX(500), POSX(24)),
		CCTextAlignmentLeft,
		"Arial",
		POSX(24));
	pNextVipLabel->setAnchorPoint(CCPointZero);
	pNextVipLabel->setPosition(ccp(POSX(230), POSX(25)));
	pNextVipLabel->setColor(ccc3(255, 56, 56));
	pBgLayer->addChild(pNextVipLabel, 0, TAG_LABEL_VIP_NEXT);
	
	return pBgLayer;
}

void VipView::initPlayerInfo()
{

}

void VipView::initView()
{
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/res_icon.plist");
}

void VipView::resetVipLev()
{
	updatePlayerInfo();
	/*CCLabelTTF *pPercentLabel = (CCLabelTTF *) pNode->getChildByTag(TAG_LABEL_PERCENT);
	if(pPercentLabel)
	{
	pPercentLabel->setString(_pRate);
	}*/
}

void VipView::onPurchaseItemClickListener( CCObject *pSender )
{
	CCMenu *pMenu = (CCMenu *) pSender;
	if(!pMenu)
		return;

	switch(pMenu->getTag())
	{
	case TAG_BUTTON_PURCHASE:
		{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		/*	LangManager::msgShow("TMP001");
			return;*/
			callExcharge("1000", g_pLoginManage->getExchargeServerId().c_str());
#endif
            
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			[[Connect91Handler sharedTo91] buyGold:50];
#endif
		}
		break;

	case TAG_BUTTON_WELFARE:
		{
			dispatchEvent(VipMediator::GET_VIP_REWARD, NULL);
		}
		break;

	default:
		break;
	}
}

void VipView::updatePlayerInfo()
{
	CCNode *pNode = this->getChildByTag(TAG_LAYER_PARENT);
	if(!pNode)
	{
		return;
	}

	pNode = pNode->getChildByTag(TAG_LAYER_INFO);
	if(!pNode)
	{
		return;
	}

	AccountInfoVo *pAccountInfo = RoleManage::Instance()->accountInfo();
	if(!pAccountInfo)
		return;

	ValuesUtil *pValuesUtil = ValuesUtil::Instance();

	int gold = pAccountInfo->goldcount();
	int vipLv  = pAccountInfo->vipLev();
	int nextGold = 0;
	int disGold = 0;
	if (gold>=150000){
		nextGold = 0;
	}
	else if(gold>=100000){
		nextGold = 150000;
	}
	else if (gold>=50000){
		nextGold = 100000;
	}
	else if (gold>=20000){
		nextGold = 50000;
	}
	else if (gold>=10000){
		nextGold = 20000;
	}
	else if (gold>=5000){
		nextGold = 10000;
	}
	else if (gold>=2000){
		nextGold = 5000;
	}
	else if(gold>=1000){
		nextGold = 2000;
	}
	else if(gold>=500){
		nextGold = 1000;
	}
	else if(gold>=100){
		nextGold = 500;
	}
	else {
		nextGold = 100;
	}
	disGold = nextGold - gold;

	CCProgressTimer *pProgressBar = (CCProgressTimer *) pNode->getChildByTag(TAG_PROGRESS_BAR);
	if(pProgressBar)
	{

		if(vipLv >= 10)
		{
			pProgressBar->setPercentage(100);
		}
		else if(gold == 0)
		{
			pProgressBar->setPercentage(0);
		}
		else
		{
			pProgressBar->setPercentage(100 - (float) gold * 100 / (float) nextGold);
		}
	}

	CCLabelTTF *pPercentLabel = (CCLabelTTF *) pNode->getChildByTag(TAG_LABEL_PERCENT);
	if(pPercentLabel)
	{
		if(vipLv >= 10)
		{
			pPercentLabel->setString("150000/150000");
		}
		else
		{
			char pPercent[20];
			sprintf(pPercent, "%d/%d", gold, nextGold);
			pPercentLabel->setString(pPercent);
		}
	}

	CCLabelTTF *pGoldTotalLabel = (CCLabelTTF *) pNode->getChildByTag(TAG_LABEL_GOLD_TOTAL);
	if(pGoldTotalLabel)
	{
		char pGoldTotal[20];
		sprintf(pGoldTotal, pValuesUtil->getString("VIP097").c_str(), gold);
		pGoldTotalLabel->setString(pGoldTotal);
	}

	CCLabelTTF *pNextVipLabel = (CCLabelTTF *) pNode->getChildByTag(TAG_LABEL_VIP_NEXT);
	if(pNextVipLabel)
	{

		if(vipLv >= 10)
		{
			pNextVipLabel->setString(pValuesUtil->getString("VIP002").c_str());
		}
		else
		{
			char pGoldTotal[128];
			sprintf(pGoldTotal, pValuesUtil->getString("VIP001").c_str(), (nextGold - gold), (vipLv + 1));
			pNextVipLabel->setString(pGoldTotal);
		}
	}

	if(_pScrollView)
	{
		_pScrollView->scrollToPage(vipLv + 1);
	}
}

void VipView::onScrollListener( int pageId )
{
	updateVipGiftInfo(pageId);

	CCNode *pNode = this->getChildByTag(TAG_LAYER_PARENT);
	if(!pNode)
	{
		return;
	}
	CCMenu *pPreMenu = (CCMenu *) pNode->getChildByTag(TAG_BUTTON_PRE_PAGE);
	if(pPreMenu)
	{
		if(pageId > 1)
		{
			pPreMenu->setIsVisible(true);
		}
		else
		{
			pPreMenu->setIsVisible(false);
		}
	}
	CCMenu *pNextMenu = (CCMenu *) pNode->getChildByTag(TAG_BUTTON_NEXT_PAGE);
	if(pNextMenu)
	{
		if(pageId > 10)//mao 2013.1.23
		{
			pNextMenu->setIsVisible(false);
		}
		else
		{
			pNextMenu->setIsVisible(true);
		}
	}
}

void VipView::updateVipGiftInfo( int vipId )
{
	CCNode *pNode = this->getChildByTag(TAG_LAYER_PARENT);
	if(!pNode)
	{
		return;
	}

	// Remove all gift icons

	pNode->removeChildByTag(TAG_ICON_VIP_GOODS,     true);
	pNode->removeChildByTag(TAG_ICON_VIP_GOODS + 1, true);
	pNode->removeChildByTag(TAG_ICON_VIP_GOODS + 2, true);
	pNode->removeChildByTag(TAG_ICON_VIP_GOODS + 3, true);


	CCLabelTTF *pGiftLabel = (CCLabelTTF *) pNode->getChildByTag(TAG_LABEL_VIP_GIFT);
	if(pGiftLabel)
	{
		char pGift[50];
		sprintf(pGift, ValuesUtil::Instance()->getString("VIP098").c_str(), vipId);
		pGiftLabel->setString(pGift);
		pGiftLabel->setIsVisible(false);
	}
	
	//get vip giftlist
	std::list<VipGiftVo *> giftList = VipManager::Instance()->getVipGiftList(vipId);
	if(giftList.empty())
	{
		return;
	}

	int career = RoleManage::Instance()->roleInfo()->playerBaseInfo.career;

	//display reward from giftlist
	std::list<VipGiftVo *>::iterator it;
	int x = 285;
	int disX = 145;
	int tag = TAG_ICON_VIP_GOODS;
	for(it = giftList.begin(); it != giftList.end(); ++it)
	{
		VipGiftVo *giftVo = *it;
		if(!giftVo)
		{
			continue;
		}

		if(giftVo->_career != 0 && giftVo->_career != career)
		{
			continue;
		}

		VipGiftView *pGiftView = new VipGiftView(giftVo->_goodsId, giftVo->_count);
		if(pGiftView)
		{
			pGiftView->setPosition(ccp(POSX(x), 0));
			pGiftView->setAnchorPoint(CCPointZero);
			pNode->addChild(pGiftView, 0, tag);
			pGiftView->release();

			x += disX;
			++ tag;
		}
	}

	if(x != 285)
	{
		pGiftLabel->setIsVisible(true);
	}

}

//change page to pre
void VipView::onPrePageItemClickListener( CCObject *pSender )
{
	if(_pScrollView)
	{
		_pScrollView->moveToPreviousPage();
		
		this->onScrollListener(_pScrollView->currentScreen);

	}
}
//change page to next
void VipView::onNextPageItemClickListener( CCObject *pSender )
{
	if(_pScrollView)
	{
		_pScrollView->moveToNextPage();

		this->onScrollListener(_pScrollView->currentScreen);

	}
}
