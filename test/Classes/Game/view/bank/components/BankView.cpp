#include "BankView.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "BankCreate.h"
#include "BankUIPartialScrollView.h"
#include "manager/GlobalManage.h"
#include "manager/LayerManager.h"
#include "manager/OverPanelManage.h"
#include "Alert.h"
#include "manager/PopEventName.h"
#include "model/backpack/GoodsManager.h"
#include "CCUIBackground.h"
#include "Confirm.h"
#include "model/player/RoleManage.h"
#include "model/player/vo/AccountInfoVo.h"
#include <cmath>
#include "utils/ValuesUtil.h"
#include "utils/TipHelps.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"
#include "manager/ViewManager.h"

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

BankView::BankView()
{
	m_pCurSelectedBankGoods = 0;
	_selectFrameShow = false;
	//LayerManager::tipsLayer->setLastItemGID(NONEINT);
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/res_icon.plist");
}

BankView::~BankView()
{
	//LH20120108
	if (g_pBankCreate)
	{
		g_pBankCreate->removeAllLayer();
		g_pBankCreate->removeFromParentAndCleanup(true);
		g_pBankCreate = 0;
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

void BankView::removeDataObjectChild()
{
	if (ViewManager::getInstance()->bankView)
	{
		ViewManager::getInstance()->bankView = 0;
	}
	
	BankMediator * pM = (BankMediator * )g_pFacade->retrieveMediator(AppFacade_BANK_PROXY_CHANGE);
	if (pM)
	{
		pM->_bankView = 0;
	}
	
}


int32 BankView::getSelfTag() 
{return OVER_7_BAG_ITEM;}

bool BankView::init()//Don't set bankview coordinates, and always maintain the0��0
{
	if (!CCLayer::init())
	{
		return false;
	}

	//Init key
	key = PopEventName::BANK;
	//Initial touch coordinates
	preTouchPoint = ccp(0,0);
	currentTouchPoint = ccp(0,0);
	//Make can be touch
	this->setIsTouchEnabled(true);
	//Set the coordinates
	//Set touch initial condition
	setTouchState(TouchState_0);
	//Set touch update function
	//scheduleUpdate();
	schedule(schedule_selector(BankView::step), 0.1f);
	//Screen resolution
	//CCSize winSizePixels = CCDirector::sharedDirector()->getWinSizeInPixels();
	//The background layer

	m_viewSize = CCSizeMake(POSX(448), /*POSX(628)*/CCDirector::sharedDirector()->getWinSize().height);

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
		__container->release(); //LH20130111
	}
	//Background picture
	//SpriteNode* _bankContainer = new SpriteNode();
	//_bankContainer->initWithFile("assets/ui/pack/_bagContainer.png");	//_bankContainer
	//_bankContainer->setIsRelativeAnchorPoint(true);
 //   _bankContainer->setAnchorPoint(ccp(0,0));
	//__container->addChild(_bankContainer,RENDERZ_bankContainer);
	//m_viewSize = _bankContainer->getTexture()->getContentSize();//With the size of the background picture decide this VIEW size
	//_bankContainer->release();

	//title
	{
		SpriteNode* titleSp = new SpriteNode();
		titleSp->initWithSpriteFrameName("bank/title.png");
		titleSp->setPosition(ccp(POSX(220), POSX(540)));
		__container->addChild(titleSp, RENDERZ_title);
	}
	//bg
	CCUIBackground* _bankContainer = new CCUIBackground();
	_bankContainer->initWithSpriteFrame("ui2.png", 
		ccp(0, POSX(78)),
		ccp(0,0),
		CCSizeMake(POSX(444),POSX(454)));//CCSizeMake(rowMaxFontCount/2*fontSize, rowcount*rowHeight)
	__container->addChild(_bankContainer, RENDERZ_bankContainer);
	//m_viewSize = _bankContainer->getContentSize();
	_bankContainer->release();
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

	//Set full screen center, 00 in the bottom left corner
	//__container->setPosition(ccp((winSizePixels.width-m_viewSize.width)/2, 
	//							 (winSizePixels.height-m_viewSize.height)/2));
	//__container->setPosition(ccp(0, 0));
	__container->setContentSize(m_viewSize);
	this->setContentSize(CCSizeMake(m_viewSize.width, m_viewSize.height));//+_btnClose->getContentSize().width/2
	setPopContentSize(m_viewSize);
	//this->setPosition(ccp((winSizePixels.width-m_viewSize.width)/2, 
	//							 (winSizePixels.height-m_viewSize.height)/2));


	return true;
}

void BankView::reinit()
{
	//Set touch initial condition
	setTouchState(TouchState_0);
	//Set touch update function
//	scheduleUpdate();
	schedule(schedule_selector(BankView::step), 0.1f);	
}

/**
	* Open bank 
	* 
	*/		
void BankView::OpenBank(std::map<int32, GoodsInfo*>& goodDic, int32 noEmpty, uint32 goodsNum)
{
	if (!g_pBankCreate)
	{
		BankCreate *scrollView = BankCreate::bankScrollViewWithCCRect(CCRectMake(POSX(6), POSX(40), POSX(436), m_viewSize.height));

		//
		int pagecount = (int)ceil((double)BANKMAXGRID/BANK_ITEM_COUNT_PER_PAGE);
		for (int i = 0; i < pagecount; i++)
		{
			scrollView->addLayerByTag(i);
		}

		g_pBankCreate =scrollView;

		__container->addChild(g_pBankCreate,RENDERZ_g_pBankCreate);

		//LH20120108
		g_pBankCreate->release();
	}
	
	
	_capacity = goodsNum;
	_noEmpty = noEmpty;			
	g_pBankCreate->creatGood(goodDic, goodsNum);
//	layout();	
}

//touch begin

void BankView::registerWithTouchDispatcher()
{

 //   CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 1, true);
}

void BankView::onEnter()
{
	this-> setIsTouchEnabled (true);
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_Bank, true);
	CCLayer::onEnter();
}

