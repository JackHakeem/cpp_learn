#include "MainStrengView.h"
#include "cocos2d.h"
#include "manager/PopEventName.h"
#include "StrengPanel.h"
#include "MeltingPanel.h"
#include "manager/ViewManager.h"
#include "../MainStrengMediator.h"
#include "manager/OverPanelManage.h"
#include "utils/ValuesUtil.h"
#include "MagicPanel.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "MeltingBagCreate.h"
#include "MeltingTips.h"
#include "manager/LayerManager.h"
#include "manager/LevLimitConst.h"

using namespace cocos2d;

static const int s_MeltingMagicOpenLev = 40;

MainStrengView::MainStrengView()
{
	strengPanel = 0;
	meltingPanel = 0;
	magicPanel = 0;
	inheritPanel = 0;

	_tabMc1 = 0;
	_tabMc2 = 0;
	_tabMc3 = 0;
	_tabMc4 = 0;

	_pContainer = 0;

	m_iInitUIRoleLev = 0;

	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/res_icon.plist"); 
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/streng/res_streng.plist");
}

void MainStrengView::removeDataObjectChild()
{
	if (ViewManager::getInstance()->_mainStrengView)
	{
		ViewManager::getInstance()->_mainStrengView = 0;
	}
	
	if (g_pMainStrengMediator)
	{
		g_pMainStrengMediator->_mainStrengView = 0;
	}
}

int32 MainStrengView::getSelfTag() 
{
	return OVER_14_MAINSTRENGVIEW;
}

bool MainStrengView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	// initial key
	key = PopEventName::STRENG;

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	this->setPopContentSize( winSize );
	this->setContentSize(winSize);

	if(!_pContainer)
	{
		_pContainer = new CCLayer();
		_pContainer->setAnchorPoint(CCPointZero);
		_pContainer->setPosition(POS(ccp(0, 12), ScaleUtil::CENTER_TOP));

		//CCLayerColor *pTestLayer = CCLayerColor::layerWithColorWidthHeight(ccc4(0, 0, 255, 128),
		//	winSize.width,
		//	winSize.height);
		//pTestLayer->setAnchorPoint(CCPointZero);
		//pTestLayer->setPosition(CCPointZero);
		//_pContainer->addChild(pTestLayer);
	}

	ValuesUtil* pValuesUtil = ValuesUtil::Instance();

	CCPoint cpLabel = ccp( POSX(154/2), POSX(61/2) );

	_tabMc1 = CCMenuItemImage::itemFromNormalSprite(
		CCSprite::spriteWithSpriteFrameName("ui/tab.png"), 
		CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
		CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
		this,
		menu_selector(MainStrengView::onTabHandler) );
	CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
		pValuesUtil->getString( "StTab1" ).c_str(), g_sSimHeiFont, POSX(24) );
	pLabel->setPosition( cpLabel );
	_tabMc1->addChild( pLabel );
	
	m_iInitUIRoleLev = RoleManage::Instance()->roleLev();
	if ( m_iInitUIRoleLev >= LevLimitConst::Limit_Strength )
	{
		if (m_iInitUIRoleLev >= LevLimitConst::Limit_Melting)
		{
			_tabMc2 = CCMenuItemImage::itemFromNormalSprite(
				CCSprite::spriteWithSpriteFrameName("ui/tab.png"), 
				CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
				CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
				this,
				menu_selector(MainStrengView::onTabHandler) );
			pLabel = CCLabelTTF::labelWithString(
				pValuesUtil->getString( "StTab2" ).c_str(), g_sSimHeiFont, POSX(24) );
			pLabel->setPosition( cpLabel );
			_tabMc2->addChild( pLabel );
		}
		
		if (m_iInitUIRoleLev >= LevLimitConst::Limit_Magic)
		{
			_tabMc3 = CCMenuItemImage::itemFromNormalSprite(
				CCSprite::spriteWithSpriteFrameName("ui/tab.png"), 
				CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
				CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
				this,
				menu_selector(MainStrengView::onTabHandler) );
			pLabel = CCLabelTTF::labelWithString(
				pValuesUtil->getString( "StTab3" ).c_str(), g_sSimHeiFont, POSX(24) );
			pLabel->setPosition( cpLabel );
			_tabMc3->addChild( pLabel );
		}

		
		if (m_iInitUIRoleLev >= LevLimitConst::Limit_EquipHeritage)
		{
			_tabMc4 = CCMenuItemImage::itemFromNormalSprite(
				CCSprite::spriteWithSpriteFrameName("ui/tab.png"), 
				CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
				CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
				this,
				menu_selector(MainStrengView::onTabHandler) );
			pLabel = CCLabelTTF::labelWithString(
				pValuesUtil->getString( "StTab4" ).c_str(), g_sSimHeiFont, POSX(24) );
			pLabel->setPosition( cpLabel );
			_tabMc4->addChild( pLabel );
		}
		
		pTabMenu = CCMenu::menuWithItems( _tabMc1,_tabMc4, _tabMc2, _tabMc3,  0 );

		pTabMenu->setContentSize( CCSizeMake( POSX(570), POSX(61) ) );
		pTabMenu->setPosition( ccp( POSX(141+570/2), POSX(575+15) ) );
		pTabMenu->alignItemsHorizontallyWithPadding( POSX(10.0f) );
	}
	else
	{
		pTabMenu = CCMenu::menuWithItems( _tabMc1, 0 );

		pTabMenu->setContentSize( CCSizeMake( POSX(155), POSX(61) ) );
		pTabMenu->setPosition( ccp( POSX(141+155/2), POSX(575+15) ) );
	}
	
	pTabMenu->setTouchLayer( TLE::WindowLayer_Common_btn );
	_pContainer->addChild( pTabMenu );
	
	CCSprite* spTitle = CCSprite::spriteWithSpriteFrameName( "streng/title.png" );
	spTitle->setAnchorPoint( CCPointZero );
	spTitle->setPosition( ccp( POSX(454), POSX(532) ) );
	_pContainer->addChild( spTitle );

	this->addChild(_pContainer);

	_pContainer->release(); //LH20120116 memory

	return true;
}

