#include "BagView.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "BagCreate.h"
#include "BagUIPartialScrollView.h"
#include "manager/GlobalManage.h"
#include "manager/LayerManager.h"
#include "manager/OverPanelManage.h"
#include "Alert.h"
#include "utils/TipsEquipCanvas.h"
#include "manager/PopEventName.h"
#include "manager/PopManage.h"
#include "model/backpack/GoodsManager.h"
#include "CCUIBackground.h"
#include "events/GameDispatcher.h"
#include "CCUIBackground.h"
#include "Confirm.h"
#include "model/player/RoleManage.h"
#include "model/player/vo/AccountInfoVo.h"
#include "utils/ValuesUtil.h"
#include "utils/TipHelps.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"
#include <cmath>
#include "manager/CDManage.h"
#include "manager/LangManager.h"
#include "manager/ViewManager.h"
#include "manager/VIPLimitConst.h"
#include "manager/VIPMgr.h"
#include "MessageInfoBox.h"

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
const int TAG_PARENT_LAYER = 1001;
BagView::BagView()
{
	m_pCurSelectedBagGoods = 0;
	_selectFrameShow = false;
	lastZhengliTime = 0;
	//LayerManager::tipsLayer->setLastItemGID(NONEINT);
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/res_icon.plist");
}

BagView::~BagView()
{
	if (g_pBagCreate)
	{
		g_pBagCreate->removeAllLayer();
		g_pBagCreate->removeFromParentAndCleanup(true);
		g_pBagCreate = 0;
	}
	ViewManager::getInstance()->bagView = 0;
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/icon/res_icon.plist");
	//CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/icon/res_icon.pvr.ccz");
}

void BagView::removeDataObjectChild()
{
	if (ViewManager::getInstance()->bagView)
	{
		ViewManager::getInstance()->bagView = 0;
	}
	BagMediator * pM = (BagMediator *)g_pFacade->retrieveMediator(AppFacade_BAG_PROXY_CHANGE);
	if (pM)
	{
		pM->_bagView = 0;
	}
}

int32 BagView::getSelfTag() 
{return OVER_7_BAG_ITEM;}

