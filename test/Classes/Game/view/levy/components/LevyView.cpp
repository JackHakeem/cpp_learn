#include "manager/PopEventName.h"
#include "utils/ValuesUtil.h"
#include "Message.h"
#include "events/GameDispatcher.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "LevyView.h"
#include "model/player/vo/LevyInfoVo.h"
#include "events/CDEvent.h"
#include "manager/CDManage.h"
#include "utils/Utils.h"
#include "utils/ScaleUtil.h"
#include "manager/LangManager.h"
#include "model/player/RoleManage.h"
#include "manager/TouchLayerEnum.h"
#include "CCUIBackground.h"
#include "PopUIBg.h"
#include "manager/sound/SoundManager.h"
#include "manager/LevLimitConst.h"
#include "../LevyMediator.h"
#include "GoldLevyPanel.h"
#include "model/newhand/NewhandManager.h"
#include "model/newhand/vo/NewhandConst.h"
#include "manager/ButtonIDConst.h"
#include "manager/ViewManager.h"

static const int TAG_PARENT = 1001;
static const int TAG_PARENTGold = 1003;
static const int TAG_CD = 1002;
static const int TAG_MENU_ITEM = 1;

LevyView::LevyView()
{
	pParentLayer = 0;
	pParentLayerGold = 0;
	_txtLevySilver = 0;
	_txtAmount = 0;

	_goldCost = 0;
	_cdTime = 0;

	_levy = 0;
	_goldLevy = 0;

	_rest = 0;
	_limit = 0;
	_silver = 0;
	_levyReward = 0;
	_levyCost = 0;
	_info = 0;

	_txtIn1 = 0;
	_txtIn2 = 0;

	_cd = 0;
	_LevyItem = 0;
} 

LevyView::~LevyView()
{

	ViewManager::getInstance()->levyView = 0;

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/levy/res_goldlevy.plist");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/levy/res_goldlevy.pvr.ccz");
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/levy/res_levy.plist");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/levy/res_levy.pvr.ccz");

	CDManage::Instance()->removeEventListener( CDManage::CDCHANGED,
		this, callfuncND_selector(LevyView::cdChangedHandler) ); 

	g_pLevyMediator->_levyView = 0;
	g_pLevyMediator->_goldPanel = 0;
}

void LevyView::removeDataObjectChild()
{
	if (ViewManager::getInstance()->levyView)
	{
		ViewManager::getInstance()->levyView = 0;
	}
	

	g_pLevyMediator->_levyView = 0;
	g_pLevyMediator->_goldPanel = 0;
}

