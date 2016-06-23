#include "TrainView.h"
#include "model/player/RoleManage.h"
#include "../TrainViewMediator.h"
#include "manager/PopEventName.h"
#include "model/player/FigureBaseManage.h"
#include "utils/ValuesUtil.h"
#include "TrainTime.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"
#include "manager/TouchLayerEnum.h"
#include "CustomCD.h"
#include "view/figure/components/FigureCreate.h"
#include "model/newhand/NewhandManager.h"
#include "manager/LangManager.h"
#include "manager/ViewManager.h"
#include "mvc/Facade.h"
#include "Confirm.h"
#include "RoleListView.h"
#include "TrainRoleItem.h"
#include "manager/LevLimitConst.h"
#include "manager/ButtonIDConst.h"
#include "model/newhand/vo/NewhandConst.h"
#include "manager/PopManage.h"
#include "manager/VIPLimitConst.h"
#include "manager/VIPMgr.h"

#define CCSZIE_TRAIN_LISTVIEW CCRectMake(POSX(2 + 10), POSX(28 + 10 + 102) , POSX(454),POSX(504 -20 - 102))

TrainView::TrainView()
{
	_trainVo = 0;
	_mercId = 0;
	m_SelectedItem = 0;
	_merc = 0;
	_timeObj = 0;

	_btnStart = 0;
	_btnDoubleExpStart = 0;

	_btnEnd = 0;

	_btnGold = 0;

	_trainTime = 0;

	_txtModeFont = 0;
	_txtMode = 0;

	_txtTufe = 0;
	_txtTufeContent = 0;
	
	strs = 0;

	_btnBuy = 0;

	_txtSite = 0;
	_txtSiteCnt = 0;

	m_vipLev = 0;
	m_selectTimeIndex = 0;
	
	_btnExpImg = 0;
	_btnGoldImg = 0;

	_trainBgNor = 0;
	_trainBgRush = 0;

	_btnStartItem = 0;
	_txtTrainUp = 0;
}


bool TrainView::reinitcd()
{
	if ( _trainTime )
	{
		_trainTime->reinit();
	}
	
	return true;
}

