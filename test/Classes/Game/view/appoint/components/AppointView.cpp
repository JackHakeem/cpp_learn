#include "AppointView.h"
#include "manager/PopEventName.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"
#include "../AppointMediator.h"
#include "UICheckButton/UICheckButton.h"
#include "model/appoint/AppointManager.h"
#include "CustomCD.h"
#include "manager/CDManage.h"
#include "AppointBlessView.h"
#include "model/player/RoleManage.h"
#include "manager/LangManager.h"
#include "manager/VIPMgr.h"
#include "manager/VIPLimitConst.h"
#include "MessageInfoBox.h"


const int SIZE_ORIGIN_BACKGROUND_BOX =  98;
const int POS_GOODS_X = 30;
const int POS_GOODS_Y = 134;
const int SIZE_GOODS_X = 98;
const int SIZE_GOODS_Y = 98;
const int DIS_GOODS_X = 6;
const int DIS_GOODS_Y = 10;
const int POS_TRADER_X = 64;
const int POS_TRADER_Y = 310;
const int SIZE_TRADER_X = 74;
const int SIZE_TRADER_Y = 74;
const int DIS_TRADER_X = 20;
const int DIS_TRADER_Y = 10;
const int COUNT_TRADER_X = 5;
const int COUNT_TRADER_Y = 2;
const int COUNT_GOODS_X = 6;
const int COUNT_GOODS_Y = 2;
const int POS_SILVER_X = 615;
const int POS_SILVER_Y = 370;
const int POS_GOLD_X = 615;
const int POS_GOLD_Y = 315;
const int POS_PICK_ALL_X = 735;
const int POS_PICK_ALL_Y = 180;
const int POS_SELL_ALL_X = 735;
const int POS_SELL_ALL_Y = 95;
const int POS_TRADER_NAME_X = 615;
const int POS_TRADER_NAME_Y = 505;
const int POS_TRADER_DETAIL_X = 615;
const int POS_TRADER_DETAIL_Y = 440;

const int TAG_PARENT = 1001;
const int TAG_BUTTON_SILVER = TAG_PARENT + 1;
const int TAG_BUTTON_GOLD = TAG_PARENT + 2;
const int TAG_BUTTON_PICK_ALL = TAG_PARENT + 3;
const int TAG_BUTTON_SELL_ALL = TAG_PARENT + 4;
const int TAG_BUTTON_BLESS = TAG_PARENT + 5;
const int TAG_LAYER_BLESS = 1049;
const int TAG_CD = 1050;
const int TAG_LABEL_BLESS_VALUE = 1051;
const int TAG_LABEL_TRADER_NAME = TAG_LABEL_BLESS_VALUE + 1;
const int TAG_LABEL_TRADER_DETAIL = TAG_LABEL_BLESS_VALUE + 2;
const int TAG_LABEL_SILVER_COST = TAG_LABEL_BLESS_VALUE + 3;
const int TAG_LABEL_GOLD_COST = TAG_LABEL_BLESS_VALUE + 4;
const int TAG_LABEL_FREE_TIMES = TAG_LABEL_BLESS_VALUE + 5;
const int TAG_LABEL_CD_TIMES = TAG_LABEL_BLESS_VALUE + 6;
const int TAG_PROGRESS_BAR = 1100;
const int TAG_GOODS_BASE = 1101;
const int TAG_TRADER_BASE = 1201;
const int TAG_TRADER_HEADER = 1300;
const int TAG_TRADER_HIGHLIGHT = 1301;
const int TAG_DIS_MENU = 2000;
const int TAG_DIS_GOODS = 1000;
const int TAG_DIS_HEADER = 1000;
AppointView::AppointView()
{
	key = PopEventName::APPOINT;
	_canGoldAppoint = false;

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/appoint/res_appoint.plist");

	initView();
	initText();
	initButton();
	initTrader();
	initBless();
}

AppointView::~AppointView()
{

}