bool BagView::init()//Don't set bagview coordinates, and always maintain the0，0
{
	if (!CCLayer::init())
	{
		return false;
	}
	// initialization dispatcher
	dispatcher = GameDispatcher::getInstance ();
	// initialization key
	key = PopEventName::BAG;
	// initial touch coordinates
	preTouchPoint = ccp (0, 0);
	currentTouchPoint = ccp (0, 0);
	// that can be touch
	this-> setIsTouchEnabled (true);
	// set this coordinates
	// set touch initial condition
	setTouchState (TouchState_0);
	// set touch update function
	scheduleUpdate ();
	schedule (schedule_selector (BagView::step), 0.1f);
	// screen resolution
	//CCSize winSizePixels = CCDirector::sharedDirector ()-> getWinSizeInPixels ();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	m_viewSize = CCSizeMake(POSX(448), /*POSX(628)*/CCDirector::sharedDirector()->getWinSize().height);

	// background layer
	__container = new LayerNode();
	if (__container)
	{
		__container->setTag(TAG_PARENT_LAYER);
		__container->setAnchorPoint(CCPointZero);
		__container->setPosition(POS(ccp(0, 12), ScaleUtil::TOP_LEFT));

		/*CCLayerColor *pTestLayer = CCLayerColor::layerWithColorWidthHeight(ccc4(255, 0, 0, 128),
		m_viewSize.width,
		m_viewSize.height);
		pTestLayer->setAnchorPoint(CCPointZero);
		pTestLayer->setPosition(CCPointZero);
		__container->addChild(pTestLayer);*/
		this->addChild(__container,0);
		__container->release(); //LH20130111
	}
	//背景图
	//SpriteNode* _bagContainer = new SpriteNode();
	//_bagContainer->initWithFile("assets/ui/pack/_bagContainer.png");	//_bagContainer
	//_bagContainer->setIsRelativeAnchorPoint(true);
 //   _bagContainer->setAnchorPoint(ccp(0,0));
	//__container->addChild(_bagContainer,RENDERZ_bagContainer);
	//m_viewSize = _bagContainer->getTexture()->getContentSize();//??????????VIEW??
	//_bagContainer->release();

	CCUIBackground* _bagContainer = new CCUIBackground();
	_bagContainer->initWithSpriteFrame("ui2.png", 
		ccp(POSX(2), POSX(78)),
		ccp(0,0),
		CCSizeMake(POSX(444),POSX(454)));//CCSizeMake(rowMaxFontCount/2*fontSize, rowcount*rowHeight)
	__container->addChild(_bagContainer, RENDERZ_bagContainer);
	//464 550;
	_bagContainer->release();
	//Gold thread trimming X coordinate values
	//float goldlinexoffet = 6;
	/*
	//Left gold line
	SpriteNode* _leftGoldLine = new SpriteNode();
	_leftGoldLine->initWithFile("assets/ui/pack/goldline.png");	
	_leftGoldLine->setIsRelativeAnchorPoint(true);
    _leftGoldLine->setAnchorPoint(ccp(0,0));
	_leftGoldLine->setPosition(ccp(goldlinexoffet,0));
	__container->addChild(_leftGoldLine, RENDERZ_goldline);
	_leftGoldLine->release();

	//Right gold line
	SpriteNode* _rightGoldLine = new SpriteNode();
	_rightGoldLine->initWithFile("assets/ui/pack/goldline.png");	
	_rightGoldLine->setIsRelativeAnchorPoint(true);
    _rightGoldLine->setAnchorPoint(ccp(0,0));
	__container->addChild(_rightGoldLine, RENDERZ_goldline);
	float goldlinewight = _rightGoldLine->getTexture()->getContentSize().width;
	_rightGoldLine->setPosition(ccp(m_viewSize.width - goldlinewight-6, 0));
	_rightGoldLine->release();
	*/

	

		

	
	//Remote warehouse
	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
	if(!pNormalSprite || !pPressedSprite)
	{
		return false;
	}
	CCMenuItemSprite *	_btnFarBank = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite,
		pPressedSprite, 
		this, 
		menu_selector(BagView::onClickFarBank) );
	_btnFarBank->setPosition(ccp(POSX(10), POSX(28)));
	_btnFarBank->setAnchorPoint(CCPointZero);

	//_btn_check->setScaleX(0.8f);//规模

	CCSprite *pNormalSprite1 = CCSprite::spriteWithSpriteFrameName("button.png");
	CCSprite *pPressedSprite1 = CCSprite::spriteWithSpriteFrameName("button1.png");
	if(!pNormalSprite1 || !pPressedSprite1)
	{
		return false;
	}
	CCMenuItemSprite *	_btnZhengli = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite1,
		pPressedSprite1,
		this, 
		menu_selector(BagView::onClickSort) );
	_btnZhengli->setPosition(ccp(POSX(160), POSX(28)));
	_btnZhengli->setAnchorPoint(CCPointZero);
	
	//Remote store
	CCSprite *pNormalSprite2 = CCSprite::spriteWithSpriteFrameName("button.png");
	CCSprite *pPressedSprite2 = CCSprite::spriteWithSpriteFrameName("button1.png");
	if(!pNormalSprite2 || !pPressedSprite2)
	{
		return false;
	}
	CCMenuItemSprite *	_btnFarShop = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite2,
		pPressedSprite2, 
		this, 
		menu_selector(BagView::onClickFarShop) );
	_btnFarShop->setPosition(ccp(POSX(310), POSX(28)));
	_btnFarShop->setAnchorPoint(CCPointZero);

	//
	CCMenu *buttonMenu = CCMenu::menuWithItems(_btnFarBank, _btnFarShop, _btnZhengli,NULL);//_btnClose, 
    buttonMenu->setPosition( CCPointZero );
	buttonMenu->setTouchLayer(TLE::WindowLayer_Bag-2);

	__container->addChild(buttonMenu, RENDERZ_buttonMenu, 1001);
	//字符串
	CCLabelTTF* pLable_btnFarBank = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("BAG001").c_str(), 
		CCSizeMake(POSX(200), POSX(20)),
		CCTextAlignmentCenter,
		"Arial", 
		POSX(20));
	pLable_btnFarBank->setPosition(
		ccp(_btnFarBank->getContentSize().width / 2,
		_btnFarBank->getContentSize().height / 2));
	_btnFarBank->addChild(pLable_btnFarBank, 2);
	pLable_btnFarBank->setColor(ccc3(254, 189, 0));

	CCLabelTTF* pLable_btnFarShop = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("BAG002").c_str(), 
		CCSizeMake(POSX(200), POSX(20)),
		CCTextAlignmentCenter, 
		"Arial", 
		POSX(20));
	pLable_btnFarShop->setPosition(
		ccp(_btnFarShop->getContentSize().width / 2,
		_btnFarShop->getContentSize().height / 2));
	_btnFarShop->addChild(pLable_btnFarShop, 2);
	pLable_btnFarShop->setColor(ccc3(254, 189, 0));

	CCLabelTTF* pLable_btnZhengli = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("BAG011").c_str(), 
		CCSizeMake(POSX(200), POSX(20)),
		CCTextAlignmentCenter, 
		"Arial", 
		POSX(20));
	pLable_btnZhengli->setPosition(
		ccp(_btnZhengli->getContentSize().width / 2,
		_btnZhengli->getContentSize().height / 2));
	_btnZhengli->addChild(pLable_btnZhengli, 2);
	pLable_btnZhengli->setColor(ccc3(254, 189, 0));

	//Set full screen center, 00 in the bottom left corner
	//__container->setPosition(ccp((winSizePixels.width-m_viewSize.width)/2, 
	//							 (winSizePixels.height-m_viewSize.height)/2));
	//__container->setPosition(ccp(0, 0));
	__container->setContentSize(m_viewSize);
	this->setContentSize(CCSizeMake(POSX(448), POSX(628)));//+_btnClose->getContentSize().width/2
	setPopContentSize(m_viewSize);
	//this->setPosition(ccp((winSizePixels.width-m_viewSize.width)/2, 
	//							 (winSizePixels.height-m_viewSize.height)/2));


	return true;
}

