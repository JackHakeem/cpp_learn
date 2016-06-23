#include "CampFightView.h"
#include "UIListView/CCUIListView.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"
#include "utils/ColorUtil.h"
#include "manager/PopEventName.h"
#include "manager/LangManager.h"
#include "manager/TouchLayerEnum.h"
#include "BaseType.h"
#include "manager/GlobalManage.h"
#include "manager/LayerManager.h"

#include "mvc/Facade.h"
#include "control/AppFacade.h"
//leave
#include "socket/command/c45/CCMD452.h"
#include "socket/command/c45/CCMD454.h"
#include "socket/command/c45/CCMD456.h"
#include "socket/network/GameServerSocket.h"
//#include "ccTypes.h"

CampFightView::CampFightView()
{
	m_pCampFightProxy = NULL;
	if (g_pFacade)
	{
		m_pCampFightProxy = 
			dynamic_cast<CampFightProxy*>(g_pFacade->retrieveProxy(AppFacade_CampFight_Proxy));
		//m_pCampFightMediator = 
		//dynamic_cast<CampFightMediator*>(g_pFacade->retrieveMediator(AppFacade_CampFight_Mediator));
	}
	m_pContainer = 0;
	m_pbg        = 0;
	m_ptnClose   = 0;
	m_pLeftBg    = 0;
	m_pMidBg     = 0;
	m_pRightBg   = 0;

	m_pIceCityText   = 0;
	m_pIceCityScore  = 0;
	m_pFireCityText  = 0;
	m_pFireCityScore = 0;
	m_pTimeTips      = 0;
	m_pTimeContext   = 0;

	divide1 = 0;
	divide2 = 0;
	divide3 = 0;
	divide4 = 0;
	divide5 = 0;
	divide6 = 0;

	m_plsIcePlayers  = NULL;
	m_plsFirePlayers = NULL;
	m_plsMsg         = NULL;

	m_pFightLable = NULL;
	m_pBtnIFightMenu = NULL;
	m_pBtnCancelMenu = NULL;
	m_pBtnFightSpr = NULL;
	m_pBtnCancelSpr = NULL;

	m_myScoreLabel = NULL;
	m_myHisConWinTmsLabel = NULL;
	m_myTotalAwardLabel = NULL;
	m_attackAddLabel = NULL;
	m_lifeAddLabel = NULL;
}
CampFightView::~CampFightView()
{
	
}
bool CampFightView::init()
{
	do 
	{
		if (!LayerNode::init())
			return false;
		this->key = PopEventName::CAMPFIGHT; 
		//this->setIsTouchEnabled(true);
		//this->setIsRelativeAnchorPoint(true);
		//this->setAnchorPoint(CCPointZero);
		CCSize winSize;// = CCDirector::sharedDirector()->getWinSize();
		winSize.height = POSX(534);
		winSize.width = POSX(700);
		this->setPopContentSize(winSize);
		this->setContentSize(winSize);
		this->setNeedBg(NeedBg_NO);
		//this->setPosition();
		//this->setAnchorPoint(POS(128,828),ScaleUtil::CENTER);

		if (!m_pContainer)
		{
			m_pContainer = new CCLayer();
			if (!m_pContainer || !m_pContainer->init())
			{
				break;
			}
			this->addChild(m_pContainer);
			m_pContainer->setAnchorPoint(CCPointZero);
			/*
			screenSize.width * 1.0f /2, 
			screenSize.height * 1.0f /2
			*/
			CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
			//m_pContainer->setPosition(POS(
				//ccp((screenSize.width - winSize.width)*1.0f/2,(screenSize.height - winSize.height)*1.0f/2), 
				//ScaleUtil::BOTTOM_LEFT));//0 12 , ScaleUtil::CENTER_TOP
			m_pContainer->setPosition(POS(ccp(0,12) , ScaleUtil::CENTER_TOP));
			m_pContainer->release();
		}
		if (!m_pbg)
		{
			m_pbg = new CCUIBackground();
			m_pbg->initWithSpriteFrame("ui.png", CCPointZero,CCPointZero,winSize);
			m_pContainer->addChild(m_pbg, 0);
			m_pbg->release();
		}
		
		//Begin : add left background
		if (!m_pLeftBg)
		{
			m_pLeftBg = new CCUIBackground();
			m_pLeftBg->initWithSpriteFrame("ui2.png", ccp(POSX(10), POSX(10)), CCPointZero, CCSizeMake(POSX(194), POSX(514)));
			m_pLeftBg->setAnchorPoint(CCPointZero);
			m_pLeftBg->setPosition(ccp(POSX(10), POSX(10)));
			m_pContainer->addChild(m_pLeftBg,1);
			m_pLeftBg->release();
		}
		//End
		//Begin : add middle background
		if (!m_pMidBg)
		{
			m_pMidBg = new CCUIBackground();
			m_pMidBg->initWithSpriteFrame("ui2.png", ccp(POSX(10), POSX(10)), CCPointZero, CCSizeMake(POSX(292), POSX(514)));
			m_pMidBg->setAnchorPoint(CCPointZero);
			m_pMidBg->setPosition(ccp(POSX(204), POSX(10)));
			m_pContainer->addChild(m_pMidBg,2);
			m_pMidBg->release();
		}
		//End
		//Begin : add right background
		if (!m_pRightBg)
		{
			m_pRightBg = new CCUIBackground();
			m_pRightBg->initWithSpriteFrame("ui2.png", ccp(POSX(10), POSX(10)), CCPointZero, CCSizeMake(POSX(194), POSX(514)));
			m_pRightBg->setAnchorPoint(CCPointZero);
			m_pRightBg->setPosition(ccp(POSX(496), POSX(10)));
			m_pContainer->addChild(m_pRightBg,3);
			m_pRightBg->release();
		}
		//End

		//close buttom
		if (!m_ptnClose)
		{
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_normal.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_pressed.png");
			CCMenuItemSprite *btnSprit = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this, 
				menu_selector(CampFightView::onClose) );
			btnSprit->setPosition(ccp(POSX(690), POSX(524)));

			m_ptnClose = CCMenu::menuWithItems(btnSprit, 0); 
			m_ptnClose->setPosition( CCPointZero );
			m_ptnClose->setTouchLayer(TLE::WindowLayer_campFight);
			m_pContainer->addChild(m_ptnClose, 4);
		}
		//
		if (!InitLsView())
		{
			return false;
		}
		if (!InitLable())
		{
			return false;
		}
		if (!InitDivede())
		{
			return false;
		}
		if (!InitBtn())
		{
			return false;
		}
		if (!this->getisPop())
		{
			this->setisPop(true);
		}
		return true;
	} while (0);
	return false;
}
bool CampFightView::InitBtn()
{
	do 
	{
		//金币鼓舞按钮
		{
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
			if(pNormalSprite && pPressedSprite && pSelectdSprite)
			{
				CCMenuItemSprite* btnInspireSpr = CCMenuItemSprite::itemFromNormalSprite(
					pNormalSprite,
					pPressedSprite,
					pSelectdSprite,
					this,
					menu_selector(CampFightView::onInspireByGold) );
				//btnInspireSpr->setContentSize(CCSizeMake(POSX(103), POSX(26)));
				btnInspireSpr->setPosition( ccp(POSX(290), POSX(96)) );
				//_btnGUA->setAnchorPoint(ccp(0, 0));
				btnInspireSpr->setScale(0.8f);
				CCMenu* btnInspire = CCMenu::menuWithItems(btnInspireSpr, 0);
				btnInspire->setTouchLayer( TLE::WindowLayer_campFight );
				btnInspire->setPosition( CCPointZero );
				m_pContainer->addChild( btnInspire );

				CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
					ValuesUtil::Instance()->getString( "CFA016" ).c_str(),
					CCSizeMake(POSX(103), POSX(22)), CCTextAlignmentCenter, 
					g_sSimHeiFont, POSX(21) );
				txtLabel->setPosition( ccp(btnInspireSpr->getContentSize().width/2, 
					btnInspireSpr->getContentSize().height/2+2.0f) );
				btnInspireSpr->addChild( txtLabel );
			}
		}
		//历练鼓舞按钮
		{
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
			if(pNormalSprite && pPressedSprite && pSelectdSprite)
			{
				CCMenuItemSprite* btnInspireSpr = CCMenuItemSprite::itemFromNormalSprite(
					pNormalSprite,
					pPressedSprite,
					pSelectdSprite,
					this,
					menu_selector(CampFightView::onInspireByPratice) );
				//btnInspireSpr->setContentSize(CCSizeMake(POSX(103), POSX(26)));
				btnInspireSpr->setPosition( ccp(POSX(419), POSX(96)) );
				//_btnGUA->setAnchorPoint(ccp(0, 0));
				btnInspireSpr->setScale(0.8f);
				CCMenu* btnInspire = CCMenu::menuWithItems(btnInspireSpr, 0);
				btnInspire->setTouchLayer( TLE::WindowLayer_campFight );
				btnInspire->setPosition( CCPointZero );
				m_pContainer->addChild( btnInspire );
				//btnInspire->setScale(0.6f);
				CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
					ValuesUtil::Instance()->getString( "CFA019" ).c_str(),
					CCSizeMake(POSX(103), POSX(22)), CCTextAlignmentCenter, 
					g_sSimHeiFont, POSX(21) );
				txtLabel->setPosition( ccp(btnInspireSpr->getContentSize().width/2, 
					btnInspireSpr->getContentSize().height/2+2.0f) );
				btnInspireSpr->addChild( txtLabel );
			}
		}
		//参战按钮
		if(!m_pBtnIFightMenu)
		{
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
			if(pNormalSprite && pPressedSprite && pSelectdSprite)
			{
				m_pBtnFightSpr = CCMenuItemSprite::itemFromNormalSprite(
					pNormalSprite,
					pPressedSprite,
					pSelectdSprite,
					this,
					menu_selector(CampFightView::onFight) );
				//btnInspireSpr->setContentSize(CCSizeMake(POSX(80), POSX(30)));
				m_pBtnFightSpr->setPosition( ccp(POSX(290), POSX(41)) );
				//_btnGUA->setAnchorPoint(ccp(0, 0));
				m_pBtnFightSpr->setScaleX(0.8f);
				m_pBtnIFightMenu = CCMenu::menuWithItems(m_pBtnFightSpr, 0);
				m_pBtnIFightMenu->setTouchLayer( TLE::WindowLayer_campFight );
				m_pBtnIFightMenu->setPosition( CCPointZero );
				m_pContainer->addChild( m_pBtnIFightMenu );

				m_pFightLable = CCLabelTTF::labelWithString(
					ValuesUtil::Instance()->getString( "CFA012" ).c_str(),
					CCSizeMake(POSX(103), POSX(26)), CCTextAlignmentCenter, 
					g_sSimHeiFont, POSX(24) );
				//txtLabel->setPosition( ccp(btnInspireSpr->getContentSize().width/2, 
					//btnInspireSpr->getContentSize().height/2+2.0f) );
				m_pFightLable->setPosition( ccp(POSX(290), POSX(41)) );
				m_pContainer->addChild( m_pFightLable );
			}
		}
		//取消按钮
		if(!m_pBtnCancelMenu)
		{
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
			if(pNormalSprite && pPressedSprite && pSelectdSprite)
			{
				m_pBtnCancelSpr = CCMenuItemSprite::itemFromNormalSprite(
					pNormalSprite,
					pPressedSprite,
					pSelectdSprite,
					this,
					menu_selector(CampFightView::onCancel) );
				//btnInspireSpr->setContentSize(CCSizeMake(POSX(80), POSX(30)));
				m_pBtnCancelSpr->setPosition( ccp(POSX(419), POSX(41)) );
				//_btnGUA->setAnchorPoint(ccp(0, 0));
				m_pBtnCancelSpr->setScaleX(0.6f);
				m_pBtnCancelMenu = CCMenu::menuWithItems(m_pBtnCancelSpr, 0);
				m_pBtnCancelMenu->setTouchLayer( TLE::WindowLayer_campFight );
				m_pBtnCancelMenu->setPosition( CCPointZero );
				m_pContainer->addChild( m_pBtnCancelMenu );
				//
				m_pBtnCancelSpr->setIsEnabled(false);
				CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
					ValuesUtil::Instance()->getString( "CFA017" ).c_str(),
					CCSizeMake(POSX(103), POSX(26)), CCTextAlignmentCenter, 
					g_sSimHeiFont, POSX(24) );
				/*txtLabel->setPosition( ccp(btnInspireSpr->getContentSize().width/2, 
					btnInspireSpr->getContentSize().height/2+2.0f) );*/
				txtLabel->setPosition( ccp(POSX(419), POSX(41)) );
				m_pContainer->addChild( txtLabel );
			}
		}
		return true;
	} while (0);
	return false;
}
void CampFightView::onFight(CCObject* pSender)
{
	CCMD454 cmd;
	GameServerSocket::getInstance()->sendMessage(&cmd);
	//LayerManager::loadingPic->socketWait( WMSG_CAMPFIGHT_FIGHT_RES, 0, 0);
	char msg[100] = "\0";
	sprintf(msg,"%s",ValuesUtil::Instance()->getString( "CFA011" ).c_str());
	m_pFightLable->setString(msg);
	m_pBtnFightSpr->setIsEnabled(false);
	m_pBtnCancelSpr->setIsEnabled(true);
}
void CampFightView::onCancel(CCObject* pSender)
{
	CCMD456 cmd;
	GameServerSocket::getInstance()->sendMessage(&cmd);
	//LayerManager::loadingPic->socketWait( WMSG_CAMPFIGHT_FIGHT_RES, 0, 0);
	char msg[100] = "\0";
	sprintf(msg,"%s",ValuesUtil::Instance()->getString( "CFA012" ).c_str());
	m_pFightLable->setString(msg);
	m_pBtnFightSpr->setIsEnabled(true);
	m_pBtnCancelSpr->setIsEnabled(false);
}
void CampFightView::onInspireByGold(CCObject* pSender)
{

}
void CampFightView::onInspireByPratice(CCObject* pSender)
{

}
bool CampFightView::InitLsView()
{
	if (m_plsIcePlayers && m_plsFirePlayers && m_plsMsg)
	{
		return true;
	}
	else if (m_plsIcePlayers || m_plsFirePlayers || m_plsMsg)
	{
		return false;
	}
	m_plsIcePlayers = new CCFPlayerListView();
	m_plsIcePlayers->SetCamp(CAMP_ICE);
	if (!m_plsIcePlayers || !m_plsIcePlayers->init())
	{
		return false;
	}
	m_plsIcePlayers->setAnchorPoint(CCPointZero);
	m_plsIcePlayers->setPosition(ccp(POSX(10), POSX(10)));
	m_pContainer->addChild(m_plsIcePlayers);
	m_plsIcePlayers->release();
	m_plsFirePlayers = new CCFPlayerListView();
	m_plsFirePlayers->SetCamp(CAMP_FIRE);
	if (!m_plsFirePlayers || !m_plsFirePlayers->init())
	{
		return false;
	}
	m_plsFirePlayers->setAnchorPoint(CCPointZero);
	m_plsFirePlayers->setPosition(ccp(POSX(499), POSX(10)));
	m_pContainer->addChild(m_plsFirePlayers);
	m_plsFirePlayers->release();
	
	m_plsMsg = new CCFMsgListView();
	if (!m_plsMsg || !m_plsMsg->init())
	{
		return false;
	}
	m_plsMsg->setAnchorPoint(CCPointZero);
	m_plsMsg->setPosition(ccp(POSX(210),POSX(209)));
	m_pContainer->addChild(m_plsMsg);
	m_plsMsg->release();	
}

