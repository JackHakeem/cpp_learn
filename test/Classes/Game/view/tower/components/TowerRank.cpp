#include "TowerRank.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"
#include "PopUIBg.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ValuesUtil.h"
#include "../TowerMediator.h"
#include "manager/LayerManager.h"
#include "Confirm.h"
#include "socket/command/c3c/CCMD3CD.h"
#include "manager/LangManager.h"
#include "TowerConfirm.h"
#include "model/player/RoleManage.h"
#include "socket/command/c3c/CCMD3CA.h"
#include "socket/network/GameServerSocket.h"


static const float FontSize3 = 24.0f;
static float FontSize2 = 20.0f;

TowerRank::TowerRank()
{
	_pageNav = 0;
	leaveNameFighting = false;

	_pStrengUpItem = 0;
	_btnStrengUp = 0;

	m_bFirstOpen = true;
	m_bClickRank = false;
	_preRank = 0;
	m_bRnkNeedFight = false;
}

bool TowerRank::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	//
	CCSize csIner( POSX(923), POSX(562) );
	_container = new LayerNode();
	this->addChild(_container);
	_container->setContentSize(csIner);
	_container->setPosition(POS(ccp(17, 15), ScaleUtil::CENTER_TOP));

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	//title
	SpriteNode* title = new SpriteNode();
	title->initWithSpriteFrameName("tower/towerRank.png");
	_container->addChild(title, 1);
	title->setPosition(ccp(POSX(403-45), POSX(541)));
	title->setAnchorPoint(CCPointZero);
	title->release();

	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("popuibg/bg1.png",
		ccp(POSX(0), POSX(0)), ccp(0,0), CCSizeMake(w_bg1, h_bg1));
	_container->addChild(_bg1);
	_bg1->release();

	CCUIBackground* _bg2 = new CCUIBackground();
	_bg2->initWithSpriteFrame("popuibg/bg2.png",
		ccp(POSX(11), POSX(19)), ccp(0,0), CCSizeMake(w_bg2, h_bg2));
	_container->addChild(_bg2);
	_bg2->release();

	CCUIBackground* _bg3 = new CCUIBackground();
	_bg3->initWithSpriteFrame("popuibg/bg2.png",
		ccp(POSX(11), POSX(29)), ccp(0,0), CCSizeMake(POSX(613), POSX(506)));
	_container->addChild(_bg3);
	_bg3->release();

	CCUIBackground* _bg4 = new CCUIBackground();
	_bg4->initWithSpriteFrame("popuibg/bg2.png",
		ccp(POSX(629), POSX(29)), ccp(0,0), CCSizeMake(POSX(282), POSX(506)));
	_container->addChild(_bg4);
	_bg4->release();

	initView();

	// close
	CCSprite *pCloseNormalSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_normal.png");
	CCSprite *pClosePressedSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_pressed.png");
	CCMenuItemSprite *_btnX = CCMenuItemSprite::itemFromNormalSprite(
		pCloseNormalSprite,
		pClosePressedSprite,
		this, 
		menu_selector(TowerRank::dispear) );
	_btnX->setPosition(ccp(POSX(912), POSX(592)) );

	CCMenu *buttonMenu = new CCMenu();
	buttonMenu->init();
	buttonMenu->addChild(_btnX, 0, 0);
	buttonMenu->setPosition(ccp(0, 0));
	buttonMenu->setTouchLayer(TLE::WindowLayer_PopUIBgTAG_btn_X-200);
	_container->addChild(buttonMenu);
	buttonMenu->setIsVisible(true);
	buttonMenu->release();

	//我的成绩
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("TOWR060").c_str(),
			CCSizeMake(POSX(283), POSX(31)), CCTextAlignmentCenter, "Arial", POSX(31));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(629), POSX(496)));
		_container->addChild(pLabel);
		pLabel->setColor(ccc3(255,196,0));		
	}

	//最佳成绩
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("TOWR062").c_str(),
			CCSizeMake(POSX(105), POSX(22)), CCTextAlignmentLeft, "Arial", POSX(22));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(645), POSX(435)));
		_container->addChild(pLabel);
		pLabel->setColor(ccWHITE);

		_txtBest = CCLabelTTF::labelWithString(
			"0",
			CCSizeMake(POSX(80+40), POSX(48)), CCTextAlignmentCenter, "Arial", POSX(48));
		_txtBest->setAnchorPoint(ccp(0, 0));
		_txtBest->setPosition(ccp(POSX(645+105), POSX(435)));
		_container->addChild(_txtBest);
		_txtBest->setColor(ccWHITE);

		pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("TOWR061").c_str(),
			CCSizeMake(POSX(105), POSX(22)), CCTextAlignmentCenter, "Arial", POSX(22));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(645+105+80), POSX(435)));
		_container->addChild(pLabel);
		pLabel->setColor(ccWHITE);
	}

	//上次成绩
	{
		//CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
		//	ValuesUtil::Instance()->getString("TOWR063").c_str(),
		//	CCSizeMake(POSX(120), POSX(22)), CCTextAlignmentLeft, "Arial", POSX(22));
		//pLabel->setAnchorPoint(ccp(0, 0));
		//pLabel->setPosition(ccp(POSX(645), POSX(325)));
		//_container->addChild(pLabel);
		//pLabel->setColor(ccWHITE);

		//_txtLast = CCLabelTTF::labelWithString(
		//	"0",
		//	CCSizeMake(POSX(80), POSX(48)), CCTextAlignmentCenter, "Arial", POSX(48));
		//_txtLast->setAnchorPoint(ccp(0, 0));
		//_txtLast->setPosition(ccp(POSX(645+105), POSX(325)));
		//_container->addChild(_txtLast);
		//_txtLast->setColor(ccWHITE);

		//pLabel = CCLabelTTF::labelWithString(
		//	ValuesUtil::Instance()->getString("TOWR061").c_str(),
		//	CCSizeMake(POSX(105), POSX(22)), CCTextAlignmentCenter, "Arial", POSX(22));
		//pLabel->setAnchorPoint(ccp(0, 0));
		//pLabel->setPosition(ccp(POSX(645+105+80), POSX(325)));
		//_container->addChild(pLabel);
		//pLabel->setColor(ccWHITE);
	}

	//我的留名
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("TOWR064").c_str(),
			CCSizeMake(POSX(120), POSX(22)), CCTextAlignmentLeft, "Arial", POSX(22));
		pLabel->setAnchorPoint(ccp(0, 0));
		//pLabel->setPosition(ccp(POSX(645), POSX(218)));
		pLabel->setPosition(ccp(POSX(645), POSX(325)));
		_container->addChild(pLabel);
		pLabel->setColor(ccWHITE);


		_txtMyRecord = CCLabelTTF::labelWithString(
			"0",
			CCSizeMake(POSX(80+40), POSX(48)), CCTextAlignmentCenter, "Arial", POSX(48));
		_txtMyRecord->setAnchorPoint(ccp(0, 0));
		//_txtMyRecord->setPosition(ccp(POSX(645+105), POSX(218)));
		_txtMyRecord->setPosition(ccp(POSX(645+105), POSX(325)));
		_container->addChild(_txtMyRecord);
		_txtMyRecord->setColor(ccWHITE);

		pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("TOWR061").c_str(),
			CCSizeMake(POSX(105), POSX(22)), CCTextAlignmentCenter, "Arial", POSX(22));
		pLabel->setAnchorPoint(ccp(0, 0));
		//pLabel->setPosition(ccp(POSX(645+105+80), POSX(218)));
		pLabel->setPosition(ccp(POSX(645+105+80), POSX(325)));
		_container->addChild(pLabel);
		pLabel->setColor(ccWHITE);
	}

	//印上榜单
	{
		_restCountLabel = CCLabelTTF::labelWithString(
			"",
			CCSizeMake(POSX(283), POSX(24)), CCTextAlignmentCenter, "Arial", POSX(20));
		_restCountLabel->setAnchorPoint(ccp(0, 0));
		_restCountLabel->setPosition(ccp(POSX(629), POSX(50)));
		_container->addChild(_restCountLabel);
		_restCountLabel->setColor(ccWHITE);		
	}

	this->setIsTouchEnabled(true);
	return true;
}