void BagView::reinit()
{
	//
	setTouchState(TouchState_0);
	//????????
	//scheduleUpdate();
	schedule(schedule_selector(BagView::step), 0.1f);	
}

/**
	* Open backpack
	* 
	*/		
void BagView::OpenBag(std::map<int32, GoodsInfo*>& goodDic, int32 noEmpty, uint32 goodsNum)
{
	if (!g_pBagCreate)
	{
		BagCreate *scrollView = BagCreate::bagScrollViewWithCCRect(CCRectMake(POSX(6), POSX(40), POSX(436), m_viewSize.height));//430 430
		scrollView->m_pri = TLE::WindowLayer_Bag-1;
		//
		int pagecount = (int)ceil((double)BAGMAXGRID/BACKPACK_ITEM_COUNT_PER_PAGE);
		for (int i = 0; i < pagecount; i++)
		{
			scrollView->addLayerByTag(i);
		}

		g_pBagCreate =scrollView;

		__container->addChild(g_pBagCreate,RENDERZ_g_pBagCreate);

		//LH20120108
		g_pBagCreate->release();
	}
	
	
	_capacity = goodsNum;
	_noEmpty = noEmpty;			
	g_pBagCreate->creatGood(goodDic, goodsNum);
//	layout();	
}




//touch begin

void BagView::registerWithTouchDispatcher()
{
 //   CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_Bag, true);
}

CCRect BagView::rect()
{
	return CCRectMake(__container->getPosition().x,__container->getPosition().y,
		m_viewSize.width, m_viewSize.height);
}

void BagView::onEnter()
{
	this-> setIsTouchEnabled (true);
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_Bag-2, true);
	CCLayer::onEnter();
}

void BagView::onExit()
{
	this-> setIsTouchEnabled (false);
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}	

bool BagView::containsTouchLocation(CCPoint touchPoint)
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


bool BagView::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	//
	setTouchState(TouchState_0);
	//
	CCPoint locationInView = touch->locationInView(touch->view());
    preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
	//TIPS?????
	LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
	//
	if (g_pGlobalManage->getCurFocusGID() != LayerManager::windowLayer->getMyFocusGID())//The current need windowLayer focus
	{
		//LayerManager::tipsLayer->setLastItemGID(NONEINT);
		LayerManager::tipsLayer->setLastItemGID(NONEINT);
		return false;
	}
	/*
	if (OVER_0_NONE == LayerManager::windowLayer->getCurNodeTag(preTouchPoint))
	{//touch the area out
		clickCloseHandler(0);
		return false;
	}
	*/

	if (g_pBagCreate && g_pBagCreate->getIsTouchInContentLayer(touch) ) 
	{
		setSelectFrameShow(true);
		
		setTouchState(TouchState_1);
		return g_pBagCreate->ccTouchBegan(touch, event);
	}
	
	LayerManager::tipsLayer->setLastItemGID(NONEINT);
	return false;
}