void AppointView::initView()
{
	this->setContentSize(CCDirector::sharedDirector()->getWinSize());
	this->setPopContentSize(this->getContentSize());

	CCLayer *pParent = new CCLayer();
	pParent->setAnchorPoint(CCPointZero);
	pParent->setContentSize(this->getContentSize());
	pParent->setPosition(POS(ccp(0, 12), ScaleUtil::CENTER_TOP));
	this->addChild(pParent, 0, TAG_PARENT);
	pParent->release();

	CCLayerColor *pDividerLayer = CCLayerColor::layerWithColorWidthHeight(
		ccc4(207, 165, 37, 255),
		/*pParent->getContentSize().width - */POSX(960 - 40),
		POSX(1));
	pDividerLayer->setAnchorPoint(CCPointZero);
	pDividerLayer->setPosition(ccp(POSX(20), POSX(265)));
	pParent->addChild(pDividerLayer);

	int tag = TAG_GOODS_BASE;
	int x = POS_GOODS_X;
	int y = POS_GOODS_Y;
	for(int j=0; j<COUNT_GOODS_Y; ++j)
	{
		for(int i=0; i<COUNT_GOODS_X; ++i)
		{
			CCSprite *pBackgroundSprite = new CCSprite();
			if(pBackgroundSprite &&
				pBackgroundSprite->initWithSpriteFrameName("pack/unlock.png"))
			{
				pBackgroundSprite->setAnchorPoint(CCPointZero);
				pBackgroundSprite->setPosition(ccp(POSX(x), POSX(y)));
				pParent->addChild(pBackgroundSprite, 0, tag);
				pBackgroundSprite->release();
			}
			++ tag;
			x += SIZE_GOODS_X + DIS_GOODS_X;
		}
		y -= SIZE_GOODS_Y + DIS_GOODS_Y;
		x = POS_GOODS_X;
	}

	CCSprite *pProgressBg = CCSprite::spriteWithSpriteFrameName("figure/exp_bg.png");
	if(pProgressBg)
	{
		pProgressBg->setPosition(ccp(POSX(320), POSX(510)));
		pParent->addChild(pProgressBg);
	}

	AppointManager *pAppointManager = AppointManager::Instance();
	CCProgressTimer *pProgressBar = new CCProgressTimer();
	if (pProgressBar)
	{	
		if (pProgressBar->initWithFile("assets/ui/figure/exp.png"))
		{
			pProgressBar->setPosition(ccp(POSX(320), POSX(510)));
			pProgressBar->getSprite()->setColor(ccc3(0,255,0));
			float percent;
			if(pAppointManager->getBlessValue() >= pAppointManager->getBlessTotal())
			{
				percent = 100;
			}
			else if(pAppointManager->getBlessValue() == 0)
			{
				percent = 0;
			}
			else
			{
				percent = 100 - (float) pAppointManager->getBlessValue() * 100  / (float) pAppointManager->getBlessTotal();
			}
			pProgressBar->setPercentage(percent);
			pProgressBar->setType(CCProgressTimerType(2));
			/*CCProgressTo * pProgressTo = CCProgressTo::actionWithDuration(0.2f, 1.0f); 
			pProgressBar->runAction(pProgressTo);*/
			pParent->addChild(pProgressBar, 0, TAG_PROGRESS_BAR);
			pProgressBar->release();
		}
	}

	CustomCD * pCustomCD = new CustomCD(CDManage::APPOINT);
	if(pCustomCD)
	{
		pCustomCD->setPosition(ccp(POSX(260), POSX(270)));
		pCustomCD->setAnchorPoint(CCPointZero);
		//pCustomCD->reinit();
		pParent->addChild(pCustomCD, 0, TAG_CD);
		pCustomCD->release();
	}
}