void TowerRank::initView()
{
	_pageNav = new TowerPageNav();
	_pageNav->init();
	//_pageNav->addEventListener(TowerRank::PAGE_CHANGE,
	//	g_pTowerMediator, callfuncND_selector(TowerMediator::onPageChange)); 
	_container->addChild(_pageNav, 1, 99);
	_pageNav->setPosition( ccp( POSX(223), POSX(29) ) );
	_pageNav->setPage( 12, 1);

	_listContainer = ListContainer::ListContainerScrollViewWithCCRect(
		CCRectMake(POSX(11), POSX(94),POSX(613), POSX(390))
		); 
	_listContainer->m_pri = TLE::IntervalLayer;
	_container->addChild(_listContainer);
	_listContainer->release();
	//CCLayerColor* pCol = CCLayerColor::layerWithColorWidthHeight(ccc4(0,0,255,100),POSX(615), POSX(389));
	//_listContainer->addChild(pCol);

	float fTitleH = POSX(500);
	float fTitleW = (35.0f+5.0f);
	ccColor3B c3 = ccYELLOW;//{255, 180, 0};
	////排名
	//{
	//	CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
	//		ValuesUtil::Instance()->getString("GLD1002").c_str(),
	//		CCSizeMake(POSX(58), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
	//	pLabel->setAnchorPoint(ccp(0, 0));
	//	pLabel->setPosition(ccp(POSX(20), fTitleH));
	//	_container->addChild(pLabel);
	//	pLabel->setColor(c3);		
	//}
	//层级
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("TOWR050").c_str(),
			CCSizeMake(POSX(58), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(80-fTitleW), fTitleH));
		_container->addChild(pLabel);
		pLabel->setColor(c3);		
	}

	//玩家
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("TOWR051").c_str(),
			CCSizeMake(POSX(146), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(140-fTitleW), fTitleH));
		_container->addChild(pLabel);
		pLabel->setColor(c3);		
	}

	//公会
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("GLD1003").c_str(),
			CCSizeMake(POSX(146), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(290-fTitleW), fTitleH));
		_container->addChild(pLabel);
		pLabel->setColor(c3);		
	}

	//等级
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("GLD1005").c_str(),
			CCSizeMake(POSX(57), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(440-fTitleW), fTitleH));
		_container->addChild(pLabel);
		pLabel->setColor(c3);		
	}

	//留名时间
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("TOWR052").c_str(),
			CCSizeMake(POSX(104), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(500-fTitleW), fTitleH));
		_container->addChild(pLabel);
		pLabel->setColor(c3);		
	}

	// name btn
	CCSize csBt( POSX(121), POSX(49 ));
	{
		{
			_pStrengUpItem = CCMenuItemSprite::itemFromNormalSprite(
				CCSprite::spriteWithSpriteFrameName("button.png"),
				CCSprite::spriteWithSpriteFrameName("button1.png"),
				CCSprite::spriteWithSpriteFrameName("button2.png"),
				this,
				menu_selector(TowerRank::rankMe) );
			_pStrengUpItem->setPosition( ccp( POSX(710)+csBt.width/2, POSX(85)+csBt.height/2 ) );
			_btnStrengUp = CCMenu::menuWithItems(_pStrengUpItem, 0);
			_btnStrengUp->setTouchLayer( TLE::WindowLayer_Common_btn-1 );
			_btnStrengUp->setPosition( CCPointZero );
			_container->addChild( _btnStrengUp );
			CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
				ValuesUtil::Instance()->getString( "TOWR066" ).c_str(),
				CCSizeMake(POSX(150), POSX(49)), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
			txtLabel->setAnchorPoint(CCPointZero);
			txtLabel->setPosition( ccp( POSX(  (121-150)/2  ), 0 ) );
			_pStrengUpItem->addChild( txtLabel );
		}
		
	}

}

