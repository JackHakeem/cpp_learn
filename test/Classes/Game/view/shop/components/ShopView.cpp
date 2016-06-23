#include "ShopView.h"
#include "model/shop/ShopManage.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "manager/PopManage.h"
#include "CCUIBackground.h"
#include "manager/GlobalManage.h"
#include "ShopUIPartialScrollView.h"
#include "manager/GlobalManage.h"
#include "manager/LayerManager.h"
#include "manager/OverPanelManage.h"
#include "ShopCreate.h"
#include "ShopGoods.h"
#include "utils/TipHelps.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"
#include "manager/ViewManager.h"
#include "../ShopMediator.h"

USING_NS_CC;

/*
Doyang
-------------------------
  2px     2px
    ------     ------  
   |      |   |      |   
   |444px |   |      |   
   |      |   |      |   
    ------     ------    

-------------------------
*/

ShopView::ShopView()
{
	_pagesize = 15;
	//LayerManager::tipsLayer->setLastItemGID(NONEINT);
	_selectFrameShow = false;
}

ShopView::~ShopView()
{
	if (g_pShopCreate)
	{
		g_pShopCreate->removeAllLayer();
		g_pShopCreate->removeFromParentAndCleanup(true);
		g_pShopCreate = 0;
	}

	if(ViewManager::getInstance()->bagView
		&& ViewManager::getInstance()->bagView->getisPop())
	{

	}
	else
	{
		//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/icon/res_icon.plist"); 
		//CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/icon/res_icon.pvr.ccz");
	}
}

void ShopView::removeDataObjectChild()
{
	if (ViewManager::getInstance()->_shopView)
	{
		ViewManager::getInstance()->_shopView = 0;
	}

	ShopMediator * pM = (ShopMediator * )g_pFacade->retrieveMediator(AppFacade_SHOP_PROXY_CHANGE);
	if (pM)
	{
		pM->_shopView = 0;
	}
	
}