void AppointView::initText()
{
	CCLayer *pParent = (CCLayer *) this->getChildByTag(TAG_PARENT);
	if(!pParent)
		return;
	char pFont[10] = "Arial";
	ValuesUtil *pValuesUtil = ValuesUtil::Instance();

	// Add my bless name
	CCLabelTTF *pMyBlessName = CCLabelTTF::labelWithString(
		pValuesUtil->getString("APT017").c_str(),
		CCSizeMake(POSX(90), POSX(18)),
		CCTextAlignmentLeft,
		pFont,
		POSX(18));
	pMyBlessName->setColor(ccc3(255, 198, 0));
	pMyBlessName->setAnchorPoint(CCPointZero);
	pMyBlessName->setPosition(ccp(POSX(35), POSX(500)));
	pParent->addChild(pMyBlessName);
	
	// Add my bless value
	AppointManager *pAppointManager = AppointManager::Instance();
	char pPercent[20];
	sprintf(pPercent, "%d/%d", pAppointManager->getBlessValue(), pAppointManager->getBlessTotal());
	CCLabelTTF *pMyBlessValue = CCLabelTTF::labelWithString(
		pPercent,
		CCSizeMake(POSX(400), POSX(18)),
		CCTextAlignmentCenter,
		pFont,
		POSX(18));
	pMyBlessValue->setColor(ccc3(255, 180, 0));
	pMyBlessValue->setAnchorPoint(ccp(0.5, 0.5));
	pMyBlessValue->setPosition(ccp(POSX(320), POSX(510)));
	pParent->addChild(pMyBlessValue, 0, TAG_LABEL_BLESS_VALUE);

	// Add trader name
	CCLabelTTF *pTraderName = CCLabelTTF::labelWithString(
		"",
		CCSizeMake(POSX(120), POSX(18)),
		CCTextAlignmentLeft,
		pFont,
		POSX(18));
	pTraderName->setColor(ccc3(255, 198, 0));
	pTraderName->setAnchorPoint(CCPointZero);
	pTraderName->setPosition(ccp(POSX(615), POSX(500)));
	pParent->addChild(pTraderName, 0, TAG_LABEL_TRADER_NAME);

	// Add trader detail
	CCLabelTTF *pTraderDetail = CCLabelTTF::labelWithString(
		"",
		CCSizeMake(POSX(300), POSX(54)),
		CCTextAlignmentLeft,
		pFont,
		POSX(18));
	pTraderDetail->setColor(ccc3(255, 255, 255));
	pTraderDetail->setAnchorPoint(CCPointZero);
	pTraderDetail->setPosition(ccp(POSX(615), POSX(440)));
	pParent->addChild(pTraderDetail, 0, TAG_LABEL_TRADER_DETAIL);

	// Add center text
	CCLabelTTF *pFreeTextLabel = CCLabelTTF::labelWithString(
		pValuesUtil->getString("APT018").c_str(),
		CCSizeMake(POSX(200), POSX(18)),
		CCTextAlignmentLeft,
		pFont,
		POSX(18));
	pFreeTextLabel->setColor(ccc3(255, 255, 255));
	pFreeTextLabel->setAnchorPoint(CCPointZero);
	pFreeTextLabel->setPosition(ccp(POSX(94), POSX(274)));
	pParent->addChild(pFreeTextLabel);

	CCLabelTTF *pFreeTimesLabel = CCLabelTTF::labelWithString(
		"0",
		CCSizeMake(POSX(18), POSX(18)),
		CCTextAlignmentLeft,
		pFont,
		POSX(18));
	pFreeTimesLabel->setColor(ccc3(255, 198, 0));
	pFreeTimesLabel->setAnchorPoint(CCPointZero);
	pFreeTimesLabel->setPosition(ccp(POSX(94 + 130), POSX(274)));
	pParent->addChild(pFreeTimesLabel, 1, TAG_LABEL_FREE_TIMES);

	/*CCLabelTTF *pCDLabel = CCLabelTTF::labelWithString(
	pValuesUtil->getString("APT019").c_str(),
	CCSizeMake(POSX(90), POSX(18)),
	CCTextAlignmentLeft,
	pFont,
	POSX(18));
	pCDLabel->setColor(ccc3(255, 255, 255));
	pCDLabel->setAnchorPoint(CCPointZero);
	pCDLabel->setPosition(ccp(POSX(320), POSX(274)));
	pParent->addChild(pCDLabel);*/
	//Add cd times

	CCLabelTTF *pTipsLabel = CCLabelTTF::labelWithString(
		pValuesUtil->getString("APT020").c_str(),
		CCSizeMake(POSX(300), POSX(18)),
		CCTextAlignmentLeft,
		pFont,
		POSX(18));
	pTipsLabel->setColor(ccc3(255, 255, 255));
	pTipsLabel->setAnchorPoint(CCPointZero);
	pTipsLabel->setPosition(ccp(POSX(610), POSX(274)));
	pParent->addChild(pTipsLabel);

	//Add silver cost
	CCLabelTTF *pSilverCostLabel = CCLabelTTF::labelWithString(
		"",
		CCSizeMake(POSX(200), POSX(18)),
		CCTextAlignmentLeft,
		pFont,
		POSX(18));
	pSilverCostLabel->setColor(ccc3(255, 255, 255));
	pSilverCostLabel->setAnchorPoint(CCPointZero);
	pSilverCostLabel->setPosition(ccp(POSX(764), POSX(388)));
	pParent->addChild(pSilverCostLabel, 0, TAG_LABEL_SILVER_COST);
	//Add gold cost
	CCLabelTTF *pGoldCostLabel = CCLabelTTF::labelWithString(
		"",
		CCSizeMake(POSX(200), POSX(18)),
		CCTextAlignmentLeft,
		pFont,
		POSX(18));
	pGoldCostLabel->setColor(ccc3(255, 255, 255));
	pGoldCostLabel->setAnchorPoint(CCPointZero);
	pGoldCostLabel->setPosition(ccp(POSX(764), POSX(328)));
	pParent->addChild(pGoldCostLabel, 0, TAG_LABEL_GOLD_COST);
    
	//Add tip cost
	CCLabelTTF *pDoubleClickTipLabel = CCLabelTTF::labelWithString(
                                                             pValuesUtil->getString("APT028").c_str(),
                                                             CCSizeMake(POSX(200), POSX(18)),
                                                             CCTextAlignmentLeft,
                                                             pFont,
                                                             POSX(18));
	pDoubleClickTipLabel->setColor(ccc3(255, 255, 255));
	pDoubleClickTipLabel->setAnchorPoint(CCPointZero);
	pDoubleClickTipLabel->setPosition(ccp(POSX(735), POSX(50)));
	pParent->addChild(pDoubleClickTipLabel);

}