//闯塔留名
void TowerRank::rankMe(CCObject* obj)
{
	if (_rankVo->restCount<=0)
	{
		LangManager::msgShow("TOWR107");
		return;
	}
	//如果选中层大于玩家最佳成绩
	if ( _listContainer->selectedItem->itemVo->floor > _rankVo->maxFloor )
	{
		LangManager::msgShow("TOWR103");
		return;
	}

	string tip = "";
	TowerConfirm* pConfirm = new TowerConfirm();
	if (_rankVo->myRank!=0)
	{
		tip = LangManager::getText("TOWR102");
		pConfirm->initWithParam( tip.c_str(),
			this, menu_selector(TowerRank::rankConfirm),
			menu_selector(TowerRank::rankCancel));
	}
	else
	{
		if(_rankVo->maxFloor == 0){
			tip = LangManager::getText("TWR021");
			pConfirm->initWithString( tip );
		}else if(_rankVo->myRank == _rankVo->maxFloor){
			tip = LangManager::getText("TWR022",_rankVo->myRank);
			pConfirm->initWithString( tip );
		}else{
			tip = tip = LangManager::getText("TWR023", _listContainer->selectedItem->itemVo->floor);
			pConfirm->initWithParam( tip.c_str(),
				this, menu_selector(TowerRank::rankConfirm),
				menu_selector(TowerRank::rankCancel));
		}
	}

	LayerManager::tipsLayer->addChild(pConfirm,
		TipsLayer::TipsLayerZ_confirmFrameTower,
		TipsLayer::TipsLayerTAG_confirmFrameTower);
	pConfirm->release();
}

void TowerRank::rankConfirm(CCObject* boj)
{
	leaveNameFighting = true;
	m_bClickRank = true;

	CCMD3CD cmd;
	cmd.a_namedFloor = _listContainer->selectedItem->itemVo->floor;//_rankVo->maxFloor;
	cmd.b_isPay = 0;
	//this.dispatchEvent(new ParamEvent(TowerConfirm.RANK_ME, cmd));
	dispatchEvent(TowerRank::RANK_ME, &cmd);

	TowerConfirm* pConfirm = (TowerConfirm*)LayerManager::tipsLayer->getChildByTag(
		TipsLayer::TipsLayerTAG_confirmFrameTower);
	pConfirm->removeFromParentAndCleanup(true);
}