/**
* Streng panel as default
* 
*/
void MainStrengView::setDefaultStrengPanel()
{
	setPanel(  1, (CCLayer*)strengPanel  ); 
}
		
void MainStrengView::onTabHandler( CCObject* pSender )
{
	if ( pSender == _tabMc1 )
	{
		setPanel(  1, (CCLayer*)strengPanel  );
	}
	else if ( pSender == _tabMc2 )
	{
		setPanel(  2, (CCLayer*)meltingPanel  );
	}
	else if ( pSender == _tabMc3 )
	{
		setPanel(  3, (CCLayer*)strengPanel  );
	}
	else if ( pSender == _tabMc4 )
	{
		setPanel(  4, (CCLayer*)inheritPanel  );
	}
}

/**
* set main board 
* @param type
*/		
void MainStrengView::setPanel( int type, CCLayer* panel /*= 0*/ )
{
	if (strengPanel)
	{
		strengPanel->removeFromParentAndCleanup(true);
		strengPanel = 0;
		ViewManager::getInstance()->strengPanel = 0;
		g_pMainStrengMediator->_strengPanel = 0;
	}
	if (meltingPanel)
	{
		meltingPanel->removeFromParentAndCleanup(true);
		meltingPanel = 0;
		g_pMainStrengMediator->_meltingPanel = 0;
	}
	if (magicPanel)
	{
		magicPanel->removeFromParentAndCleanup(true);
		magicPanel = 0;
		g_pMainStrengMediator->_magicPanel = 0;
	}
	if (inheritPanel)
	{
		inheritPanel->removeFromParentAndCleanup(true);
		inheritPanel = 0;
		g_pMainStrengMediator->_inheritPanel = 0;
	}
	

	switch(type)
	{
	case 1:
		if ( !strengPanel )
		{
			strengPanel = new StrengPanel();
			strengPanel->init();
			_pContainer->addChild( strengPanel );
			ViewManager::getInstance()->strengPanel = strengPanel;
			strengPanel->release();
		} 
		else
		{
			strengPanel->setIsVisible( true );
			strengPanel->_figureCreate->setIsTouchEnabled(true);
			strengPanel->_strengCreate->setIsTouchEnabled(true);
			if (strengPanel->_strengCreateBag)
			{
				strengPanel->_strengCreateBag->setIsTouchEnabled(true);
			}		

			if (
				(m_iInitUIRoleLev < s_MeltingMagicOpenLev)
				&& (RoleManage::Instance()->roleLev() >= 40)
				)
			{
				m_iInitUIRoleLev = RoleManage::Instance()->roleLev();

				refreshTabMenu();
			}
			
		}

		if ( meltingPanel )
		{
			meltingPanel->setIsVisible( false );
			if (meltingPanel->bagCreate && meltingPanel->bagCreate->_meltingCreate)
			{
				meltingPanel->bagCreate->_meltingCreate->setIsTouchEnabled(false);
				meltingPanel->bagCreate->clearEquipment();
			}		
		}
		if ( magicPanel )
		{
			magicPanel->setIsVisible( false );
			magicPanel->_figureCreate->setIsTouchEnabled(false);
			magicPanel->_magicCreate->setIsTouchEnabled(false);

			magicPanel->clearEquipment();
		}
		if ( inheritPanel )
		{
			inheritPanel->setIsVisible( false );
		}

		g_pMainStrengMediator->tabChange( type );

		if (_tabMc1)
		{
			_tabMc1->setIsEnabled(false);
		}
		if (_tabMc2)
		{
			_tabMc2->setIsEnabled(true);
		}
		if (_tabMc3)
		{
			_tabMc3->setIsEnabled(true);
		}
		if (_tabMc4)
		{
			_tabMc4->setIsEnabled(true);
		}
		
		break;
	case 2:
		if ( strengPanel )
		{
			strengPanel->setIsVisible( false );
			strengPanel->_figureCreate->setIsTouchEnabled(false);
			strengPanel->_strengCreate->setIsTouchEnabled(false);
			if (strengPanel->_strengCreateBag)
			{
				strengPanel->_strengCreateBag->setIsTouchEnabled(false);
			}
		}	
		if ( !meltingPanel )
		{
			meltingPanel = new MeltingPanel();
			if ( meltingPanel )
			{
				meltingPanel->init();
				_pContainer->addChild( meltingPanel );
				meltingPanel->release();
			}			
		}
		else
		{
			meltingPanel->setIsVisible( true );
			meltingPanel->setIsTouchEnabled(true);
			if (meltingPanel->bagCreate && meltingPanel->bagCreate->_meltingCreate)
			{
				meltingPanel->bagCreate->_meltingCreate->setIsTouchEnabled(true);
			}
		}
		if ( magicPanel )
		{
			magicPanel->setIsVisible( false );
			magicPanel->_figureCreate->setIsTouchEnabled(false);
			magicPanel->_magicCreate->setIsTouchEnabled(false);

			magicPanel->clearEquipment();
		}
		if ( inheritPanel )
		{
			inheritPanel->setIsVisible( false );
		}
		g_pMainStrengMediator->tabChange( type );

		if (_tabMc1)
		{
			_tabMc1->setIsEnabled(true);
		}
		if (_tabMc2)
		{
			_tabMc2->setIsEnabled(false);
		}
		if (_tabMc3)
		{
			_tabMc3->setIsEnabled(true);
		}
		if (_tabMc4)
		{
			_tabMc4->setIsEnabled(true);
		}
		break;
	case 3:
		if ( strengPanel )
		{
			strengPanel->setIsVisible( false );
			strengPanel->_figureCreate->setIsTouchEnabled(false);
			strengPanel->_strengCreate->setIsTouchEnabled(false);
			if (strengPanel->_strengCreateBag)
			{
				strengPanel->_strengCreateBag->setIsTouchEnabled(false);
			}
		}	
		if ( meltingPanel )
		{
			meltingPanel->setIsVisible( false );

			if (meltingPanel->bagCreate && meltingPanel->bagCreate->_meltingCreate)
			{
				meltingPanel->bagCreate->_meltingCreate->setIsTouchEnabled(false);
				meltingPanel->bagCreate->clearEquipment();
			}
		}
		if ( !magicPanel )
		{
			magicPanel = new MagicPanel();
			if ( magicPanel )
			{
				magicPanel->init();
				_pContainer->addChild( magicPanel );
				magicPanel->release();
			}	
		}
		else
		{
			magicPanel->setIsVisible( true );
			magicPanel->_figureCreate->setIsTouchEnabled(true);
			magicPanel->_magicCreate->setIsTouchEnabled(true);
		}

		if ( inheritPanel )
		{
			inheritPanel->setIsVisible( false );
		}
		g_pMainStrengMediator->tabChange( type );

		if (_tabMc1)
		{
			_tabMc1->setIsEnabled(true);
		}
		if (_tabMc2)
		{
			_tabMc2->setIsEnabled(true);
		}
		if (_tabMc3)
		{
			_tabMc3->setIsEnabled(false);
		}
		if (_tabMc4)
		{
			_tabMc4->setIsEnabled(true);
		}
		break;
	case 4:
		if ( strengPanel )
		{
			strengPanel->setIsVisible( false );
			strengPanel->_figureCreate->setIsTouchEnabled(false);
			strengPanel->_strengCreate->setIsTouchEnabled(false);
			if (strengPanel->_strengCreateBag)
			{
				strengPanel->_strengCreateBag->setIsTouchEnabled(false);
			}
			
		}	
		if ( meltingPanel )
		{
			meltingPanel->setIsVisible( false );
			meltingPanel->setIsTouchEnabled(false);

			if (meltingPanel->bagCreate && meltingPanel->bagCreate->_meltingCreate)
			{
				meltingPanel->bagCreate->_meltingCreate->setIsTouchEnabled(false);
				meltingPanel->bagCreate->clearEquipment();
			}
		}
		if ( magicPanel )
		{
			magicPanel->setIsVisible( false );
			magicPanel->_figureCreate->setIsTouchEnabled(false);
			magicPanel->_magicCreate->setIsTouchEnabled(false);

			magicPanel->clearEquipment();
		}
		if ( !inheritPanel )
		{
			inheritPanel = new HeritagePanel();
			if ( inheritPanel )
			{
				inheritPanel->init();
				_pContainer->addChild( inheritPanel );
				inheritPanel->release();
			}
		}
		else
		{
			inheritPanel->setIsVisible( true );
			if (inheritPanel->_gridSelect1)
			{
				inheritPanel->_gridSelect1->setIsVisible(true);
			}
			if (inheritPanel->_gridSelect2)
			{
				inheritPanel->_gridSelect2->setIsVisible(false);
			}
			inheritPanel->caculateCost();
		}

		g_pMainStrengMediator->tabChange( type );

		if (_tabMc1)
		{
			_tabMc1->setIsEnabled(true);
		}
		if (_tabMc2)
		{
			_tabMc2->setIsEnabled(true);
		}
		if (_tabMc3)
		{
			_tabMc3->setIsEnabled(true);
		}
		if (_tabMc4)
		{
			_tabMc4->setIsEnabled(false);
		}
		break;	
	}
}