void BankView::onExit()
{
	this-> setIsTouchEnabled (false);
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}	

CCRect BankView::rect()
{
	return CCRectMake(__container->getPosition().x,__container->getPosition().y,
		m_viewSize.width, m_viewSize.height);
}


bool BankView::containsTouchLocation(CCPoint touchPoint)
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

bool BankView::ccTouchBegan(CCTouch* touch, CCEvent* event)
{

	//
	setTouchState(TouchState_0);
	//
	CCPoint locationInView = touch->locationInView(touch->view());
    preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
	//TIPS?????
	LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
	//
	if (g_pGlobalManage->getCurFocusGID() != LayerManager::windowLayer->getMyFocusGID())//????windowLayer??
	{
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

	if (g_pBankCreate && g_pBankCreate->getIsTouchInContentLayer(touch) ) 
	{
		setSelectFrameShow(true);
		setTouchState(TouchState_1);
		return g_pBankCreate->ccTouchBegan(touch, event);
		
	}
	
	LayerManager::tipsLayer->setLastItemGID(NONEINT);
	return false;
}

void BankView::ccTouchMoved(CCTouch* touch, CCEvent* event)
{	
	setSelectFrameShow(false);
	//
	CCPoint locationInView = touch->locationInView(touch->view());
    currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
	//
	int diaotaX = abs(currentTouchPoint.x - preTouchPoint.x);

	//Doyang 20120924
	if(diaotaX < 5)
	{
	    return;
	}

	//X crane tower limit, too small think didn't move
	if (g_pBankCreate)// && g_pBankCreate->getIsScrolling()
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
			g_pBankCreate->ccTouchMoved(touch, event);
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

	//
	preTouchPoint = currentTouchPoint;
}

void BankView::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	setSelectFrameShow(false);

	CCPoint locationInView = touch->locationInView(touch->view());
    currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	if (g_pBankCreate)// && g_pBankCreate->getIsScrolling()
	{
		if (getTouchState() == TouchState_1)
		{//
			setTouchState(TouchState_6);
			//Detection met which backpack BankGoods grid
			BankGoods* bankGoods = 0;
			bankGoods = getCurSelectedBankGoods(currentTouchPoint);//touchbegan?????preTouchPoint
		
			if (bankGoods)
			{
				if (!bankGoods->_lock)
				{//???????
					if (bankGoods->myInfo->id > 0)
					{//??????
						if (LayerManager::tipsLayer->getLastItemGID() == bankGoods->getTag())
						{
							LayerManager::tipsLayer->setLastItemGID(NONEINT);
						}//LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
						else
						{
							bankGoods->myTip->rollOverHander();	
							LayerManager::tipsLayer->setLastItemGID(bankGoods->getMyFocusGID());
						}
						//setSelectFrameShow(true);
					}
				}
				else
				{//????,???????
					onClickHandler(bankGoods);
					//Confirm* pConfirm = new Confirm();
					//pConfirm->initWithParam("��Ѿ", this, menu_selector(BagView::handleBuyCell));
					//LayerManager::windowLayer->addChild(pConfirm,109);
				}
			}


		}
		if (getTouchState() == TouchState_3)
		{
			g_pBankCreate->ccTouchEnded(touch, event);
		}
		else if (getTouchState() == TouchState_5)
		{
			if (m_pCurSelectedBankGoods)
					m_pCurSelectedBankGoods->onMouseUpHnadler(currentTouchPoint);
		}
	}
	

	//Change to return without state
	setTouchState(TouchState_0);
} 

