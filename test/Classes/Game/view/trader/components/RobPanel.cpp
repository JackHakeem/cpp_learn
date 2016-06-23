#include "RobPanel.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"
#include "manager/TouchLayerEnum.h"
#include "manager/LangManager.h"
#include "manager/ViewManager.h"
#include "manager/PopEventName.h"
#include "model/trader/TraderManager.h"
#include "../CityTraderMediator.h"
#include "manager/SourceCacheManage.h"
#include "model/scene/TokenManager.h"
#include "socket/command/c29/CCMD29B.h"
#include "manager/GlobalManage.h"
#include "CustomCD.h"
#include "manager/CDManage.h"
#include "events/CDEvent.h"
#include "manager/VIPMgr.h"
#include "manager/VIPLimitConst.h"
#include "MessageInfoBox.h"

RobPanel::RobPanel()
{
	_beated = 0;
	_id = 0;
	_robBtnImg = 0;
}

bool RobPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	//init key
	setNeedBg( NeedBg_NO );

	key = PopEventName::CITY_TRADER;


	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/trader/res_trader.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/trader/res_trader_goods.plist");

	this->setPosition(CCPointZero);
	this->setContentSize(CCDirector::sharedDirector()->getWinSize());
	this->setPopContentSize(this->getContentSize());

	CCSize csIner( POSX(461), POSX(457) );
	pInnerLayer = new CCLayer();
	if(!pInnerLayer || !pInnerLayer->init()) 
	{
		return false;
	}
	CCPoint innerLayerPosition = POS(ccp(265.0f, 92.0f), ScaleUtil::CENTER_TOP);
	pInnerLayer->setAnchorPoint(CCPointZero);
	pInnerLayer->setPosition(innerLayerPosition);
	pInnerLayer->setIsRelativeAnchorPoint(true);
	pInnerLayer->setContentSize(csIner);
	this->addChild(pInnerLayer);

	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame(  "popuibg/bg1.png", 
		ccp( POSX(0), POSX(0) ), CCPointZero, csIner  );
	pInnerLayer->addChild(_bg1);
	_bg1->release();

	// bg top
	CCUIBackground* _infoContainer = new CCUIBackground();
	_infoContainer->initWithSpriteFrame("ui2.png", 
		ccp(POSX(12), POSX(335)),
		ccp(2,2),
		CCSizeMake(POSX(285),POSX(96)));
	pInnerLayer->addChild(_infoContainer);
	_infoContainer->release();

	// bg left
	_infoContainer = new CCUIBackground();
	_infoContainer->initWithSpriteFrame("ui2.png", 
		ccp(POSX(12), POSX(80)),
		ccp(2,2),
		CCSizeMake(POSX(285),POSX(247)));
	pInnerLayer->addChild(_infoContainer);
	_infoContainer->release();

	TraderProxy* _traderProxy = (TraderProxy*)g_pFacade->retrieveProxy(AppFacade_CITY_TRADER_CHANGE);
	// rob btn
	{
		_robBtnImg = CCMenuItemSprite::itemFromNormalSprite(
			CCSprite::spriteWithSpriteFrameName("button.png"),
			CCSprite::spriteWithSpriteFrameName("button1.png"),
			CCSprite::spriteWithSpriteFrameName("button2.png"),
			this,
			menu_selector(RobPanel::robthatsonofbitch) );
		_robBtnImg->setPosition( ccp( POSX(103+121/2), POSX(14+25) ) );
		CCLabelTTF* pConfirm = CCLabelTTF::labelWithString( 
			ValuesUtil::Instance()->getString( "TRD044" ).c_str(),
			g_sSimHeiFont, POSX(23) );
		pConfirm->setColor(ccWHITE);
		_robBtnImg->addChild( pConfirm );
		pConfirm->setPosition( ccp( POSX(121/2), POSX(49/2) ) );
		_robBtnImg->setTag(101);
		CCMenu* _btnStart = CCMenu::menuWithItems(_robBtnImg, 0);
		_btnStart->setTouchLayer(TLE::WindowLayer_Common_btn);
		_btnStart->setPosition( CCPointZero );
		pInnerLayer->addChild(_btnStart);
	}

	// buy btn
	{
		int gold = min(100, 10 * _traderProxy->_buyTokenCnt);
		CCMenuItemSprite *pStartItem = CCMenuItemSprite::itemFromNormalSprite(
			CCSprite::spriteWithSpriteFrameName("button.png"),
			CCSprite::spriteWithSpriteFrameName("button1.png"),
			this,
			menu_selector(RobPanel::buyTradeToken) );
		pStartItem->setPosition( ccp( POSX(313+121/2+10), POSX(85+25) ) );
		pStartItem->setScaleX(1.2f);
		_buyTokenBtnTxt = CCLabelTTF::labelWithString( 
			LangManager::getText( "TRD004", gold ).c_str(),
			g_sSimHeiFont, POSX(23) );
		_buyTokenBtnTxt->setColor(ccWHITE);
		pInnerLayer->addChild( _buyTokenBtnTxt, 10 );
		_buyTokenBtnTxt->setPosition( ccp( POSX(313+121/2+10), POSX(85+49/2) ) );
		pStartItem->setTag(101);
		CCMenu* _btnStart = CCMenu::menuWithItems(pStartItem, 0);
		_btnStart->setTouchLayer(TLE::WindowLayer_Common_btn);
		_btnStart->setPosition( CCPointZero );
		pInnerLayer->addChild(_btnStart);
	}

	// close btn
	CCMenuItemSprite *_btnX = CCMenuItemSprite::itemFromNormalSprite(
		CCSprite::spriteWithSpriteFrameName("btn_close_1_normal.png"),
		CCSprite::spriteWithSpriteFrameName("btn_close_1_pressed.png"),
		this, 
		menu_selector(RobPanel::clickCloseHandler) );
	_btnX->setPosition(  ccp( POSX(461), POSX(454) )  );
	CCMenu* _buttonMenuX = new CCMenu();
	_buttonMenuX->init();
	_buttonMenuX->setTouchLayer( TLE::WindowLayer_Common_btn );
	_buttonMenuX->addChild(_btnX, 0, 0);
	_buttonMenuX->setPosition(CCPointZero);
	pInnerLayer->addChild(_buttonMenuX);
	_buttonMenuX->release();

	// movie
	char _assetURL[128];
	sprintf( _assetURL, "assets/res/%d", 900);
	roleMovieClip = new BitmapMovieClip();
	roleMovieClip->loadModelAsync(_assetURL,
		900, 0.1f/*, this, callfuncOD_selector(MyRobPanel::loadModelCallback), NULL*/);
	
	roleMovieClip->setAnchorPoint(ccp(0.5,0.5));
	roleMovieClip->setPosition(POSX(142), POSX(204+125 / 2));

	pInnerLayer->addChild(roleMovieClip, 2);
	roleMovieClip->release();
	
	if(roleMovieClip)
		roleMovieClip->runActionEx(BitmapMovieClip::ACTION_WALK, 2);


	//team tip
	CCLabelTTF* txtPosTip = CCLabelTTF::labelWithString(
		LangManager::getText("TRD001", g_pCityTraderMediator->_name.c_str()).c_str(),
		CCSizeMake( POSX(285), POSX(24) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(22));
	txtPosTip->setPosition( ccp( POSX(0), POSX(390) ) );
	txtPosTip->setAnchorPoint(CCPointZero);
	pInnerLayer->addChild( txtPosTip );
	txtPosTip->setColor( ccc3(255,198,0) );

	// team lev
	txtPosTip = CCLabelTTF::labelWithString(
		LangManager::getText("TRD002", g_pCityTraderMediator->_lv).c_str(),
		CCSizeMake( POSX(285), POSX(26) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24));
	txtPosTip->setPosition( ccp( POSX(0), POSX(353) ) );
	txtPosTip->setAnchorPoint(CCPointZero);
	pInnerLayer->addChild( txtPosTip );
	txtPosTip->setColor( ccWHITE );
	
	// token num
	_tokenNum = TokenManager::Instance()->getNum(TokenManager::TOKEN_TRADE);
	_freeTokenTxt = CCLabelTTF::labelWithString(
		LangManager::getText("TRD003", _tokenNum).c_str(),
		CCSizeMake( POSX(161), POSX(22) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(19));
	_freeTokenTxt->setPosition( ccp( POSX(297), POSX(150) ) );
	_freeTokenTxt->setAnchorPoint(CCPointZero);
	pInnerLayer->addChild( _freeTokenTxt );
	_freeTokenTxt->setColor( ccc3(255,198,0) );

	// rob get silver tip
	txtPosTip = CCLabelTTF::labelWithString(
		LangManager::getText("TRD005").c_str(),
		CCSizeMake( POSX(139), POSX(26) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24));
	txtPosTip->setPosition( ccp( POSX(307), POSX(341) ) );
	txtPosTip->setAnchorPoint(CCPointZero);
	pInnerLayer->addChild( txtPosTip );
	txtPosTip->setColor( ccWHITE );
	
	// rob get silver
	//int silver = static_cast<int>( (4000*(RoleManage::Instance()->roleLev()/10))
	//	* (0.2f * _traderProxy->_beatedCnt) * _traderProxy->GetGoodQuality());
	_robGetSil = CCLabelTTF::labelWithString(
		"",
		CCSizeMake( POSX(139), POSX(26) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24));
	_robGetSil->setPosition( ccp( POSX(307), POSX(341-28) ) );
	_robGetSil->setAnchorPoint(CCPointZero);
	pInnerLayer->addChild( _robGetSil );
	_robGetSil->setColor( ccWHITE );

	_robGetPop = CCLabelTTF::labelWithString(
		"",
		CCSizeMake( POSX(139), POSX(26) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24));
	_robGetPop->setPosition( ccp( POSX(307), POSX(341-28*2) ) );
	_robGetPop->setAnchorPoint(CCPointZero);
	pInnerLayer->addChild( _robGetPop );
	_robGetPop->setColor( ccWHITE );


	//Custom CD
	_cd = new CustomCD( CDManage::RobTraderCD );
	_cd->setPosition( ccp(POSX(230), POSX(30)) );
	//_cd->setPosition( ccp(POSX(90), POSX(120)) );
	pInnerLayer->addChild( _cd );
	//CCMenuItemFont *pCDlockTimeNameItem = (CCMenuItemFont *)_cd->_tf->getChildByTag(2);
	//pCDlockTimeNameItem->setFontSizeObj(POSX(36));
	//pCDlockTimeNameItem->setColor(ccYELLOW);
	//_cd->m_cpBtOffset = ccp(POSX(8),POSX(5));
	_cd->release();
	_cd->reinit();

	//CCLayerColor* p = CCLayerColor::layerWithColorWidthHeight(ccc4(0,0,255,100), _cd->getContentSize().width,
	//	_cd->getContentSize().height);
	//_cd->addChild(p);

	CDManage::Instance()->addEventListener( CDManage::CDCHANGED, this, callfuncND_selector(RobPanel::cdChangedHandler) ); 

	int type = CDManage::Instance()->getLockBytype( CDManage::RobTraderCD );
	isLockHandler(type);

	return true;
}

RobPanel::~RobPanel()
{
	CDManage::Instance()->removeEventListener( CDManage::CDCHANGED,
		this, callfuncND_selector(RobPanel::cdChangedHandler) );

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/trader/res_trader.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/trader/res_trader_goods.plist");

	//CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/trader/res_trader.pvr.ccz");
	//CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/trader/res_trader_goods.pvr.ccz");
	g_pCityTraderMediator->_robPanel = 0;
}


void RobPanel::cdChangedHandler( CCNode* n, void* data )
{
	CDEvent* e = (CDEvent*)data;
	if( e->cdType == CDManage::RobTraderCD )
	{
		isLockHandler( e->lock );
	}
}

void RobPanel::clickCloseHandler( CCObject* pSender )
{
	PopContainer::clickCloseHandler(pSender);
}

void RobPanel::robthatsonofbitch( CCObject* pSender )
{
	if (g_pGlobalManage->_isOnBusiness)
	{
		LangManager::msgShow("TRD101");
		return;
	}
	if(_tokenNum==0){
		LangManager::msgShow("TRD040");
		return;
	}

	if (_beated>=2)
	{
		LangManager::msgShow("TRD041");
		return;
	}

	dispatchEvent(ROB_THAT_SON_OF_BITCH, &_id);

	clickCloseHandler(0);
}

void RobPanel::buyTradeToken(CCObject* obj)
{
	if (!VIPMgr::Instance()->hasVIPFunc(VIPLimitConst::VIP_BuyRobeCount , RoleManage::Instance()->accountInfo()->vipLev()))
	{
		char path[128] = {0};
		sprintf(path , ValuesUtil::Instance()->getString("WLC010").c_str() , VIPLimitConst::VIP_BuyRobeCount);
		MessageInfoBox::Instance()->show(path,ccc3(12,233,25));
		return;
	}

	TraderProxy* _traderProxy = (TraderProxy*)g_pFacade->retrieveProxy(AppFacade_CITY_TRADER_CHANGE);
	int gold = min(100, 10 * _traderProxy->_buyTokenCnt);
	if (RoleManage::Instance()->accountInfo()->gold()<gold)
	{
		LangManager::msgShow("S3");
		return;
	}

	CCMD29B cmd;
	GameServerSocket::getInstance()->sendMessage(&cmd);
}

void RobPanel::updateData()
{
	_tokenNum = TokenManager::Instance()->getNum(TokenManager::TOKEN_TRADE);
	_freeTokenTxt->setString(LangManager::getText("TRD003", _tokenNum).c_str());


	TraderProxy* _traderProxy = (TraderProxy*)g_pFacade->retrieveProxy(AppFacade_CITY_TRADER_CHANGE);
	int gold = min(100, 10 * _traderProxy->_buyTokenCnt);
	_buyTokenBtnTxt->setString(LangManager::getText( "TRD004", gold ).c_str());
}

void RobPanel::updateGetInfo( int sil, int pop, int beated, int buyTokenCnt )
{
	_robGetSil->setString(LangManager::getText("TRD006", sil).c_str());
	_robGetPop->setString(LangManager::getText("TRD007", pop).c_str());
	_beated = beated;

	TraderProxy* _traderProxy = (TraderProxy*)g_pFacade->retrieveProxy(AppFacade_CITY_TRADER_CHANGE);
	_traderProxy->_buyTokenCnt = buyTokenCnt;

	updateData(); 
}

void RobPanel::isLockHandler( int lock )
{
	if (_robBtnImg)
	{
		if(lock==1)
		{
			_robBtnImg->setIsEnabled(false);
		}
		else
		{
			_robBtnImg->setIsEnabled(true);
		}
	}	
}
