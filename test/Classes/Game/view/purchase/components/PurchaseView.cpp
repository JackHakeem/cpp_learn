#include "PurchaseView.h"
#include "manager/PopEventName.h"
#include "CCUIBackground.h"
#include "utils/ValuesUtil.h"
//#include "IAPManager.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "LoginManage.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import "Connect91Handler.h"
#endif


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "jni/slcq/JniManager.h"
#endif
//#define CCPOINT_INNER_LAYER ccp(90, 92)
//#define CCPOINT_CLOSE_BTN ccp(820, 634)
#define CCPOINT_CELL_ICON ccp(POSX(8), POSX(44))
#define CCPOINT_CELL_NAME ccp(POSX(10), POSX(14))
#define CCPOINT_CELL_GOLD ccp(POSX(140), POSX(60))
#define CCPOINT_CELL_BUY_BTN ccp(POSX(300), POSX(50))
#define CCPOINT_CELL_BUY_TEXT ccp(POSX(320), POSX(65))

#define CCPOINT_FIRST_CELL CCPointZero
#define CCPOINT_SECOND_CELL ccp(POSX(444), 0)
//#define CCPOINT_THIRD_CELL ccp(POSX(480), POSX(8))

//#define CCSIZE_INNER_LAYER CCSizeMake(POSX(740), POSX(588))
#define CCSIZE_ITEM_CELL CCSizeMake(POSX(440), POSX(156))
#define CCSIZE_ITEM_LAYER CCSizeMake(POSX(886), POSX(158))
//#define CCRECT_LIST_VIEW CCRectMake(POSX(18), POSX(30), POSX(710), POSX(480))

//#define CCRECT_LIST_CLIP CCRectMake(POSX(108),\
//	POSX(118), \
//	CCRECT_LIST_VIEW.size.width,\
//	CCRECT_LIST_VIEW.size.height + POSX(10))


#define SCALE_BUY_BTN 0.826


#define CCPOINT_CONTENT_LAYER ccp(POSX(20), POSX(24))
#define CCSIZE_CONTENT_LAYER CCSizeMake(POSX(886), POSX(518))

