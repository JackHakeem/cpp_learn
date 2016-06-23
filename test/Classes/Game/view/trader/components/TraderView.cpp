#include "TraderView.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"
#include "manager/TouchLayerEnum.h"
#include "manager/LangManager.h"
#include "manager/ViewManager.h"
#include "manager/PopEventName.h"
#include "model/trader/TraderManager.h"
#include "../CityTraderMediator.h"
#include "manager/GlobalManage.h"
#include "model/scene/NPCManager.h"
#include "model/scene/vo/NPCVo.h"
#include "view/task/components/TaskType.h"
 
TraderView::TraderView()
{
	_starTrade = 0;
	_vipLv = 0;
	_silever = 0;
	_refreshCost = 0;

	_btnGo = 0;
	_btnRefresh = 0;

	_hasGoods = false;
	_hasDest = false;

	_mapId = 0;
	_restNum = 0;

	_isFull = false;
	_lockGrid = 0;
	_roleManage = RoleManage::Instance();

	pInnerLayer = 0;
	_infoContainer = 0;

	_txtRestTrader = 0;

	_needGoldPic = 0;

	m_selectedSpriteImage = 0;
	_curGood = 0;
	_clickRefresh = false;

	_bgSkillTips = 0;
}

bool TraderView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	//init key
	key = PopEventName::CITY_TRADER;


	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/trader/res_trader.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/trader/res_trader_goods.plist");

	this->setIsTouchEnabled(true);

	this->setPosition(CCPointZero);
	this->setContentSize(CCDirector::sharedDirector()->getWinSize());
	this->setPopContentSize(this->getContentSize());

	CCSize csIner( POSX(923), POSX(562) );
	pInnerLayer = new CCLayer();
	if(!pInnerLayer || !pInnerLayer->init()) 
	{
		return false;
	}
	CCPoint innerLayerPosition = POS(ccp(17.0f, 12.0f), ScaleUtil::CENTER_TOP);
	pInnerLayer->setAnchorPoint(CCPointZero);
	pInnerLayer->setPosition(innerLayerPosition);
	pInnerLayer->setIsRelativeAnchorPoint(true);
	pInnerLayer->setContentSize(csIner);
	this->addChild(pInnerLayer);
	pInnerLayer->release();

	// title
	CCSprite* pTitile = new CCSprite;
	pTitile->initWithSpriteFrameName("trader_title.png");
	pTitile->setAnchorPoint(CCPointZero);
	pTitile->setPosition(ccp(POSX(273), POSX(462)));
	pInnerLayer->addChild(pTitile);
	pTitile->release();

	// shang
	CCSprite* pShang = new CCSprite;
	pShang->initWithSpriteFrameName("trader_shang.png");
	pShang->setAnchorPoint(CCPointZero);
	pShang->setPosition(ccp(POSX(138), POSX(517)));
	pInnerLayer->addChild(pShang);
	pShang->release();

	CCLabelTTF* pTitleExplain = new CCLabelTTF;
	pTitleExplain->initWithString(
		ValuesUtil::Instance()->getString("TRD055").c_str(),
		CCSizeMake(POSX(394), POSX(38)), CCTextAlignmentCenter, g_sSimHeiFont, POSX(34) );
	pTitleExplain->setAnchorPoint(CCPointZero);
	pTitleExplain->setPosition(ccp(POSX(1), POSX(31)));
	pTitile->addChild(pTitleExplain);
	pTitleExplain->release();

	_infoContainer = new CCUIBackground();
	_infoContainer->initWithSpriteFrame("ui2.png", 
		ccp(POSX(18), POSX(239)),
		ccp(2,2),
		CCSizeMake(POSX(888),POSX(216)));
	pInnerLayer->addChild(_infoContainer);
	_infoContainer->release();

	//rest cnt:
	_txtRestTrader = CCLabelTTF::labelWithString(
		ValuesUtil::Instance()->getString("TRD050").c_str(),
		CCSizeMake( POSX(354), POSX(32) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(29));
	_txtRestTrader->setPosition( ccp( POSX(312), POSX(186) ) );
	_txtRestTrader->setAnchorPoint(CCPointZero);
	pInnerLayer->addChild( _txtRestTrader );
	_txtRestTrader->setColor( ccWHITE );

	_txtRestTraderCnt = CCLabelTTF::labelWithString(
		"4",
		CCSizeMake( POSX(44), POSX(44) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(41));
	_txtRestTraderCnt->setPosition( ccp( POSX(312+232), POSX(186) ) );
	_txtRestTraderCnt->setAnchorPoint(CCPointZero);
	pInnerLayer->addChild( _txtRestTraderCnt );
	_txtRestTraderCnt->setColor( ccGREEN );

	// bg tips
	CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
		ValuesUtil::Instance()->getString("TRD053").c_str(),
		CCSizeMake( POSX(901), POSX(23) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(19));
	txtLabel->setPosition( ccp( POSX(1), POSX(39) ) );
	txtLabel->setAnchorPoint(CCPointZero);
	pInnerLayer->addChild( txtLabel );
	txtLabel->setColor( ccYELLOW );

	// double tips
	string doubleTips = ValuesUtil::Instance()->getString("TRD107") + "\n12:00 - 14:00 19:00 - 23:00";
	txtLabel = CCLabelTTF::labelWithString(
		doubleTips.c_str(),
		CCSizeMake( POSX(327), POSX(45) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(19));
	txtLabel->setPosition( ccp( POSX(47), POSX(185-19) ) );
	txtLabel->setAnchorPoint(CCPointZero);
	pInnerLayer->addChild( txtLabel );
	txtLabel->setColor( ccYELLOW );

	// shua btn
	if (g_pCityTraderMediator->_traderViewType==1)
	{
		CCMenuItemSprite *pStartItem = CCMenuItemSprite::itemFromNormalSprite(
			CCSprite::spriteWithSpriteFrameName("trader_shua.png"),
			CCSprite::spriteWithSpriteFrameName("trader_shuaP.png"),
			this,
			menu_selector(TraderView::refreshHandler) );
		pStartItem->setPosition( ccp( POSX(658+147/2), POSX(76+147/2) ) );
		pStartItem->setTag(101);
		_btnRefresh = CCMenu::menuWithItems(pStartItem, 0);
		_btnRefresh->setTouchLayer(TLE::WindowLayer_Common_btn);
		_btnRefresh->setPosition( CCPointZero );
		pInnerLayer->addChild(_btnRefresh);
	}

	// trader btn
	{
		CCMenuItemSprite *pStartItem = CCMenuItemSprite::itemFromNormalSprite(
			CCSprite::spriteWithSpriteFrameName("button.png"),
			CCSprite::spriteWithSpriteFrameName("button1.png"),
			this,
			menu_selector(TraderView::tradeHandler) );
		pStartItem->setPosition( ccp( POSX(407+121/2), POSX(95)+POSX(25) ) );

		if (g_pCityTraderMediator->_traderViewType==1)
		{
			string strConfirm = ValuesUtil::Instance()->getString( "TRD051" );
			CCLabelTTF* pConfirm = CCLabelTTF::labelWithString( strConfirm.c_str(), g_sSimHeiFont, POSX(23) );
			pConfirm->setColor(ccWHITE);
			pStartItem->addChild( pConfirm );
			pConfirm->setPosition( ccp( POSX(121/2), POSX(49/2) ) );
		}
		else
		{
			string strConfirm = ValuesUtil::Instance()->getString( "TRD110" );
			CCLabelTTF* pConfirm = CCLabelTTF::labelWithString( strConfirm.c_str(), g_sSimHeiFont, POSX(23) );
			pConfirm->setColor(ccWHITE);
			pStartItem->addChild( pConfirm );
			pConfirm->setPosition( ccp( POSX(121/2), POSX(49/2) ) );
		}
		pStartItem->setTag(101);
		CCMenu* _btnStart = CCMenu::menuWithItems(pStartItem, 0);
		_btnStart->setTouchLayer(TLE::WindowLayer_Common_btn);
		_btnStart->setPosition( CCPointZero );
		pInnerLayer->addChild(_btnStart);
	}

	// need gold
	TraderProxy* _traderProxy = (TraderProxy*)g_pFacade->retrieveProxy(AppFacade_CITY_TRADER_CHANGE);
	if (g_pCityTraderMediator->_traderViewType==1)
	{
		_needGoldPic = new CCSprite;
		if (_traderProxy->_refreshCnt==0)
		{
			_needGoldPic->initWithSpriteFrameName("trader_1gold.png");
		} 
		else
		{
			_needGoldPic->initWithSpriteFrameName("trader_3gold.png");
		}	
		_needGoldPic->setAnchorPoint(CCPointZero);
		_needGoldPic->setPosition(ccp(POSX(818), POSX(129)));
		pInnerLayer->addChild(_needGoldPic);
		_needGoldPic->release();
	}	

	m_selectedSpriteImage = new CCUIBackground();
	m_selectedSpriteImage->initWithSpriteFrame( "train/gold_back.png",
		ccp(POSX(27 + 15), POSX(93)), CCPointZero, CCSizeMake( POSX(98), POSX(98) ) );
	_infoContainer->addChild( m_selectedSpriteImage, 10 );
	m_selectedSpriteImage->release();

	return true;
}

void TraderView::cityChange( CityPriceVo* vo )
{
}

void TraderView::historyChange( std::list<int> _historyList )
{
}

void TraderView::showTraderGoods( std::list<int> _itemList )
{
	clearGoods();
	if (_itemList.size()>0)
	{
		int newPos = *(_itemList.begin());
		if ( _clickRefresh )
		{
			_clickRefresh = false;
			if (_curGood==newPos)
			{
				//LangManager::msgShow("TRD017");
				Message::Instance()->show( ValuesUtil::Instance()->getString("TRD017") );
			}
			else
			{
				Message::Instance()->show( ValuesUtil::Instance()->getString("TRD018") );
			}			
		}
		_curGood = newPos;	

		if (m_selectedSpriteImage)
		{
			m_selectedSpriteImage->setPosition(  ccp(POSX(27+(newPos-1)*173 + 15), POSX(93))  );
		}		
	}

	TraderProxy* _traderProxy = (TraderProxy*)g_pFacade->retrieveProxy(AppFacade_CITY_TRADER_CHANGE);
	if ( (_traderProxy->_refreshCnt>=1)&&(g_pCityTraderMediator->_traderViewType==1) )
	{
		_needGoldPic->removeFromParentAndCleanup(true);

		// need gold
		_needGoldPic = new CCSprite;
		_needGoldPic->initWithSpriteFrameName("trader_3gold.png");
		_needGoldPic->setAnchorPoint(CCPointZero);
		_needGoldPic->setPosition(ccp(POSX(818), POSX(129)));
		pInnerLayer->addChild(_needGoldPic);
		_needGoldPic->release();
	}		

	for (int i = 1; i <= 5 ; i++)
	{
		TraderGoodsVo* vo = TraderManager::Instance()->getGoodsById(i);
		TraderGoodsItem* item = new TraderGoodsItem();
		item->init();
		item->initVo(vo);
		item->setPosition( ccp(POSX(27+(i-1)*173),0) );
		_infoContainer->addChild(item, 1);
		item->release();
		goodArr.push_back(item);
	}
	
}

void TraderView::showBankGoods( std::list<BankGridVo*> _bankList )
{
}

void TraderView::eventChange( std::list<TraderEventVo*> _eventList )
{
}

TraderView::~TraderView()
{
	ViewManager::getInstance()->traderView = 0;
	g_pCityTraderMediator->_traderView = 0;

	goodArr.clear();


	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/trader/res_trader.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/trader/res_trader_goods.plist");

	//CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/trader/res_trader.pvr.ccz");
	//CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/trader/res_trader_goods.pvr.ccz");
}

void TraderView::clearGoods()
{
	std::list<TraderGoodsItem*>::iterator it = goodArr.begin();
	for ( ; it != goodArr.end(); it++ ){
		TraderGoodsItem* item = *it;
		item->removeFromParentAndCleanup(true);
	}
	goodArr.clear();
}

void TraderView::tradeHandler(CCObject* obj)
{
	if (g_pCityTraderMediator->_traderViewType==1)
	{
		_hasDest = false;
		dispatchEvent(TraderView::GO_TRADE, (void*)&_mapId);
	} 
	else
	{
		NPCVo *pNpcVo = NPCManager::Instance()->getNPC(13);
		FindVo findVo;
		findVo._type = TaskType::NPC;
		findVo._sceneId = 1003;
		findVo._npcId = 13;
		GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::FIND_ELEMENT, &findVo);
	}
}

void TraderView::refreshHandler(CCObject* obj)
{
	if (_curGood==5)
	{
		LangManager::msgShow("TRD021");
		return;
	}

	if(_restNum==0){
		LangManager::msgShow("TRD014");
		return;
	}
	else if(_roleManage->accountInfo()->vipLev()>=1 || _roleManage->accountInfo()->trialVip()){
		if(_roleManage->accountInfo()->gold()<_refreshCost)
		{
			LangManager::msgShow("TRD015");
			return;
		}
		else{
			_clickRefresh = true;
			dispatchEvent(TraderView::REFRESH_GOODS, 0);
		}
	}
	else//  Alert.show(LangManager.getText("TRD016"));
		LangManager::msgShow("TRD016");

}

void TraderView::buyNumChange(int num){
	_restNum = num;
	char x[64]={0};
	sprintf(x, "%d", _restNum);
	_txtRestTraderCnt->setString(x);

	TraderProxy* _traderProxy = (TraderProxy*)g_pFacade->retrieveProxy(AppFacade_CITY_TRADER_CHANGE);
	_refreshCost = (_traderProxy->_refreshCnt>=1)?5:0;

	if(_restNum==0){
		if (g_pCityTraderMediator->_traderViewType==1)
		{
			if (_needGoldPic)
			{
				_needGoldPic->setIsVisible(false);
			}
		}
		if (_btnRefresh)
		{
			_btnRefresh->setIsVisible(false);
		}
	}
	else{
		if (g_pCityTraderMediator->_traderViewType==1)
		{
			if (_needGoldPic)
			{
				_needGoldPic->setIsVisible(true);
			}
		}
		if (_btnRefresh)
		{
			_btnRefresh->setIsVisible(true);
		}
	}
}

CityPriceVo* TraderView::getHighestPrice(std::list<CityPriceVo*>& cityList, int mapId){
	int sitGrid =1;
	CityPriceVo* _tempVo = new CityPriceVo;
	_tempVo->cityPrice = 0;
	std::list<CityPriceVo*>::iterator it = cityList.begin();
	for ( ; it!=cityList.end();it++){
		CityPriceVo* vo = *it;
		if(vo->mapId==mapId) continue;
		if(vo->cityPrice>_tempVo->cityPrice)
		{
			_tempVo->mapId = vo->mapId;
			_tempVo->cityName = vo->cityName;
			_tempVo->cityPrice = vo->cityPrice;
			_tempVo->npcId = vo->npcId;

			_hasDest = true;
			_mapId = _tempVo->mapId;
		}
	}
	return _tempVo;
}

void TraderView::clickCloseHandler( CCObject* pSender )
{
	PopContainer::clickCloseHandler(pSender);
}


void TraderView::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate( this, TLE::WindowLayer_Common, true );
}