bool TowerRank::needFight()
{
	return m_bRnkNeedFight;
}

void TowerRank::rankCancel(CCObject* boj)
{
	TowerConfirm* pConfirm = (TowerConfirm*)LayerManager::tipsLayer->getChildByTag(
		TipsLayer::TipsLayerTAG_confirmFrameTower);
	pConfirm->removeFromParentAndCleanup(true);
}

void TowerRank::rankConfirm2( CCObject* boj )
{
	int hasGold = RoleManage::Instance()->accountInfo()->gold();
	if(hasGold < 10)
	{
		//setTip(LangManager.getText("TWR020"));
		LangManager::msgShow("TWR020");
	}
	else
	{
		CCMD3CD cmd;
		cmd.a_namedFloor = _rankVo->maxFloor;
		cmd.b_isPay = 1;
		//this.dispatchEvent(new ParamEvent(TowerConfirm.RANK_ME, cmd));
		dispatchEvent(TowerRank::RANK_ME, &cmd);
	}


	TowerConfirm* pConfirm = (TowerConfirm*)LayerManager::tipsLayer->getChildByTag(
		TipsLayer::TipsLayerTAG_confirmFrameTower);
	pConfirm->removeFromParentAndCleanup(true);
}


void TowerRank::dispear(CCObject* pSender)
{
	TowerRank* eqview = (TowerRank*)LayerManager::intervalLayer->getChildByTag(
		IntervalLayer::IntervalLayerTAG_towerRank);
	if (eqview)
	{
		eqview->removeFromParentAndCleanup(true);
	}
}

//void TowerRank::registerWithTouchDispatcher( void )
//{
//	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate( this, TLE::WindowLayer_Common_btn-1, true );
//}

void TowerRank::onEnter()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_Common_btn-1, true);
	CCLayer::onEnter();
}

void TowerRank::onExit()
{
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

void TowerRank::resetTouchDispatcher()
{
	this->setIsTouchEnabled(true);
	_btnStrengUp->setTouchLayer( TLE::WindowLayer_Common_btn-1 );
	_listContainer->setIsTouchEnabled(true);
	_listContainer->m_pri = TLE::IntervalLayer;
}

bool TowerRank::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void TowerRank::updateRanking( TowerRankListVo* vo )
{
	TowerProxy* _towerProxy = (TowerProxy*)g_pFacade->retrieveProxy( AppFacade_TOWER_PROXY_CHANGE );
	if (!_towerProxy->getpanel1Vo())
	{
		return;
	}
	int lev = _towerProxy->getpanel1Vo()->maxFloor;
	int pageLimit = 0;
	if(lev <= 40){
		pageLimit = 9;
	}else if(lev <= 60){
		pageLimit = 7;
	}else if(lev <= 80){
		pageLimit = 5;
	}else if(lev <= 100){
		pageLimit = 3;
	}else if(lev <= 120){
		pageLimit = 1;
	}
	if ( (vo->page<pageLimit) || (vo->page>(pageLimit+3)) )
	{
		_listContainer->moveToPageImmediately(pageLimit);
		CCMD3CA cmd;
		cmd.a_sit = pageLimit;
		GameServerSocket::getInstance()->sendMessage(&cmd);
		return;
	}

	_rankVo = vo;
	_preRank = vo->myRank;

	if (_txtBest)
	{
		char txt[52];
		//maxFloor = vo.maxFloor;
		sprintf(txt, "%d", vo->maxFloor);
		_txtBest->setString(txt);
		//sprintf(txt, "%d", vo->curFloor);
		//_txtLast->setString(txt);
		sprintf(txt, "%d", vo->myRank);
		_txtMyRecord->setString(txt);
		_restCountLabel->setString( LangManager::getText("TOWR065", vo->restCount).c_str() );
	}

	_pageNav->_curPage = vo->page;
	_pageNav->setPage(12,  vo->page);

	if (m_bFirstOpen) 
	{
		m_bFirstOpen = false;
		if (_listContainer)
		{
			_listContainer->currentScreen = vo->page;
		}
	}

	if(_listContainer)
		_listContainer->updateList(vo->rankList, vo->page);

}

void TowerRank::checkClickSelf( TowerRankItemVo* itemVo )
{
	if (!_pStrengUpItem)
		return;
	if (itemVo->floor==_rankVo->myRank)
	{
		_pStrengUpItem->setIsEnabled(false);
	}
	else
	{
		_pStrengUpItem->setIsEnabled(true);
	}

	m_bRnkNeedFight = (itemVo->name!="");
}