void MainStrengView::CloseBtCallback( CCObject* pSender )
{
	PopContainer::setisPop( false );
}

MainStrengView::~MainStrengView()
{
	ViewManager::getInstance()->_mainStrengView = 0;

	if (meltingPanel&&meltingPanel->getParent())
	{
		meltingPanel->removeFromParentAndCleanup(true);
		meltingPanel = 0;
	}
	g_pMainStrengMediator->_meltingPanel = 0;
	CC_SAFE_DELETE( meltingPanel );

	if (strengPanel && strengPanel->getParent())
	{
		strengPanel->removeFromParentAndCleanup(true);
		strengPanel = 0;
	}
	CC_SAFE_DELETE( strengPanel );
	g_pMainStrengMediator->_strengPanel = 0;

	if (inheritPanel && inheritPanel->getParent())
	{
		inheritPanel->removeFromParentAndCleanup(true);
		inheritPanel = 0;
	}
	CC_SAFE_DELETE( inheritPanel );
	g_pMainStrengMediator->_inheritPanel = 0;
	
	if (magicPanel && magicPanel->getParent())
	{
		magicPanel->removeFromParentAndCleanup(true);
		magicPanel = 0;
	}
	CC_SAFE_DELETE( magicPanel );
	g_pMainStrengMediator->_magicPanel = 0;
	
	g_pMainStrengMediator->_mainStrengView = 0;
	ViewManager::getInstance()->_mainStrengView = 0;
	
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/streng/res_streng.plist"); 
	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/streng/res_streng.pvr.ccz");
	
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/icon/res_icon.plist"); 
	//CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/icon/res_icon.pvr.ccz");
}