bool TraderView::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if (_bgSkillTips)
	{
		_bgSkillTips->removeFromParentAndCleanup(true);
		_bgSkillTips = 0;
	}

	return true;
}

void TraderView::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint m_locationInView = CCDirector::sharedDirector()->convertToGL(
		pTouch->locationInView(pTouch->view()) );

	std::list<TraderGoodsItem*>::iterator it = goodArr.begin();
	int index = 1;
	for ( ; it != goodArr.end(); it++ ){
		TraderGoodsItem* _good = *it;

		if (!_good || !_good->_good )
		{
			continue;
		}

		CCPoint itemPoint = getScreenPos(_good);
		CCSize itemSize = _good->getContentSize();
		if ( CCRect::CCRectContainsPoint(
			CCRectMake(itemPoint.x,itemPoint.y, itemSize.width,itemSize.height), m_locationInView)
			)
		{
			CCPoint m_initPoint = _good->_good->getPosition();
			CCNode* pNode = (CCNode*)_good->_good;
			while ( pNode != (CCNode*)this )
			{
				if ( pNode && (pNode = pNode->getParent()) )
				{
					m_initPoint = ccpAdd( m_initPoint, pNode->getPosition() );
				}
			}

			_bgSkillTips = new CCUIBackground();
			m_initPoint.y -= POSX(84);
			if (index>3)
			{
				m_initPoint.x -= ( POSX(220 - 98 ) );
			}
			
			_bgSkillTips->initWithSpriteFrame("ui.png",
			m_initPoint , ccp(POSX(6),POSX(7)),
			CCSizeMake(POSX(240), POSX(84)));
			this->addChild(_bgSkillTips, 1);
			_bgSkillTips->setAnchorPoint(CCPointZero);
			_bgSkillTips->release();

			int silver = static_cast<int>( (4000*(RoleManage::Instance()->roleLev()/10))* GetGoodQuality(index) );
			int pop = getBasePop(index);
			string str = LangManager::getText("TRD106", silver, pop);
			CCLabelTTF* _nameEquipment = CCLabelTTF::labelWithString( 
				str.c_str(),
				CCSizeMake( POSX(220), POSX(50) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(20) );
			_nameEquipment->setColor(  getTradeColor(index)  );
			_nameEquipment->setAnchorPoint(CCPointZero);
			_nameEquipment->setPosition( ccp( POSX(10), POSX(25) ) );
			_bgSkillTips->addChild( _nameEquipment, 2 );
		}
		++index;
	}


}


ccColor3B TraderView::getTradeColor( int goodsId )
{
	switch (goodsId)
	{
	case 1:
		return ccGREEN;
		break;
	case 2:
		return ccBLUE;
		break;
	case 3:
		return ccc3(0x99, 0x32, 0xCD);//9932CD
		break;
	case 4:
		return ccc3(255, 124, 0);
		break;
	case 5:
		return ccRED;
		break;
	}

	return ccGREEN;
}

float TraderView::GetGoodQuality( int goodsId )
{
	switch (goodsId)
	{
	case 1:
		return 1.0f;
		break;
	case 2:
		return 1.5f;
		break;
	case 3:
		return 2.0f;
		break;
	case 4:
		return 4.0f;
		break;
	case 5:
		return 8.0f;
		break;
	}

	return 0.0f;
}

int TraderView::getBasePop( int goodsId )
{
	switch (goodsId)
	{
	case 1:
		return 100/2;
		break;
	case 2:
		return 200/2;
		break;
	case 3:
		return 300/2;
		break;
	case 4:
		return 600/2;
		break;
	case 5:
		return 1000/2;
		break;
	}
	return 0;
}