//????????
void BankView::onClickHandler(BankGoods* bankGoods)
{
	if (!bankGoods)
		return;
	int32 index = bankGoods->getTag();
	int32 smoney = _capacity - 18 + 1;
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

	g_pBankCreate->setHeightLine(index, true);

	Confirm* pConfirm = new Confirm();
	tmp_num = num;
	tmp_money = money;
	tmp_sitNum = index;
	char str[80];
	sprintf(str, ValuesUtil::Instance()->getString("BB001").c_str(), money, num);//??????%d????%d???????
	std::string stdstr = str;
	UTF8(stdstr);
	pConfirm->initWithParam(stdstr.c_str(), this, menu_selector(BankView::handleBuyCellConfirm),menu_selector(BankView::handleBuyCellCancel));
	LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
	pConfirm->release();
}

//CC_PROPERTY(int32, _TouchState, TouchState)	
int32 BankView::getTouchState()
{
	return _TouchState;
}

void BankView::setTouchState(int32 var)
{
	_TouchState = var;
}

//CC_PROPERTY(bool, _selectFrameShow, SelectFrameShow)
bool BankView::getSelectFrameShow()
{
	return _selectFrameShow;
}

void BankView::setSelectFrameShow(bool var)
{
	//if (_selectFrameShow == var)
	//	return;

	if (var)
	{
		BankGoods* bankGoods = (BankGoods*)__container->getChildByTag(RENDERTAG_select);
		if (bankGoods)
			__container->removeChildByTag(RENDERTAG_select, true);

		bankGoods = getCurSelectedBankGoods(preTouchPoint);//touchbegan?????preTouchPoint
		if (!bankGoods)
			return;
		CCPoint tarpos = bankGoods->getPosition();
		SpriteNode* pSelect = new SpriteNode();
		pSelect->initWithSpriteFrameName("pack/select.png");
		__container->addChild(pSelect, RENDERZ_select ,RENDERTAG_select);
		pSelect->release();
		pSelect->setPosition(ccpAdd(ccp(tarpos.x, tarpos.y),
			g_pBankCreate->getPosition()));
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

void BankView::step(ccTime dt)
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
			//Detection met which backpack BankGoods grid
			if (g_pBankCreate)
			{
	
				BankGoods* bankGoods = 0;
				bankGoods = getCurSelectedBankGoods(preTouchPoint);//Inside the preTouchPoint touchbegan set
				if (!bankGoods)
					return;
				CCPoint b =bankGoods->getPosition();

				m_pCurSelectedBankGoods = 0;//Set empty
				if (!m_pCurSelectedBankGoods)
					m_pCurSelectedBankGoods = bankGoods;
				if (bankGoods)
				{//Click on to capture a props

					//p = preTouchPoint;
					m_pCurSelectedBankGoods->onMouseDownHandler(this->getPosition());
				}
			}
		}
	}	
}

//touch end

BankGoods* BankView::getCurSelectedBankGoods(CCPoint p)
{
	p = ccpSub(p, this->getPosition());
	p = ccpSub(p, g_pBankCreate->getPosition());
	p = ccpSub(p, __container->getPosition());

	BankGoods* bankGoods = 0;
	bankGoods = g_pBankCreate->getCurSelectedBankGoods(p);//Inside the preTouchPoint touchbegan set
	if (!bankGoods) 
		return 0;
	//int tag = bankGoods->getTag();
	return bankGoods;
}

/**
	*
	* Items information change, may be switched positions, delete, finishing
	*/		
void BankView::updateGoods(char* arr, int32 noEmpty)
{
	_noEmpty = noEmpty;
	g_pBankCreate->updateGoods(arr);
	//layout();
}

void BankView::handleBuyCellConfirm(CCObject* pSender)
{
	addGrid(tmp_num, tmp_money);
	//??????
	g_pBankCreate->setHeightLine(tmp_sitNum, false);
	//remove??
	Confirm* pConfirm = (Confirm*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pConfirm && pConfirm->getParent())
		pConfirm->getParent()->removeChild(pConfirm, true);
	return;
}

void BankView::handleBuyCellCancel(CCObject* pSender)
{
	//??????
	g_pBankCreate->setHeightLine(tmp_sitNum, false);
	//remove??
	Confirm* pConfirm = (Confirm*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pConfirm && pConfirm->getParent())
		pConfirm->getParent()->removeChild(pConfirm, true);
	return;
}

void BankView::addGrid(int32 num, int32 money)
{
	if (money >  RoleManage::Instance()->_accountInfo.gold())
	{
		//MsgManage.getInstance().showMsg(MsgManage.SYSTEM_MSG, "W0004");
		//return;
	}
	dispatchEvent(BANK_ADD_GRID_CLICK, &num);
}