CCNode * MainStrengView::getNewHandItem( int id )
{
	if(id == 99){
		//return __skin["_btnClose"];
		return NULL;
	}
	else{
		return ViewManager::getInstance()->strengPanel->getNewHandItem(id);
	}
}

void MainStrengView::refreshTabMenu()
{
	if ( pTabMenu )
	{
		pTabMenu->removeFromParentAndCleanup(true);
	}

	CCPoint cpLabel = ccp( POSX(154/2), POSX(61/2) );
	ValuesUtil* pValuesUtil = ValuesUtil::Instance();
	CCLabelTTF* pLabel = 0;


	//if (m_iInitUIRoleLev >= LevLimitConst::Limit_Melting)
	{
		_tabMc1 = CCMenuItemImage::itemFromNormalSprite(
			CCSprite::spriteWithSpriteFrameName("ui/tab.png"), 
			CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
			CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
			this,
			menu_selector(MainStrengView::onTabHandler) );
		pLabel = CCLabelTTF::labelWithString(
			pValuesUtil->getString( "StTab1" ).c_str(), g_sSimHeiFont, POSX(24) );
		pLabel->setPosition( cpLabel );
		_tabMc1->addChild( pLabel );
	}

	if (RoleManage::Instance()->roleLev() >= LevLimitConst::Limit_Melting)
	{
		_tabMc2 = CCMenuItemImage::itemFromNormalSprite(
			CCSprite::spriteWithSpriteFrameName("ui/tab.png"), 
			CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
			CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
			this,
			menu_selector(MainStrengView::onTabHandler) );
		pLabel = CCLabelTTF::labelWithString(
			pValuesUtil->getString( "StTab2" ).c_str(), g_sSimHeiFont, POSX(24) );
		pLabel->setPosition( cpLabel );
		_tabMc2->addChild( pLabel );
	}

	if (RoleManage::Instance()->roleLev() >= LevLimitConst::Limit_Magic)
	{
		_tabMc3 = CCMenuItemImage::itemFromNormalSprite(
			CCSprite::spriteWithSpriteFrameName("ui/tab.png"), 
			CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
			CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
			this,
			menu_selector(MainStrengView::onTabHandler) );
		pLabel = CCLabelTTF::labelWithString(
			pValuesUtil->getString( "StTab3" ).c_str(), g_sSimHeiFont, POSX(24) );
		pLabel->setPosition( cpLabel );
		_tabMc3->addChild( pLabel );
	}

	if (RoleManage::Instance()->roleLev() >= LevLimitConst::Limit_EquipHeritage)
	{
		_tabMc4 = cocos2d::CCMenuItemSprite::itemFromNormalSprite(
			CCSprite::spriteWithSpriteFrameName("ui/tab.png"), 
			CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
			CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
			this,
			menu_selector(MainStrengView::onTabHandler) );
		pLabel = CCLabelTTF::labelWithString( pValuesUtil->getString( "StTab4" ).c_str(), g_sSimHeiFont, POSX(24) );
		pLabel->setPosition( cpLabel );
		_tabMc4->addChild( pLabel );
	}

	pTabMenu = CCMenu::menuWithItems( _tabMc1, _tabMc4,_tabMc2, _tabMc3, 0 );
	pTabMenu->setTouchLayer( TLE::WindowLayer_Common_btn );
	pTabMenu->alignItemsHorizontallyWithPadding( POSX(10.0f) );
	pTabMenu->setPosition( ccp( POSX(141+570/2), POSX(575+15) ) );
	pTabMenu->setContentSize( CCSizeMake( POSX(570), POSX(61) ) );
	_pContainer->addChild( pTabMenu, 2 );

}

void MainStrengView::clickCloseHandler( CCObject* pSender )
{
	MeltingTips* pTips = (MeltingTips*)LayerManager::tipsLayer->getChildByTag(
		TipsLayer::TipsLayerTAG_tipHelpMelting);
	if (pTips)
	{ 
		pTips->removeFromParentAndCleanup(true);
	}
	
	PopContainer::clickCloseHandler(pSender);
}