bool ShopView::init()//not set bagview coord，keeping 0，0
{
	if (!CCLayer::init())
	{
		return false;
	}
	//start dispatcher
	//dispatcher = GameDispatcher::getInstance();
	//start key
	key = PopEventName::SHOP;
	//start coord
	preTouchPoint = ccp(0,0);
	currentTouchPoint = ccp(0,0);
	//can touch
	this->setIsTouchEnabled(true);

	//set touch start state
	//setTouchState(TouchState_0);
	//update fun
	//scheduleUpdate();
	//schedule(schedule_selector(BagView::step), 0.1f);
	//
	//CCSize winSizePixels = CCDirector::sharedDirector()->getWinSizeInPixels();

	m_viewSize = CCSizeMake(POSX(448), /*POSX(628)*/CCDirector::sharedDirector()->getWinSize().height);

	//bg
	__container = new LayerNode();
	if (__container)
	{
		__container->setAnchorPoint(CCPointZero);
		__container->setPosition(POS(ccp(0, 12), ScaleUtil::TOP_LEFT));
		/*CCLayerColor *pTestLayer = CCLayerColor::layerWithColorWidthHeight(ccc4(255, 0, 0, 128),
		m_viewSize.width,
		m_viewSize.height);
		pTestLayer->setAnchorPoint(CCPointZero);
		pTestLayer->setPosition(CCPointZero);
		__container->addChild(pTestLayer);*/
		this->addChild(__container,0);
		__container->release(); //LH20120111
	}


	//
	//SpriteNode* _bagContainer = new SpriteNode();
	//_bagContainer->initWithFile("assets/ui/pack/_bagContainer.png");	//_bagContainer
	//_bagContainer->setIsRelativeAnchorPoint(true);
 //   _bagContainer->setAnchorPoint(ccp(0,0));
	//__container->addChild(_bagContainer,RENDERZ_bagContainer);
	//m_viewSize = _bagContainer->getTexture()->getContentSize();
	//_bagContainer->release();

	//title
	{
		SpriteNode* titleSp = new SpriteNode();
		titleSp->initWithSpriteFrameName("shop/title.png");
		titleSp->setPosition(ccp(POSX(220), POSX(540)));
		__container->addChild(titleSp, RENDERZ_title);
	}
	//
	CCUIBackground* _bagContainer = new CCUIBackground();
	_bagContainer->initWithSpriteFrame("ui2.png", 
		ccp(0, POSX(78)),
		ccp(0,0),
		CCSizeMake(POSX(444),POSX(454)));//CCSizeMake(rowMaxFontCount/2*fontSize, rowcount*rowHeight)
	__container->addChild(_bagContainer, RENDERZ_shopContainer);
	//m_viewSize = _bagContainer->getContentSize();
	_bagContainer->release();

	//
	//CCUIBackground* bg = new CCUIBackground();
	////float bg_x = (sitNum%2)?16:16+206;
	////float bg_y = 500 - (sitNum/2+1)*(this->getContentSize().height + 24) - 20;
	//bg->initWithSpriteFrame("ui2.png", ccp(20, 14), ccp(0,0),  CCSizeMake(m_viewSize.width - 40, m_viewSize.height - 52));//CCSizeMake(rowMaxFontCount/2*fontSize, rowcount*rowHeight)
	//__container->addChild(bg, RENDERZ_shopbg);
	//bg->release();

	//
//	float goldlinexoffet = 6;
	/*
	//
	SpriteNode* _leftGoldLine = new SpriteNode();
	_leftGoldLine->initWithFile("assets/ui/pack/goldline.png");	
	_leftGoldLine->setIsRelativeAnchorPoint(true);
    _leftGoldLine->setAnchorPoint(ccp(0,0));
	_leftGoldLine->setPosition(ccp(goldlinexoffet,0));
	__container->addChild(_leftGoldLine, RENDERZ_goldline);
	_leftGoldLine->release();

	//
	SpriteNode* _rightGoldLine = new SpriteNode();
	_rightGoldLine->initWithFile("assets/ui/pack/goldline.png");	
	_rightGoldLine->setIsRelativeAnchorPoint(true);
    _rightGoldLine->setAnchorPoint(ccp(0,0));
	__container->addChild(_rightGoldLine, RENDERZ_goldline);
	float goldlinewight = _rightGoldLine->getTexture()->getContentSize().width;
	_rightGoldLine->setPosition(ccp(m_viewSize.width - goldlinewight-6, 0));
	_rightGoldLine->release();
	*/
	

	//
 /*   CCMenuItemImage *_btnClose = CCMenuItemImage::itemFromNormalImage(
		"assets/ui/pack/ui/btnClose", 
		"assets/ui/pack/_btnClose1.png", 
		this, 
		menu_selector(ShopView::clickCloseHandler) );
	_btnClose->setPosition( ccp(m_viewSize.width-8, m_viewSize.height-30) );
	//__container
	CCMenu *buttonMenu = CCMenu::menuWithItems(_btnClose, NULL);
    buttonMenu->setPosition( CCPointZero );
//	_btnClose->setPosition( ccp(m_viewSize.width-8, m_viewSize.height+10) );

	__container->addChild(buttonMenu, RENDERZ_buttonMenu);*/

	//
	//__container->setPosition(ccp((winSizePixels.width-m_viewSize.width)/2, 
	//							 (winSizePixels.height-m_viewSize.height)/2));
	//__container->setPosition(ccp(0, 0));
	__container->setContentSize(m_viewSize);
	this->setContentSize(CCSizeMake(m_viewSize.width, m_viewSize.height));//+_btnClose->getContentSize().width/2
	setPopContentSize(m_viewSize);
	//this->setPosition(ccp((winSizePixels.width-m_viewSize.width)/2, 
	//							 (winSizePixels.height-m_viewSize.height)/2));

	//g_pShopCreate
	if (!g_pShopCreate)
	{
		ShopCreate *scrollView = ShopCreate::shopScrollViewWithCCRect(CCRectMake(POSX(6), POSX(40), POSX(436), m_viewSize.height));

		//
		//int pagecount = (int)ceil((double)BANKMAXGRID/BANK_ITEM_COUNT_PER_PAGE);
		//for (int i = 0; i < pagecount; i++)
		//{
		//	scrollView->addLayerByTag(i);
		//}

		g_pShopCreate =scrollView;

		__container->addChild(g_pShopCreate,RENDERZ_g_pShopCreate);

		//LH20120108
		g_pShopCreate->release();
	}

	return true;
}