void BagView::ccTouchMoved(CCTouch* touch, CCEvent* event)
{	
	setSelectFrameShow(false);
	//
	CCPoint locationInView = touch->locationInView(touch->view());
    currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
	//XCoordinate crane tower limit, too small think didn't move
	int diaotaX = abs(currentTouchPoint.x - preTouchPoint.x);
	//
	if (g_pBagCreate)// && g_pBagCreate->getIsScrolling()
	{
		//Confirm what state is
		switch(getTouchState())
		{
		case TouchState_1:
			if (diaotaX > BAGVIEW_TOUCH_DIAOTAX)
				setTouchState(TouchState_3);//Identify the backpack to scroll mode
			break;
		case TouchState_2:
			setTouchState(TouchState_4);//Confirmation is what all not stem mode
			break;
		default:
			break;
		}

		if (getTouchState() == TouchState_3)
		{
			g_pBagCreate->ccTouchMoved(touch, event);
		}
		else if (getTouchState() == TouchState_5)
		{
			CCPoint dstp = currentTouchPoint;
			dstp = ccp(currentTouchPoint.x, currentTouchPoint.y);
			
			if (m_pCurSelectedBagGoods)
			{
				CCPoint p = currentTouchPoint;
				//CCPoint __containerPosition = __container->getPosition();
				//p = ccp(p.x-__containerPosition.x, p.y-__containerPosition.y);
				m_pCurSelectedBagGoods->onMouseMoveHnadler(ccp(currentTouchPoint.x - preTouchPoint.x, currentTouchPoint.y - preTouchPoint.y));
			}
		}
	}

	//
	preTouchPoint = currentTouchPoint;
}

void BagView::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	setSelectFrameShow(false);

	CCPoint locationInView = touch->locationInView(touch->view());
    currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	if (g_pBagCreate)// && g_pBagCreate->getIsScrolling()
	{
		if (getTouchState() == TouchState_1)
		{//
			setTouchState(TouchState_6);
			//Detection met which backpack BagGood grid
			BagGoods* bagGoods = 0;
			bagGoods = getCurSelectedBagGoods(currentTouchPoint);//touchbegan Inside the preTouchPoint set
			//Display props information box
			if (bagGoods)
			{
				if (!bagGoods->_lock)
				{//???????
					if (bagGoods->myInfo->id > 0)
					{//??????
						if (LayerManager::tipsLayer->getLastItemGID() == bagGoods->getTag())
						{
							LayerManager::tipsLayer->setLastItemGID(NONEINT);
						}//LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
						else
						{
							bagGoods->myTip->rollOverHander();	

							LayerManager::tipsLayer->setLastItemGID(bagGoods->getMyFocusGID());
						}
						//setSelectFrameShow(true);
					}
				}
				else
				{//选中锁框，是否付费打开框
					onClickHandler(bagGoods);
					//Confirm* pConfirm = new Confirm();
					//pConfirm->initWithParam("你丫", this, menu_selector(BagView::handleBuyCell));
					//LayerManager::windowLayer->addChild(pConfirm,109);
				}
			}
		}
		if (getTouchState() == TouchState_3)
		{
			g_pBagCreate->ccTouchEnded(touch, event);
		}
		else if (getTouchState() == TouchState_5)
		{
			if (m_pCurSelectedBagGoods)
					m_pCurSelectedBagGoods->onMouseUpHnadler(currentTouchPoint);
		}
	}
	

	//Change to return without state
	setTouchState(TouchState_0);
} 

//单击增加容量按钮
void BagView::onClickHandler(BagGoods* bagGoods)
{
	if (!bagGoods)
		return;
	int32 index = bagGoods->getTag();
	int32 smoney = _capacity - 12 + 1;
	if (smoney > 10) smoney = 10;
	int32 num = index - _capacity + 1;
	int32 money = 0;

	for (int32 i = 0; i < num; i++)
	{
		if (smoney == 10 || smoney+i >= 10)
		{
			money += 10;
		}
		else
		{
			money += smoney + i;
		}
	}

	g_pBagCreate->setHeightLine(index, true);

	Confirm* pConfirm = new Confirm();
	tmp_num = num;
	tmp_money = money;
	tmp_sitNum = index;
	char str[80];
	sprintf(str, ValuesUtil::Instance()->getString("BB001").c_str(), money, num);//??????%d????%d???????
	std::string stdstr = str;
	UTF8(stdstr);
	pConfirm->initWithParam(stdstr.c_str(), this, menu_selector(BagView::handleBuyCellConfirm),menu_selector(BagView::handleBuyCellCancel));
	LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
	pConfirm->release();
}