void AppointView::initButton()
{
	CCLayer *pParent = (CCLayer *) this->getChildByTag(TAG_PARENT);
	if(!pParent)
		return;
	ValuesUtil *pValuesUtil = ValuesUtil::Instance();
	char pFont[10] = "Arial";

	

	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		if(pNormalSprite && pPressedSprite)
		{
			CCMenuItemSprite *pSilverMenuImage = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this,
				menu_selector(AppointView::onMenuClickListener));
			pSilverMenuImage->setTag(TAG_BUTTON_SILVER);
			pSilverMenuImage->setPosition(ccp(POSX(POS_SILVER_X), POSX(POS_SILVER_Y)));
			pSilverMenuImage->setAnchorPoint(CCPointZero);
			CCMenu *pSilverMenu = CCMenu::menuWithItem(pSilverMenuImage);
			pSilverMenu->setPosition(CCPointZero);
			pSilverMenu->setTouchLayer(TLE::WindowLayer_AppointView);
			pParent->addChild(pSilverMenu);

			CCLabelTTF *pSilverLabel = CCLabelTTF::labelWithString(
				pValuesUtil->getString("APT022").c_str(),
				CCSizeMake(POSX(80), POSX(20)),
				CCTextAlignmentCenter,
				pFont,
				POSX(20));
			pSilverLabel->setColor(ccc3(255, 255, 255));
			pSilverLabel->setPosition(ccpAdd(pSilverMenuImage->getPosition(),
				ccp(pSilverMenuImage->getContentSize().width / 2, pSilverMenuImage->getContentSize().height / 2)));
			pParent->addChild(pSilverLabel);
		}
	}
	


	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			CCMenuItemSprite *pGoldMenuImage = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this,
				menu_selector(AppointView::onMenuClickListener));
			pGoldMenuImage->setTag(TAG_BUTTON_GOLD);
			pGoldMenuImage->setPosition(ccp(POSX(POS_GOLD_X), POSX(POS_GOLD_Y)));
			pGoldMenuImage->setAnchorPoint(CCPointZero);
			CCMenu *pGoldMenu = CCMenu::menuWithItems(pGoldMenuImage, NULL);
			pGoldMenu->setPosition(CCPointZero);
			pGoldMenu->setTouchLayer(TLE::WindowLayer_AppointView);
			pParent->addChild(pGoldMenu, 0, TAG_BUTTON_GOLD);

			CCLabelTTF *pGoldLabel = CCLabelTTF::labelWithString(
				pValuesUtil->getString("APT021").c_str(),
				CCSizeMake(POSX(80), POSX(20)),
				CCTextAlignmentCenter,
				pFont,
				POSX(20));
			pGoldLabel->setColor(ccc3(255, 255, 255));
			pGoldLabel->setPosition(ccpAdd(pGoldMenuImage->getPosition(),
				ccp(pGoldMenuImage->getContentSize().width / 2, pGoldMenuImage->getContentSize().height / 2)));
			pParent->addChild(pGoldLabel);
		}
	}


	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		if(pNormalSprite && pPressedSprite)
		{
			CCMenuItemSprite *pPickAllMenuImage = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this,
				menu_selector(AppointView::onMenuClickListener));
			pPickAllMenuImage->setTag(TAG_BUTTON_PICK_ALL);
			pPickAllMenuImage->setPosition(ccp(POSX(POS_PICK_ALL_X), POSX(POS_PICK_ALL_Y)));
			pPickAllMenuImage->setAnchorPoint(CCPointZero);
			CCMenu *pPickAllMenu = CCMenu::menuWithItem(pPickAllMenuImage);
			pPickAllMenu->setPosition(CCPointZero);
			pPickAllMenu->setTouchLayer(TLE::WindowLayer_AppointView);
			pParent->addChild(pPickAllMenu);

			CCLabelTTF *pPickAllLabel = CCLabelTTF::labelWithString(
				pValuesUtil->getString("APT024").c_str(),
				CCSizeMake(POSX(80), POSX(20)),
				CCTextAlignmentCenter,
				pFont,
				POSX(20));
			pPickAllLabel->setColor(ccc3(255, 255, 255));
			pPickAllLabel->setPosition(ccpAdd(pPickAllMenuImage->getPosition(),
				ccp(pPickAllMenuImage->getContentSize().width / 2, pPickAllMenuImage->getContentSize().height / 2)));
			pParent->addChild(pPickAllLabel);
		}
	}


	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		if(pNormalSprite && pPressedSprite)
		{
			CCMenuItemSprite *pSellAllMenuImage = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this,
				menu_selector(AppointView::onMenuClickListener));
			pSellAllMenuImage->setTag(TAG_BUTTON_SELL_ALL);
			pSellAllMenuImage->setPosition(ccp(POSX(POS_SELL_ALL_X), POSX(POS_SELL_ALL_Y)));
			pSellAllMenuImage->setAnchorPoint(CCPointZero);
			CCMenu *pSellAllMenu = CCMenu::menuWithItem(pSellAllMenuImage);
			pSellAllMenu->setPosition(CCPointZero);
			pSellAllMenu->setTouchLayer(TLE::WindowLayer_AppointView);
			pParent->addChild(pSellAllMenu);

			CCLabelTTF *pSellAllLabel = CCLabelTTF::labelWithString(
				pValuesUtil->getString("APT023").c_str(),
				CCSizeMake(POSX(80), POSX(20)),
				CCTextAlignmentCenter,
				pFont,
				POSX(20));
			pSellAllLabel->setColor(ccc3(255, 255, 255));
			pSellAllLabel->setPosition(ccpAdd(pSellAllMenuImage->getPosition(),
				ccp(pSellAllMenuImage->getContentSize().width / 2, pSellAllMenuImage->getContentSize().height / 2)));
			pParent->addChild(pSellAllLabel);
		}
	}


	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		if(pNormalSprite && pPressedSprite)
		{
			CCMenuItemSprite *pBlessMenuImage = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this,
				menu_selector(AppointView::onMenuClickListener));
			pBlessMenuImage->setTag(TAG_BUTTON_BLESS);
			pBlessMenuImage->setPosition(ccp(POSX(514), POSX(485)));
			pBlessMenuImage->setAnchorPoint(CCPointZero);
			pBlessMenuImage->setScaleX(0.826f);
			CCMenu *pBlessMenu = CCMenu::menuWithItem(pBlessMenuImage);
			pBlessMenu->setPosition(CCPointZero);
			pBlessMenu->setTouchLayer(TLE::WindowLayer_AppointView);
			pParent->addChild(pBlessMenu);

			CCLabelTTF *pBlessLabel = CCLabelTTF::labelWithString(
				pValuesUtil->getString("APT025").c_str(),
				CCSizeMake(POSX(40), POSX(20)),
				CCTextAlignmentCenter,
				pFont,
				POSX(20));
			pBlessLabel->setColor(ccc3(255, 255, 255));
			pBlessLabel->setPosition(ccp(POSX(564), POSX(510)));
			pParent->addChild(pBlessLabel);
		}
	}

	
}

