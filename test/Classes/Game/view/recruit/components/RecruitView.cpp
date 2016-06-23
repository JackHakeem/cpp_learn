#include "RecruitView.h"
#include "manager/PopEventName.h"
#include "view/train/components/TrainView.h"
#include "utils/ValuesUtil.h"
#include "RecruitPanel.h"
#include "model/recruit/vo/RecruitInfo.h"
#include "Message.h"
#include "events/GameDispatcher.h"
#include "../RecruitMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "SkillPic.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "manager/LangManager.h"
#include "CCUIBackground.h"
#include "model/skill/SkillManager.h"
#include "model/skill/SkillProxy.h"
#include "view/figure/components/SkillItem.h"
#include "utils/TipHelps.h"
#include "RecruitTips.h"
#include "manager/layer/TipsLayer.h"
#include "manager/LayerManager.h"
#include "manager/LevLimitConst.h"
#include "manager/ViewManager.h"

static const int TAG_PARENT_LAYER = 1101;
static const int Tag_skill1 = 1102;
static const int Tag_skill2 = 1103;
static const int Tag_skill3 = 1104;

RecruitView::RecruitView()
{
	pParentLayer = 0;
	_curIndex = 0;
	_myTroops = 0;
	_myExp = 0;
	_page = 1;
	_info = 0;
	_totalPage = 1;
	
	_myPop = 0;
	_name = 0;		
	_blood = 0;		
	_stamina = 0;	
	_brawn = 0;		
	_intell = 0;   

	_txtAbout = 0;
	_txtForce = 0;

	_txtCareer = 0;

	_money = 0;    
	_fame = 0;     

	_rebirthPic = 0;

	_pic1 = 0;
	_pic2 = 0;
	_pic3 = 0;
	_icon1 = 0;
	_icon2 = 0;
	_icon3 = 0;
	_icon = 0;

	m_selectedSpriteImage = 0;
	m_locationInView = CCPointZero;
	m_helpBtn = 0;
	_bgSkillTips = 0;
}