void ShopView::createList(int32 shopId, int32 page)
{
	_shopId = shopId;
	_shopGoods = g_pShopManage->getGoodsByShopId(shopId);
	if (_shopGoods)
	{
		int32 length = _shopGoods->size();
		_totalPage = length/_pagesize + 1;
		resetPage(page);
	}
}

ShopGoods* ShopView::getCurSelectedShopGoods(CCPoint p)
{
	p = ccpSub(p, this->getPosition());
	p = ccpSub(p, g_pShopCreate->getPosition());
	p = ccpSub(p, __container->getPosition());

	ShopGoods* shopGoods = 0;
	shopGoods = g_pShopCreate->getCurSelectedShopGoods(p);//touchbegan里面设置的preTouchPoint
	if (!shopGoods)
		return 0;
	//int tag = shopGoods->getTag();
	return shopGoods;	
}

//CC_PROPERTY(bool, _selectFrameShow, SelectFrameShow)
bool ShopView::getSelectFrameShow()
{
	return _selectFrameShow;
}


void ShopView::setSelectFrameShow(bool var)
{
	//if (_selectFrameShow == var)
	//	return;

	if (var)
	{
		ShopGoods* shopGoods = (ShopGoods*)__container->getChildByTag(RENDERTAG_select);
		if (shopGoods)
			__container->removeChildByTag(RENDERTAG_select, true);

		shopGoods = getCurSelectedShopGoods(preTouchPoint);//touchbegan里面设置的preTouchPoint
		if (!shopGoods)
			return;
		LayerManager::tipsLayer->setLastItemGID(shopGoods->getMyFocusGID());// = shopGoods->getTag();
		CCPoint tarpos = shopGoods->getBgPos();
		CCPoint tarItemBgpos = shopGoods->getItemBgPos();
		SpriteNode* pSelect = new SpriteNode();
		pSelect->initWithSpriteFrameName("pack/select.png");
		pSelect->setAnchorPoint(CCPointZero);
		__container->addChild(pSelect, RENDERZ_select ,RENDERTAG_select);
		pSelect->release();
		pSelect->setPosition(ccpAdd(ccp(tarpos.x, tarpos.y),
			g_pShopCreate->getPosition()));

		_selectFrameShow = var;
	}
	else
	{
		ShopGoods* shopGoods = (ShopGoods*)__container->getChildByTag(RENDERTAG_select);
		if (shopGoods)
			__container->removeChildByTag(RENDERTAG_select, true);

		_selectFrameShow = var;
	}
}

/**
*
* @param page
* 
*/		
void ShopView::resetPage(int32 page)
{
	_curPage = page;
	//pageLayout();

	g_pShopCreate->createGood(_shopGoods,page,_pagesize);
}

//begin

void ShopView::registerWithTouchDispatcher()
{
   // CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
}

void ShopView::onEnter()
{
	this-> setIsTouchEnabled (true);
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_Shop, true);
	CCLayer::onEnter();
}

void ShopView::onExit()
{
	this-> setIsTouchEnabled (false);
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}	

CCRect ShopView::rect()
{
	return CCRectMake(__container->getPosition().x,__container->getPosition().y,
		m_viewSize.width, m_viewSize.height);
}


bool ShopView::containsTouchLocation(CCPoint touchPoint)
{
	CCRect contentLayerRect = CCRectZero;
	contentLayerRect.origin = this->getPosition();
	contentLayerRect.size = this->getContentSize();
	return CCRect::CCRectContainsPoint(contentLayerRect, touchPoint);
	////return CCRect::CCRectContainsPoint(rect(), convertTouchToNodeSpaceAR(touch));
	//CCPoint nodeSpaceLocation = this->convertTouchToNodeSpace(touch);

 //   CCRect contentLayerRect = CCRectZero;
 //   contentLayerRect.origin = CCPointZero;
 //   contentLayerRect.size = m_viewSize;//contentLayer->getContentSize();

 //   return CCRect::CCRectContainsPoint(contentLayerRect, nodeSpaceLocation);
}