void AppointView::initTrader()
{
	CCLayer *pParent = (CCLayer *) this->getChildByTag(TAG_PARENT);
	if(!pParent)
		return;

	int tag = TAG_TRADER_BASE;
	int x = POS_TRADER_X;
	int y = POS_TRADER_Y;
	for(int j=0; j<COUNT_TRADER_Y; ++j)
	{
		for(int i=0; i<COUNT_TRADER_X; ++i)
		{
			CCSprite *pBackgroundSprite = new CCSprite();
			if(pBackgroundSprite &&
				pBackgroundSprite->initWithSpriteFrameName("pack/lock.png"))
			{
				pBackgroundSprite->setAnchorPoint(CCPointZero);
				pBackgroundSprite->setPosition(ccp(POSX(x), POSX(y)));
				pBackgroundSprite->setScale((float) SIZE_TRADER_X / (float) SIZE_ORIGIN_BACKGROUND_BOX);
				pParent->addChild(pBackgroundSprite, 0, tag);
				pBackgroundSprite->release();
			}

			//Add menu
			if(tag != TAG_TRADER_BASE && tag != TAG_TRADER_BASE + 5)
			{
				CCSprite *pHeader = createTraderHeader(i);
				if(pHeader)
				{
					pHeader->setPosition(ccp(POSX(2), POSX(2)));
					pHeader->setAnchorPoint(CCPointZero);
					pHeader->setPosition(ccp(POSX(x + 2), POSX(y + 2)));
					pHeader->setIsVisible(false);
					pParent->addChild(pHeader, 0, tag + TAG_DIS_HEADER);
				}

				CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("pack/frame_blank.png");
				CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("pack/qualityfram_5.png");
				CCMenuItemSprite *pMenuImage = CCMenuItemSprite::itemFromNormalSprite(
					pNormalSprite,
					pPressedSprite,
					this,
					menu_selector(AppointView::onMenuClickListener) );
				pMenuImage->setTag(tag + TAG_DIS_MENU);
				pMenuImage->setAnchorPoint(CCPointZero);
				pMenuImage->setPosition(ccp(POSX(x), POSX(y)));
				pMenuImage->setScale((float) SIZE_TRADER_X / (float) SIZE_ORIGIN_BACKGROUND_BOX);
				UICheckButton *pCheckButton = UICheckButton::menuWithItems(pMenuImage, NULL);
				pCheckButton->setPosition(CCPointZero);
				pCheckButton->setTouchLayer(TLE::WindowLayer_TaskView);
				pParent->addChild(pCheckButton, 0, tag + TAG_DIS_MENU);
			}

			++ tag;
			x += SIZE_TRADER_X + DIS_TRADER_X;
		}
		y += SIZE_TRADER_Y + DIS_TRADER_Y;
		x = POS_TRADER_X;
	}

	// Add two icons
	CCSprite *pRingSprite = CCSprite::spriteWithSpriteFrameName("appoint/icon_ring.png");
	if(pRingSprite)
	{
		pRingSprite->setAnchorPoint(CCPointZero);
		pRingSprite->setPosition(ccp(POSX(POS_TRADER_X + 2), POSX(POS_TRADER_Y + DIS_TRADER_Y + SIZE_TRADER_Y + 2)));
		pParent->addChild(pRingSprite);
	}
	CCSprite *pCloakSprite = CCSprite::spriteWithSpriteFrameName("appoint/icon_cloak.png");
	if(pCloakSprite)
	{
		pCloakSprite->setAnchorPoint(CCPointZero);
		pCloakSprite->setPosition(ccp(POSX(POS_TRADER_X + 2), POSX(POS_TRADER_Y + 2)));
		pParent->addChild(pCloakSprite);
	}

}