bool PurchaseView::init() 
{
	if(!CCLayer::init())
	{
		return false;
	}
	//this->setIsTouchEnabled(true);

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/purchase/res_purchase.plist");

	this->setPosition(CCPointZero);
	this->setContentSize(CCDirector::sharedDirector()->getWinSize());
	this->setPopContentSize(this->getContentSize());

	CCLayer *pInnerLayer = new CCLayer();
	if(!pInnerLayer || !pInnerLayer->init()) 
	{
		return false;
	}
	CCPoint innerLayerPosition = POS(ccp(16.0f, 12.0f), ScaleUtil::CENTER_TOP);
	pInnerLayer->setAnchorPoint(CCPointZero);
	//pInnerLayer->initWithColor(ccc4(255, 128, 128, 100));
	pInnerLayer->setPosition(innerLayerPosition);
	pInnerLayer->setIsRelativeAnchorPoint(true);
	pInnerLayer->setContentSize(CCDirector::sharedDirector()->getWinSize());
	this->addChild(pInnerLayer);
	pInnerLayer->release();
    
	/*CCSprite *pBackgroundSprite = CCSprite::spriteWithFile("assets/ui/purchase/PurchaseBg.png");
	if(!pBackgroundSprite) 
	{
		return false;
	}
	pBackgroundSprite->setAnchorPoint(CCPointZero);
	pBackgroundSprite->setPosition(CCPointZero);
	pBackgroundSprite->setIsRelativeAnchorPoint(true);

	CCLog("=========width=%f,height=%f", CCDirector::sharedDirector()->getWinSize().width,
          CCDirector::sharedDirector()->getWinSize().height);
    
	pInnerLayer->addChild(pBackgroundSprite);*/

	// Close button
	//CCMenuItemImage *pCloseBtn = CCMenuItemImage::itemFromNormalImage(
	//	"assets/task/TaskViewCloseBtnNormal.png",
	//	"assets/task/TaskViewCloseBtnPressed.png",
	//	this,
	//	menu_selector(PurchaseView::closeButtonClick));
	//pCloseBtn->setPosition(POS(CCPOINT_CLOSE_BTN, ScaleUtil::CENTER));
	////pCloseBtn->setAnchorPoint(CCPointZero);
	//CCMenu* pCloseMenu = CCMenu::menuWithItems(pCloseBtn, NULL);
	//pCloseMenu->setPosition(CCPointZero);
	//this->addChild(pCloseMenu , 1);
	_pListView = CCUIListView::listViewWithCCRect(CCRectMake(CCPOINT_CONTENT_LAYER.x,
		CCPOINT_CONTENT_LAYER.y,
		CCSIZE_CONTENT_LAYER.width,
		CCSIZE_CONTENT_LAYER.height), 
		false);
	_pListView->setAnchorPoint(CCPointZero);
	_pListView->setSpacingVertical(POSX(10));
	_pListView->setHeaderSize(POSX(20));
	_pListView->setFooterSize(POSX(20));
	_pListView->setAdapter(this);
	_pListView->setIsRelativeAnchorPoint(true);
	//_pListView->setClipLayerRect(CCRECT_LIST_CLIP);
	_pListView->setWorldSpaceLeftBottomPoint(ccp(this->getPosition().x + pInnerLayer->getPosition().x + _pListView->getPosition().x,
		this->getPosition().y + pInnerLayer->getPosition().y + _pListView->getPosition().y));
	_pListView->m_pri = TLE::WindowLayer_PurchaseView;
	pInnerLayer->addChild(_pListView);
	_pListView->release(); // Kenfly 20130125

   // IAPManager::getInstance()->setCallback(this);

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/purchase/res_purchase.plist");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/purchase/res_purchase.pvr.ccz");
	return true;
}

PurchaseView::PurchaseView()
{
    _isPaymentReturn = true;
	key = PopEventName::PURCHASE;
}

//void PurchaseView::registerWithTouchDispatcher( void )
//{
//	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, kCCMenuTouchPriority, true);
//}

int PurchaseView::getCount()
{
	return 3;
}

LayerNode * PurchaseView::getView( int POSXition )
{
	return createListItem(POSXition);
}

PurchaseView* PurchaseView::initView()
{
	PurchaseView *pPurchaseView = new PurchaseView();
	if(pPurchaseView && pPurchaseView->init())
	{
		return pPurchaseView;
	}
	CC_SAFE_DELETE(pPurchaseView);
	return NULL;
}

void PurchaseView::onBuyButtonClick( CCObject* pSender )
{
	CCMenu *pMenu = (CCMenu *) pSender;
	if(!pMenu)
	{
		return;
	}
	int position = pMenu->getTag();
	char goldNum[20];
	sprintf(goldNum, "%s%d", "pur_gold_", position);
	/*int gold = atoi(ValuesUtil::Instance()->getString(goldNum).c_str());
	if(gold <= 0)
	{
		gold = 1000;
	}*/
	char pGold[20];
	sprintf(pGold, "%s", ValuesUtil::Instance()->getString(goldNum).c_str());

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	callExcharge(pGold, g_pLoginManage->getExchargeServerId().c_str());
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [[Connect91Handler sharedTo91] buyGold:gold];
#endif

    


//    if(!_isPaymentReturn) return;
//    
//    _isPaymentReturn = false;
//	CCMenu *pTaskMenu = (CCMenu *) pSender;
//	CCLog("----------------tag=%d", POSXition);
////    std::string productId = "com.4399.hlqs.test.00";
//    char productId[23];
//    sprintf(productId, "com.4399.hlqs.test.00%d", POSXition + 1);
   // IAPManager::getInstance()->sendProductRequest(productId);
}