bool LevyView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	//
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/levy/res_goldlevy.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/levy/res_levy.plist");
	//
	setNeedBg(NeedBg_NO);
	// initial key
	key = PopEventName::LEVY;

	CCSize cs( POSX(923), POSX(562) );
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	this->setPopContentSize( size );

	pParentLayer = new CCLayer();
	if(!pParentLayer)
	{
		return false;
	}
	pParentLayer->init();
	pParentLayer->setContentSize( cs );
	//pParentLayer->setPosition(POS(ccp(17, 15), ScaleUtil::CENTER_TOP));
	pParentLayer->setPosition(POS(ccp(17 + (923 - 450)/2, 15), ScaleUtil::CENTER_TOP));
	pParentLayer->setAnchorPoint(CCPointZero);
	pParentLayer->setTag(TAG_PARENT );
	this->addChild( pParentLayer , 1 );
	pParentLayer->release();

	{
		pParentLayerGold = new CCLayer();
		if(!pParentLayerGold)
		{
			return false;
		}
		pParentLayerGold->init();
		pParentLayerGold->setContentSize( cs );
		//pParentLayerGold->setPosition(POS(ccp(17, 15), ScaleUtil::CENTER_TOP));
		pParentLayerGold->setPosition(POS(ccp(17 - (923 - 480)/2, 15), ScaleUtil::CENTER_TOP));
		pParentLayerGold->setAnchorPoint(CCPointZero);
		pParentLayerGold->setTag(TAG_PARENTGold);
		this->addChild( pParentLayerGold , 1 );
		pParentLayerGold->release();
	}
	

	CCSize innerSize( 450, 522 );
	// Add background1
	
	CCUIBackground *pBackground1 = new CCUIBackground();
	pBackground1->initWithSpriteFrame("popuibg/bg1.png", 
		CCPointZero,
		CCPointZero, 
		CCSizeMake(/*cs.width*/POSX(innerSize.width +40), cs.height));
	pBackground1->setPosition(POS(ccp(17 + (923 - 470)/2, 15), ScaleUtil::CENTER_TOP));
	this->addChild(pBackground1 , 0);
	pBackground1->release();

	// Add background2
	CCUIBackground *pBackground2 = new CCUIBackground();
	pBackground2->initWithSpriteFrame(  "ui2.png", 
		ccp(POSX(8), POSX(19)),
		ccp(0,0), 
		CCSizeMake( POSX(innerSize.width), POSX(innerSize.height) )  );
	pParentLayer->addChild(pBackground2);
	pBackground2->release();
	
	CCSize csLabel( POSX(390), POSX(28) );
	float fFont( POSX(28) );

	// title
	CCSprite* spTitle = CCSprite::spriteWithSpriteFrameName("levy/title.png");
	spTitle->setPosition( ccp(POSX(189), POSX(500)) );
	spTitle->setAnchorPoint(CCPointZero);
	pParentLayer->addChild( spTitle );

	// _txtAmount Font
	CCLabelTTF* pLabel = CCLabelTTF::labelWithString( LangManager::getText("LVY024").c_str(),
		CCSizeMake(POSX(240), POSX(28)), CCTextAlignmentLeft, g_sSimHeiFont, fFont );
	pLabel->setPosition( ccp( POSX(35), POSX(451) ) );
	pLabel->setAnchorPoint( CCPointZero );
	pLabel->setColor( ccc3(0xff, 0xc6, 0x00) );
	pParentLayer->addChild( pLabel );

	// _txtAmount
	_txtAmount = CCLabelTTF::labelWithString( "", 
		CCSizeMake(POSX(95), POSX(28)), CCTextAlignmentLeft, g_sSimHeiFont, fFont );
	_txtAmount->setPosition( ccp( POSX(260), POSX(451) ) );
	_txtAmount->setAnchorPoint( CCPointZero );
	_txtAmount->setColor( ccc3(0x30, 0xff, 0x00) );
	pParentLayer->addChild( _txtAmount );

	
	// Levy Money text
	CCLabelTTF* txtLevy = CCLabelTTF::labelWithString( LangManager::getText("LVY025").c_str(),
		csLabel, CCTextAlignmentLeft, g_sSimHeiFont, fFont );
	txtLevy->setPosition( ccp( POSX(35), POSX(411) ) );
	txtLevy->setAnchorPoint( CCPointZero );
	txtLevy->setAnchorPoint( CCPointZero );
	txtLevy->setColor( ccc3(0xff, 0xc6, 0x00) );
	pParentLayer->addChild( txtLevy );
	
	//Begin Kenfly 20121025 : modify
	/*
	// Levy Gold
	CCSprite* spLevyGold = CCSprite::spriteWithSpriteFrameName("levy/gold.png");//gold pic
	spLevyGold->setAnchorPoint( CCPointZero );
	spLevyGold->setPosition( ccp(POSX(172), POSX(411)) );
	pParentLayer->addChild( spLevyGold );

	CCLabelTTF* _txtLevyGold = CCLabelTTF::labelWithString( "1", csLabel, CCTextAlignmentLeft, g_sSimHeiFont, fFont );	// gold txt
	_txtLevyGold->setPosition( ccp( POSX(215), POSX(411) ) );
	_txtLevyGold->setAnchorPoint( CCPointZero );
	_txtLevyGold->setColor( ccc3(0xff, 0xc6, 0x00) );
	pParentLayer->addChild( _txtLevyGold );
	*/
	//End Kenfly 20121025

	// Levy Silver
	CCSprite* spLevySilver = CCSprite::spriteWithSpriteFrameName("levy/silver.png");	//silver pic
	spLevySilver->setAnchorPoint( CCPointZero );
	spLevySilver->setPosition( ccp(POSX(172), POSX(411)) );
	pParentLayer->addChild( spLevySilver );

	_txtLevySilver = CCLabelTTF::labelWithString( "", csLabel, CCTextAlignmentLeft, g_sSimHeiFont, fFont );	//silver txt
	_txtLevySilver->setPosition( ccp( POSX(215), POSX(411) ) );
	_txtLevySilver->setAnchorPoint( CCPointZero );
	_txtLevySilver->setColor( ccc3(0xff, 0xc6, 0x00) );
	pParentLayer->addChild( _txtLevySilver );


	//// _cdTime
	//_cdTime = CCLabelTTF::labelWithString( "", csLabel, CCTextAlignmentLeft, g_sSimHeiFont, fFont );
	//_cdTime->setPosition( ccp( POSX(35), POSX(368) ) );
	//_cdTime->setAnchorPoint( CCPointZero );
	//pParentLayer->addChild( _cdTime );

	//// _goldCost
	//_goldCost = CCLabelTTF::labelWithString( "", CCSizeMake( POSX(160), POSX(40) ), CCTextAlignmentLeft, g_sSimHeiFont, fFont );
	//_goldCost->setPosition( ccp( POSX(425), POSX(175) ) );
	//_goldCost->setAnchorPoint( CCPointZero );
	//_goldCost->setColor( ccc3(0xff, 0xc6, 0x00) );
	//pParentLayer->addChild( _goldCost );

	/*
	CCLabelTTF* _effectSys = CCLabelTTF::labelWithString( ValuesUtil::Instance()->getString("LVY026").c_str(),
		CCSizeMake( POSX(280), POSX(28) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(28) );
	_effectSys->setPosition( ccp( POSX(59), POSX(323) ) );
	_effectSys->setAnchorPoint( CCPointZero );
	_effectSys->setColor( ccc3(255, 204, 0) );
	pParentLayer->addChild( _effectSys );

	_txtIn1 = CCLabelTTF::labelWithString( "",
		CCSizeMake( POSX(375), POSX(28) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(28) );
	_txtIn1->setPosition( ccp( POSX(59), POSX(292) ) );
	_txtIn1->setAnchorPoint( CCPointZero );
	_txtIn1->setColor( ccWHITE );
	pParentLayer->addChild( _txtIn1 );
	*/

	//_txtIn2 = CCLabelTTF::labelWithString( "",
	//	CCSizeMake( POSX(270), POSX(28) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(28) );
	//_txtIn2->setPosition( ccp( POSX(325), POSX(95) ) );
	//_txtIn2->setAnchorPoint( CCPointZero );
	//_txtIn2->setColor( ccWHITE );
	//pParentLayer->addChild( _txtIn2 );

	CCSprite* pGlodDui = new CCSprite;
	if ( pGlodDui && pGlodDui->initWithSpriteFrameName("levy/gold_show.png") )
	{
		pGlodDui->setAnchorPoint( CCPointZero );
		pGlodDui->setPosition( ccp(POSX(76), POSX(120)) );
		pParentLayer->addChild( pGlodDui );
		pGlodDui->release();
	}

	CCSize csBt( POSX(121), POSX(49) );
	// _levy btn
	if (RoleManage::Instance()->roleLev() >= LevLimitConst::Limit_Levy)
	{
		
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			_LevyItem = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this,
				menu_selector(LevyView::onLevy) );
			_LevyItem->setPosition( ccp( POSX(162)+csBt.width/2, POSX(34)+csBt.height/2 ) );
			_LevyItem->setTag( TAG_MENU_ITEM );
			_levy = CCMenu::menuWithItems(_LevyItem, 0);
			_levy->setTouchLayer( TLE::WindowLayer_Common_btn );
			_levy->setPosition( CCPointZero );
			pParentLayer->addChild( _levy );
			string txt = ValuesUtil::Instance()->getString( "LVY027" );
			CCLabelTTF* txtLabel = CCLabelTTF::labelWithString( txt.c_str(), csBt, CCTextAlignmentCenter, g_sSimHeiFont, fFont );
			txtLabel->setPosition( ccp( csBt.width/2, csBt.height/2 ) );
			_LevyItem->addChild( txtLabel );
		}
		
	}

	// close btn
	CCSprite *pCloseNormalSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_normal.png");
	CCSprite *pClosePressedSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_pressed.png");
	CCMenuItemSprite *_btnX = CCMenuItemSprite::itemFromNormalSprite(
		pCloseNormalSprite,
		pClosePressedSprite,
		this, 
		menu_selector(LevyView::clickCloseHandler) );
	//_btnX->setPosition(ccp(POSX(910 )-cs.width/2 + POSX(innerSize.width +100)/2, POSX(592)));
	_btnX->setPosition(POS(ccp(910-923/2 + (450 +100)/2, 592), ScaleUtil::CENTER_TOP));
	CCMenu *buttonMenu = new CCMenu();
	buttonMenu->init();
	buttonMenu->setTouchLayer( TLE::WindowLayer_Common_btn );
	buttonMenu->addChild(_btnX, 0);
	buttonMenu->setPosition(CCPointZero);
	this->addChild(buttonMenu,1);
	buttonMenu->release();
	
	_info = RoleManage::Instance()->accountInfo();          //save cur gold account

	//Custom CD
	_cd = new CustomCD( CDManage::COLLECTION );
	_cd->setPosition( ccp(POSX(136-20), POSX(323+(411-323)/2-5)) );
	_cd->setTag(TAG_CD);
	pParentLayer->addChild( _cd );
	CCMenuItemFont *pCDlockTimeNameItem = (CCMenuItemFont *)_cd->_tf->getChildByTag(2);
	pCDlockTimeNameItem->setFontSizeObj(POSX(36));
	pCDlockTimeNameItem->setColor(ccYELLOW);
	_cd->m_cpBtOffset = ccp(POSX(8),POSX(5));

	CDManage::Instance()->addEventListener( CDManage::CDCHANGED, this, callfuncND_selector(LevyView::cdChangedHandler) ); 

	int type = CDManage::Instance()->getLockBytype( CDManage::COLLECTION );
	isLockHandler(type);

	return true;
}