void AppointView::initBless()
{
	AppointManager *pAppointManager = AppointManager::Instance();
	updateBlessInfo(true, pAppointManager->getBlessValue(), pAppointManager->getBlessTotal());
}

void AppointView::startFlasher()
{

}

void AppointView::stopFlasher()
{

}

void AppointView::updateGoldAppoint( int vipLev, int crystalLev )
{
	if (!VIPMgr::Instance()->hasVIPFunc(VIPLimitConst::VIP_Appoint_Gold , RoleManage::Instance()->accountInfo()->vipLev()))
	{
		char path[128] = {0};
		sprintf(path , ValuesUtil::Instance()->getString("APT030").c_str() , VIPLimitConst::VIP_Appoint_Gold);
		MessageInfoBox::Instance()->show(path,ccc3(12,233,25));
		return;
	}

	/*
	bool key = vipLev >= 7;

	if(!key)
		return;
	*/

	std::string tip = ValuesUtil::Instance()->getString("APT012");
	enableGoldBtn(crystalLev >= 80, tip);
	if(crystalLev >= 80)
	{
		_canGoldAppoint = true;
	}
}

void AppointView::updateBlessInfo( bool isOpen,int blessValue,int total )
{
	CCLayer *pParent = (CCLayer *) this->getChildByTag(TAG_PARENT);
	if(!pParent)
		return;

	char pPercent[128];
	sprintf(pPercent, "%d/%d", blessValue, total);
	CCLabelTTF *pMyBlessValue = (CCLabelTTF *) pParent->getChildByTag(TAG_LABEL_BLESS_VALUE);
	if(pMyBlessValue)
	{
		pMyBlessValue->setString(pPercent);
	}

	CCProgressTimer *pProgressBar = (CCProgressTimer *) pParent->getChildByTag(TAG_PROGRESS_BAR);
	if(pProgressBar)
	{
		float percent;
		if(blessValue >= total)
		{
			percent = 100;
		}
		else if(blessValue == 0)
		{
			percent = 0;
		}
		else
		{
			percent = 100 - (float) blessValue * 100 / (float) total;
		}
		pProgressBar->setPercentage(percent);
	}

	// Update AppointBlessView

	AppointBlessView *pAppointBlessView = (AppointBlessView *) this->getChildByTag(TAG_LAYER_BLESS);
	if(pAppointBlessView)
	{
		pAppointBlessView->updateExchangeState(blessValue);
	}
}

AppointVo * AppointView::getCurTraderInfo()
{
	return _curTraderInfo;
}

void AppointView::setCurTraderInfo( AppointVo *pAppointVo )
{
	_curTraderInfo = pAppointVo;
	updateInfo();
	showTrader();
}

void AppointView::updateInfo()
{
	if(!_curTraderInfo)
	{
		return;
	}

	CCLayer *pParent = (CCLayer *) this->getChildByTag(TAG_PARENT);
	if(!pParent)
		return;
	CCLabelTTF *pTraderNameLabel = (CCLabelTTF *) pParent->getChildByTag(TAG_LABEL_TRADER_NAME);
	if(pTraderNameLabel)
	{
		pTraderNameLabel->setString(_curTraderInfo->name.c_str());
	}
	CCLabelTTF *pTraderDetailLabel = (CCLabelTTF *) pParent->getChildByTag(TAG_LABEL_TRADER_DETAIL);
	if(pTraderDetailLabel)
	{
		pTraderDetailLabel->setString(_curTraderInfo->info.c_str());
	}


	CCLabelTTF *pSilverCostLabel = (CCLabelTTF *) pParent->getChildByTag(TAG_LABEL_SILVER_COST);
	if(pSilverCostLabel)
	{
		if(_curTraderInfo->freeNum > 0)
		{
			pSilverCostLabel->setString(ValuesUtil::Instance()->getString("APT014").c_str());
		}
		else
		{
			char pSilver[128];
			sprintf(pSilver, "%d %s", _curTraderInfo->silver, ValuesUtil::Instance()->getString("silver").c_str());
			pSilverCostLabel->setString(pSilver);
		}
	}

	CCLabelTTF *pGoldCostLabel = (CCLabelTTF *) pParent->getChildByTag(TAG_LABEL_GOLD_COST);
	if(pGoldCostLabel)
	{
		char pGold[20];
		sprintf(pGold, "%d%s", _curTraderInfo->gold, ValuesUtil::Instance()->getString("gold").c_str());
		pGoldCostLabel->setString(pGold);
	}

	CCLabelTTF *pFreeTimesLabel = (CCLabelTTF *) pParent->getChildByTag(TAG_LABEL_FREE_TIMES);
	if(pFreeTimesLabel)
	{
		char pTimes[10];
		sprintf(pTimes, "%d", _curTraderInfo->freeNum);
		pFreeTimesLabel->setString(pTimes);
	}

	//��ߵȼ����˲���ʹ�ý��ί��
	if(_canGoldAppoint)
	{
		std::string tip = ValuesUtil::Instance()->getString("APT015");
		enableGoldBtn(_curTraderInfo->level < 3, tip);
	}
}