void PurchaseView::closeButtonClick( CCObject* pSender )
{
	this->setisPop(false);
}

LayerNode * PurchaseView::createListItem( int position )
{
	ValuesUtil *pValuesUtil = ValuesUtil::Instance();

	LayerNode *pItemLayer = new LayerNode();
	if(!pItemLayer || !pItemLayer->init())
	{
		return NULL;
	}
	pItemLayer->setContentSize(CCSIZE_ITEM_LAYER);
	pItemLayer->setvisibleSize(CCSIZE_ITEM_LAYER);

	int pos = position * 2;

	char nameStr[20];
	char goldNum[20];
    std::string iconStr = "pack/unlock.png";

	sprintf(nameStr, "%s%d", "pur_", pos);
	sprintf(goldNum, "%s%d", "pur_gold_", pos);

	char goldStr[30];
	sprintf(goldStr, "%s%s", pValuesUtil->getString(goldNum).c_str(), pValuesUtil->getString("pur_num").c_str());
	// Add first cell
	CCLayer *pFirstCellLayer = createListItemCell(
		pValuesUtil->getString(nameStr).c_str(),
		goldStr,
		iconStr.c_str(), 
		pValuesUtil->getString("pur_buy").c_str(), pos);
	if(pFirstCellLayer)
	{
		pFirstCellLayer->setIsRelativeAnchorPoint(true);
		pFirstCellLayer->setAnchorPoint(CCPointZero);
		pFirstCellLayer->setPosition(CCPOINT_FIRST_CELL);
		pItemLayer->addChild(pFirstCellLayer);
		pFirstCellLayer->release();
	}
	
	pos ++;
	sprintf(nameStr, "%s%d", "pur_", pos);
	sprintf(goldNum, "%s%d", "pur_gold_", pos);

	sprintf(goldStr, "%s%s", pValuesUtil->getString(goldNum).c_str(), pValuesUtil->getString("pur_num").c_str());
	// Add first cell
	CCLayer *pSecondCellLayer = createListItemCell(
		pValuesUtil->getString(nameStr).c_str(),
		goldStr,
		iconStr.c_str(), 
		pValuesUtil->getString("pur_buy").c_str(), pos);
	if(pSecondCellLayer)
	{
		pSecondCellLayer->setIsRelativeAnchorPoint(true);
		pSecondCellLayer->setAnchorPoint(CCPointZero);
		pSecondCellLayer->setPosition(CCPOINT_SECOND_CELL);
		pItemLayer->addChild(pSecondCellLayer);
		pSecondCellLayer->release();
	}
	//pos ++;
	//sprintf(nameStr, "%s%d", "pur_", pos);
	//sprintf(goldStr, "%s%d", "pur_gold_", pos);
	//// Add first cell
	//CCLayer *pThirdCellLayer = createListItemCell(
	//	pValuesUtil->getString(nameStr).c_str(),
	//	pValuesUtil->getString(goldStr).c_str(),
	//	iconStr.c_str(), 
	//	pValuesUtil->getString("pur_buy").c_str(), pos);
	//pThirdCellLayer->setIsRelativeAnchorPoint(true);
	//pThirdCellLayer->setAnchorPoint(CCPointZero);
	//pThirdCellLayer->setPosition(CCPOINT_THIRD_CELL);
	//pItemLayer->addChild(pThirdCellLayer);
    
    return pItemLayer;
}