//CC_PROPERTY(int32, _TouchState, TouchState)	
int32 BagView::getTouchState()
{
	return _TouchState;
}

void BagView::setTouchState(int32 var)
{
	_TouchState = var;
}

//CC_PROPERTY(bool, _selectFrameShow, SelectFrameShow)
bool BagView::getSelectFrameShow()
{
	return _selectFrameShow;
}

void BagView::setSelectFrameShow(bool var)
{
	//if (_selectFrameShow == var)
	//	return;

	if (var)
	{
		BagGoods* bagGoods = (BagGoods*)__container->getChildByTag(RENDERTAG_select);
		if (bagGoods)
			__container->removeChildByTag(RENDERTAG_select, true);

		bagGoods = getCurSelectedBagGoods(preTouchPoint);//touchbegan里面设置的preTouchPoint
		if (!bagGoods)
			return;

		//LayerManager::tipsLayer->getLastItemGID() = bagGoods->getTag();

		CCPoint tarpos = bagGoods->getPosition();
		SpriteNode* pSelect = new SpriteNode();
		pSelect->initWithSpriteFrameName("pack/select.png");
		__container->addChild(pSelect, RENDERZ_select ,RENDERTAG_select);
		pSelect->release();
		pSelect->setPosition(ccpAdd(ccp(tarpos.x, tarpos.y),
			g_pBagCreate->getPosition()));

		_selectFrameShow = var;
	}
	else
	{
		BagGoods* bagGoods = (BagGoods*)__container->getChildByTag(RENDERTAG_select);
		if (bagGoods)
			__container->removeChildByTag(RENDERTAG_select, true);

		_selectFrameShow = var;
	}
}

void BagView::step(ccTime dt)
{
	if (getTouchState() == TouchState_0)
	{
		m_fStepCounter = 0;
		return;
	}
	else if (getTouchState() == TouchState_1)
	{
		m_fStepCounter += dt;
		if (m_fStepCounter >= BAGVIEW_TOUCH_STATE1_INTERVAL)
		{
			//In the backpack in the window, the mouse is fixed, time to, convert the selected state
			setTouchState(TouchState_5);
			//Detection met which backpack BagGoods grid
			if (g_pBagCreate)
			{
	
				BagGoods* bagGoods = 0;
				bagGoods = getCurSelectedBagGoods(preTouchPoint);//touchbegan?????preTouchPoint
				if (!bagGoods)
					return;
				CCPoint b =bagGoods->getPosition();

				m_pCurSelectedBagGoods = 0;//Set empty
				if (!m_pCurSelectedBagGoods)
					m_pCurSelectedBagGoods = bagGoods;
				if (bagGoods)
				{//Click on to capture a props

					//p = preTouchPoint;
					m_pCurSelectedBagGoods->onMouseDownHandler(this->getPosition());
				}
			}
		}
	}	
}

//touch end

BagGoods* BagView::getCurSelectedBagGoods(CCPoint p)
{
	p = ccpSub(p, this->getPosition());
	p = ccpSub(p, g_pBagCreate->getPosition());
	p = ccpSub(p, __container->getPosition());

	BagGoods* bagGoods = 0;
	bagGoods = g_pBagCreate->getCurSelectedBagGoods(p);//Inside the preTouchPoint touchbegan set
	if (!bagGoods) 
		return 0;

	m_pCurSelectedBagGoods = bagGoods;//kevin0927
	//int tag = bagGoods->getTag();
	return bagGoods;
}

/**
	*Items information change, may be switched positions, delete, finishing
	* 
	*/		
void BagView::updateGoods(char* arr, int32 noEmpty)
{
	_noEmpty = noEmpty;
	g_pBagCreate->updateGoods(arr);
	//layout();
}

void BagView::onClickFarBank(CCObject* pSender)
{
	//if (!VIPMgr::Instance()->hasVIPFunc(VIPLimitConst::VIP_RemoteBank , RoleManage::Instance()->accountInfo()->vipLev()))
	//{
	//	char path[128] = {0};
	//	sprintf(path , ValuesUtil::Instance()->getString("WLC010").c_str() , VIPLimitConst::VIP_RemoteBank);
	//	MessageInfoBox::Instance()->show(path,ccc3(12,233,25));
	//	return;
	//}
	//if(RoleManage.getInstance().accountInfo.vipLev >= 1 || RoleManage.getInstance().accountInfo.trialVip)
	//{
		openFarBankOrShop(1);
	//}
	//else if(RoleManage.getInstance().accountInfo.gold < 2){
	//	Alert.show("??????,???????(??VIP1????????)");
	//}
	//else{
	//	Alert.show("????????2??(??VIP1????????)","", 1, openFarBankOrShop, null, null, null, type);
	//}	
}