void AppointView::showTrader()
{
	CCLayer *pParent = (CCLayer *) this->getChildByTag(TAG_PARENT);
	if(!pParent)
		return;

	int bitNum = _curTraderInfo->bitNum;
	if(bitNum < 0) return;	//���ʱ��
	int baseTag = TAG_TRADER_BASE;
	int lev = _curTraderInfo->level + baseTag  + TAG_DIS_MENU;
	baseTag += TAG_DIS_HEADER;
	if(_curTraderInfo->type == 0)
	{	
		//0����ָ����
		setTraderHeaderVisible((bitNum & 1), baseTag + 9);
		setTraderHeaderVisible((bitNum & 2), baseTag + 8);
		setTraderHeaderVisible((bitNum & 4), baseTag + 7);
		setTraderHeaderVisible(true, baseTag + 6);
		lev += 6;
	}
	else if(_curTraderInfo->type == 1)
	{	//1���������
		setTraderHeaderVisible((bitNum & 1), baseTag + 4);
		setTraderHeaderVisible((bitNum & 2), baseTag + 3);
		setTraderHeaderVisible((bitNum & 4), baseTag + 2);
		setTraderHeaderVisible(true, baseTag + 1);
		lev += 1;
	}
	/*for(var i:int=0; i<_traders.length; i++){
	var trader:MovieClip = _traders[i] as MovieClip;
	trader.gotoAndStop("up");
	}*/
	setTraderHighlight(true, lev);
}

void AppointView::onMenuClickListener( CCObject *pObject )
{
	CCMenu *pMenu = (CCMenu *) pObject;
	if(!pMenu)
	{
		return;
	}
	int tag = pMenu->getTag();
	switch(tag)
	{
	case TAG_BUTTON_GOLD:
		{
			// Tip VIP lev required.
            int vipLev = RoleManage::Instance()->accountInfo()->_vipLev;
            int lev = RoleManage::Instance()->roleLev();
            
            if( lev < 80)
            {
                LangManager::msgShow("APT012");
            }
            
            if (vipLev < 2)
            {
                LangManager::msgShow("APT027");
            }
			_curTraderInfo->isGoldAppoint = true;
			dispatchEvent(AppointMediator::APPOINT_TRADER, _curTraderInfo);
		}
		break;

	case TAG_BUTTON_SILVER:
		{
			_curTraderInfo->isGoldAppoint = false;
			dispatchEvent(AppointMediator::APPOINT_TRADER, _curTraderInfo);
		}
		break;

	case TAG_BUTTON_PICK_ALL:
		{
			dispatchEvent(AppointMediator::RECEIVE_ALL, NULL);
		}
		break;

	case TAG_BUTTON_SELL_ALL:
		{
			dispatchEvent(AppointMediator::SELL_ALL, NULL);
		}
		break;

	case TAG_BUTTON_BLESS:
		{
			openBlessView();
		}
		break;

	case TAG_TRADER_BASE + TAG_DIS_MENU + 1:
	case TAG_TRADER_BASE + TAG_DIS_MENU + 2:
	case TAG_TRADER_BASE + TAG_DIS_MENU + 3:
	case TAG_TRADER_BASE + TAG_DIS_MENU + 4:
	case TAG_TRADER_BASE + TAG_DIS_MENU + 6:
	case TAG_TRADER_BASE + TAG_DIS_MENU + 7:
	case TAG_TRADER_BASE + TAG_DIS_MENU + 8:
	case TAG_TRADER_BASE + TAG_DIS_MENU + 9:
		{
			setTraderHighlight(true, tag);

			int *pInt = new int;
			*pInt = tag - TAG_TRADER_BASE - TAG_DIS_MENU;

			dispatchEvent(AppointMediator::ON_TRADER_CLICK, pInt);
			CC_SAFE_DELETE(pInt);
		}
		break;

	default:
		break;
	}
}