bool ShopView::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	//
	//setTouchState(TouchState_0);
	//
	CCPoint locationInView = touch->locationInView(touch->view());
    preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
	//
	if (g_pGlobalManage->getCurFocusGID() != LayerManager::windowLayer->getMyFocusGID())//windowLayer
	{
		setSelectFrameShow(false);
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
		return false;
	}
	/*
	if (OVER_0_NONE == LayerManager::windowLayer->getCurNodeTag(preTouchPoint))
	{//touch the area out
		clickCloseHandler(0);
		return false;
	}
	*/
	if (g_pShopCreate && g_pShopCreate->getIsTouchInContentLayer(touch) ) 
	{
		ShopGoods* shopGoods = getCurSelectedShopGoods(preTouchPoint);//touchbegan里面设置的preTouchPoint
		if (shopGoods && shopGoods->getTag() == LayerManager::tipsLayer->getLastItemGID())
		{
			LayerManager::tipsLayer->setLastItemGID(NONEINT);
			setSelectFrameShow(false);
			LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
		}
		else
		{
			setSelectFrameShow(true);
			LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);		
		}


		//setTouchState(TouchState_1);
		return g_pShopCreate->ccTouchBegan(touch, event);
		
	}

	setSelectFrameShow(false);
	LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
	return false;
}

void ShopView::ccTouchMoved(CCTouch* touch, CCEvent* event)
{	
	setSelectFrameShow(false);
	//
	CCPoint locationInView = touch->locationInView(touch->view());
    currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	g_pShopCreate->ccTouchMoved(touch, event);
	/*
	//
	int diaotaX = abs(currentTouchPoint.x - preTouchPoint.x);
	//
	if (g_pShopCreate)// && _pBankCreate->getIsScrolling()
	{
		//
		switch(getTouchState())
		{
		case TouchState_1:
			if (diaotaX > BAGVIEW_TOUCH_DIAOTAX)
				setTouchState(TouchState_3);//
			break;
		case TouchState_2:
			setTouchState(TouchState_4);//
			break;
		default:
			break;
		}

		if (getTouchState() == TouchState_3)
		{
			g_pShopCreate->ccTouchMoved(touch, event);
		}
		else if (getTouchState() == TouchState_5)
		{
			CCPoint dstp = currentTouchPoint;
			dstp = ccp(currentTouchPoint.x, currentTouchPoint.y);
			
			if (m_pCurSelectedBankGoods)
			{
				CCPoint p = currentTouchPoint;
				//CCPoint __containerPosition = __container->getPosition();
				//p = ccp(p.x-__containerPosition.x, p.y-__containerPosition.y);
				m_pCurSelectedBankGoods->onMouseMoveHnadler(ccp(currentTouchPoint.x - preTouchPoint.x, currentTouchPoint.y - preTouchPoint.y));
			}
		}
	}
	*/

	//
	preTouchPoint = currentTouchPoint;
}

void ShopView::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	//if (!g_pShopCreate->getIsScrolling())
	//	setSelectFrameShow(false);

	if (LayerManager::tipsLayer->getLastItemGID() == -1)
	{
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
	}
	else if (!g_pShopCreate->getIsTouchingMoving())//getSelectFrameShow()
	{//显示道具信息框
		ShopGoods* shopGoods = getCurSelectedShopGoods(preTouchPoint);//touchbegan里面设置的preTouchPoint
		if (!shopGoods)
			return;

		shopGoods->myTip->rollOverHander();	
		//bagGoods->myTip->rollOverHander();				
	}

	CCPoint locationInView = touch->locationInView(touch->view());
    currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	g_pShopCreate->ccTouchEnded(touch, event);
} 