void BagView::onClickFarShop(CCObject* pSender)
{
	//if (!VIPMgr::Instance()->hasVIPFunc(VIPLimitConst::VIP_RemoteShop , RoleManage::Instance()->accountInfo()->vipLev()))
	//{
	//	char path[128] = {0};
	//	sprintf(path , ValuesUtil::Instance()->getString("WLC010").c_str() , VIPLimitConst::VIP_RemoteShop);
	//	MessageInfoBox::Instance()->show(path,ccc3(12,233,25));
	//	return;
	//}
	//if(RoleManage.getInstance().accountInfo.vipLev >= 1 || RoleManage.getInstance().accountInfo.trialVip)
	//{
		openFarBankOrShop(2);
	//}
	//else if(RoleManage.getInstance().accountInfo.gold < 2){
	//	Alert.show("??????,???????(??VIP1????????)");
	//}
	//else{
	//	Alert.show("????????2??(??VIP1????????)","", 1, openFarBankOrShop, null, null, null, type);
	//}	
}

void BagView::onClickSort(CCObject* pSender)
{
	if (CDManage::Instance()->getServerTime() - lastZhengliTime > 4000)
	{
		lastZhengliTime = CDManage::Instance()->getServerTime();
		this->dispatchEvent(BAG_SORT_CLICK, 0);	
	}
	else
		LangManager::msgShow("BAG012");
	//if (wiatTime > 0)
	//{
	//	LangManager.msgShow("W0006");
	//	return;
	//}
	
	//wiatTime = setInterval(function():void
	//{
	//	clearInterval(wiatTime);
	//	wiatTime = 0;
	//}, sendGap);
}


void BagView::openFarBankOrShop(int32 type)
{
	bool isOp = false;
	if(type==1){
		if(!g_pPopManage->isViewPop(PopEventName::BANK)){
			int param = 0;
			dispatcher->dispatchEvent(PopEventName::SHOW_UI_BANK, &param);
			isOp = true;
		}
	}
	else{
		if(!g_pPopManage->isViewPop(PopEventName::SHOP)){
			int param = 1;
			dispatcher->dispatchEvent(PopEventName::SHOW_UI_SHOP, &param);
			isOp = true;
		}
	}
	if(isOp)
	{
		struct sdata
		{
			int32 UseType;
			int32 type;
		};
		sdata d;
		d.UseType = 10;
		d.type = type;
		
		dispatcher->dispatchEvent(GameDispatcher::PACK_CHANGE, &d);
	}
		
}

void BagView::handleBuyCellConfirm(CCObject* pSender)
{
	addGrid(tmp_num, tmp_money);
	//取消格子高亮
	g_pBagCreate->setHeightLine(tmp_sitNum, false);
	//remove自己
	Confirm* pConfirm = (Confirm*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pConfirm && pConfirm->getParent())
		pConfirm->getParent()->removeChild(pConfirm, true);
	return;
}

void BagView::handleBuyCellCancel(CCObject* pSender)
{
	//取消格子高亮
	g_pBagCreate->setHeightLine(tmp_sitNum, false);
	//remove自己
	Confirm* pConfirm = (Confirm*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pConfirm && pConfirm->getParent())
		pConfirm->getParent()->removeChild(pConfirm, true);
	return;
}

void BagView::addGrid(int32 num, int32 money)
{
	if (money >  RoleManage::Instance()->_accountInfo.gold())
	{
		//MsgManage.getInstance().showMsg(MsgManage.SYSTEM_MSG, "W0004");
		//return;
	}
	dispatchEvent(BAG_ADD_GRID_CLICK, &num);
}

void BagView::backHandlerByCurrentUIStage()
{}

CCNode * BagView::getNewHandItem( int sitNum )
{
	if(sitNum == -9 && __container)
	{
		return __container->getChildByTag(1001);
	}

	if(g_pBagCreate)
	{
		return g_pBagCreate->getBagGoods(sitNum);
	}

	return NULL;
}