void LevyView::clickCloseHandler(CCObject * pSender)
{
	if (!g_pLevyMediator->_levyView)
	{
		return;
	}	

	//PopContainer::clickCloseHandler(pSender);
	//PopContainer::close();

	// new hand
	{
		int nLevType = -1; 
		int nButtonId = -1; 
		int nOverId = -1; 
		if (pParentLayerGold->getIsVisible())
		{
			nLevType = LevLimitConst::Limit_GoldLevy;
			nButtonId = ButtonIDConst::ButtonID_GoldLevy;
			nOverId = NewhandConst::EVENT_GOLDLEVY_GET;
		}
		else if (pParentLayer->getIsVisible())
		{
			nLevType = LevLimitConst::Limit_Levy;
			nButtonId = ButtonIDConst::ButtonID_Levy;
			nOverId = NewhandConst::EVENT_LEVY_GET;
		}
		else
		{

		}
		if (NewhandManager::Instance()->getNewHandStateByType(nLevType) == NewhandManager::Flag_New)
		{
			NewhandManager::Instance()->touchNextScript("addBtn" , nButtonId);
		}
		else if (NewhandManager::Instance()->getNewHandStateByType(nLevType) == NewhandManager::Flag_Done)
		{
			NewhandManager::Instance()->setNewHandStateByType(nLevType , NewhandManager::Flag_Close);
			NewhandManager::Instance()->touchNextEvent(nOverId);
			//NewhandManager::Instance()->doTaskFollow();
		}
	}

	this->setisPop(false); //LH20120108
	//PopContainer::clickCloseHandler(0);
	
}