bool CampFightView::InitLable()
{
	if (m_pIceCityText && m_pIceCityScore && m_pFireCityText 
		&& m_pFireCityScore && m_pTimeTips && m_pTimeContext)
	{
		return true;
	}
	else if (m_pIceCityText || m_pIceCityScore || m_pFireCityText 
		|| m_pFireCityScore || m_pTimeTips || m_pTimeContext)
	{
		return false;
	}
	float fFont( POSX(36) );
	float fSmallFont( POSX(28) );
	//if (!m_pIceCityText)
	{
		m_pIceCityText = CCLabelTTF::labelWithString( LangManager::getText("CFA002").c_str(),
			CCSizeMake(POSX(120), POSX(36)), CCTextAlignmentCenter, g_sSimHeiFont, fFont );
		m_pIceCityText->setPosition( ccp( POSX(107), POSX(495) ) );
		//m_pIceCityText->setAnchorPoint( CCPointZero );
		m_pIceCityText->setColor( ccc3(1,246,255) );//ccc3(0xff, 0xc6, 0x00)
		m_pContainer->addChild( m_pIceCityText );
	}
	//if (!m_pIceCityScore)
	{
		char tmp[20];
		sprintf(tmp,ValuesUtil::Instance()->getString("CFA004").c_str(),0);
		m_pIceCityScore = CCLabelTTF::labelWithString(tmp,
			CCSizeMake(POSX(120), POSX(36)), CCTextAlignmentCenter, g_sSimHeiFont, fSmallFont );
		m_pIceCityScore->setPosition( ccp( POSX(107), POSX(459) ) );
		//m_pIceCityText->setAnchorPoint( CCPointZero );
		m_pIceCityScore->setColor( ccc3(0, 255, 0) );//ccc3(0xff, 0xc6, 0x00)
		m_pContainer->addChild( m_pIceCityScore );
	}
	//if (!m_pFireCityText)
	{
		m_pFireCityText = CCLabelTTF::labelWithString( LangManager::getText("CFA003").c_str(),
			CCSizeMake(POSX(120), POSX(36)), CCTextAlignmentCenter, g_sSimHeiFont, fFont );
		m_pFireCityText->setPosition( ccp( POSX(593), POSX(495) ) );
		//m_pIceCityText->setAnchorPoint( CCPointZero );
		m_pFireCityText->setColor( ccc3(255,1,1) );//ccc3(0xff, 0xc6, 0x00)
		m_pContainer->addChild( m_pFireCityText );
	}
	//if (!m_pFireCityScore)
	{
		char tmp[20];
		sprintf(tmp,ValuesUtil::Instance()->getString("CFA004").c_str(),0);
		m_pFireCityScore = CCLabelTTF::labelWithString(tmp,
			CCSizeMake(POSX(120), POSX(36)), CCTextAlignmentCenter, g_sSimHeiFont, fSmallFont );
		m_pFireCityScore->setPosition( ccp( POSX(593), POSX(459) ) );
		//m_pIceCityText->setAnchorPoint( CCPointZero );
		m_pFireCityScore->setColor( ccc3(0, 255, 0) );//ccc3(0xff, 0xc6, 0x00)
		m_pContainer->addChild( m_pFireCityScore );
	}
	{
		m_pTimeTips = CCLabelTTF::labelWithString(LangManager::getText("CFA005").c_str(),
			CCSizeMake(POSX(180), POSX(36)), CCTextAlignmentCenter, g_sSimHeiFont, fSmallFont );
		m_pTimeTips->setPosition( ccp( POSX(350), POSX(495) ) );
		//m_pIceCityText->setAnchorPoint( CCPointZero );
		m_pTimeTips->setColor( ccc3(0xff, 0xc6, 0x00) );//ccc3(0xff, 0xc6, 0x00)
		m_pContainer->addChild( m_pTimeTips );	
	}
	{
		m_pTimeContext = CCLabelTTF::labelWithString(LangManager::getText("CFA006").c_str(),
			CCSizeMake(POSX(180), POSX(36)), CCTextAlignmentCenter, g_sSimHeiFont, fSmallFont );
		m_pTimeContext->setPosition( ccp( POSX(350), POSX(459) ) );
		//m_pIceCityText->setAnchorPoint( CCPointZero );
		m_pTimeContext->setColor( ccc3(0xff, 0xc6, 0x00) );//ccc3(0xff, 0xc6, 0x00)
		m_pContainer->addChild( m_pTimeContext );	
	}

	{
		m_pIcePlayerName = CCLabelTTF::labelWithString(LangManager::getText("CFA007").c_str(),
			CCSizeMake(POSX(180), POSX(36)), CCTextAlignmentCenter, g_sSimHeiFont, fSmallFont - 4 );
		m_pIcePlayerName->setPosition( ccp( POSX(282), POSX(415) ) );
		//m_pIceCityText->setAnchorPoint( CCPointZero );
		m_pIcePlayerName->setColor( ccc3(255,255,255) );//ccc3(0xff, 0xc6, 0x00)
		m_pContainer->addChild( m_pIcePlayerName );	
	}
	{
		m_pFirePlayerName = CCLabelTTF::labelWithString(LangManager::getText("CFA007").c_str(),
			CCSizeMake(POSX(180), POSX(36)), CCTextAlignmentCenter, g_sSimHeiFont, fSmallFont - 4 );
		m_pFirePlayerName->setPosition( ccp( POSX(418), POSX(415) ) );
		//m_pIceCityText->setAnchorPoint( CCPointZero );
		m_pFirePlayerName->setColor( ccc3(255,255,255) );//ccc3(0xff, 0xc6, 0x00)
		m_pContainer->addChild( m_pFirePlayerName );	
	}

	{
		m_pIcePlayerContiWinTms = CCLabelTTF::labelWithString(LangManager::getText("CFA013").c_str(),
			CCSizeMake(POSX(180), POSX(36)), CCTextAlignmentCenter, g_sSimHeiFont, fSmallFont - 4 );
		m_pIcePlayerContiWinTms->setPosition( ccp( POSX(282), POSX(391) ) );
		//m_pIceCityText->setAnchorPoint( CCPointZero );
		m_pIcePlayerContiWinTms->setColor( ccc3(0xff, 0xc6, 0x00) );//ccc3(0xff, 0xc6, 0x00)
		m_pContainer->addChild( m_pIcePlayerContiWinTms );	
	}
	{
		m_pFirePlayerContiWinTms = CCLabelTTF::labelWithString(LangManager::getText("CFA013").c_str(),
			CCSizeMake(POSX(180), POSX(36)), CCTextAlignmentCenter, g_sSimHeiFont, fSmallFont - 4 );
		m_pFirePlayerContiWinTms->setPosition( ccp( POSX(418), POSX(391) ) );
		//m_pIceCityText->setAnchorPoint( CCPointZero );
		m_pFirePlayerContiWinTms->setColor( ccc3(0xff, 0xc6, 0x00) );//ccc3(0xff, 0xc6, 0x00)
		m_pContainer->addChild( m_pFirePlayerContiWinTms );	
	}
	//my score
	if (!m_myScoreLabel)
	{
		m_myScoreLabel = CCLabelTTF::labelWithString("",
			CCSizeMake(POSX(95), POSX(36)), CCTextAlignmentLeft, g_sSimHeiFont, fSmallFont - 4 );
		m_myScoreLabel->setAnchorPoint(CCPointZero);
		m_myScoreLabel->setPosition( ccp( POSX(208), POSX(176) ) );
		m_pContainer->addChild( m_myScoreLabel );
		//init
		if (!SetMyScore(0))
		{
			return false;
		}
	}
	//my historical continuous win times
	if (!m_myHisConWinTmsLabel)
	{
		m_myHisConWinTmsLabel = CCLabelTTF::labelWithString("",
			CCSizeMake(POSX(150), POSX(36)), CCTextAlignmentCenter, 
			g_sSimHeiFont, fSmallFont - 4 );
		m_myHisConWinTmsLabel->setAnchorPoint(CCPointZero);
		m_myHisConWinTmsLabel->setPosition( ccp( POSX(347), POSX(176) ) );
		m_pContainer->addChild( m_myHisConWinTmsLabel );
		//init
		if (!SetMyHisContiWinTms(0))
		{
			return false;
		}
	}

	std::string myAwardsTips = LangManager::getText("CFA010");
	char cMyAwardsTips[30];
	sprintf(cMyAwardsTips,myAwardsTips.c_str());
	CCLabelTTF* myAwardsTipsText = CCLabelTTF::labelWithString(cMyAwardsTips,
		CCSizeMake(POSX(150), POSX(28)), CCTextAlignmentLeft, g_sSimHeiFont, 
		fSmallFont - 4 );
	myAwardsTipsText->setAnchorPoint(CCPointZero);
	myAwardsTipsText->setPosition( ccp( POSX(208), POSX(156) ) );
	myAwardsTipsText->setColor( ccc3(0xff, 0xc6, 0x00) );
	m_pContainer->addChild( myAwardsTipsText );

	if (!m_myTotalAwardLabel)
	{
		m_myTotalAwardLabel = CCLabelTTF::labelWithString("",
			CCSizeMake(POSX(280), POSX(28)), CCTextAlignmentLeft, 
			g_sSimHeiFont, fSmallFont - 5 );
		m_myTotalAwardLabel->setAnchorPoint(CCPointZero);
		m_myTotalAwardLabel->setPosition( ccp( POSX(248), POSX(132) ) );
		m_myTotalAwardLabel->setColor( ccc3(0xff, 0xc6, 0x00) );
		m_pContainer->addChild( m_myTotalAwardLabel );
		//init
		if (!SetMyTotalAwards(0,0))
		{
			return false;
		}
	}

	if (!m_attackAddLabel)
	{
		m_attackAddLabel = CCLabelTTF::labelWithString("",
			CCSizeMake(POSX(100), POSX(28)), CCTextAlignmentCenter, 
			g_sSimHeiFont, fSmallFont - 6 );
		m_attackAddLabel->setPosition( ccp( POSX(285), POSX(126) ) );
		m_pContainer->addChild( m_attackAddLabel );
		//init
		if (!SetAttackAddStr(0))
		{
			return false;
		}
	}
	
	if (!m_lifeAddLabel)
	{
		m_lifeAddLabel = CCLabelTTF::labelWithString("",
			CCSizeMake(POSX(100), POSX(28)), CCTextAlignmentCenter, 
			g_sSimHeiFont, fSmallFont - 6 );
		m_lifeAddLabel->setPosition( ccp( POSX(418), POSX(126) ) );
		m_pContainer->addChild( m_lifeAddLabel );
		//init
		if (!SetLifeAddStr(0))
		{
			return false;
		}
	}

	return true;
}
bool CampFightView::SetAttackAddStr(int16 per, ccColor3B color )
{
	if (!m_attackAddLabel)
	{
		return false;
	}
	char cper[5];
	sprintf(cper,"%d",per);
	strcat(cper,"%");
	std::string myAddAttack = LangManager::getText("CFA014");
	char cMyAddAttack[100];
	sprintf(cMyAddAttack,myAddAttack.c_str(),cper);
	m_attackAddLabel->setString(cMyAddAttack);
	m_attackAddLabel->setColor( color );
	return true;
}
bool CampFightView::SetLifeAddStr(int16 per, ccColor3B color )
{
	if (!m_lifeAddLabel)
	{
		return false;
	}
	//char cper[5];
	//sprintf(cper,"%d",per);
	//strcat(cper,"%");
	std::string myAddAttack = LangManager::getText("CFA015");
	char cMyAddAttack[100];
	sprintf(cMyAddAttack,myAddAttack.c_str(),per);
	m_lifeAddLabel->setString(cMyAddAttack);
	m_lifeAddLabel->setColor( color );
	return true;
}
bool CampFightView::SetMyTotalAwards(uint16 pop, uint32 silver, ccColor3B color )
{
	if (!m_myTotalAwardLabel)
	{
		return false;
	}
	std::string myAwards = LangManager::getText("CFA018");
	char cMyAwards[100];
	sprintf(cMyAwards,myAwards.c_str(),pop,silver);
	m_myTotalAwardLabel->setString(cMyAwards);
	m_myTotalAwardLabel->setColor( color );
	return true;
}
bool CampFightView::SetMyHisContiWinTms(uint16 wins, ccColor3B color )
{
	if (!m_myHisConWinTmsLabel)
	{
		return false;
	}
	std::string myHiConWinTms = LangManager::getText("CFA009");
	char cMyHiConWinTms[30] = "\0";
	sprintf(cMyHiConWinTms,myHiConWinTms.c_str(),wins);
	m_myHisConWinTmsLabel->setString(cMyHiConWinTms);
	m_myHisConWinTmsLabel->setColor( color );
}
bool CampFightView::SetMyScore(uint16 score,ccColor3B color)
{
	if (!m_myScoreLabel)
	{
		return false;
	}
	std::string myScore = LangManager::getText("CFA008");
	char cMyScore[20] = "\0";
	sprintf(cMyScore,myScore.c_str(),score);
	m_myScoreLabel->setString(cMyScore);
	m_myScoreLabel->setColor( color );	
	return true;
}
bool CampFightView::InitDivede()
{
	if (divide1 && divide2 && divide3 && divide4 && divide5 && divide6)
	{
		return true;
	}
	else if (divide1 || divide2 || divide3 || divide4 || divide5 || divide6)
	{
		return false;
	}
	divide1 = CCLayerColor::layerWithColorWidthHeight(ccc4(255, 255, 255, 255), 
		POSX(190), POSX(1));
	divide1->setPosition(ccp (POSX(12), POSX(430)));
	divide1->setColor(ccc3(0xff, 0xc6, 0x00));
	m_pContainer->addChild(divide1);
	divide2 = CCLayerColor::layerWithColorWidthHeight(ccc4(255, 255, 255, 255), 
		POSX(284), POSX(1));
	divide2->setPosition(ccp (POSX(208), POSX(430)));
	divide2->setColor(ccc3(0xff, 0xc6, 0x00));
	m_pContainer->addChild(divide2);
	divide3 = CCLayerColor::layerWithColorWidthHeight(ccc4(255, 255, 255, 255), 
		POSX(190), POSX(1));
	divide3->setPosition(ccp (POSX(498), POSX(430)));
	divide3->setColor(ccc3(0xff, 0xc6, 0x00));
	m_pContainer->addChild(divide3);

	divide4 = CCLayerColor::layerWithColorWidthHeight(ccc4(255, 255, 255, 255), 
		POSX(284), POSX(1));
	divide4->setPosition(ccp (POSX(208), POSX(376)));
	divide4->setColor(ccc3(0xff, 0xc6, 0x00));
	m_pContainer->addChild(divide4);
	divide5 = CCLayerColor::layerWithColorWidthHeight(ccc4(255, 255, 255, 255), 
		POSX(284), POSX(1));
	divide5->setPosition(ccp (POSX(208), POSX(208)));
	divide5->setColor(ccc3(0xff, 0xc6, 0x00));
	m_pContainer->addChild(divide5);
	divide6 = CCLayerColor::layerWithColorWidthHeight(ccc4(255, 255, 255, 255), 
		POSX(284), POSX(1));
	divide6->setPosition(ccp (POSX(208), POSX(72)));
	divide6->setColor(ccc3(0xff, 0xc6, 0x00));
	m_pContainer->addChild(divide6);
	return true;
}
void CampFightView::clickCloseHandler(CCObject* pSender)
{
	//
	CCMD452 cmd;
	GameServerSocket::getInstance()->sendMessage(&cmd);
	////这里需要同步
	LayerManager::loadingPic->socketWait( WMSG_CAMPFIGHT_QUIT_RES, 0, 0);
	//PopContainer::close();
	//g_pGlobalManage->setCurFocusGID(LayerManager::sceneLayer->getMyFocusGID());
}
void CampFightView::onClose(CCObject* pSender)
{
	//
	CCMD452 cmd;
	GameServerSocket::getInstance()->sendMessage(&cmd);
	////这里需要同步
	//LayerManager::loadingPic->socketWait( WMSG_CAMPFIGHT_QUIT_RES, 0, 0);
	//PopContainer::close();
	//g_pGlobalManage->setCurFocusGID(LayerManager::sceneLayer->getMyFocusGID());
}
void CampFightView::closeView(int ApplyRes)
{
	if (ApplyRes != 0)
	{
		return;
	}
	PopContainer::close();
	g_pGlobalManage->setCurFocusGID(LayerManager::sceneLayer->getMyFocusGID());
}
void CampFightView::UpdateCampFightSceneInfo()
{
	//todo:update scene info
	if (!m_pCampFightProxy)
	{
		return;
	}
	if (!m_pCampFightProxy || !m_plsIcePlayers || !m_plsFirePlayers)
	{
		return;
	}
	ccColor3B color = {255,246,215};
	const TCampInfo* pIce = m_pCampFightProxy->GetIceCampFightInfo();
	if (!pIce)
	{
		return;
	}
	m_plsIcePlayers->RemoveAllItems();
	for (int i = 0; i < pIce->members.size(); ++i)
	{
		LayerNode* item = new LayerNode();
		item->init();
		item->setContentSize(CCSizeMake(POSX(193), POSX(27)));
		item->setvisibleSize(CCSizeMake(POSX(193), POSX(27)));
		char msg[20] = "\0";
		sprintf(msg, "%s", (pIce->members[i])->name);

		CCLabelTTF* pNameLabel = CCLabelTTF::labelWithString(msg, 
			CCSizeMake(POSX(193), POSX(27)), CCTextAlignmentCenter,
			g_sSimHeiFont, POSX(25));
		if (pNameLabel)
		{
			pNameLabel->setPosition(ccp(POSX(96), POSX(14)));
			pNameLabel->setColor(color);
			item->addChild(pNameLabel);
		}
		m_plsIcePlayers->AddItem(item);
	}
	m_plsIcePlayers->Refresh();

	const TCampInfo* pFire = m_pCampFightProxy->GetFireCampFightInfo();
	if (!pFire)
	{
		return;
	}
	m_plsFirePlayers->RemoveAllItems();
	for (int i = 0; i < pFire->members.size(); ++i)
	{
		LayerNode* item = new LayerNode();
		item-init();
		item->setContentSize(CCSizeMake(POSX(193), POSX(27)));
		item->setvisibleSize(CCSizeMake(POSX(193), POSX(27)));
		char msg[20] = "\0";
		std::string name = (pFire->members[i])->name; 
		sprintf(msg, "%s", name);

		CCLabelTTF* pNameLabel = CCLabelTTF::labelWithString(msg, 
			CCSizeMake(POSX(193), POSX(27)), CCTextAlignmentCenter, g_sSimHeiFont, 
			POSX(25));
		if (pNameLabel)
		{
			pNameLabel->setPosition(ccp(POSX(96), POSX(14)));
			pNameLabel->setColor(color);
			item->addChild(pNameLabel);
		}
		m_plsFirePlayers->AddItem(item);
	}
		//add Background
		/*CCUIBackground* pBg = new CCUIBackground();
		pBg->initWithSpriteFrame("ui2.png", CCPointZero, CCPointZero, item->getContentSize());
		pBg->setAnchorPoint(CCPointZero);
		pBg->setPosition(CCPointZero);
		item->addChild(pBg);
		pBg->release();*/
	//write to the view
	m_plsFirePlayers->Refresh();
}
void CampFightView::UpdateMyInfo()
{
	if (!m_pCampFightProxy)
	{
		return;
	}
	const TMyCampFightInfo* pMyInfo = m_pCampFightProxy->GetMyInfo();
	SetMyScore(pMyInfo->score);
	SetMyHisContiWinTms(pMyInfo->hisConstiWinTims);
	SetMyTotalAwards(pMyInfo->sumPop,pMyInfo->sumSilver);
}
void CampFightView::TestListView()
{
	//=>test
		for (int i = 0; i != 20; ++i)
		{
			LayerNode* tmpitem = new LayerNode();
			tmpitem->init();
			tmpitem->setContentSize(CCSizeMake(POSX(193), POSX(27)));
			tmpitem->setvisibleSize(CCSizeMake(POSX(193), POSX(27)));
			char msg[100];
			sprintf(msg,"%d",i);
			//sprintf(msg,"%d,%d",m_pContainer->getPosition().x,m_pContainer->getPosition().y);
			CCLabelTTF* pNameLabel_test = CCLabelTTF::labelWithString(msg, CCSizeMake(POSX(193),
				POSX(27)), CCTextAlignmentCenter, g_sSimHeiFont, POSX(25));
			if (pNameLabel_test)
			{
				//pNameLabel_test->setPosition(ccp(POSX(1), POSX(1)));
				pNameLabel_test->setPosition(ccp(POSX(96), POSX(14)));
				pNameLabel_test->setColor(ccc3(0xff, 0xc6, 0x00));
				tmpitem->addChild(pNameLabel_test);
			}
			m_plsIcePlayers->AddItem(tmpitem);
		}
		m_plsIcePlayers->Refresh();
		for (int i = 0; i != 10 ; ++i)
		{
			LayerNode* tmpitem2 = new LayerNode();
			tmpitem2->init();
			tmpitem2->setContentSize(CCSizeMake(POSX(193), POSX(27)));
			tmpitem2->setvisibleSize(CCSizeMake(POSX(193), POSX(27)));

			CCLabelTTF* pNameLabel_test2 = CCLabelTTF::labelWithString("sssss", CCSizeMake(POSX(193),
				POSX(27)), CCTextAlignmentCenter, g_sSimHeiFont, POSX(25));
			if (pNameLabel_test2)
			{
				//pNameLabel_test->setPosition(ccp(POSX(1), POSX(1)));
				pNameLabel_test2->setPosition(ccp(POSX(96), POSX(14)));
				pNameLabel_test2->setColor(ccc3(255, 255, 255));
				tmpitem2->addChild(pNameLabel_test2);
			}
			m_plsFirePlayers->AddItem(tmpitem2);
		}
		m_plsFirePlayers->Refresh();
		for (int i = 0; i != 20; ++i)
		{
			/*LayerNode* tmpitem = new LayerNode();
			tmpitem->init();
			tmpitem->setContentSize(CCSizeMake(POSX(193), POSX(27)));
			tmpitem->setvisibleSize(CCSizeMake(POSX(193), POSX(27)));*/
			char msg[100];
			CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
			sprintf(msg,"%d,%d",screenSize.width,screenSize.height);
			//sprintf(msg,"%d,%d",m_pContainer->getPosition().x,m_pContainer->getPosition().y);
			//CCLabelTTF* pNameLabel_test = CCLabelTTF::labelWithString(msg, CCSizeMake(POSX(193),
			//	POSX(27)), CCTextAlignmentCenter, g_sSimHeiFont, POSX(25));
			//if (pNameLabel_test)
			//{
			//	//pNameLabel_test->setPosition(ccp(POSX(1), POSX(1)));
			//	pNameLabel_test->setPosition(ccp(POSX(96), POSX(14)));
			//	pNameLabel_test->setColor(ccc3(0xff, 0xc6, 0x00));
			//	tmpitem->addChild(pNameLabel_test);
			//}
			m_plsMsg->AddRecords(msg);
		}
		//tmpitem->release();
	//<=
}