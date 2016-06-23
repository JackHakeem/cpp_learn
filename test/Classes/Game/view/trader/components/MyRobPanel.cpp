#include "MyRobPanel.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"
#include "manager/TouchLayerEnum.h"
#include "manager/LangManager.h"
#include "manager/ViewManager.h"
#include "manager/PopEventName.h"
#include "model/trader/TraderManager.h"
#include "../CityTraderMediator.h"
#include "manager/SourceCacheManage.h"
#include "view/notify/NotifyManager.h"
#include "view/notify/NotifyType.h"
#include "model/scene/SceneManager.h"

MyRobPanel::MyRobPanel()
{
	_PosTxt = 0;
}

bool MyRobPanel::init()
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


	CCSize csIner( POSX(597), POSX(457) );
	pInnerLayer = new CCLayer();
	if(!pInnerLayer || !pInnerLayer->init()) 
	{
		return false;
	}
	CCPoint innerLayerPosition = POS(ccp(178.0f, 79.0f), ScaleUtil::CENTER_TOP);
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
		CCSizeMake(POSX(573),POSX(96)));
	pInnerLayer->addChild(_infoContainer);
	_infoContainer->release();

	// bg left
	_infoContainer = new CCUIBackground();
	_infoContainer->initWithSpriteFrame("ui2.png", 
		ccp(POSX(12), POSX(12)),
		ccp(2,2),
		CCSizeMake(POSX(363),POSX(314)));
	pInnerLayer->addChild(_infoContainer);
	_infoContainer->release();

	// bg right
	_infoContainer = new CCUIBackground();
	_infoContainer->initWithSpriteFrame("ui2.png", 
		ccp(POSX(382), POSX(12)),
		ccp(2,2),
		CCSizeMake(POSX(203),POSX(314)));
	pInnerLayer->addChild(_infoContainer);
	_infoContainer->release();


	char _assetURL[128];
	sprintf( _assetURL, "assets/res/%d", 900);
	roleMovieClip = new BitmapMovieClip();
	roleMovieClip->loadModelAsync(_assetURL,
		900, 0.1f/*, this, callfuncOD_selector(MyRobPanel::loadModelCallback), NULL*/);
		//SourceCacheManage::Instance()->loadModel(
		//_assetURL, 900, 0.1f, true);
	
	roleMovieClip->setAnchorPoint(ccp(0.5,0.5));
	roleMovieClip->setPosition(POSX(197), POSX(180+125 / 2));

	pInnerLayer->addChild(roleMovieClip, 2);
	roleMovieClip->release();
	
	if(roleMovieClip)
		roleMovieClip->runActionEx(BitmapMovieClip::ACTION_WALK, 2);

	//pos tip
	CCLabelTTF* txtPosTip = CCLabelTTF::labelWithString(
		ValuesUtil::Instance()->getString("TRD056").c_str(),
		CCSizeMake( POSX(181), POSX(25) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(23));
	txtPosTip->setPosition( ccp( POSX(146-80-30), POSX(390) ) );
	txtPosTip->setAnchorPoint(CCPointZero);
	pInnerLayer->addChild( txtPosTip );
	txtPosTip->setColor( ccc3(255,198,0) );

	TraderProxy* _traderProxy = (TraderProxy*)g_pFacade->retrieveProxy(AppFacade_CITY_TRADER_CHANGE);
	SceneVo* vo = SceneManager::Instance()->getSceneDic(_traderProxy->_currentMapId);
	if (vo)
	{
		_PosTxt = CCLabelTTF::labelWithString(
			vo->name.c_str(),
			CCSizeMake( POSX(151), POSX(25) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(23));
		_PosTxt->setPosition( ccp( POSX(146+190-80-10-30), POSX(390) ) );
		_PosTxt->setAnchorPoint(CCPointZero);
		pInnerLayer->addChild( _PosTxt );
		_PosTxt->setColor( ccWHITE );
	}	

	// destination
	txtPosTip = CCLabelTTF::labelWithString(
		ValuesUtil::Instance()->getString("TRD061").c_str(),
		CCSizeMake( POSX(131), POSX(25) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(23));
	txtPosTip->setPosition( ccp( POSX(146+150-80-10+150-30), POSX(390) ) );
	txtPosTip->setAnchorPoint(CCPointZero);
	pInnerLayer->addChild( txtPosTip );
	txtPosTip->setColor( ccc3(255,198,0) );

	//if (_traderProxy->selectedVo)
	{
		txtPosTip = CCLabelTTF::labelWithString(
			SceneManager::Instance()->getSceneDic(1001)->name.c_str(),
			CCSizeMake( POSX(131), POSX(25) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(23));
		txtPosTip->setPosition( ccp( POSX(146+150-80-10+150+130-30), POSX(390) ) );
		txtPosTip->setAnchorPoint(CCPointZero);
		pInnerLayer->addChild( txtPosTip );
		txtPosTip->setColor( ccWHITE );
	}	

	//silver
	int silver = static_cast<int>( (4000*(RoleManage::Instance()->roleLev()/10))
		* _traderProxy->GetGoodQuality() * 1 - _traderProxy->_robedSilver);
	//int pop = (int)(_traderProxy->getBasePop()*(1.0f-0.2f*_traderProxy->_beatedCnt));
	int pop = _traderProxy->getBasePop() - _traderProxy->_robedPop;
	_awardTxt = CCLabelTTF::labelWithString(
		LangManager::getText("TRD045", silver, pop).c_str(),
		CCSizeMake( POSX(395+80), POSX(25) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(23));
	_awardTxt->setPosition( ccp( POSX(146-80), POSX(353) ) );
	_awardTxt->setAnchorPoint(CCPointZero);
	pInnerLayer->addChild( _awardTxt );
	_awardTxt->setColor( ccWHITE );

	// close btn
	CCMenuItemSprite *_btnX = CCMenuItemSprite::itemFromNormalSprite(
		CCSprite::spriteWithSpriteFrameName("btn_close_1_normal.png"),
		CCSprite::spriteWithSpriteFrameName("btn_close_1_pressed.png"),
		this, 
		menu_selector(RobPanel::clickCloseHandler) );
	_btnX->setPosition(  ccp( POSX(597), POSX(453) )  );
	CCMenu* _buttonMenuX = new CCMenu();
	_buttonMenuX->init();
	_buttonMenuX->setTouchLayer( TLE::WindowLayer_Common_btn );
	_buttonMenuX->addChild(_btnX, 0, 0);
	_buttonMenuX->setPosition(CCPointZero);
	pInnerLayer->addChild(_buttonMenuX);
	_buttonMenuX->release();

	if (g_pCityTraderMediator->_msgDic.size()==0)
	{
		_robInfo1Txt = CCLabelTTF::labelWithString(
			LangManager::getText("TRD020").c_str(),
			CCSizeMake( POSX(176), POSX(77) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
		_robInfo1Txt->setPosition( ccp( POSX(395), POSX(220) ) );
		_robInfo1Txt->setAnchorPoint(CCPointZero);
		pInnerLayer->addChild( _robInfo1Txt );
		_robInfo1Txt->setColor( ccWHITE );
	}

	if (g_pCityTraderMediator->_msgDic.size()>=1)
	{
		// rob1
		string robResult = "";
		SCMD2C5 cmd = *g_pCityTraderMediator->_msgDic.begin();
		if (cmd.c_result==0)
		{
			robResult = LangManager::getText("TRD047", cmd.b_name.c_str());
		}
		else
		{
			char txt[128];
			sprintf( txt, ValuesUtil::Instance()->getString( "TRD046" ).c_str(),
				cmd.b_name.c_str(), cmd.d_lostNum );
			robResult = txt;
		}
		
		_robInfo1Txt = CCLabelTTF::labelWithString(
			robResult.c_str(),
			CCSizeMake( POSX(176), POSX(77) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
		_robInfo1Txt->setPosition( ccp( POSX(395), POSX(220) ) );
		_robInfo1Txt->setAnchorPoint(CCPointZero);
		pInnerLayer->addChild( _robInfo1Txt );
		_robInfo1Txt->setColor( ccWHITE );
	}

	if (g_pCityTraderMediator->_msgDic.size()>=2)
	{
		string robResult = "";
		std::list<SCMD2C5>::iterator it =g_pCityTraderMediator->_msgDic.begin();
		it++;
		SCMD2C5 cmd = *it;
		if (cmd.c_result==0)
		{
			robResult = LangManager::getText("TRD047", cmd.b_name.c_str());
		}
		else
		{
			char txt[128];
			sprintf( txt, ValuesUtil::Instance()->getString( "TRD046" ).c_str(),
				cmd.b_name.c_str(), cmd.d_lostNum );
			robResult = txt;
		}
		// rob2
		_robInfo2Txt = CCLabelTTF::labelWithString(
			robResult.c_str(),
			CCSizeMake( POSX(176), POSX(77) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
		_robInfo2Txt->setPosition( ccp( POSX(395), POSX(220-80) ) );
		_robInfo2Txt->setAnchorPoint(CCPointZero);
		pInnerLayer->addChild( _robInfo2Txt );
		_robInfo2Txt->setColor( ccWHITE );

	}

	return true;
}

MyRobPanel::~MyRobPanel()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/trader/res_trader.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/trader/res_trader_goods.plist");

	//CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/trader/res_trader.pvr.ccz");
	//CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/trader/res_trader_goods.pvr.ccz");

	g_pCityTraderMediator->_myRobPanel = 0;

	//NotifyManager::Instance()->addNotification(NotifyType::NType_Trader);
}

void MyRobPanel::clickCloseHandler( CCObject* pSender )
{
	PopContainer::clickCloseHandler(pSender);
}

void MyRobPanel::updateData()
{
	//silver
	TraderProxy* _traderProxy = (TraderProxy*)g_pFacade->retrieveProxy(AppFacade_CITY_TRADER_CHANGE);
	int silver = static_cast<int>( (4000*(RoleManage::Instance()->roleLev()/10))
		* _traderProxy->GetGoodQuality() * 1 - _traderProxy->_robedSilver);
	int pop = (int)(_traderProxy->getBasePop()*(1.0f-0.2f*_traderProxy->_beatedCnt));
	_awardTxt->setString(LangManager::getText("TRD045", silver, pop).c_str());

	if (!pInnerLayer)
	{
		return;
	}
	

	if ( (g_pCityTraderMediator->_msgDic.size()>=1) && !_robInfo1Txt )
	{
		// rob1
		string robResult = "";
		SCMD2C5 cmd = *g_pCityTraderMediator->_msgDic.begin();
		if (cmd.c_result==0)
		{
			robResult = LangManager::getText("TRD047", cmd.b_name.c_str());
		}
		else
		{
			char txt[128];
			sprintf( txt, ValuesUtil::Instance()->getString( "TRD046" ).c_str(),
				cmd.b_name.c_str(), cmd.d_lostNum );
			robResult = txt;
		}

		_robInfo1Txt = CCLabelTTF::labelWithString(
			robResult.c_str(),
			CCSizeMake( POSX(176), POSX(77) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
		_robInfo1Txt->setPosition( ccp( POSX(395), POSX(220) ) );
		_robInfo1Txt->setAnchorPoint(CCPointZero);
		pInnerLayer->addChild( _robInfo1Txt );
		_robInfo1Txt->setColor( ccWHITE );
	}

	if ( (g_pCityTraderMediator->_msgDic.size()>=2) && !_robInfo2Txt )
	{
		string robResult = "";
		std::list<SCMD2C5>::iterator it =g_pCityTraderMediator->_msgDic.begin();
		it++;
		SCMD2C5 cmd = *it;
		if (cmd.c_result==0)
		{
			robResult = LangManager::getText("TRD047", cmd.b_name.c_str());
		}
		else
		{
			char txt[128];
			sprintf( txt, ValuesUtil::Instance()->getString( "TRD046" ).c_str(),
				cmd.b_name.c_str(), cmd.d_lostNum );
			robResult = txt;
		}
		// rob2
		_robInfo2Txt = CCLabelTTF::labelWithString(
			robResult.c_str(),
			CCSizeMake( POSX(176), POSX(77) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18));
		_robInfo2Txt->setPosition( ccp( POSX(395), POSX(220-80) ) );
		_robInfo2Txt->setAnchorPoint(CCPointZero);
		pInnerLayer->addChild( _robInfo2Txt );
		_robInfo2Txt->setColor( ccWHITE );
	}
}