bool TrainView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	//init key
	key = PopEventName::TRAIN;
	
	CCSize popContainerSize = CCSizeMake(POSX(448 * 2), CCDirector::sharedDirector()->getWinSize().height);
	float fFontSize( POSX(24) );
	
	this->setPopContentSize( popContainerSize );

	m_ContentLayer = new CCLayer;
	m_ContentLayer->init();
	m_ContentLayer->setAnchorPoint(CCPointZero);
	m_ContentLayer->setContentSize( popContainerSize );
	m_ContentLayer->setPosition( POS(ccp(0, 12), ScaleUtil::TOP_LEFT) );
	
	this->addChild( m_ContentLayer, RENDERZ_Container );
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/formation/res_formation_1.plist");

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/train/res_train_dragon.plist");
	// left bg
	
	CCUIBackground* _bagContainer1 = new CCUIBackground();
	_bagContainer1->initWithSpriteFrame("ui2.png", 
		ccp(POSX(2), POSX(28)),
		ccp(0,0),
		CCSizeMake(POSX(444),POSX(504)));
	m_ContentLayer->addChild(_bagContainer1, RENDERZ_Container);
	_bagContainer1->release();
	

	// right bg
	CCUIBackground* _bagContainer = new CCUIBackground();
	_bagContainer->initWithSpriteFrame("ui2.png", 
		ccp(POSX(448 + 12), POSX(28)),
		ccp(0,0),
		CCSizeMake(POSX(434),POSX(504)));
	m_ContentLayer->addChild(_bagContainer, RENDERZ_Container);
	_bagContainer->release();

	CCSprite* pDragonSp = new CCSprite();
	pDragonSp->initWithSpriteFrameName("train_dragon.png");
	pDragonSp->setAnchorPoint(CCPointZero);
	pDragonSp->setPosition( ccp( POSX(494-465 + 458), POSX(145) ) );
	m_ContentLayer->addChild( pDragonSp );
	pDragonSp->release();

	// right jiao
	{
		CCSprite* pJiao = new CCSprite();	// left bottom
		pJiao->initWithSpriteFrameName("train_jiao.png");
		pJiao->setAnchorPoint(CCPointZero);
		pJiao->setPosition( ccp( POSX(465-465+5 + 458), POSX(35-4) ) );
		m_ContentLayer->addChild( pJiao );
		pJiao->release();

		pJiao = new CCSprite();	// right bottom
		pJiao->initWithSpriteFrameName("train_jiao.png");
		pJiao->setFlipX(true);
		pJiao->setAnchorPoint(CCPointZero);
		pJiao->setPosition( ccp( POSX(878-465 + 458 -10), POSX(35-4) ) );
		m_ContentLayer->addChild( pJiao );
		pJiao->release();

		pJiao = new CCSprite();	// left top
		pJiao->initWithSpriteFrameName("train_jiao.png");
		pJiao->setFlipY(true);
		pJiao->setAnchorPoint(CCPointZero);
		pJiao->setPosition( ccp( POSX(465-465+5 + 458), POSX(500) ) );
		m_ContentLayer->addChild( pJiao );
		pJiao->release();

		pJiao = new CCSprite();	// r t
		pJiao->initWithSpriteFrameName("train_jiao.png");
		pJiao->setFlipX(true);
		pJiao->setFlipY(true);
		pJiao->setAnchorPoint(CCPointZero);
		pJiao->setPosition( ccp( POSX(878-465 + 458 -10), POSX(500) ) );
		m_ContentLayer->addChild( pJiao );
		pJiao->release();
	}

	//left jiao
	{
		CCSprite* pJiao = new CCSprite();	// left bottom
		pJiao->initWithSpriteFrameName("train_jiao.png");
		pJiao->setAnchorPoint(CCPointZero);
		pJiao->setPosition( ccp( POSX(465-465+5), POSX(35-4) ) );
		m_ContentLayer->addChild( pJiao , 2 );
		pJiao->release();

		pJiao = new CCSprite();	// right bottom
		pJiao->initWithSpriteFrameName("train_jiao.png");
		pJiao->setFlipX(true);
		pJiao->setAnchorPoint(CCPointZero);
		pJiao->setPosition( ccp( POSX(878-465), POSX(35-4) ) );
		m_ContentLayer->addChild( pJiao , 2 );
		pJiao->release();

		pJiao = new CCSprite();	// left top
		pJiao->initWithSpriteFrameName("train_jiao.png");
		pJiao->setFlipY(true);
		pJiao->setAnchorPoint(CCPointZero);
		pJiao->setPosition( ccp( POSX(465-465+5 ), POSX(500) ) );
		m_ContentLayer->addChild( pJiao , 2 );
		pJiao->release();

		pJiao = new CCSprite();	// r t
		pJiao->initWithSpriteFrameName("train_jiao.png");
		pJiao->setFlipX(true);
		pJiao->setFlipY(true);
		pJiao->setAnchorPoint(CCPointZero);
		pJiao->setPosition( ccp( POSX(878-465 ), POSX(500) ) );
		m_ContentLayer->addChild( pJiao , 2 );
		pJiao->release();
	}

	// _btnStart
	{
		{
			CCMenuItemSprite *pStartItem = CCMenuItemSprite::itemFromNormalSprite(
				CCSprite::spriteWithSpriteFrameName("button.png"),
				CCSprite::spriteWithSpriteFrameName("button1.png"),
				this,
				menu_selector(TrainView::startTrainHandler) );
			pStartItem->setPosition( ccp( POSX(55+121/2 + 458), POSX(60)+POSX(25) ) );
			string strConfirm = ValuesUtil::Instance()->getString( "T0001" );
			CCLabelTTF* pConfirm = CCLabelTTF::labelWithString( strConfirm.c_str(), g_sSimHeiFont, fFontSize );
			pConfirm->setColor(ccWHITE);
			pStartItem->addChild( pConfirm );
			pConfirm->setPosition( ccp( POSX(121/2), POSX(49/2) ) );
			pStartItem->setTag(101);
			_btnStart = CCMenu::menuWithItems(pStartItem, 0);
			_btnStart->setTouchLayer(TLE::WindowLayer_Common_btn);
			_btnStart->setPosition( CCPointZero );
			m_ContentLayer->addChild(_btnStart);
		}
	}
	
	// buy seat position btn
	{
		CCMenuItemSprite *pStartItem = CCMenuItemSprite::itemFromNormalSprite(
			CCSprite::spriteWithSpriteFrameName("button.png"),
			CCSprite::spriteWithSpriteFrameName("button1.png"),
			this,
			menu_selector(TrainView::buyClickHandler) );
		pStartItem->setPosition( ccp( POSX(282+121/2 + 458), POSX(370)+POSX(49/2) ) );
		string strConfirm = ValuesUtil::Instance()->getString( "trSP" );
		CCLabelTTF* pConfirm = CCLabelTTF::labelWithString( strConfirm.c_str(), g_sSimHeiFont, POSX(24) );
		pStartItem->addChild( pConfirm );
		pConfirm->setColor(ccWHITE);
		pConfirm->setPosition( ccp( POSX(121/2), POSX(49/2) ) );
		_btnBuy = CCMenu::menuWithItems( pStartItem, 0 );
		_btnBuy->setTouchLayer(TLE::WindowLayer_Common_btn);
		_btnBuy->setPosition( CCPointZero );
		m_ContentLayer->addChild( _btnBuy );
	}

	// nor bg
	_trainBgNor = new CCUIBackground();
	_trainBgNor->initWithSpriteFrame("ui2.png", 
		ccp(POSX(14 + 458), POSX(127)),
		ccp(0,0),
		CCSizeMake(POSX(183),POSX(179)));
	m_ContentLayer->addChild(_trainBgNor);
	_trainBgNor->release();

	CCLabelTTF* labelNor = new CCLabelTTF();//hours
	labelNor->initWithString(
		ValuesUtil::Instance()->getString("trT2").c_str(),
		CCSizeMake( POSX(182), POSX(28) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
	labelNor->setColor( ccc3(255, 91, 1) );
	labelNor->setAnchorPoint( CCPointZero );
	_trainBgNor->addChild(labelNor);
	labelNor->setPosition( ccp(POSX(0), POSX(126)) );
	labelNor->release();

	TrainProxy* trainProxy = (TrainProxy*)g_pFacade->retrieveProxy(AppFacade_TRAIN_PROXY_CHANGE);
	char txtNor[128]={0};
	sprintf( txtNor, ValuesUtil::Instance()->getString("TRN019").c_str(), trainProxy->getTimeList()[0].silver );
	labelNor = new CCLabelTTF();//money
	labelNor->initWithString(
		txtNor,
		CCSizeMake( POSX(182), POSX(28) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
	labelNor->setColor( ccc3(255, 91, 1) );
	labelNor->setAnchorPoint( CCPointZero );
	_trainBgNor->addChild(labelNor);
	labelNor->setPosition( ccp(POSX(0), POSX(126-43)) );
	labelNor->release();

	labelNor = new CCLabelTTF();//type
	labelNor->initWithString(
		ValuesUtil::Instance()->getString("TRN020").c_str(),
		CCSizeMake( POSX(182), POSX(28) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
	labelNor->setColor( ccc3(255, 91, 1) );
	labelNor->setAnchorPoint( CCPointZero );
	_trainBgNor->addChild(labelNor);
	labelNor->setPosition( ccp(POSX(0), POSX(126-43*2)) );
	labelNor->release();
	
	// train time tips
	_txtTrain = new CCLabelTTF();
	_txtTrain->initWithString( ValuesUtil::Instance()->getString( "trTime" ).c_str(),
		CCSizeMake( POSX(121), POSX(24) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(20) );
	_txtTrain->setColor( cocos2d::ccWHITE );
	_txtTrain->setAnchorPoint( CCPointZero );
	_txtTrain->setPosition(ccp(POSX(14 + 458), POSX(349)));
	m_ContentLayer->addChild(_txtTrain);
	_txtTrain->release();

	// train time tips
	_txtTufeiGet = new CCLabelTTF();
	_txtTufeiGet->initWithString( ValuesUtil::Instance()->getString( "TRN032" ).c_str(),
		CCSizeMake( POSX(121), POSX(24) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(20) );
	_txtTufeiGet->setColor( cocos2d::ccWHITE );
	_txtTufeiGet->setAnchorPoint( CCPointZero );
	_txtTufeiGet->setPosition(ccp(POSX(14 + 458), POSX(229)));
	m_ContentLayer->addChild(_txtTufeiGet);
	_txtTufeiGet->release();

	_txtGoldRapid = new CCLabelTTF();
	_txtGoldRapid->initWithString(
		ValuesUtil::Instance()->getString("TRN031").c_str(),
		CCSizeMake( POSX(133), POSX(22) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );
	_txtGoldRapid->setColor( cocos2d::ccWHITE );
	_txtGoldRapid->setAnchorPoint( CCPointZero );
	m_ContentLayer->addChild(_txtGoldRapid);
	_txtGoldRapid->release();
	_txtGoldRapid->setPosition( ccp(POSX(303+6 + 458), POSX(178+3)) );
	_txtGoldRapid->setIsVisible(false);
	
	{
		_txtSite = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString( "trPos").c_str(),
			CCSizeMake(POSX(140), POSX(30)), CCTextAlignmentLeft, g_sSimHeiFont, POSX(26));
		_txtSite->setColor( ccc3(161, 254, 0) );
		_txtSite->setAnchorPoint(CCPointZero);
		_txtSite->setPosition( ccp(POSX(30 + 458), POSX(382) ) );
		m_ContentLayer->addChild(_txtSite);
	}

	{
		_txtSiteCnt = CCLabelTTF::labelWithString(
			"",
			CCSizeMake(POSX(80), POSX(30)), CCTextAlignmentLeft, g_sSimHeiFont, POSX(26));
		_txtSiteCnt->setAnchorPoint(CCPointZero);
		_txtSite->setColor( ccc3(161, 254, 0) );
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		_txtSiteCnt->setPosition( ccp(POSX(30+145 + 458), POSX(382) ) );
		m_ContentLayer->addChild(_txtSiteCnt);
	}

	m_vipLev = RoleManage::Instance()->accountInfo()->vipLev();

	// role list view
	addScrollListView();

	
	// left position left and  merch number
	setTrainTips();

	return true;
}

void TrainView::setTrainTips()
{
	char path[128] = {0};
	if (!m_ContentLayer->getChildByTag(Tag_TrainTips1))
	{
		memset(path , 0 ,  sizeof(path));
		sprintf(path , ValuesUtil::Instance()->getString("TRN037").c_str() , RoleManage::Instance()->_mercListEx.size()-1);
		CCLabelTTF * pLabelMercNum = CCLabelTTF::labelWithString(path , CCSizeMake(POSX(420) , POSX(30)) , CCTextAlignmentLeft , "Arial" , POSX(28));
		pLabelMercNum->setColor(ccc3(255,215,0));
		pLabelMercNum->setPosition(ccp(POSX(50) , POSX(105)));
		pLabelMercNum->setAnchorPoint(ccp(0 , 0.5));
		pLabelMercNum->setTag(Tag_TrainTips1);
		m_ContentLayer->addChild(pLabelMercNum , RENDERZ_Container+1);
	}

	if (!m_ContentLayer->getChildByTag(Tag_TrainTips2))
	{
		memset(path , 0 ,  sizeof(path));
		sprintf(path , ValuesUtil::Instance()->getString("TRN036").c_str() , TrainManager::Instance()->getTrainNum() , TrainManager::Instance()->getTrainLim());
		CCLabelTTF * pLabelPos = CCLabelTTF::labelWithString(path , CCSizeMake(POSX(420) , POSX(30)) , CCTextAlignmentLeft , "Arial" , POSX(28));
		pLabelPos->setColor(ccc3(12,233,25));
		pLabelPos->setPosition(ccp(POSX(50) , POSX(65)));
		pLabelPos->setAnchorPoint(ccp(0 , 0.5));
		pLabelPos->setTag(Tag_TrainTips2);
		m_ContentLayer->addChild(pLabelPos , RENDERZ_Container+1);
	}
	else
	{
		memset(path , 0 ,  sizeof(path));
		sprintf(path , ValuesUtil::Instance()->getString("TRN036").c_str() , TrainManager::Instance()->getTrainNum() , TrainManager::Instance()->getTrainLim());
		((CCLabelTTF * )m_ContentLayer->getChildByTag(Tag_TrainTips2))->setString(path);
	}	
}

void TrainView::setRoleItem( int id, PlayerInfoVo* pPlayerInfoVo )
{
	if ( !pPlayerInfoVo )
	{
		cocos2d::CCLog("TrainView::pPlayerInfoVo 0!");
		return;
	}

	sDic.push_back( pPlayerInfoVo->playerBaseInfo.id );

	itemDic.insert( make_pair(id, pPlayerInfoVo) );
}

/**
* creat merc list
*/ 
void TrainView::createMercList( std::map<int, TrainVo*>* trainDic )
{
	resetRoleItem();

	int i = 0;
	RoleManage * pInstance = RoleManage::Instance();
	PlayerInfoVo* pPlayerInfoVo = pInstance->roleInfo();
	//setRoleItem( i, pPlayerInfoVo );

	//std::map<int, PlayerInfoVo>* dic = pInstance->mercList();
	//std::map<int, PlayerInfoVo>::iterator it = dic->begin(); 
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* dic = RoleManage::Instance()->mercListEx();  // LH20121019listorder
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator it = dic->begin();

	for ( it ; it != dic->end(); it++ )
	{
		//if ( it->first == pPlayerInfoVo->playerBaseInfo.id ) continue;
		PlayerInfoVo& playerInfo = it->second;
		setRoleItem( ++i, &playerInfo );
	}
	//_mercId = pPlayerInfoVo->playerBaseInfo.id;

	if (g_pFigureScrollView)
	{
		m_SelectedItem = g_pFigureScrollView->currentScreen-1;
	}
	
	if ( m_SelectedItem < (int)sDic.size() )
	{
		_mercId = sDic[m_SelectedItem];
	}	
}
void TrainView::resetRoleItem()
{
	sDic.clear();
	itemDic.clear();
}

void TrainView::roleItemClickHandler( int index )
{
	if ( index < 0 )
	{
		index = 0;
	}
	m_SelectedItem = index;
	if ( m_SelectedItem < (int)sDic.size() )
	{
		_mercId = sDic[m_SelectedItem];
		std::map<int, PlayerInfoVo*>::iterator it = itemDic.find( index );

		if ( it != itemDic.end() )
		{
			_merc = it->second ;
		}
	}

	TrainViewMediator* pMeditor = (TrainViewMediator*)g_pFacade->retrieveMediator( AppFacade_TRAIN_PROXY_CHANGE );
	pMeditor->selectMercHandler(_mercId);
}

/**
* openTrainPanel
* @trainVo Vo
*/
void TrainView::openTrainPanel( TrainVo* trainVo )
{
	_trainVo = trainVo;

	CCSize csBt( POSX(121), POSX(49) );
	float fFontSize( POSX(20) );

	if ( !_trainTime )
	{
		// train time
		_trainTime = TrainTime::TrainTimeWithTrainVo( trainVo );
		_trainTime->setPosition( ccp(POSX(110 + 458), POSX(350-5)) );
		m_ContentLayer->addChild(_trainTime);
	}
	else
	{
		_trainTime->update(_trainVo);
		_trainTime->reinit();
	}

	if ( !_txtMode )
	{
		// cur mode
		string strName = ValuesUtil::Instance()->getString( "" );

		_txtMode = CCLabelTTF::labelWithString( strName.c_str(),
			CCSizeMake( POSX(141), POSX(24) ), CCTextAlignmentLeft, g_sSimHeiFont, fFontSize );
		_txtMode->setAnchorPoint( CCPointZero );
		_txtMode->setColor( cocos2d::ccWHITE );
		_txtMode->setPosition( ccp(POSX(16+153 + 458), POSX(440) ) );
		m_ContentLayer->addChild(_txtMode);
	}
	if ( !_txtTufeContent )
	{
		// lilian tufei tips
		_txtTufeContent = CCLabelTTF::labelWithString("",
			CCSizeMake(POSX(220), POSX(30)), CCTextAlignmentLeft, g_sSimHeiFont, POSX(26));
		_txtTufeContent->setAnchorPoint( CCPointZero );
		_txtTufeContent->setColor( ccc3( 222, 255, 0 ) );
		_txtTufeContent->setPosition( ccp(POSX(110 + 458), POSX(225+3) ) );
		m_ContentLayer->addChild(_txtTufeContent);
	}

	{
		if (!_btnGold)
		{
			//  mode btn
			{
				_btnGoldImg = CCMenuItemSprite::itemFromNormalSprite(
					CCSprite::spriteWithSpriteFrameName("button.png"),
					CCSprite::spriteWithSpriteFrameName("button1.png"),
					CCSprite::spriteWithSpriteFrameName("button2.png"),
					this,
					menu_selector(TrainView::goldRapidHandler) );
				_btnGoldImg->setPosition( ccp( POSX(290+3 + 458)+csBt.width/2, POSX(212+3)+csBt.height/2 ) );
				CCLabelTTF* pConfirm = CCLabelTTF::labelWithString(
					ValuesUtil::Instance()->getString( "trGoldBtn" ).c_str(),
					CCSizeMake( POSX(121), POSX(28) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
				pConfirm->setColor(ccWHITE);
				_btnGoldImg->addChild( pConfirm );
				_btnGoldImg->setTag(101);
				pConfirm->setPosition( ccp( POSX(121/2), POSX(49/2) ) );
				_btnGold = CCMenu::menuWithItems(_btnGoldImg, 0);
				_btnGold->setTouchLayer( TLE::WindowLayer_Common_btn );
				_btnGold->setPosition( CCPointZero );
				m_ContentLayer->addChild(_btnGold);
			}
		}
		/*		if (m_iInitUIRoleLev>=1)
		{
		if (_btnGoldImg)
		{
		_btnGoldImg->setIsEnabled(true);
		}			
		} 
		else
		{
		if (_btnGoldImg)
		{
		_btnGoldImg->setIsEnabled(false);
		}
		}*/		
	}
	
	if ( !_btnEnd )
	{
		//  end btn
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		if(pNormalSprite && pPressedSprite)
		{
			CCMenuItemSprite *pItem = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this,
				menu_selector(TrainView::endTrainHandler) );
			pItem->setPosition( ccp( POSX(290+3 + 458)+csBt.width/2, POSX(338+2)+csBt.height/2 ) );
			string strConfirm = ValuesUtil::Instance()->getString( "T0002" );
			CCLabelTTF* pConfirm = CCLabelTTF::labelWithString(
				strConfirm.c_str(),
				CCSizeMake( POSX(121), POSX(28) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
			pItem->addChild( pConfirm );
			pConfirm->setColor(ccWHITE);
			pConfirm->setPosition( ccp( POSX(121/2), POSX(49/2) ) );
			_btnEnd = CCMenu::menuWithItems(pItem, 0);
			_btnEnd->setTouchLayer( TLE::WindowLayer_Common_btn );
			_btnEnd->setPosition( CCPointZero );
			m_ContentLayer->addChild(_btnEnd);
		}
	}

	if ( !_txtTrainUp )
	{
		// cur mode tips
		_txtTrainUp = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString( "TRN030" ).c_str(),
			CCSizeMake( POSX(437), POSX(28) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
		_txtTrainUp->setAnchorPoint( CCPointZero );
		_txtTrainUp->setColor( cocos2d::ccRED );
		_txtTrainUp->setPosition( ccp(POSX(0 + 458), POSX(110)) );
		m_ContentLayer->addChild(_txtTrainUp);
	}

	SetVisibleTrainPanel( true );
	SetVisibleTimePanel( false );

}

void TrainView::SetVisibleTrainPanel( bool bVar )
{
	if ( _trainTime )
	{
		_trainTime->setIsVisible(bVar);    // train time 
	}

	if (_txtTrain)
	{
		_txtTrain->setIsVisible(bVar);   // train time tips
	}
	
	if (_btnEnd)
	{
		_btnEnd->setIsVisible(bVar);				// end btn
	}
	
	if (_txtTufeContent)
	{
		_txtTufeContent->setIsVisible(bVar);
	}
	
	if (_btnGold)
	{
		_btnGold->setIsVisible(bVar);
	}

	if (_txtGoldRapid)
	{
		_txtGoldRapid->setIsVisible(bVar);
	}

	if (_txtTufeiGet)
	{
		_txtTufeiGet->setIsVisible(bVar);
	}

	if (_txtTrainUp)
	{
		_txtTrainUp->setIsVisible(bVar);
	}
	
}
	 
/**
* open Time Panel
* @infos train time array 
*/
void TrainView::openTimePanel( vector<TimeInitStruct>& infos )
{
	int timesize = infos.size();

	resetTimeItem();
	for ( int i = 0; i < timesize; i++ )
	{
		timeDic[i].id = infos[i].id;
		timeDic[i].silver = infos[i].silver;
		timeDic[i].gold = infos[i].gold;
		timeDic[i].desc = infos[i].desc;
	}
	
	_timeObj = &timeDic[1];
	m_selectTimeIndex = 1;

	if ( !_txtModeFont )
	{
		// cur mode tips
		_txtModeFont = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString( "trCurMo" ).c_str(),
			CCSizeMake( POSX(437), POSX(24) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
		_txtModeFont->setAnchorPoint( CCPointZero );

		_txtModeFont->setColor( cocos2d::ccRED );
		_txtModeFont->setPosition( ccp(POSX(0 + 458), POSX(480)) );
		m_ContentLayer->addChild(_txtModeFont);
	}


	// _btnDoubleExpStart
	{
		if ( !_btnDoubleExpStart/*&& (m_iInitUIRoleLev>=1)*/ )
		{
			_btnStartItem = CCMenuItemSprite::itemFromNormalSprite(
				CCSprite::spriteWithSpriteFrameName("button.png"),
				CCSprite::spriteWithSpriteFrameName("button1.png"),
				CCSprite::spriteWithSpriteFrameName("button2.png"),
				this,
				menu_selector(TrainView::startDoubleTrainHandler) );
			_btnStartItem->setPosition( ccp( POSX(282+121/2 + 458), POSX(60)+POSX(25) ) );
			string strConfirm = ValuesUtil::Instance()->getString( "T030" );
			CCLabelTTF* pConfirm = CCLabelTTF::labelWithString( strConfirm.c_str(), g_sSimHeiFont, POSX(24) );
			pConfirm->setColor(ccWHITE);
			_btnStartItem->addChild( pConfirm );
			pConfirm->setPosition( ccp( POSX(121/2), POSX(49/2) ) );
			_btnStartItem->setTag(101);
			_btnDoubleExpStart = CCMenu::menuWithItems(_btnStartItem, 0);
			_btnDoubleExpStart->setTouchLayer(TLE::WindowLayer_Common_btn);
			_btnDoubleExpStart->setPosition( CCPointZero );
			m_ContentLayer->addChild(_btnDoubleExpStart);
		}
		/*		if (m_iInitUIRoleLev>=1)
		{
		if (_btnStartItem)
		{
		_btnStartItem->setIsEnabled(true);
		}			
		} 
		else
		{
		if (_btnStartItem)
		{
		_btnStartItem->setIsEnabled(false);
		}			
		}	*/	
	}
	// rush bg
	if ( !_trainBgRush/* && (m_iInitUIRoleLev>=1)*/ )
	{
		_trainBgRush = new CCUIBackground();
		_trainBgRush->initWithSpriteFrame("ui2.png", 
			ccp(POSX(244 + 458), POSX(127)),
			ccp(0,0),
			CCSizeMake(POSX(183),POSX(179)));
		m_ContentLayer->addChild(_trainBgRush);
		_trainBgRush->release();

		CCLabelTTF* labelDouble = new CCLabelTTF();
		labelDouble->initWithString(
			ValuesUtil::Instance()->getString("trT5").c_str(),
			CCSizeMake( POSX(182), POSX(28) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
		labelDouble->setAnchorPoint( CCPointZero );
		_trainBgRush->addChild(labelDouble);
		labelDouble->setColor( ccc3(161, 254, 0) );
		labelDouble->setPosition( ccp(POSX(0), POSX(126)) );
		labelDouble->release();

		TrainProxy* trainProxy = (TrainProxy*)g_pFacade->retrieveProxy(AppFacade_TRAIN_PROXY_CHANGE);
		char txtNor[128]={0};
		sprintf( txtNor, ValuesUtil::Instance()->getString("TRN018").c_str(), 10 );
		labelDouble = new CCLabelTTF();//money
		labelDouble->initWithString(
			txtNor,
			CCSizeMake( POSX(182), POSX(28) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
		labelDouble->setColor( ccc3(161, 254, 0) );
		labelDouble->setAnchorPoint( CCPointZero );
		_trainBgRush->addChild(labelDouble);
		labelDouble->setPosition( ccp(POSX(0), POSX(126-43)) );
		labelDouble->release();

		labelDouble = new CCLabelTTF();//type
		labelDouble->initWithString(
			ValuesUtil::Instance()->getString("TRN021").c_str(),
			CCSizeMake( POSX(182), POSX(28) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
		labelDouble->setColor( ccc3(161, 254, 0) );
		labelDouble->setAnchorPoint( CCPointZero );
		_trainBgRush->addChild(labelDouble);
		labelDouble->setPosition( ccp(POSX(0), POSX(126-43*2)) );
		labelDouble->release();
	}
		
	SetVisibleTimePanel( true );
	SetVisibleTrainPanel( false );
}
void TrainView::SetVisibleTimePanel( bool bVar )
{
	if ( !_btnStart )
	{
		return;
	}
	if ( _btnStart )
	{
		_btnStart->setIsVisible(bVar); // btn Start 
	}

	if (_btnBuy)
	{
		_btnBuy->setIsVisible(bVar);
	}
	
	if (_txtSite)
	{
		_txtSite->setIsVisible(bVar);
		_txtSiteCnt->setIsVisible(bVar);
	}

	if (_txtModeFont)
	{
		_txtModeFont->setIsVisible(bVar);			// train mode tips
	}

	if (_btnDoubleExpStart)
	{
		_btnDoubleExpStart->setIsVisible(bVar);
	}
	if (_trainBgNor)
	{
		_trainBgNor->setIsVisible(bVar);
	}
	if (_trainBgRush)
	{
		_trainBgRush->setIsVisible(bVar);
	}	
}
void TrainView::setTimeItem( int i, TimeInitStruct* info )
{    
    //CCLog("=====================info=%s,Silver=%d,Gold=%d", info->desc.c_str(), info->silver, info->gold);
	timeDic[i] = info[i];
}

void TrainView::resetTimeItem()
{
	for ( int i = 0; i < 7; i++ )
	{
		timeDic[i].id = 0;
		timeDic[i].silver = 0;
		timeDic[i].gold = 0;
		timeDic[i].desc = "";
	}
}


/**
* update Merc Info
* @merc Info
*/
void TrainView::updateMercInfo( PlayerInfoVo* merc, bool notToCheck/* = false */ )
{
	//if ( _headMc && m_pTextureList[m_SelectedItem] )
	//{
	//	_headMc->setTexture( m_pTextureList[m_SelectedItem] );
	//}

	//char txt[20];
	//if ( _txtName )
	//{
	//	_txtName->setString( merc->playerBaseInfo.name.c_str() );
	//}
	//if ( _txtLevel )
	//{
	//	sprintf( txt, ValuesUtil::Instance()->getString( "trJi" ).c_str(), merc->playerBaseInfo.lev() );		
	//	_txtLevel->setString( txt );
	//}
	//if ( _txtCarer )
	//{
	//	string str = FigureBaseManage::Instance()->getCareerStr( merc->playerBaseInfo.career );
	//	_txtCarer->setString( str.c_str() );
	//}
}

void TrainView::CloseBtCallback( CCObject* pSender )
{
	PopContainer::setisPop( false );
}

/**
* update Merc Exp
* 
*/
void TrainView::updateMercExp( int mercId, int curExp, int needExp )
{
	//if(  _mercId==mercId && _txtExp  )
	//{
	//	//_barExpMc.width = curExp/needExp * 162;  
	//	//_txtExp.text = curExp + "/" + needExp;
	//	char txt[52];
	//	sprintf( txt, "%d/%d", curExp, needExp );
	//	_txtExp->setString( txt );
	//}
}

/** 
* update Train Num Tips 
*/
void TrainView::updateTrainNumTips( int trainNum, int trainLim )
{
	//_txtSite.text = "训练位置  "+ trainNum + "/" + trainLim;	 %d / %d
	char str[ 54 ];
	sprintf( str, "%d/%d", trainNum, trainLim );
	if ( _txtSiteCnt )
	{
		_txtSiteCnt->setString( str );
	}
}

///**
// * end click event
// */
//private function btnEndClickHandler(event:MouseEvent):void{
//	Alert.show("你确定结束训练吗","",1, endOK, 0, "确定", "取消");
//	function endOK():void{
//		dispatchEvent(new ParamEvent(END_TRAIN));
//	}
//}

/** 
 * buy pos
 */ 
void TrainView::buyClickHandler(CCObject* pSender)
{
	//dispatchEvent(new ParamEvent(BUY_POSITION));
	TrainViewMediator* pViewMeditor = (TrainViewMediator*)g_pFacade->retrieveMediator( AppFacade_TRAIN_PROXY_CHANGE );
	pViewMeditor->buyPositionHandler();
}

/**
* start Train Handler
* @param: info.id info.silver info.gold
*/ 
void TrainView::startTrainHandler(CCObject* pSender)
{
	// new hand
	if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_Train) == NewhandManager::Flag_New)
	{
		NewhandManager::Instance()->setNewHandStateByType(LevLimitConst::Limit_Train , NewhandManager::Flag_Done);
		NewhandManager::Instance()->touchNextEvent(208);
	}


	TrainProxy* trainProxy = (TrainProxy*)g_pFacade->retrieveProxy(AppFacade_TRAIN_PROXY_CHANGE);
	//if ( _timeObj )
	{
		TrainViewMediator* pViewMeditor = (TrainViewMediator*)g_pFacade->retrieveMediator( AppFacade_TRAIN_PROXY_CHANGE );
		pViewMeditor->startTrainHandler( _mercId, 0, 0, 0, trainProxy->getTimeList()[0].silver );
	}

	m_selectTimeIndex = 1;

	//
	showIsTrained(_mercId);

	// by LONGHUI 20121012
	// start train button
	NewhandManager::Instance()->touchNextEvent(103);
}

void TrainView::startDoubleTrainHandler(CCObject* pSender)
{
	m_iInitVipLev = RoleManage::Instance()->accountInfo()->vipLev();
	if (!VIPMgr::Instance()->hasVIPFunc(VIPLimitConst::VIP_GoldTrainMode , m_iInitVipLev))
	{
		CCNode* pConfirmLayer = LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame);
		if (pConfirmLayer)
		{
			return;
		}
		Confirm* pConfirm = new Confirm();
		std::string stdstr = LangManager::getText("TRN033", 1);
		pConfirm->initWithParam( stdstr.c_str(), this,
			menu_selector(TrainViewMediator::onAlertBuySit),
			menu_selector(TrainViewMediator::onCancelBuySit),
			LangManager::getText("COM659") );

		LayerManager::windowLayer->addChild(pConfirm,WindowLayer::WindowLayerZ_confirmFrame, WindowLayer::WindowLayerTAG_confirmFrame);
		pConfirm->release();	
		return;
	}

	m_selectTimeIndex = 4;

	TrainProxy* trainProxy = (TrainProxy*)g_pFacade->retrieveProxy(AppFacade_TRAIN_PROXY_CHANGE);
	//if ( _timeObj )
	{
		TrainViewMediator* pViewMeditor = (TrainViewMediator*)g_pFacade->retrieveMediator( AppFacade_TRAIN_PROXY_CHANGE );
		pViewMeditor->startTrainHandler( _mercId, 1, 3, 10, 0 );
	}

	// by LONGHUI 20121012
	NewhandManager::Instance()->touchNextEvent(103);
}

/**
* end Train Handler
*/ 
void TrainView:: endTrainHandler(CCObject* pSender)
{
	TrainViewMediator* pViewMeditor = (TrainViewMediator*)g_pFacade->retrieveMediator( AppFacade_TRAIN_PROXY_CHANGE );
	pViewMeditor->endTrainHandler( _mercId );

}

void TrainView:: goldRapidHandler(CCObject* pSender)
{
	if (RoleManage::Instance()->accountInfo()->gold() < 5)
	{
		LangManager::msgShow("trGold");
		return;
	}

	//m_iInitVipLev = RoleManage::Instance()->accountInfo()->vipLev();
	//if (m_iInitVipLev<1)
	//{
	//	CCNode* pConfirmLayer = LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame);
	//	if (pConfirmLayer)
	//	{
	//		return;
	//	}
	//	Confirm* pConfirm = new Confirm();
	//	std::string stdstr = LangManager::getText("TRN033", 1);
	//	pConfirm->initWithParam( stdstr.c_str(), this,
	//		menu_selector(TrainViewMediator::onAlertBuySit),
	//		menu_selector(TrainViewMediator::onCancelBuySit),
	//		LangManager::getText("COM659") );

	//	LayerManager::windowLayer->addChild(pConfirm,WindowLayer::WindowLayerZ_confirmFrame, WindowLayer::WindowLayerTAG_confirmFrame);
	//	pConfirm->release();	
	//	return;
	//}	

	TrainViewMediator* pViewMeditor = (TrainViewMediator*)g_pFacade->retrieveMediator( AppFacade_TRAIN_PROXY_CHANGE );
	pViewMeditor->rapidLeapHandler( _mercId, 1 );
}

/**
* update Rapic Effect
* @param mercId :ID
* @param: exp Added
*/
void TrainView:: updateRapicEffect( int mercId, int rapicExp, int critExp )
{
	if(_mercId==mercId){
		//TrainEffectUtil.playRapicEffect(rapics);
				
		//var isCrit:Boolean = (critExp==0)?false:true;
		//var rapicMc:RapicMC =new RapicMC(rapicExp+critExp, isCrit);
		//rapicMc.x = 202;
		//rapicMc.y = 148;
		//_trainPanel.addChild(rapicMc);
		//		
		//var group:TweenGroup = new TweenGroup();
		//var tween:TweenLite = TweenLite.from(rapicMc, 0.5, {alpha:0});
		//group.tweens.push(tween);
		//group.align = TweenGroup.ALIGN_START;
		//TweenPlugin.activate([GlowFilterPlugin]); 
		//tween = TweenLite.to(rapicMc, 0.1, {glowFilter:{alpha:0.7, blurX:8, blurY:8, color:0xffff00, strength:8}});
		//group = new TweenGroup([tween]);
		//group.yoyo = 3;
		//		
 	//	rapics.push(rapicMc);

		// tips：exp add
		char txtTufe[54];
		if ( critExp == 0 )
		{
			sprintf( txtTufe, ValuesUtil::Instance()->getString( "trGetEx ").c_str(), rapicExp );
		}
		else
		{
			sprintf( txtTufe, ValuesUtil::Instance()->getString( "trGetExCri ").c_str(), rapicExp, critExp );
		}
		if ( !strs )
		{
			string strName = txtTufe;
			
			strs = CCLabelTTF::labelWithString( strName.c_str(), g_sSimHeiFont, POSX(20) );
			strs->setColor( cocos2d::ccYELLOW );
			CCSize size = CCDirector::sharedDirector()->getWinSize();
			strs->setPosition( ccp( size.width/2 + POSX( 458)- POSX(30), size.height/2 - POSX(200) ) );
			m_ContentLayer->addChild(strs);
		}
		else
		{
			strs->setString(txtTufe);
		}
		
		CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(TrainView::rapicFunction), this, 3.0f, false);
	}
}

void TrainView::rapicFunction( float dt )
{
	strs->setIsVisible(false);
	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(TrainView::rapicFunction), this);
}

/**
* play Crit Effect 
* 
*/		
void TrainView::playCritEffect( int critExp )
{
	if(critExp<=0) return;

	//var pid:int = setInterval(delayFunc, 100);
	//function delayFunc():void{
	//	clearInterval(pid);
	//	_eftCrit.visible = true;
	//	_eftCrit.addEventListener(Event.ENTER_FRAME, onEnterFrame);
	//	_eftCrit.gotoAndPlay(1);
	//}
	//		
	//function onEnterFrame(e:Event):void{
	//	if(_eftCrit.currentFrame >= _eftCrit.totalFrames) {
	//		_eftCrit.gotoAndStop(1);
	//		_eftCrit.visible = false;
	//		_eftCrit.removeEventListener(Event.ENTER_FRAME, onEnterFrame);
	//	}
	//}
}

/** 
 * Set Not EnoughGold
 */ 
void TrainView::SetNotEnoughGold()
{
	if ( _txtSite )
	{
		string strName = ValuesUtil::Instance()->getString("trGold");
		
		_txtSite->setString( strName.c_str() );
	}
}

void TrainView::updateRapicTips( bool showCD, string rapicTips, int exp )
{
	if ( _txtTufeContent )
	{
		_txtTufeContent->setString( rapicTips.c_str() );
	}

	//// gold rapic txt
	//if (_txtGoldRapid)
	//{	
	//	char tmp[128]={0};
	//	sprintf( tmp, ValuesUtil::Instance()->getString("TRN031").c_str(), _rapicGold, exp );
	//	_txtGoldRapid->setString( tmp );
	//}
}

int TrainView::getMercId()
{
	return _mercId;
}

void TrainView::setMercId(int id)
{
	_mercId = id;
}

void TrainView::showIsTrained(int id)
{
	if (!m_ContentLayer)
	{
		return;
	}	
	RoleListView * pListView = (RoleListView *)m_ContentLayer->getChildByTag(Tag_ListView);
	if (pListView)
	{
		pListView->showIsTrained(id);
	}	
}

void TrainView::clickCloseHandler( CCObject* pSender )
{
	PopContainer::clickCloseHandler(pSender);

	this->release();

	TrainViewMediator* pMediator = (TrainViewMediator*)g_pFacade->retrieveMediator(AppFacade_TRAIN_PROXY_CHANGE);
	pMediator->_trainView = 0;
	ViewManager::getInstance()->trainView = 0;

	// new hand
	if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_Train) == NewhandManager::Flag_New)
	{
		NewhandManager::Instance()->touchNextScript("addBtn" , ButtonIDConst::ButtonID_Train);
	}
	else if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_Train) == NewhandManager::Flag_Done)
	{
		NewhandManager::Instance()->setNewHandStateByType(LevLimitConst::Limit_Train , NewhandManager::Flag_Close);
		NewhandManager::Instance()->touchNextEvent(NewhandConst::EVENT_TRAIN_OVER);
		NewhandManager::Instance()->doTaskFollow();
	}
}

void TrainView::addScrollListView()
{
	if (!m_ContentLayer)
	{
		return;
	}
	
	RoleListView * pListView = RoleListView::listViewWithCCRect(CCSZIE_TRAIN_LISTVIEW, false);
	pListView->m_pri = TLE::WindowLayer_TrainList - 1;
	pListView->setAnchorPoint(CCPointZero);
	pListView->setSpacingVertical(POSX(10));
	//pListView->setOnItemActionListener(pListView);
	pListView->scrollToEnd(0);
	pListView->setWorldSpaceLeftBottomPoint(ccpAdd(ccpAdd(pListView->getPosition() , this->getPosition()) , m_ContentLayer->getPosition()));
	pListView->setTag(Tag_ListView);
	m_ContentLayer->addChild(pListView);
	pListView->resetView();
	pListView->release();
}

void TrainView::updateLevelLabel(int figureId , int level)
{
	if (!m_ContentLayer)
	{
		return;
	}	
	RoleListView * pListView = (RoleListView *)m_ContentLayer->getChildByTag(Tag_ListView);
	if (!pListView)
	{
		return;
	}	
	CCMutableArray<LayerNode *> * pArray = pListView->getChilds();
	if (!pArray)
	{
		return;
	}	
	int n = pArray->count();
	for (int i = 0; i < n ; i++)
	{
		LayerNode * pLayer = pArray->getObjectAtIndex(i);
		if (pLayer)
		{
			TrainRoleItem * pItem = (TrainRoleItem *)pLayer->getChildByTag(RoleListView::Tag_ListItem);
			if (pItem && pItem->getAcountId() == figureId)
			{
				pItem->updateLevelLabel(level);
				break;
			}
		}
	}
}

TrainView::~TrainView()
{
	ViewManager::getInstance()->trainView = 0;

	this->removeAllChildrenWithCleanup(true);

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/formation/res_formation_1.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/train/res_train_dragon.plist");
}

CCNode *  TrainView::getNewHandItem(int id)
{
	switch (id)
	{
	case 100:
		{
			if (_btnStart)
			{
				return _btnStart->getChildByTag(101);
			}
		}
		break;
	case 101:
		{
			
		}
		break;
	case 103:
		{
			return g_pPopManage->getBtnX();
		}
	default:
		break;
	}
	return 0;
}