bool RecruitView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	// initial key
	key = PopEventName::RECRUIT;
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/streng/res_heritage2.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/res_icon.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/res_skill_icon.plist");

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize panelSize( POSX(923), POSX(562) );
	this->setContentSize(winSize);
	this->setPopContentSize( winSize );

	pParentLayer = new CCLayer();
	if(!pParentLayer)
	{
		return false;
	}
	pParentLayer->init();
	pParentLayer->setContentSize( panelSize );
	pParentLayer->setAnchorPoint(CCPointZero);
	pParentLayer->setPosition(POS(ccp(17, 12), ScaleUtil::CENTER_TOP));
	this->addChild( pParentLayer );
	pParentLayer->setTag(TAG_PARENT_LAYER);
	pParentLayer->release();
	
	// left bg
	CCUIBackground* bgLeft = new CCUIBackground();
	bgLeft->initWithSpriteFrame( "popuibg/bg2.png",
		ccp(POSX(10), POSX(20)), ccp(0,0), CCSizeMake(POSX(500), POSX(522)) );
	pParentLayer->addChild( bgLeft );
	bgLeft->release();

	//right bg
	bgLeft = new CCUIBackground();
	bgLeft->initWithSpriteFrame( "popuibg/bg2.png",
		ccp(POSX(518), POSX(20)), ccp(0,0), CCSizeMake(POSX(398), POSX(522)) );
	pParentLayer->addChild( bgLeft );
	bgLeft->release();

	_recPanel = RecruitPanel::recruitPanelScrollViewWithCCRect( CCRectMake( POSX(20), POSX(70), POSX(480), POSX(460) ) );
	pParentLayer->addChild( _recPanel );

	_myTroops = CCLabelTTF::labelWithString( "",
		CCSizeMake( POSX(130), POSX(26) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(20) );
	_myTroops->setAnchorPoint(CCPointZero);
	_myTroops->setPosition( ccp( POSX(33+25), POSX(62-20) ) );
	_myTroops->setColor(ccWHITE);
	pParentLayer->addChild( _myTroops );

	_myPop = CCLabelTTF::labelWithString( "",
		CCSizeMake( POSX(150), POSX(26) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(20) );
	_myPop->setPosition( ccp( POSX(33+130+10), POSX(62-20) ) );
	_myPop->setAnchorPoint(CCPointZero);
	_myPop->setColor(/*ccc3(255,198,0)*/ccWHITE);
	pParentLayer->addChild( _myPop );

	_myExp = CCLabelTTF::labelWithString( "",
		CCSizeMake( POSX(150), POSX(26) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(20) );
	_myExp->setPosition( ccp( POSX(33+130+10+150+10), POSX(62-20) ) );
	_myExp->setAnchorPoint(CCPointZero);
	_myExp->setColor(/*ccc3(255,198,0)*/ccWHITE);
	pParentLayer->addChild( _myExp );

	// recruit btn
	CCSize csBt( POSX(121), POSX(49) );
	{
		{
			CCMenuItemSprite *pRecruitItem = CCMenuItemSprite::itemFromNormalSprite(
				CCSprite::spriteWithSpriteFrameName("button.png"),
				CCSprite::spriteWithSpriteFrameName("button1.png"),
				CCSprite::spriteWithSpriteFrameName("button2.png"),
				this,
				menu_selector(RecruitView::onRecruitClick) );
			pRecruitItem->setPosition( ccp( POSX(617.0f+125/2+50-120), POSX(35.0f+49/2+20) ) );
			pRecruitItem->setTag(101);
			_recruitBtn = CCMenu::menuWithItems(pRecruitItem, 0);
			_recruitBtn->setTouchLayer( TLE::WindowLayer_Common_btn );
			_recruitBtn->setPosition( CCPointZero );
			pParentLayer->addChild( _recruitBtn );
			string txt = ValuesUtil::Instance()->getString( "RCR034" );
			CCLabelTTF* txtLabel = CCLabelTTF::labelWithString( txt.c_str(), csBt, CCTextAlignmentCenter, g_sSimHeiFont, POSX(20) );
			txtLabel->setPosition( ccp( csBt.width/2, csBt.height/2 ) );
			pRecruitItem->addChild( txtLabel );
		}
	}

	// dismiss btn
	{
		{
			CCMenuItemSprite *pDismissItem = CCMenuItemSprite::itemFromNormalSprite(
				CCSprite::spriteWithSpriteFrameName("button.png"),
				CCSprite::spriteWithSpriteFrameName("button1.png"),
				CCSprite::spriteWithSpriteFrameName("button2.png"),
				this,
				menu_selector(RecruitView::onDismissClick) );
			pDismissItem->setPosition( ccp( POSX(617.0f+125/2+50+100), POSX(35.0f+49/2+20) ) );
			_dismissBtn = CCMenu::menuWithItems( pDismissItem, 0 );
			_dismissBtn->setTouchLayer( TLE::WindowLayer_Common_btn );
			_dismissBtn->setPosition( CCPointZero );
			pParentLayer->addChild( _dismissBtn );
			string txt = ValuesUtil::Instance()->getString( "RCR035" );
			CCLabelTTF* txtLabel = CCLabelTTF::labelWithString( txt.c_str(), csBt, CCTextAlignmentCenter, g_sSimHeiFont, POSX(20) );
			txtLabel->setPosition( ccp( csBt.width/2, csBt.height/2 ) );
			pDismissItem->addChild( txtLabel );
		}
	}
	
	// help btn
	{
		{
			m_helpBtn = CCMenuItemSprite::itemFromNormalSprite(
				CCSprite::spriteWithSpriteFrameName("button.png"),
				CCSprite::spriteWithSpriteFrameName("button1.png"),
				this,
				menu_selector(RecruitView::helpHandler) );
			m_helpBtn->setPosition( ccp( POSX(808-30+125/2), POSX(478+49/2) ) );
			CCMenu* btn = CCMenu::menuWithItems( m_helpBtn, 0 );
			btn->setTouchLayer(  TLE::WindowLayer_Common );
			btn->setPosition( CCPointZero );
			pParentLayer->addChild( btn );
			CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
				ValuesUtil::Instance()->getString( "STG104" ).c_str(),
				csBt, CCTextAlignmentCenter, g_sSimHeiFont, POSX(20) );
			txtLabel->setPosition( ccp( csBt.width/2, csBt.height/2 ) );
			m_helpBtn->addChild( txtLabel );
		}
	}	

	int labelH( POSX(18+3) );
	//name
	_name = CCLabelTTF::labelWithString( "",
		CCSizeMake( POSX(280), labelH ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );
	_name->setPosition( ccp( POSX(612+20), POSX(495-3) ) );
	_name->setAnchorPoint(CCPointZero);
	pParentLayer->addChild( _name, 2 );

	_txtCareer = CCLabelTTF::labelWithString( "", CCSizeMake( POSX(220-53), labelH ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );
	_txtCareer->setPosition( ccp( POSX(632/*+53*/), POSX(450) ) );
	_txtCareer->setAnchorPoint(CCPointZero);
	pParentLayer->addChild( _txtCareer );

	//about
	CCLabelTTF* pAbout = CCLabelTTF::labelWithString( 
		ValuesUtil::Instance()->getString("RCR041").c_str(),
		CCSizeMake( POSX(95), POSX(22) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );
	pAbout->setPosition( ccp(POSX(535), POSX(379+20) ) );
	pAbout->setAnchorPoint(CCPointZero);
	pParentLayer->addChild( pAbout );
	pAbout->setColor(ccc3(255,180,0));
	pAbout->setIsVisible(false);

	_txtAbout = CCLabelTTF::labelWithString( "", CCSizeMake( POSX(295), POSX(40) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );
	_txtAbout->setPosition( ccp(POSX(535+90), POSX(379+2) ) );
	_txtAbout->setAnchorPoint(CCPointZero);
	pParentLayer->addChild( _txtAbout );
	_txtAbout->setIsVisible(false);

	int label22( POSX(22+3) );
	int offH(40);
	int offset(15);
	//_blood
	CCLabelTTF* blood = CCLabelTTF::labelWithString( 
		ValuesUtil::Instance()->getString("RCR036").c_str(),
		CCSizeMake( POSX(88), label22 ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(22) );
	blood->setPosition( ccp( POSX(531+offset), POSX(347+offH) ) );
	blood->setAnchorPoint(CCPointZero);
	pParentLayer->addChild( blood );
	blood->setColor(ccc3(255,180,0));

	_blood = CCLabelTTF::labelWithString( 
		"",
		CCSizeMake( POSX(22*4), label22 ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(22) );
	_blood->setPosition( ccp( POSX(531+offset+88), POSX(347+offH) ) );
	_blood->setAnchorPoint(CCPointZero);
	_blood->setColor(ccWHITE);
	pParentLayer->addChild( _blood );

	//_stamina
	CCLabelTTF* stamina = CCLabelTTF::labelWithString(
		ValuesUtil::Instance()->getString("RCR037").c_str(), 
		CCSizeMake( POSX(88), label22 ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(22) );
	stamina->setPosition( ccp( POSX(531+offset), POSX(320+offH) ) );
	stamina->setAnchorPoint(CCPointZero);
	pParentLayer->addChild( stamina );
	stamina->setColor(ccc3(255,180,0));

	_stamina = CCLabelTTF::labelWithString( "",
		CCSizeMake( POSX(22*4), label22 ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(22) );
	_stamina->setPosition( ccp( POSX(531+offset+88), POSX(320+offH) ) );
	_stamina->setAnchorPoint(CCPointZero);
	_stamina->setColor(ccWHITE);
	pParentLayer->addChild( _stamina );

	//_brawn
	CCLabelTTF* brawn = CCLabelTTF::labelWithString(
		ValuesUtil::Instance()->getString("RCR038").c_str(),
		CCSizeMake( POSX(88), label22 ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(22) );
	brawn->setPosition( ccp(POSX(531+offset), POSX(320-27+offH)) );
	brawn->setAnchorPoint(CCPointZero);
	pParentLayer->addChild( brawn );
	brawn->setColor(ccc3(255,180,0));

	_brawn = CCLabelTTF::labelWithString( "",
		CCSizeMake( POSX(22*4), label22 ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(22) );
	_brawn->setPosition( ccp(POSX(531+offset+88), POSX(320-27+offH)) );
	_brawn->setAnchorPoint(CCPointZero);
	_brawn->setColor(ccWHITE);
	pParentLayer->addChild( _brawn );
	
	//_intell
	CCLabelTTF* intell = CCLabelTTF::labelWithString( 
		ValuesUtil::Instance()->getString("RCR039").c_str(),
		CCSizeMake( POSX(88), label22 ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(22) );
	intell->setPosition( ccp(POSX(531+offset), POSX(320-27*2+offH) ) );
	intell->setAnchorPoint(CCPointZero);
	pParentLayer->addChild( intell );
	intell->setColor(ccc3(255,180,0));

	_intell = CCLabelTTF::labelWithString( "",
		CCSizeMake( POSX(22*4), label22 ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(22) );
	_intell->setPosition( ccp(POSX(531+offset+88), POSX(320-27*2+offH) ) );
	_intell->setAnchorPoint(CCPointZero);
	_intell->setColor(ccWHITE);
	pParentLayer->addChild( _intell );

	CCSprite* pIcon = new CCSprite;
	if ( pIcon && pIcon->initWithSpriteFrameName("new/skill_icon.png") )
	{
		pIcon->setAnchorPoint(CCPointZero);
		pIcon->setPosition(ccp(POSX(505+24+20),POSX(207-27+offH)));
		pParentLayer->addChild(pIcon);
	}		

	//_fame
	CCLabelTTF* tmpLabel = CCLabelTTF::labelWithString( LangManager::getText("RCR015").c_str(),
		CCSizeMake( POSX(18*7), label22 ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(22) );
	tmpLabel->setPosition( ccp( POSX(531+offset), POSX(123-3+offH) ) );
	tmpLabel->setAnchorPoint(CCPointZero);
	pParentLayer->addChild( tmpLabel );
	tmpLabel->setColor(ccc3(255,180,0));

	_fame = CCLabelTTF::labelWithString( "",
		CCSizeMake( POSX(330), label22 ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(22) );
	_fame->setPosition( ccp( POSX(531+offset+18*5+22), POSX(123-3+offH) ) );
	_fame->setAnchorPoint(CCPointZero);
	pParentLayer->addChild( _fame );
	_fame->setColor(ccRED);

	//_money
	tmpLabel = CCLabelTTF::labelWithString( LangManager::getText("RCR017").c_str(),
		CCSizeMake( POSX(18*7), label22 ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(22) );
	tmpLabel->setPosition( ccp( POSX(531+offset), POSX(93-3+offH) ) );
	tmpLabel->setAnchorPoint(CCPointZero);
	pParentLayer->addChild( tmpLabel );
	tmpLabel->setColor(ccc3(255,180,0));

	_money = CCLabelTTF::labelWithString( "",
		CCSizeMake( POSX(330), label22 ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(22) );
	_money->setPosition( ccp( POSX(531+offset+18*5+22), POSX(93-3+offH) ) );
	_money->setAnchorPoint(CCPointZero);
	pParentLayer->addChild( _money );
	_money->setColor(ccWHITE);

	//head
	CCUIBackground* bgPic = new CCUIBackground();
	bgPic->initWithSpriteFrame( "ui.png",
		ccp(POSX(526), POSX(435-10)), ccp(0,0), CCSizeMake( POSX(105), POSX(105) ) );
	pParentLayer->addChild( bgPic );
	bgPic->release();
	_icon = CCSprite::spriteWithFile( "assets/icon/head/unknown.png" );
	_icon->setPosition( ccp( POSX(105/2-1.5), POSX(105/2+3) ) );
	bgPic->addChild(_icon);
	_icon->setIsVisible(false);
	
	this->setIsTouchEnabled( true );

	m_selectedSpriteImage = new CCUIBackground();
	m_selectedSpriteImage->initWithSpriteFrame( "train/gold_back.png",
		CCPointZero, CCPointZero, CCSizeMake( POSX(215), POSX(105) ) );
	this->addChild( m_selectedSpriteImage );
	m_selectedSpriteImage->release();
	m_selectedSpriteImage->setIsVisible(false);

	CCSprite* pStrengJiantou = new CCSprite;
	pStrengJiantou->initWithSpriteFrameName("heritage_jiantou.png");
	pParentLayer->addChild(pStrengJiantou);
	pStrengJiantou->setPosition(ccp(POSX(14),POSX(300)));
	pStrengJiantou->setAnchorPoint(CCPointZero);
	pStrengJiantou->release();
	pStrengJiantou = new CCSprite;
	pStrengJiantou->initWithSpriteFrameName("heritage_jiantou.png");
	pStrengJiantou->setFlipX(true);
	pParentLayer->addChild(pStrengJiantou);
	pStrengJiantou->release();
	pStrengJiantou->setPosition(ccp(POSX(483),POSX(300)));
	pStrengJiantou->setAnchorPoint(CCPointZero);

	return true;

}

void RecruitView::helpHandler( CCObject* pSender )
{
	RecruitTips* pTips = (RecruitTips*)LayerManager::tipsLayer->getChildByTag(
		TipsLayer::TipsLayerTAG_tipHelpMelting);
	if (!pTips)
	{
		pTips = new RecruitTips;
		pTips->init();
		LayerManager::tipsLayer->addChild(pTips,
			TipsLayer::TipsLayerZ_tipHelpMelting, TipsLayer::TipsLayerTAG_tipHelpMelting);
		pTips->release();
	}

}

/**
* set index
* @param index int 0-
* @param first Boolean first or not, default false
*/
void RecruitView::setDefault( int tabIdx /*= 0*/ )
{
	_curIndex = 0;
}

/** 
* listening tab
* @param event
*/
void RecruitView::onTab1( CCObject* pSender )
{
	if(0 != _curIndex)
	{
		_curIndex = 0;
		_page = 1;
		//dispatchEvent(new ParamEvent(CHANGE_PAGE, {index :_curIndex, page: _page}));
		RecruitMediator* pRecruitMediator = (RecruitMediator*)g_pFacade->retrieveMediator( AppFacade_RECRUIT_PROXY_CHANGE );
		if ( pRecruitMediator )
		{
			cleanContent();
			pRecruitMediator->changePageHandler();
		}
	}
}
		
/**
* listening tab
* @param event
*/
void RecruitView::onTab2( CCObject* pSender )
{
	if(1 != _curIndex)
	{
		_curIndex = 1;
		_page = 1;
		//dispatchEvent(new ParamEvent(CHANGE_PAGE, {index :_curIndex, page: _page}));
		RecruitMediator* pRecruitMediator = (RecruitMediator*)g_pFacade->retrieveMediator( AppFacade_RECRUIT_PROXY_CHANGE );
		if ( pRecruitMediator )
		{
			cleanContent();
			pRecruitMediator->changePageHandler();
		}
	}
}

void RecruitView::setTroops( int roleNum, int roleLim )
{
	char troops[128];
	sprintf( troops, ValuesUtil::Instance()->getString( "RCR032" ).c_str(), roleNum, roleLim );
	_myTroops->setString( troops );
}

void RecruitView::setMyExp( int silver )
{
	char exp[52];


	sprintf( exp, ValuesUtil::Instance()->getString( "RCR033" ).c_str(),
		RoleManage::Instance()->accountInfo()->popularity() );
	_myPop->setString( exp );

	sprintf( exp, ValuesUtil::Instance()->getString( "RCR046" ).c_str(),
		RoleManage::Instance()->accountInfo()->silver() );
	_myExp->setString( exp );


	//var tips:TipHelps = new TipHelps();
	//tips.setToolTips(_myExp, Sentence.SILVER+":"+RoleManage.getInstance().accountInfo.silver);
}

/** 
* createRecruitPanel
* @param infos: can recruit array
* @param page : cur page
* @param pagesize 
*/ 
void RecruitView::createRecruitPanel( vector<RecruitInfo> infos, int page, uint totalPage, int pagesize )
{
	_recPanel->createItems( infos, page, totalPage, pagesize );
	_page = page;
	_totalPage = totalPage;
}

/**
* listen can recruit figure click
* @param event
*/
void  RecruitView::recItemHandler( RecruitItem* item )
{
	RecruitInfo* info = item->info();
	//item.highlight = true;
	_info = info;
	setContent(info);
}

/**
* onRecruitClick
* @param event
*/
void RecruitView::onRecruitClick( CCObject* pSender )
{
	if( !_info )
	{
		LangManager::msgShow("RCR010");
		//Message::Instance()->show( ValuesUtil::Instance()->getString("RCR010") );
		return;
	}

	RecruitMediator* pRecruitMediator = (RecruitMediator*)g_pFacade->retrieveMediator( AppFacade_RECRUIT_PROXY_CHANGE );
	if ( pRecruitMediator )
	{
		pRecruitMediator->recruitMercHandler( _info->mercId );
	}
	//GameDispatcher::instance()->dispatchEvent(new ParamEvent(RECRUIT_MERC, {mercId: _info.mercId}));
}
/**
* 监听解雇按钮
* @param event 
*/
void RecruitView::onDismissClick( CCObject* pSender )
{			
	if( !_info )
	{
		LangManager::msgShow("RCR011");
		//Message::Instance()->show( ValuesUtil::Instance()->getString("RCR011") );
		return;
	}
	if( _info->isRole )
	{
		LangManager::msgShow("RCR012");
		//Message::Instance()->show( ValuesUtil::Instance()->getString("RCR012") );
		return;
	}

	RecruitMediator* pRecruitMediator = (RecruitMediator*)g_pFacade->retrieveMediator( AppFacade_RECRUIT_PROXY_CHANGE );
	if ( pRecruitMediator )
	{
		pRecruitMediator->dismissMercHandler( _info->id );
	}
	//_dismissBtn.enabled = false;
	//GameDispatcher.getInstance().dispatchEvent(new ParamEvent(DISMISS_MERC, {id: _info.id}));
}

/**
* 设置面板内容
* @param info 当前Item info
*/
void RecruitView::setContent( RecruitInfo* info )
{
	pParentLayer = (CCLayer*)this->getChildByTag(TAG_PARENT_LAYER);
	if ( !pParentLayer )
	{
		return;
	}

	cleanContent();

	_info = info;
	char forStr[128];
	if (_icon)
	{
		_icon->setIsVisible(true);
	}

	CCArray * pArray = _recruitBtn->getChildren();
	CCObject* pObject = 0;
	CCMenuItemImage *pRecruitItem(0);
	CCMenuItemImage *pDismissItem(0);
	CCARRAY_FOREACH(pArray, pObject)
	{
		if( pObject == 0 )
			break;

		pRecruitItem = (CCMenuItemImage*)pObject;
	}
	pArray = _dismissBtn->getChildren();
	CCARRAY_FOREACH(pArray, pObject)
	{
		if( pObject == 0 )
			break;

		pDismissItem = (CCMenuItemImage*)pObject;
	}

	if( _info && (_info->isGray<2) )
	{
		//_recruitBtn.filters = [];  // 重置
		if( _info->isGray )
		{
			// isGray not allow to recruit or fired 
			pRecruitItem->setIsEnabled( false );
			//_recruitBtn->setIsVisible( true );
			if (_fame)
			{
				_fame->setColor(ccRED);
			}

			pDismissItem->setIsEnabled( false );
			//_dismissBtn->setIsVisible( false );
		}
		else if( _info->isHired )
		{
			// judge cold time
			pRecruitItem->setIsEnabled( false );
			//_recruitBtn->setIsVisible( false );
			if (_fame)
			{
				_fame->setColor(ccWHITE);
			}

			pDismissItem->setIsEnabled( true );
			//_dismissBtn->setIsVisible( true );
		}
		else
		{
			//_recruitBtn->setIsVisible( true );
			pRecruitItem->setIsEnabled( true );
			if (_fame)
			{
				_fame->setColor(ccWHITE);
			}

			pDismissItem->setIsEnabled( false );
			//_dismissBtn->setIsVisible( false );
		}

		map<int, RecruitItem*>::iterator it = _recPanel->_dic.find( info->mercId );
		if ( it != _recPanel->_dic.end() )
		{
			RecruitItem* pRecruitItem = it->second;

			if (_icon)
			{
				CCNode* pNode = _icon->getParent();
				_icon->removeFromParentAndCleanup(true);
				if( pRecruitItem->_info.isGray != 2 )
				{
					char strFormat[54];
					sprintf( strFormat, "assets/icon/head/%d.png", pRecruitItem->_info.cloth );
					_icon = CCSprite::spriteWithFile( strFormat );
				}
				else
				{
					_icon = CCSprite::spriteWithFile( "assets/icon/head/unknown.png" );
				}
				_icon->setPosition( ccp( POSX(105/2-1.5), POSX(105/2+3) ) );
				pNode->addChild(_icon);
			}			
		}

		ccColor3B c3 = RecruitItem::setTextColor( info->color );
		_name->setString( _info->name.c_str() );
		_name->setColor( c3 );
		
		sprintf( forStr, "%d", info->blood );
		_blood->setString( forStr );

		sprintf( forStr, "%d", info->stamina );
		_stamina->setString(forStr);

		// Career
		string str = GoodsToolTips::getCareerStr( info->careerId );
		sprintf( forStr, ValuesUtil::Instance()->getString( "COM004" ).c_str(), info->level );
		str.append(" ").append( forStr );
		_txtCareer->setString( str.c_str() );

		sprintf( forStr, "%d", info->strength );
		_brawn->setString(forStr);

		sprintf( forStr, "%d", info->intell );
		_intell->setString( forStr );

		str = info->explanation;
		_txtAbout->setString( str.c_str() );

		if( _info->needPop>0 )
		{
			sprintf( forStr, "%d", info->needPop );
			_fame->setString( forStr );
		}
		else
		{
			sprintf( forStr, "%s", info->requirement.c_str() );
			_fame->setString( forStr );
		}

		sprintf( forStr, "%d", info->silver );
		_money->setString( forStr );
		
		//skill 2
		SkillVo* skillVo = SkillManager::Instance()->getSkill( info->mainSkill1 );
		if( skillVo )
		{
			SkillProxy* pSkillProxy = (SkillProxy*)g_pFacade->retrieveProxy( AppFacade_SKILL_PROXY );
			UpGradeInfo* upInfo = pSkillProxy->getUpGradeInfo( info->mainSkill1, skillVo->rank );
			SkillItem * skillItem = new SkillItem(0, upInfo, 1);
			skillItem->setPosition( ccp(POSX(570+34+40), POSX(182-27+40)) );
			skillItem->setTag(Tag_skill2);
			pParentLayer->addChild( skillItem );
			skillItem->release();

			CCLabelTTF *_nameTextEx = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("NAM1").c_str(),
				CCSizeMake(POSX(120), POSX(40)),
				CCTextAlignmentCenter,
				g_sSimHeiFont,
				POSX(20));
			_nameTextEx->setPosition(ccp(POSX(0), POSX(5)));
			_nameTextEx->setColor(ccc3(12,233,25));
			_nameTextEx->setAnchorPoint(CCPointZero);
			_nameTextEx->setIsRelativeAnchorPoint(true);
			skillItem->addChild(_nameTextEx);

			CC_SAFE_DELETE(upInfo);
		}

		//skill 3
		skillVo = SkillManager::Instance()->getSkill( info->aoyiSkill );
		if( skillVo )
		{
			SkillProxy* pSkillProxy = (SkillProxy*)g_pFacade->retrieveProxy( AppFacade_SKILL_PROXY );
			UpGradeInfo* upInfo = pSkillProxy->getUpGradeInfo( info->aoyiSkill, skillVo->rank );
			SkillItem * skillItem = new SkillItem(0, upInfo, 1);
			skillItem->setPosition( ccp(POSX(669+36+40), POSX(182-27+40)) );
			skillItem->setTag(Tag_skill3);
			pParentLayer->addChild( skillItem );
			skillItem->release();

			CCLabelTTF *_nameTextEx = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("NAM2").c_str(),
				CCSizeMake(POSX(120), POSX(40)),
				CCTextAlignmentCenter,
				g_sSimHeiFont,
				POSX(20));
			_nameTextEx->setPosition(ccp(POSX(0), POSX(5)));
			_nameTextEx->setColor(ccc3(12,233,25));
			_nameTextEx->setAnchorPoint(CCPointZero);
			_nameTextEx->setIsRelativeAnchorPoint(true);
			skillItem->addChild(_nameTextEx);

			CC_SAFE_DELETE(upInfo);
		}

//		if(RoleManage.getInstance().roleLev<20){
//			skillForbid(_pic2, LangManager.getText("RCR018"));
//		}
	}
	else if( _info && _info->isGray==2 )
	{
		_recruitBtn->setIsVisible( true );
		pRecruitItem->setIsEnabled( false );

		if (_icon)
		{
			CCNode* pParentIcon = _icon->getParent();
			_icon->removeFromParentAndCleanup(true);
			_icon = CCSprite::spriteWithFile( "assets/icon/head/unknown.png" );
			_icon->setPosition( ccp( POSX(105/2-1.5), POSX(105/2+3) ) );
			pParentIcon->addChild(_icon);
		}

		//_rebirthPic->setString(" - ");
		_blood->setString(" - ");
		_stamina->setString(" - ");
		_brawn->setString(" - ");
		_intell->setString(" - ");
		_txtAbout->setString(" - ");
		//_txtForce->setString(" - ");
		_txtCareer->setString(" - ");

		if( _info->needPop>0 )
		{
			sprintf( forStr, "%d", info->needPop );
			_fame->setString( forStr );
		}
		else
		{
			sprintf( forStr, ValuesUtil::Instance()->getString("RCR016").c_str(), info->requirement.c_str() );
			_fame->setString( forStr );
		}

		sprintf( forStr, "%d", info->silver );
		_money->setString( forStr );
		
		//skill 2
		SkillVo* skillVo = SkillManager::Instance()->getSkill( info->mainSkill1 );
		if( skillVo )
		{
			SkillProxy* pSkillProxy = (SkillProxy*)g_pFacade->retrieveProxy( AppFacade_SKILL_PROXY );
			UpGradeInfo* upInfo = pSkillProxy->getUpGradeInfo( info->mainSkill1, skillVo->rank );
			SkillItem * skillItem = new SkillItem(0, upInfo, 1);
			skillItem->setPosition( ccp(POSX(570+34+40), POSX(182-27+40)) );
			skillItem->setTag(Tag_skill2);
			pParentLayer->addChild( skillItem );
			skillItem->release();

			CCLabelTTF *_nameTextEx = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("NAM1").c_str(),
				CCSizeMake(POSX(120), POSX(20)),
				CCTextAlignmentCenter,
				g_sSimHeiFont,
				POSX(20));
			_nameTextEx->setPosition(ccp(POSX(0), POSX(5)));
			_nameTextEx->setColor(ccc3(12,233,25));
			_nameTextEx->setAnchorPoint(CCPointZero);
			_nameTextEx->setIsRelativeAnchorPoint(true);
			skillItem->addChild(_nameTextEx);

			CC_SAFE_DELETE(upInfo);
		}

		//skill 3
		skillVo = SkillManager::Instance()->getSkill( info->aoyiSkill );
		if( skillVo )
		{
			SkillProxy* pSkillProxy = (SkillProxy*)g_pFacade->retrieveProxy( AppFacade_SKILL_PROXY );
			UpGradeInfo* upInfo = pSkillProxy->getUpGradeInfo( info->aoyiSkill, skillVo->rank );
			SkillItem * skillItem = new SkillItem(0, upInfo, 1);
			skillItem->setPosition( ccp(POSX(669+36+40), POSX(182-27+40)) );
			skillItem->setTag(Tag_skill3);
			pParentLayer->addChild( skillItem );
			skillItem->release();

			CCLabelTTF *_nameTextEx = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("NAM2").c_str(),
				CCSizeMake(POSX(120), POSX(20)),
				CCTextAlignmentCenter,
				g_sSimHeiFont,
				POSX(20));
			_nameTextEx->setPosition(ccp(POSX(0), POSX(5)));
			_nameTextEx->setColor(ccc3(12,233,25));
			_nameTextEx->setAnchorPoint(CCPointZero);
			_nameTextEx->setIsRelativeAnchorPoint(true);
			skillItem->addChild(_nameTextEx);

			CC_SAFE_DELETE(upInfo);
		}

//		skillForbid(_pic1, LangManager.getText("RCR019"));
//		skillForbid(_pic2, LangManager.getText("RCR020")
//		skillForbid(_pic3, LangManager.getText("RCR021"));
//				
	}

	if (RoleManage::Instance()->roleLev()<LevLimitConst::Limit_FigureLevBtn)
	{
		if (_dismissBtn)
		{
			_dismissBtn->setIsVisible(false);
		}
	}
}

/**
* 清空面板
*/
void RecruitView::cleanContent()
{
	_name->setString("");
	_blood->setString("");
	_stamina->setString("");
	_brawn->setString("");
	_intell->setString("");
	_txtCareer->setString("");
	_fame->setString("");
	_money->setString("");
	
	//_recruitBtn->setIsVisible(false);
	//_dismissBtn->setIsVisible(false);	

	SkillItem * skillItem = (SkillItem*)pParentLayer->getChildByTag( Tag_skill1 );
	if ( skillItem )
	{
		skillItem->removeFromParentAndCleanup(true);
	}
	skillItem = (SkillItem*)pParentLayer->getChildByTag( Tag_skill2 );
	if ( skillItem )
	{
		skillItem->removeFromParentAndCleanup(true);
	}
	skillItem = (SkillItem*)pParentLayer->getChildByTag( Tag_skill3 );
	if ( skillItem )
	{
		skillItem->removeFromParentAndCleanup(true);
	}
	_info = 0;
}

void RecruitView::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate( this, TLE::WindowLayer_Common, true );
}

bool RecruitView::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	m_locationInView = CCDirector::sharedDirector()->convertToGL( pTouch->locationInView(pTouch->view()) );

	RecruitTips* pTips = (RecruitTips*)LayerManager::tipsLayer->getChildByTag(
		TipsLayer::TipsLayerTAG_tipHelpMelting);
	if (pTips)
	{ 
		pTips->removeFromParentAndCleanup(true);
		return true;
	}

	if (_bgSkillTips)
	{
		_bgSkillTips->removeFromParentAndCleanup(true);
		_bgSkillTips = 0;
	}

	//if (m_helpBtn)
	//{
	//	CCPoint itemPoint = ccp( POSX(808-30), POSX(478) );// getScreenPos(m_helpBtn->getNormalImage());
	//	CCSize csBt( POSX(121/*+17*/), POSX(49/*+12*/) );
	//	//CCSize itemSize = (CCSprite*)(m_helpBtn->getNormalImage())->get;
	//	if ( CCRect::CCRectContainsPoint(
	//		CCRectMake(itemPoint.x,itemPoint.y, csBt.width,csBt.height), m_locationInView)
	//		)
	//	{
	//		//helpHandler(0);
	//		return false;
	//	}
	//}


	return true;
}

void RecruitView::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	m_locationInView = CCDirector::sharedDirector()->convertToGL( pTouch->locationInView(pTouch->view()) );

	for (int i = 0;i<3;i++)
	{
		SkillItem* skillItem = (SkillItem*)pParentLayer->getChildByTag(Tag_skill1+i);
		if ( !skillItem )
		{
			continue;
		}
		
		CCPoint itemPoint = getScreenPos(skillItem);
		CCSize itemSize = skillItem->getContentSize();
		if ( CCRect::CCRectContainsPoint(
			CCRectMake(itemPoint.x,itemPoint.y, itemSize.width,itemSize.height), m_locationInView)
			)
		{
			if( _info && _info->isGray==2 )
			{
				_bgSkillTips = new CCUIBackground();
				_bgSkillTips->initWithSpriteFrame("ui.png",
					ccp(m_locationInView.x-POSX(240+6), m_locationInView.y-POSX(36+7)), ccp(POSX(6),POSX(7)),
					CCSizeMake(POSX(240), POSX(36)));
				pParentLayer->addChild(_bgSkillTips, 1);
				_bgSkillTips->release();

				string str = LangManager::getText("RCR047");
				if (i==2)
				{
					str = LangManager::getText("RCR048");
				}
				CCLabelTTF* _nameEquipment = CCLabelTTF::labelWithString( 
					str.c_str(),
					CCSizeMake( POSX(220), POSX(30) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(20) );
				_nameEquipment->setColor(  ccGREEN  );
				_nameEquipment->setAnchorPoint(CCPointZero);
				_nameEquipment->setPosition( ccp( POSX(10), POSX(10) ) );
				_bgSkillTips->addChild( _nameEquipment, 2 );
			}
			else
			{
				TipHelps* pTip = skillItem->myTip;
				if ( !pTip )
				{
					continue;
				}

				pTip->rollOverHander();
			}
		}
	}
}

void RecruitView::clickCloseHandler( CCObject* pSender )
{
	RecruitTips* pTips = (RecruitTips*)LayerManager::tipsLayer->getChildByTag(
		TipsLayer::TipsLayerTAG_tipHelpMelting);
	if (pTips)
	{ 
		pTips->removeFromParentAndCleanup(true);
	}

	_recPanel->setIsTouchEnabled(false);

	PopContainer::clickCloseHandler(pSender);
}

void RecruitView::removeDataObjectChild()
{
	_recPanel->setIsTouchEnabled(false);
	_recPanel->removeAllChild();
}

CCNode * RecruitView::getNewHandItem(int id)
{
	switch (id)
	{
	case 5:
		{
			if (_recruitBtn)
			{
				return _recruitBtn->getChildByTag(101);
			}
		}
		break;
	case 6:
		{

		}
		break;
	default:
		break;
	}
	return 0;
}

RecruitView::~RecruitView()
{
	RecruitMediator* pMeditor = (RecruitMediator*)g_pFacade->retrieveMediator(AppFacade_RECRUIT_PROXY_CHANGE);
	if (pMeditor)
	{
		pMeditor->_recruitView = 0;
	}
	
	ViewManager::getInstance()->recruitView = 0;
		

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/streng/res_heritage2.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/icon/res_icon.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/icon/res_skill_icon.plist");

	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/streng/res_heritage2.pvr.ccz");
	//CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/icon/res_icon.pvr.ccz");
	//CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/icon/res_skill_icon.pvr.ccz");
}


//void RecruitView::setIsVisible( bool bIsVisible )
//{
//	_recPanel->setIsTouchEnabled(false);
//	_recPanel->removeAllChild();
//
//	CCLayer::setIsVisible( bIsVisible );
//}