void LevyView::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate( this, TLE::WindowLayer_Common_btn, true );
}

bool LevyView::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void LevyView::setInfo( LevyInfoVo* info )
{
	_cd->reinit();

	_silver = info->reward;

	char txt[54];
	sprintf( txt, "%d", _silver );
	_txtLevySilver->setString( txt );

 	_rest = info->rest;
 	_limit = info->max;
 	sprintf( txt, "%d/%d", _rest, _limit );
 	_txtAmount->setString( txt );
	//_txtAmount->setString( "" );

	_levyCost = info->cost;

}

void LevyView::setParamInfo( int starNum, int uniteLv, int earth, int roleLev )
{
	if (_txtIn1)
	{
		_txtIn1->setString( LangManager::getText("LVY010").c_str() );
	}	
	//_txtIn2->setString( LangManager::getText("LVY011", earth).c_str() );
	//_txtIn3->setString( LangManager::getText("LVY012", uniteLv).c_str() );
	//_txtIn4->setString( LangManager::getText("LVY013", starNum).c_str() );
}


void LevyView::rest( uint iValue )
{
	_rest = iValue; 
	_txtAmount->setString( LangManager::getText("LVY024", iValue, _limit).c_str() );
}

void LevyView::reward( uint iValue)
{
	//silver
	_levyReward = iValue;
	char silver_fmt[10];
	sprintf( silver_fmt, "%d", iValue );
	_txtLevySilver->setString( silver_fmt );
}