CCLayer * PurchaseView::createListItemCell(const char* nameStr, const char* goldStr, const char* iconStr, const char* buyStr, int tag )
{
	if(tag > 8)
	{
		return NULL;
	}

	CCLayer *pLayer = new CCLayer();
	if(!pLayer || !pLayer->init())
	{
		return NULL;
	}


	pLayer->setContentSize(CCSIZE_ITEM_CELL);

	// Add background
	CCUIBackground *pBackground = new CCUIBackground();
	pBackground->initWithSpriteFrame("ui2.png", CCPointZero, CCPointZero, CCSIZE_ITEM_CELL);
	pLayer->addChild(pBackground);
	//Doyang 20120712
	pBackground->release();

	// Add name
	CCLabelTTF* pNameLabel = CCLabelTTF::labelWithString(nameStr, 
		CCSizeMake(POSX(120), POSX(22)),
		CCTextAlignmentLeft,
		"Arial",
		POSX(22));
	pNameLabel->setColor(ccc3(255, 255, 0));
	pNameLabel->setPosition( CCPOINT_CELL_NAME);
	pNameLabel->setAnchorPoint( CCPointZero );
	pNameLabel->setIsRelativeAnchorPoint(true);
	pLayer->addChild(pNameLabel);

	// Add icon
	CCSprite *pIconSprite = CCSprite::spriteWithSpriteFrameName(iconStr);
	if(pIconSprite)
	{
		pIconSprite->setAnchorPoint(CCPointZero);
		pIconSprite->setPosition(CCPOINT_CELL_ICON);
		pLayer->addChild(pIconSprite);
	}
    
    char pIconPath[128];
    sprintf(pIconPath, "purchase/icon_type_%d.png", tag);
    CCSprite *pIcon = CCSprite::spriteWithSpriteFrameName(pIconPath);
    if(pIcon)
    {
		pIcon->setAnchorPoint(CCPointZero);
		pIcon->setPosition(ccpAdd(CCPOINT_CELL_ICON, ccp(POSX(3), POSX(3))));
		pLayer->addChild(pIcon);
    }

	// Add buy button
	{
		
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		if(pNormalSprite && pPressedSprite)
		{
			CCMenuItemSprite *pBuyMenuItem = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this,
				menu_selector(PurchaseView::onBuyButtonClick) );
			pBuyMenuItem->setScaleX(SCALE_BUY_BTN);
			pBuyMenuItem->setAnchorPoint(CCPointZero);
			pBuyMenuItem->setTag(tag);
			pBuyMenuItem->setPosition( CCPOINT_CELL_BUY_BTN );
			CCMenu* pBuyMenu = CCMenu::menuWithItems(pBuyMenuItem, NULL);
			pBuyMenu->setPosition( CCPointZero );
			pBuyMenu->setTouchLayer(TLE::WindowLayer_PurchaseView - 1);
			pLayer->addChild(pBuyMenu);
		}
		
	}

	// Add buy text
	CCLabelTTF *pMenuLabel = CCLabelTTF::labelWithString(buyStr,
		CCSizeMake(POSX(80), POSX(20)),
		CCTextAlignmentLeft,
		"Arial",
		POSX(20));
	pMenuLabel->setColor(ccc3(255, 255, 0));
	pMenuLabel->setAnchorPoint(CCPointZero);
	pMenuLabel->setPosition( CCPOINT_CELL_BUY_TEXT );
	pLayer->addChild(pMenuLabel, 1);

	// Add gold text
	CCLabelTTF *pGoldLabel = CCLabelTTF::labelWithString(goldStr,
		CCSizeMake(POSX(150), POSX(28)),
		CCTextAlignmentCenter,
		"Arial", 
		POSX(26));
	pGoldLabel->setColor(ccc3(255, 255, 255));
	pGoldLabel->setAnchorPoint(CCPointZero);
	pGoldLabel->setPosition( CCPOINT_CELL_GOLD );
	pLayer->addChild(pGoldLabel);

    return pLayer;
}

bool PurchaseView::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return false;
}

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
void PurchaseView::onBuyProductFailed(const char *pProductIdentify)
{
    _isPaymentReturn = true;
    /*CCMessageBox("����ʧ��", "������");*/
}

void PurchaseView::onBuyProductSuccess(const char *pProductIdentify)
{
    _isPaymentReturn = true;
    /*CCMessageBox("����ɹ�", "������");*/
}
#endif