void AppointView::enableGoldBtn( bool enable, std::string tips )
{
	CCLayer *pParent = (CCLayer *) this->getChildByTag(TAG_PARENT);
	if(!pParent)
		return;

	CCMenu *pGoldMenu = (CCMenu *) pParent->getChildByTag(TAG_BUTTON_GOLD);
	if(pGoldMenu)
	{
		CCMenuItemSprite *pGoldMenuImage = (CCMenuItemSprite *) pGoldMenu->getChildByTag(TAG_BUTTON_GOLD);
		if(pGoldMenuImage)
		{
			pGoldMenuImage->setIsEnabled(enable);
		}
	}

	if(enable)
	{
		/*_btnGoldAppoint.filters = [];
		_tip.stopToolTips();*/
	}
	else
	{
		CCLabelTTF *pGoldCostLabel = (CCLabelTTF *) pParent->getChildByTag(TAG_LABEL_GOLD_COST);
		if(pGoldCostLabel)
		{
			pGoldCostLabel->setString(ValuesUtil::Instance()->getString("APT026").c_str());
		}
		/*Utils.applyBlackAndWhiteFilter(_btnGoldAppoint);
		_tip.setToolTips(_btnGoldAppoint, tip);*/
	}
}

CCSprite * AppointView::createTraderHeader( int id )
{
	char pIcon[30];
	sprintf(pIcon, "appoint/%d.png", id);
	CCSprite *pTraderHeader = CCSprite::spriteWithSpriteFrameName(pIcon);
	return pTraderHeader;
}

void AppointView::setTraderHeaderVisible( bool isVisible, int tag )
{
	CCLayer *pParent = (CCLayer *) this->getChildByTag(TAG_PARENT);
	if(!pParent)
		return;

	CCNode *pHeader = pParent->getChildByTag(tag);
	if(pHeader)
	{
		pHeader->setIsVisible(isVisible);
	}
	UICheckButton *pCheckButton = (UICheckButton *) pParent->getChildByTag(tag - TAG_DIS_HEADER + TAG_DIS_MENU);
	if(pCheckButton)
	{
		pCheckButton->setIsTouchEnabled(isVisible);
	}
}

void AppointView::setTraderHighlight( bool isHighLight, int tag )
{
	CCLayer *pParent = (CCLayer *) this->getChildByTag(TAG_PARENT);
	if(!pParent)
		return;

	int tmpTag = 0;
	for(int i=1; i<10; ++i)
	{
		if(i == 5)
		{
			continue;
		}
		tmpTag = TAG_TRADER_BASE + TAG_DIS_MENU + i;
		UICheckButton *pCheckButton = (UICheckButton *) pParent->getChildByTag(tmpTag);
		if(pCheckButton)
		{
			pCheckButton->setIsCheck(tmpTag == tag);
		}
		if(tmpTag == tag && (i == 4 || i == 9))
		{
			enableGoldBtn(false, "");
		}
		else
		{
			//enableGoldBtn(true, "");
		}
	}
}

void AppointView::drawGoods()
{
	CCLayer *pParent = (CCLayer *) this->getChildByTag(TAG_PARENT);
	if(!pParent)
		return;

	for(int i=0; i<13; ++i)
	{
		pParent->removeChildByTag(i + TAG_GOODS_BASE + TAG_DIS_GOODS, false);
	}

	std::list<GoodsView *> &goodsList = AppointManager::Instance()->_goodsArr;
	std::list<GoodsView *>::iterator it;
	int bgTag = TAG_GOODS_BASE;
	int goodsTag = bgTag + TAG_DIS_GOODS;
	for(it = goodsList.begin(); it != goodsList.end(); ++it)
	{
		GoodsView *pGoodsView = (GoodsView *) *it;
		if(!pGoodsView || pGoodsView->getParent())
		{
			continue;
		}

		CCNode *pBgNode = pParent->getChildByTag(bgTag);
		if(pBgNode)
		{
			pGoodsView->setAnchorPoint(CCPointZero);
			pGoodsView->setPosition(pBgNode->getPosition());
			pParent->addChild(pGoodsView, 0, goodsTag);
			//pGoodsView->release();
		}

		++ bgTag;
		++ goodsTag;
	}
}

void AppointView::reinit()
{
	CCLayer *pParent = (CCLayer *) this->getChildByTag(TAG_PARENT);
	if(!pParent)
		return;

	CustomCD * pCustomCD = (CustomCD *) pParent->getChildByTag(TAG_CD);
	if(pCustomCD)
	{
		pCustomCD->reinit();
	}
}

void AppointView::openBlessView()
{
	this->removeChildByTag(TAG_LAYER_BLESS, true);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	AppointBlessView *pAppointBlessView = new AppointBlessView();
	if(pAppointBlessView->initWithColorWidthHeight(ccc4(0, 0, 0, 128),
		winSize.width,
		winSize.height))
	{
		pAppointBlessView->initView();
		pAppointBlessView->setAnchorPoint(CCPointZero);
		pAppointBlessView->setPosition(CCPointZero);
		this->addChild(pAppointBlessView, 0, TAG_LAYER_BLESS);
		pAppointBlessView->release();
	}
}

void AppointView::closeBlessView()
{
	this->removeChildByTag(TAG_LAYER_BLESS, true);
}