void LevyView::limit( uint iValue )
{
	_limit = iValue;

	char txt[54];
	sprintf( txt, "%d/%d", _rest, _limit );
	_txtAmount->setString( txt );

	//_txtAmount->setString( LangManager::getText("LVY024", _rest, _limit).c_str() );
}

void LevyView::cdChangedHandler( CCNode* n, void* data )
{
	CDEvent* e = (CDEvent*)data;
	if( e->cdType == CDManage::COLLECTION )
	{
		isLockHandler( e->lock );
	}
}
void LevyView::isLockHandler( int lock )
{
	if (!_levy)
	{
		return;
	}
	
	CCMenuItemImage* pItem = (CCMenuItemImage*)_levy->getChildByTag( TAG_MENU_ITEM );
	if ( !pItem )
	{
		return;
	}
	if(lock==1)
	{
		//Utils::applyButtonEnable( _levy, false );
		pItem->setIsEnabled(false);
	}
	else
	{
		//Utils::applyButtonEnable( _levy, true );
		pItem->setIsEnabled(true);
	}		
}

void LevyView::onLevy( CCObject* pSender )
{

	if( (_info->silver()+_levyReward) >_info->silverLim() )
	{
		LangManager::msgShow("LVY014");
	}
	else
	{
		int param = 1;
		GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::LEVY_TYPE, &param );
		//dispatcher.dispatchEvent(new ParamEvent(GameDispatcher.LEVY_TYPE,1));
	}

	SoundManager::Instance()->playButtonEffectSound();

	if (_LevyItem)
	{
		_LevyItem->setIsEnabled(false);
		CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(LevyView::lockBtn),
			this,0.2f,false);
	}
	

	// new hand
	if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_Levy) == NewhandManager::Flag_New)
	{
		NewhandManager::Instance()->setNewHandStateByType(LevLimitConst::Limit_Levy , NewhandManager::Flag_Done);
		NewhandManager::Instance()->touchNextEvent(NewhandConst::EVENT_LEVY_GET);
	}
}

void LevyView::lockBtn(ccTime dt)
{
	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(LevyView::lockBtn), this);
	if (_LevyItem)
	{
		int lock = CDManage::Instance()->getLockBytype(CDManage::COLLECTION);
		if(lock==1)
		{
			_LevyItem->setIsEnabled(true);
		}
		else
		{
			_LevyItem->setIsEnabled(true);
		}

	}
}

void LevyView::showLevyButton()
{
	if (RoleManage::Instance()->roleLev() >= LevLimitConst::Limit_Levy)
	{
		if (!_levy)
		{
			CCSize csBt( POSX(121), POSX(49) );
			float fFont( POSX(28) );
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
			if(pNormalSprite && pPressedSprite && pSelectdSprite)
			{
				_LevyItem = CCMenuItemSprite::itemFromNormalSprite(
					pNormalSprite,
					pPressedSprite,
					pSelectdSprite,
					this,
					menu_selector(LevyView::onLevy) );
				_LevyItem->setPosition( ccp( POSX(162)+csBt.width/2, POSX(34)+csBt.height/2 ) );
				_LevyItem->setTag( TAG_MENU_ITEM );
				_levy = CCMenu::menuWithItems(_LevyItem, 0);
				_levy->setTouchLayer( TLE::WindowLayer_Common_btn );
				_levy->setPosition( CCPointZero );
				pParentLayer->addChild( _levy );
				string txt = ValuesUtil::Instance()->getString( "LVY027" );
				CCLabelTTF* txtLabel = CCLabelTTF::labelWithString( txt.c_str(), csBt, CCTextAlignmentCenter, g_sSimHeiFont, fFont );
				txtLabel->setPosition( ccp( csBt.width/2, csBt.height/2 ) );
				_LevyItem->addChild( txtLabel );
			}
		}
	}
}

CCNode * LevyView::getNewHandItem(int id)
{
	switch (id)
	{
	case 100:
		{
			return _LevyItem;
		}
		break;
	case 101:
		{
			if (g_pLevyMediator && g_pLevyMediator->_goldPanel)
			{
				return  ((GoldLevyPanel *)((LevyMediator *)g_pLevyMediator)->_goldPanel)->_GoldItem;
			}
		}
		break;
	default:		
		break;
	}
	return 0;
}