#include "HeritagePanel.h"
#include "StrengFigureCreate.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"
#include "model/player/RoleManage.h"
#include "model/streng/StrengManage.h"
#include "model/streng/vo/StrengGoodsVo.h"
#include "manager/LangManager.h"
#include "model/backpack/BagProxy.h"
#include "control/AppFacade.h"
#include "../MainStrengMediator.h"
#include "MainStrengView.h"
#include "model/com/vo/DynamicLocation.h"
#include "events/GameDispatcher.h"
#include "Confirm.h"
#include "manager/LayerManager.h"
#include "model/streng/vo/StrengVo.h"
#include "model/backpack/GoodsManager.h"

HeritagePanel::HeritagePanel()
{
	_strengCreate = 0;

	_picHtg = 0;
	_picBeHtg = 0;
	_picNew = 0;

	_materialsNum = 0;

	_tips = 0;
	_goodsInfo3 = 0;
	m_strengUplev = 0;

	_goldTxt = 0;

	m_fStep = 0.0f;
	m_bDraded = false;
	m_iClickPos = 0;
}

void HeritagePanel::initView()
{
	CCSize size = this->getContentSize();


	
	CCUIBackground* bgEquip = new CCUIBackground();
	bgEquip->initWithSpriteFrame( "popuibg/bg2.png",
		ccp(POSX(15), POSX(15)), ccp(0,0), CCSizeMake(POSX(538), POSX(428)) );
	this->addChild( bgEquip );
	bgEquip->release();

	// equipment info background
	bgEquip = new CCUIBackground();
	bgEquip->initWithSpriteFrame( "popuibg/bg2.png",
		ccp(POSX(554), POSX(15)), ccp(0,0), CCSizeMake(POSX(351), POSX(428)) );
	this->addChild( bgEquip );
	bgEquip->release();
	
	CCSize strengSize( POSX(538), POSX(428) );	// Equiment board size
	_strengCreate = HeritageCreate::HeritageCreateWithCCRect(
		CCRectMake( POSX(15), POSX(15), POSX(538), POSX(428) ) );
	this->addChild( _strengCreate );
	//_strengCreate->release(); // LH20120108

	CCSprite* pHtgL = CCSprite::spriteWithSpriteFrameName("heritage_8.png");
	this->addChild(pHtgL);
	pHtgL->setPosition(ccp(POSX(601-5),POSX(282-13)));
	pHtgL->setAnchorPoint(CCPointZero);

	CCSprite* pHtgR = CCSprite::spriteWithSpriteFrameName("heritage_8.png");
	this->addChild(pHtgR);
	pHtgR->setFlipX(true);
	pHtgR->setPosition(ccp(POSX(793-14),POSX(282-13)));
	pHtgR->setAnchorPoint(CCPointZero);

	// heritage goods back
	_unlockHtg = new SpriteNode();
	_unlockHtg->initWithSpriteFrameName("pack/unlock.png");
	this->addChild(_unlockHtg);
	_unlockHtg->setPosition(ccp(POSX(561),POSX(326-10)));
	_unlockHtg->setAnchorPoint(CCPointZero);
	_unlockHtg->release();

	_unlockBeHtg = new SpriteNode();
	_unlockBeHtg->initWithSpriteFrameName("pack/unlock.png");
	this->addChild(_unlockBeHtg);
	_unlockBeHtg->setPosition(ccp(POSX(806-5),POSX(326-10)));
	_unlockBeHtg->setAnchorPoint(CCPointZero);
	_unlockBeHtg->release();

	_unlockNew = new SpriteNode();
	_unlockNew->initWithSpriteFrameName("pack/unlock.png");
	this->addChild(_unlockNew);
	_unlockNew->setPosition(ccp(POSX(687),POSX(275)));
	_unlockNew->setAnchorPoint(CCPointZero);
	_unlockNew->release();

	CCSprite* pStrengJiantou = new CCSprite;
	pStrengJiantou->initWithSpriteFrameName("heritage_jiantou.png");
	this->addChild(pStrengJiantou);
	pStrengJiantou->setPosition(ccp(POSX(16),POSX(226)));
	pStrengJiantou->setAnchorPoint(CCPointZero);
	pStrengJiantou->release();
	pStrengJiantou = new CCSprite;
	pStrengJiantou->initWithSpriteFrameName("heritage_jiantou.png");
	this->addChild(pStrengJiantou);
	pStrengJiantou->setPosition(ccp(POSX(528-8),POSX(226)));
	pStrengJiantou->setAnchorPoint(CCPointZero);
	pStrengJiantou->release();
	pStrengJiantou->setFlipX(true);

	CCUIBackground* bgInfo = new CCUIBackground();
	bgInfo->initWithSpriteFrame( "popuibg/bg2.png",
		ccp( POSX(566), POSX(174) ), CCPointZero, CCSizeMake(POSX(338-4), POSX(98)) );
	this->addChild( bgInfo );
	bgInfo->release();

	// hetitage info
	string tmpStr = ValuesUtil::Instance()->getString("HRT06") + "\n"
		+ ValuesUtil::Instance()->getString("HRT07") + "\n"
		+ ValuesUtil::Instance()->getString("HRT08") + "\n"
		+ ValuesUtil::Instance()->getString("HRT09");
	CCLabelTTF* pTmp = CCLabelTTF::labelWithString( tmpStr.c_str(),
		CCSizeMake( POSX(300), POSX(88) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(14.5) );
	pTmp->setAnchorPoint(CCPointZero);
	pTmp->setColor(  ccWHITE  );
	pTmp->setPosition( ccp(POSX(15), POSX(0) ) );
	bgInfo->addChild( pTmp );

	// heritage saying1
	pTmp = CCLabelTTF::labelWithString( ValuesUtil::Instance()->getString("HRT10").c_str(),
		CCSizeMake( POSX(98), POSX(21) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(18) );
	pTmp->setAnchorPoint(CCPointZero);
	pTmp->setColor(  ccWHITE  );
	pTmp->setPosition( ccp(POSX(563), POSX(433-15) ) );
	this->addChild( pTmp );
	// heritage saying2
	pTmp = CCLabelTTF::labelWithString( ValuesUtil::Instance()->getString("HRT11").c_str(),
		CCSizeMake( POSX(98), POSX(21) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(18) );
	pTmp->setAnchorPoint(CCPointZero);
	pTmp->setColor(  ccWHITE  );
	pTmp->setPosition( ccp(POSX(563+240), POSX(433-15) ) );
	this->addChild( pTmp );
	// heritage saying3
	pTmp = CCLabelTTF::labelWithString( ValuesUtil::Instance()->getString("HRT12").c_str(),
		CCSizeMake( POSX(98), POSX(21) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(18) );
	pTmp->setAnchorPoint(CCPointZero);
	pTmp->setColor(  ccWHITE  );
	pTmp->setPosition( ccp(POSX(687), POSX(382) ) );
	this->addChild( pTmp );

	// grid1 image btn
	CCMenuItemSprite *pGridItem = cocos2d::CCMenuItemImage::itemFromNormalSprite(
		CCSprite::spriteWithSpriteFrameName("streng/grid.png"),
		CCSprite::spriteWithSpriteFrameName("streng/grid.png"),
		this,
		menu_selector(HeritagePanel::grid1ClickHandler) );
	pGridItem->setPosition( ccp(POSX(566+39/2), POSX(133+39/2)) );
	_menuGrid1 = CCMenu::menuWithItems(pGridItem, 0);
	_menuGrid1->setTouchLayer( TLE::WindowLayer_Common_btn );
	_menuGrid1->setPosition( CCPointZero );
	this->addChild( _menuGrid1 );
	//select
	_gridSelect1 = new CCSprite;
	if (_gridSelect1 && _gridSelect1->initWithSpriteFrameName("streng/select.png"))
	{
		_gridSelect1->setAnchorPoint(CCPointZero);
		_gridSelect1->setPosition(ccp(POSX(566), POSX(133)));
		this->addChild(_gridSelect1);
		_gridSelect1->release();
		_gridSelect1->setIsVisible(true);
	}

	_radioText1 = CCLabelTTF::labelWithString( LangManager::getText("HRT02").c_str(),
		CCSizeMake( POSX(172), POSX(21) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );
	_radioText1->setAnchorPoint(CCPointZero);
	_radioText1->setColor(  ccYELLOW  );
	_radioText1->setPosition( ccp(POSX(566+40), POSX(133) ) );
	this->addChild( _radioText1 );

	// grid2 image btn
	pGridItem = cocos2d::CCMenuItemImage::itemFromNormalSprite(
		CCSprite::spriteWithSpriteFrameName("streng/grid.png"),
		CCSprite::spriteWithSpriteFrameName("streng/grid.png"),
		this,
		menu_selector(HeritagePanel::grid2ClickHandler) );
	pGridItem->setPosition( ccp(POSX(749+39/2), POSX(133+39/2)) );
	_menuGrid2 = CCMenu::menuWithItems(pGridItem, 0);
	_menuGrid2->setTouchLayer( TLE::WindowLayer_Common_btn );
	_menuGrid2->setPosition( CCPointZero );
	this->addChild( _menuGrid2 );
	//select
	_gridSelect2 = new CCSprite;
	if (_gridSelect2 && _gridSelect2->initWithSpriteFrameName("streng/select.png"))
	{
		_gridSelect2->setAnchorPoint(CCPointZero);
		_gridSelect2->setPosition(ccp(POSX(749), POSX(133)));
		this->addChild(_gridSelect2);
		_gridSelect2->release();
		_gridSelect2->setIsVisible(false);
	}

	_radioText2 = CCLabelTTF::labelWithString(LangManager::getText("HRT03").c_str(),
		CCSizeMake( POSX(172), POSX(21) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );
	_radioText2->setAnchorPoint(CCPointZero);
	_radioText2->setColor(  ccYELLOW  );
	_radioText2->setPosition( ccp(POSX(749+40), POSX(133) ) );
	this->addChild( _radioText2 );

	//gold txt
	_goldTxt = CCLabelTTF::labelWithString( LangManager::getText("HRT05").c_str(),
		CCSizeMake( POSX(100), POSX(25) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(21) );
	_goldTxt->setAnchorPoint(CCPointZero);
	_goldTxt->setColor(  ccYELLOW  );
	_goldTxt->setPosition( ccp(POSX(594), POSX(102) ) );
	this->addChild( _goldTxt );

	_pGoldSpd = CCLabelTTF::labelWithString( "0",
		CCSizeMake( POSX(100), POSX(25) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(21) );
	_pGoldSpd->setAnchorPoint(CCPointZero);
	_pGoldSpd->setColor(  ccWHITE  );
	_pGoldSpd->setPosition( ccp(POSX(594+105), POSX(102) ) );
	this->addChild( _pGoldSpd );
}

void HeritagePanel::initButton()
{
	CCSize size = this->getContentSize();
	CCSize csBt( POSX(121), POSX(49 ));


	// bag image btn
	CCMenuItemSprite *pBagItem = cocos2d::CCMenuItemImage::itemFromNormalSprite(
		CCSprite::spriteWithSpriteFrameName("streng/bag.png"),
		CCSprite::spriteWithSpriteFrameName("streng/bag_select.png"),
		this,
		/*menu_selector(StrengPanel::bagClickHandler)*/0 );
	pBagItem->setPosition( ccp( POSX(21+95/2), POSX(439+77/2+5) ) );
	pBagItem->setIsEnabled(false);
	CCMenu* pMenuBag = CCMenu::menuWithItems(pBagItem, 0);
	pMenuBag->setTouchLayer( TLE::WindowLayer_Common_btn );
	pMenuBag->setPosition( CCPointZero );
	this->addChild( pMenuBag );

	// update btn	
	{
		_StrengUpItem = CCMenuItemSprite::itemFromNormalSprite(
			CCSprite::spriteWithSpriteFrameName("button.png"),
			CCSprite::spriteWithSpriteFrameName("button1.png"),
			CCSprite::spriteWithSpriteFrameName("button2.png"),
			this,
			menu_selector(HeritagePanel::onClickStrengUp) );
		_StrengUpItem->setPosition( ccp( POSX(599)+csBt.width/2, POSX(41)+csBt.height/2 ) );
		_btnStrengUp = CCMenu::menuWithItems(_StrengUpItem, 0);
		_btnStrengUp->setTouchLayer( TLE::WindowLayer_Common_btn );
		_btnStrengUp->setPosition( CCPointZero );
		this->addChild( _btnStrengUp );
		string txt = ValuesUtil::Instance()->getString( "HRT01" );
		CCLabelTTF* txtLabel = CCLabelTTF::labelWithString( txt.c_str(), csBt, CCTextAlignmentCenter, g_sSimHeiFont, POSX(20) );
		txtLabel->setPosition( ccp( csBt.width/2, csBt.height/2 ) );
		_StrengUpItem->addChild( txtLabel );
	}

	// cancel btn	
	{
		_StrengUpItem = CCMenuItemSprite::itemFromNormalSprite(
			CCSprite::spriteWithSpriteFrameName("button.png"),
			CCSprite::spriteWithSpriteFrameName("button1.png"),
			CCSprite::spriteWithSpriteFrameName("button2.png"),
			this,
			menu_selector(HeritagePanel::onClickCancel) );
		_StrengUpItem->setPosition( ccp( POSX(762)+csBt.width/2, POSX(41)+csBt.height/2 ) );
		_btnStrengUp = CCMenu::menuWithItems(_StrengUpItem, 0);
		_btnStrengUp->setTouchLayer( TLE::WindowLayer_Common_btn );
		_btnStrengUp->setPosition( CCPointZero );
		this->addChild( _btnStrengUp );
		string txt = ValuesUtil::Instance()->getString( "CF002" );
		CCLabelTTF* txtLabel = CCLabelTTF::labelWithString( txt.c_str(), csBt, CCTextAlignmentCenter, g_sSimHeiFont, POSX(20) );
		txtLabel->setPosition( ccp( csBt.width/2, csBt.height/2 ) );
		_StrengUpItem->addChild( txtLabel );
	}

	this->setIsTouchEnabled(true);
}

bool HeritagePanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	
	this->setPosition( ccp(POSX(17), POSX(15)) );
	this->setContentSize( CCSizeMake( POSX(923), POSX(562) ) );

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/streng/res_heritage2.plist");

	initView();
	initButton();
	return true;
}

/**
* first time open streng
* cdState = CD state   bagDic = bag data（when no equip on ）
* */
void HeritagePanel::openStreng( int cdState )
{
}

/**
* initial equip list
* @param id role ID 
* */
void HeritagePanel::creatEquipmentList( std::map<int32, GoodsInfo*>* bagDictionary )
{
	_strengCreate->removeSkinChild();

	//			
	vector<StrengGoodsVo*> infos;
	vector<StrengGoodsVo*> swordInfos;
	std::map<int32, GoodsInfo*>::iterator it;
	for ( std::map<int32, GoodsInfo*>::iterator it = bagDictionary->begin(); it != bagDictionary->end(); it++ )
	{
		GoodsInfo* pGoodsInfo = it->second;
		if ( pGoodsInfo )
		{
			if( pGoodsInfo->type != 2 )
				continue;

			if ( pGoodsInfo->strengthen == 0 )
			{
				continue;
			}			

			StrengManage* pStrengManage = StrengManage::Instance();
			RoleManage* pRoleManage = RoleManage::Instance();
			if( pGoodsInfo->equip_type == 5 )
			{
				swordInfos.push_back( pStrengManage->returnStrengGoodsVo(  pGoodsInfo,
					pGoodsInfo->sitGrid, pRoleManage->accountInfo()->roleId )  );	
			}
			else
			{
				infos.push_back(  pStrengManage->returnStrengGoodsVo( pGoodsInfo,
					pGoodsInfo->sitGrid, pRoleManage->accountInfo()->roleId )  );
			}
		}
	}

	int iSize = infos.size();
	if ( iSize != 0 )
	{
		for ( int i = 0; i < iSize-1; i++ )		//infos.sortOn(["quality"], [Array.DESCENDING]);
		{
			for ( int j = 0; j < iSize-i-1; j++ )
			{
				if ( infos[j]->quality > infos[j+1]->quality )
				{
					StrengGoodsVo* temp = infos[j];
					infos[j] = infos[j+1];
					infos[j+1] = temp;
				}

			}		
		}
	}

	iSize = swordInfos.size();
	if ( iSize != 0 )
	{
		for ( int i = 0; i < iSize-1; i++ )		//swordInfos.sortOn(["quality"], [Array.DESCENDING]);
		{
			for ( int j = 0; j < iSize-i-1; j++ )
			{
				if ( swordInfos[j]->quality > swordInfos[j+1]->quality )
				{
					StrengGoodsVo* temp = swordInfos[j];
					swordInfos[j] = swordInfos[j+1];
					swordInfos[j+1] = temp;
				}
			}		
		}
	}

	int length = swordInfos.size()+infos.size(), pagesize = 6;
	_strengCreate->pages = (length%pagesize==0) ? (length/pagesize) : (length/pagesize + 1);
	for (int i = 0; i < _strengCreate->pages; i++)
	{
		_strengCreate->addLayerByTag(i);
	}

	int sitNum(0);
	bool bHasEquip(false);
	for ( vector<StrengGoodsVo*>::iterator itGoodsVo = swordInfos.begin(); itGoodsVo != swordInfos.end(); itGoodsVo++ )
	{
		//if( sitNum <= 4 )
		{
			sitNum = _strengCreate->i%6;
			_strengCreate->createGood( *itGoodsVo, sitNum );
			//sitNum++;
			bHasEquip = true;
		}
	}
	swordInfos.clear();

	for ( vector<StrengGoodsVo*>::iterator itGoodsVo = infos.begin(); itGoodsVo != infos.end(); itGoodsVo++ )
	{
		//if( sitNum <= 4 )
		{
			sitNum = _strengCreate->i%6;
			_strengCreate->createGood( *itGoodsVo, sitNum );
			bHasEquip = true;
		}
	}
	infos.clear();
}

void HeritagePanel::onClickStrengUp(CCObject* obj)
{
	if ( !_goodsInfo1|| !_goodsInfo2)
	{
		return;
	}

	if ( (_goodsInfo2->stamina!=0) || (_goodsInfo2->wrist!=0) || (_goodsInfo2->intellect!=0) )
	{
		Confirm* pConfirm = new Confirm();
		pConfirm->initWithParam(LangManager::getText( "HRT13" ).c_str(),
			this, menu_selector(HeritagePanel::okFunction),
			menu_selector(HeritagePanel::cancelFunction));

		if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame))
		{
			LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_confirmFrame, true);
		}

		LayerManager::tipsLayer->addChild(pConfirm,
			TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);

		pConfirm->release();

		return;
	}	
	
	struct sData
	{
		int type;
		int	cost;
		int	sourcePos;
		int	sourceSit;
		int	sourceRoleId;
		int	inheritPos;
		int	inheritSit;
		int	inheritRoleId;
	} param;

	if (_gridSelect1 && _gridSelect1->getIsVisible())
	{
		param.type = 0;
	} 
	else
	{
		param.type = 1;
	}
	param.cost = _cost;
	param.sourcePos = BAG;
	param.sourceSit = _goodsInfo1->sitGrid;
	param.sourceRoleId = 0;
	param.inheritPos = BAG;
	param.inheritSit = _goodsInfo2->sitGrid;
	param.inheritRoleId = 0;

	GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::INHERIT_REQUEST, &param );
}


/* process after confirm */
void HeritagePanel::okFunction( CCObject* pObject )
{

	struct sData
	{
		int type;
		int	cost;
		int	sourcePos;
		int	sourceSit;
		int	sourceRoleId;
		int	inheritPos;
		int	inheritSit;
		int	inheritRoleId;
	} param;

	if (_gridSelect1 && _gridSelect1->getIsVisible())
	{
		param.type = 0;
	} 
	else
	{
		param.type = 1;
	}
	param.cost = _cost;
	param.sourcePos = BAG;
	param.sourceSit = _goodsInfo1->sitGrid;
	param.sourceRoleId = 0;
	param.inheritPos = BAG;
	param.inheritSit = _goodsInfo2->sitGrid;
	param.inheritRoleId = 0;

	GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::INHERIT_REQUEST, &param );
	Confirm* pConfirm = (Confirm*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pConfirm && pConfirm->getParent())
		pConfirm->getParent()->removeChild(pConfirm, true);
}

void HeritagePanel::cancelFunction( CCObject* pObject )
{
	Confirm* pConfirm = (Confirm*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pConfirm && pConfirm->getParent())
		pConfirm->getParent()->removeChild(pConfirm, true);
}


void HeritagePanel::onClickCancel(CCObject* obj)
{
	clear();
	if (_picHtg)
	{
		_picHtg->removeFromParentAndCleanup(true);
		_picHtg = 0;
	}
	if (_picBeHtg)
	{
		_picBeHtg->removeFromParentAndCleanup(true);
		_picBeHtg = 0;
	}
	if (_picNew)
	{
		_picNew->removeFromParentAndCleanup(true);
		_picNew = 0;
	}	

	BagProxy* _bagProxy = (BagProxy*)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
	std::map<int32, GoodsInfo*>* bagDictionary = &_bagProxy->_goodsList;
	creatEquipmentList(bagDictionary);
}

void HeritagePanel::dragGrid( GoodsInfo* info, int type, HeritageGoods* good )
{
	if( !info )	return;

	CCSprite* pSprite = 0;
	char tmp[128];
	sprintf( tmp, "assets/icon/goods/%d.png", info->goodId );

	switch(type)
	{
	case 0: // drag to place outside grid
		{
			if ( !_picHtg )
			{
				if (good->_equpInfo->StrengGoodsInfo->strengthen==0)
				{
					good->resetPic();
					LangManager::msgShow("HRT04");
					return;
				}
				
				_picHtg = CCSprite::spriteWithFile( tmp );
				if ( _picHtg )
				{
					_picHtg->setPosition( ccp( POSX(4), POSX(4) ) );
					_picHtg->setAnchorPoint(CCPointZero);
					_unlockHtg->addChild(_picHtg);

					_materialsNum++;
					_goodsInfo1 = info;
				}
				if (!_picNew && _goodsInfo2)
				{
					sprintf( tmp, "assets/icon/goods/%d.png", _goodsInfo2->goodId );
					_picNew = CCSprite::spriteWithFile( tmp );
					if ( _picNew )
					{
						_picNew->setPosition( ccp( POSX(4), POSX(4) ) );
						_picNew->setAnchorPoint(CCPointZero);
						_unlockNew->addChild(_picNew);
					}
				}				
				
				refreshBeHeritageGoods( info );
				caculateCost();
			}
			else if ( !_picBeHtg )
			{
				_picBeHtg = CCSprite::spriteWithFile( tmp );
				if ( _picBeHtg )
				{
					_picBeHtg->setPosition( ccp( POSX(4), POSX(4) ) );
					_picBeHtg->setAnchorPoint(CCPointZero);
					_unlockBeHtg->addChild(_picBeHtg);

					_materialsNum++;
					_goodsInfo2 = info;

					refreshWithoutOne( _goodsInfo2->goodId );
				}

				if (_picNew)
				{
					_picNew->removeFromParentAndCleanup(true);
					_picNew = 0;
				}
				_picNew = CCSprite::spriteWithFile( tmp );
				if ( _picNew )
				{
					_picNew->setPosition( ccp( POSX(4), POSX(4) ) );
					_picNew->setAnchorPoint(CCPointZero);
					_unlockNew->addChild(_picNew);
				}

				
				caculateCost();
			}

		}
	}
}

CCAction * HeritagePanel::getAction()
{
	CCFiniteTimeAction * actionFadeOut = CCFadeTo::actionWithDuration(0.5f, 1000);
	CCFiniteTimeAction * actionFadeIn = CCFadeTo::actionWithDuration(0.5f, 100);
	CCAction* pAction = CCRepeatForever::actionWithAction(
		CCSequence::actionOneTwo(actionFadeOut, actionFadeIn) );
	return pAction;
}

void HeritagePanel::fadeAct()
{
	if (!_picHtg)
	{
		_unlockHtg->runAction( getAction() );
	} 
	else
	{
		_unlockBeHtg->runAction( getAction() );
	}	
}

void HeritagePanel::StopfadeAct()
{
	if (_unlockHtg)
	{
		_unlockHtg->stopAllActions();
	} 
	if (_unlockBeHtg)
	{
		_unlockBeHtg->stopAllActions();
	}	
}

void HeritagePanel::grid1ClickHandler( CCObject* obj )
{
	if (_gridSelect1 && !_gridSelect1->getIsVisible())
	{
		_gridSelect1->setIsVisible(!_gridSelect1->getIsVisible());
	}

	if (_gridSelect2)
		_gridSelect2->setIsVisible(false);

	caculateCost();
}

void HeritagePanel::grid2ClickHandler( CCObject* obj )
{

	if (_gridSelect2 && !_gridSelect2->getIsVisible())
	{
		_gridSelect2->setIsVisible(!_gridSelect2->getIsVisible());
	}
	if (_gridSelect1)
	_gridSelect1->setIsVisible(false);

	caculateCost();
}

void HeritagePanel::clear()
{
	_materialsNum = 0;
	_goodsInfo1 = 0;
	_goodsInfo2 = 0;
	_cost = 0;

	if ( _picHtg )
	{
		_picHtg->removeFromParentAndCleanup(true);
		_picHtg = 0;
	}
	if ( _picBeHtg )
	{
		_picBeHtg->removeFromParentAndCleanup(true);
		_picBeHtg = 0;
	}
	if ( _picNew )
	{
		_picNew->removeFromParentAndCleanup(true);
		_picNew = 0;
	}
}

void HeritagePanel::refreshBeHeritageGoods( GoodsInfo* info )
{

	_strengCreate->removeSkinChild();

	//			
	BagProxy* _bagProxy = (BagProxy*)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
	std::map<int32, GoodsInfo*>* bagDictionary = &_bagProxy->_goodsList;
	vector<StrengGoodsVo*> infos;
	vector<StrengGoodsVo*> swordInfos;
	std::map<int32, GoodsInfo*>::iterator it;
	for ( std::map<int32, GoodsInfo*>::iterator it = bagDictionary->begin(); it != bagDictionary->end(); it++ )
	{
		GoodsInfo* pGoodsInfo = it->second;
		if ( pGoodsInfo )
		{
			if( pGoodsInfo->id == info->id ) //self
				continue;

			if( pGoodsInfo->type != 2 )
				continue;

			if ( pGoodsInfo->strengthen >= 40 )	// strength = 0
			{
				continue;
			}
			
			if (pGoodsInfo->equip_type != info->equip_type )	// must same pos
			{
				continue;
			}
			

			if ( pGoodsInfo->quality < info->quality )	// quality condition
				continue;

			if ( pGoodsInfo->quality > (info->quality+1) )
			{
				continue;
			}

			StrengManage* pStrengManage = StrengManage::Instance();
			RoleManage* pRoleManage = RoleManage::Instance();
			if( pGoodsInfo->equip_type == 5 )
			{
				swordInfos.push_back( pStrengManage->returnStrengGoodsVo(  pGoodsInfo,
					pGoodsInfo->sitGrid, pRoleManage->accountInfo()->roleId )  );	
			}
			else
			{
				infos.push_back(  pStrengManage->returnStrengGoodsVo( pGoodsInfo,
					pGoodsInfo->sitGrid, pRoleManage->accountInfo()->roleId )  );
			}
		}
	}

	int iSize = infos.size();
	if ( iSize != 0 )
	{
		for ( int i = 0; i < iSize-1; i++ )		//infos.sortOn(["quality"], [Array.DESCENDING]);
		{
			for ( int j = 0; j < iSize-i-1; j++ )
			{
				if ( infos[j]->quality > infos[j+1]->quality )
				{
					StrengGoodsVo* temp = infos[j];
					infos[j] = infos[j+1];
					infos[j+1] = temp;
				}

			}		
		}
	}

	iSize = swordInfos.size();
	if ( iSize != 0 )
	{
		for ( int i = 0; i < iSize-1; i++ )		//swordInfos.sortOn(["quality"], [Array.DESCENDING]);
		{
			for ( int j = 0; j < iSize-i-1; j++ )
			{
				if ( swordInfos[j]->quality > swordInfos[j+1]->quality )
				{
					StrengGoodsVo* temp = swordInfos[j];
					swordInfos[j] = swordInfos[j+1];
					swordInfos[j+1] = temp;
				}
			}		
		}
	}

	int length = swordInfos.size()+infos.size(), pagesize = 6;
	_strengCreate->pages = (length%pagesize==0) ? (length/pagesize) : (length/pagesize + 1);
	for (int i = 0; i < _strengCreate->pages; i++)
	{
		_strengCreate->addLayerByTag(i);
	}

	int sitNum(0);
	bool bHasEquip(false);
	for ( vector<StrengGoodsVo*>::iterator itGoodsVo = swordInfos.begin(); itGoodsVo != swordInfos.end(); itGoodsVo++ )
	{
		{
			sitNum = _strengCreate->i%6;
			_strengCreate->createGood( *itGoodsVo, sitNum );
			bHasEquip = true;
		}
	}
	swordInfos.clear();

	for ( vector<StrengGoodsVo*>::iterator itGoodsVo = infos.begin(); itGoodsVo != infos.end(); itGoodsVo++ )
	{
		{
			sitNum = _strengCreate->i%6;
			_strengCreate->createGood( *itGoodsVo, sitNum );
			bHasEquip = true;
		}
	}
	infos.clear();

}


void HeritagePanel::refreshHeritageGoods( GoodsInfo* info )
{
	_strengCreate->removeSkinChild();

	//			
	BagProxy* _bagProxy = (BagProxy*)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
	std::map<int32, GoodsInfo*>* bagDictionary = &_bagProxy->_goodsList;
	vector<StrengGoodsVo*> infos;
	vector<StrengGoodsVo*> swordInfos;
	std::map<int32, GoodsInfo*>::iterator it;
	for ( std::map<int32, GoodsInfo*>::iterator it = bagDictionary->begin(); it != bagDictionary->end(); it++ )
	{
		GoodsInfo* pGoodsInfo = it->second;
		if ( pGoodsInfo )
		{
			if( pGoodsInfo->id == info->id ) //self
				continue;

			if( pGoodsInfo->type != 2 )
				continue;

			if ( pGoodsInfo->strengthen == 0 )	// strength = 0
			{
				continue;
			}

			if (pGoodsInfo->equip_type != info->equip_type )	// must same pos
			{
				continue;
			}

			if ( pGoodsInfo->quality > info->quality )	// quality condition
				continue;

			if ( (pGoodsInfo->quality+1) < info->quality )
			{
				continue;
			}

			StrengManage* pStrengManage = StrengManage::Instance();
			RoleManage* pRoleManage = RoleManage::Instance();
			if( pGoodsInfo->equip_type == 5 )
			{
				swordInfos.push_back( pStrengManage->returnStrengGoodsVo(  pGoodsInfo,
					pGoodsInfo->sitGrid, pRoleManage->accountInfo()->roleId )  );	
			}
			else
			{
				infos.push_back(  pStrengManage->returnStrengGoodsVo( pGoodsInfo,
					pGoodsInfo->sitGrid, pRoleManage->accountInfo()->roleId )  );
			}
		}
	}

	int iSize = infos.size();
	if ( iSize != 0 )
	{
		for ( int i = 0; i < iSize-1; i++ )		//infos.sortOn(["quality"], [Array.DESCENDING]);
		{
			for ( int j = 0; j < iSize-i-1; j++ )
			{
				if ( infos[j]->quality > infos[j+1]->quality )
				{
					StrengGoodsVo* temp = infos[j];
					infos[j] = infos[j+1];
					infos[j+1] = temp;
				}

			}		
		}
	}

	iSize = swordInfos.size();
	if ( iSize != 0 )
	{
		for ( int i = 0; i < iSize-1; i++ )		//swordInfos.sortOn(["quality"], [Array.DESCENDING]);
		{
			for ( int j = 0; j < iSize-i-1; j++ )
			{
				if ( swordInfos[j]->quality > swordInfos[j+1]->quality )
				{
					StrengGoodsVo* temp = swordInfos[j];
					swordInfos[j] = swordInfos[j+1];
					swordInfos[j+1] = temp;
				}
			}		
		}
	}

	int length = swordInfos.size()+infos.size(), pagesize = 6;
	_strengCreate->pages = (length%pagesize==0) ? (length/pagesize) : (length/pagesize + 1);
	for (int i = 0; i < _strengCreate->pages; i++)
	{
		_strengCreate->addLayerByTag(i);
	}

	int sitNum(0);
	bool bHasEquip(false);
	for ( vector<StrengGoodsVo*>::iterator itGoodsVo = swordInfos.begin(); itGoodsVo != swordInfos.end(); itGoodsVo++ )
	{
		{
			sitNum = _strengCreate->i%6;
			_strengCreate->createGood( *itGoodsVo, sitNum );
			bHasEquip = true;
		}
	}
	swordInfos.clear();

	for ( vector<StrengGoodsVo*>::iterator itGoodsVo = infos.begin(); itGoodsVo != infos.end(); itGoodsVo++ )
	{
		{
			sitNum = _strengCreate->i%6;
			_strengCreate->createGood( *itGoodsVo, sitNum );
			bHasEquip = true;
		}
	}
	infos.clear();
}


void HeritagePanel::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_Common, true);
}

bool HeritagePanel::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	//NotifyManager::Instance()->addNotification(10);

	m_fStep = 0.0f;
	m_bDraded = false;
	m_iClickPos = 0;

	CCPoint locationInView = pTouch->locationInView( pTouch->view() );
	CCPoint currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	if ( _picHtg )
	{
		CCPoint itemPoint = getScreenPos(_picHtg);
		CCSize itemSize = _picHtg->getContentSize();
		if ( CCRect::CCRectContainsPoint(
			CCRectMake(itemPoint.x,itemPoint.y, itemSize.width,itemSize.height), currentTouchPoint) )
		{
			this->schedule(schedule_selector(HeritagePanel::update), 0);
			m_iClickPos = 1;

			//gridClick( 1 );
		}
	}
	if ( _picBeHtg )
	{
		CCPoint itemPoint = getScreenPos(_picBeHtg);
		CCSize itemSize = _picBeHtg->getContentSize();
		if ( CCRect::CCRectContainsPoint(
			CCRectMake(itemPoint.x,itemPoint.y, itemSize.width,itemSize.height), currentTouchPoint) )
		{
			this->schedule(schedule_selector(HeritagePanel::update), 0);
			m_iClickPos = 2;

			//gridClick( 2 );
		}
	}
	if ( _picNew )
	{
		CCPoint itemPoint = getScreenPos(_picNew);
		CCSize itemSize = _picNew->getContentSize();
		if ( CCRect::CCRectContainsPoint(
			CCRectMake(itemPoint.x,itemPoint.y, itemSize.width,itemSize.height), currentTouchPoint) )
		{
			gridClick( 3 );
		}

		if ( (_goodsInfo1==0) || (_goodsInfo2==0) )
		{
			_picNew->removeFromParentAndCleanup(true);
			_picNew = 0;
		}
	}

	return true;
}

void HeritagePanel::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	this->unschedule(schedule_selector(HeritagePanel::update));

	if (m_iClickPos==1)
	{
		if (m_bDraded)
		{
			gridClick( 1 );
		} 
		else
		{
			//??TIPS
			this->myInfo = _goodsInfo1;
			if (!_tips)
			{
				_tips = new TipHelps();
			}
			_tips->init(true, TipConst::STRENG);
			_tips->setToolTips(this, this);
			_tips->rollOverHander();
		}
	}
	if (m_iClickPos==2)
	{
		if (m_bDraded)
		{
			gridClick( 2 );
		} 
		else
		{
			//??TIPS
			this->myInfo = _goodsInfo2;
			if (!_tips)
			{
				_tips = new TipHelps();
			}
			_tips->init(true, TipConst::STRENG);
			_tips->setToolTips(this, this);
			_tips->rollOverHander();
		}
	}
}

void HeritagePanel::update( ccTime dt )
{
	{
		m_fStep += dt;
		if ( m_fStep > 0.1f )
		{
			this->unschedule(schedule_selector(HeritageCreate::update));
			m_fStep = 0.0f;
			m_bDraded = true;

			if (m_iClickPos==1)
			{
				if (_picHtg)
				{
					_picHtg->runAction(CCScaleTo::actionWithDuration(0.2f, 1.2f));//Increasingly large
				}				

			} 
			else
			{
				if (_picBeHtg)
				{
					_picBeHtg->runAction(CCScaleTo::actionWithDuration(0.2f, 1.2f));//Increasingly large
				}

			}
			
		}
	}
}

void HeritagePanel::gridClick( int type )
{
	switch( type )
	{
	case 1:	//"_goods1":
		if( _picHtg )
		{
			_picHtg->removeFromParentAndCleanup(true);
			_picHtg = 0;

			if (_picNew)
			{
				_picNew->removeFromParentAndCleanup(true);
				_picNew = 0;
			}			

			_strengCreate->updateGoods( _goodsInfo1, 1 );
			_goodsInfo1 = 0;
			_materialsNum --;

			if (_goodsInfo2)
			{
				refreshHeritageGoods( _goodsInfo2 );
			}
			else
			{
				BagProxy* _bagProxy = (BagProxy*)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
				std::map<int32, GoodsInfo*>* bagDictionary = &_bagProxy->_goodsList;
				creatEquipmentList(bagDictionary);
			}
		}
		break;
	case 2:	//"_goods2":
		if( _picBeHtg )
		{
			_picBeHtg->removeFromParentAndCleanup(true);
			_picBeHtg = 0;

			if (_picNew)
			{
				_picNew->removeFromParentAndCleanup(true);
				_picNew = 0;
			}

			_strengCreate->updateGoods( _goodsInfo2, 1 );
			_goodsInfo2 = 0;
			_materialsNum --;

			if (!_goodsInfo1)
			{
				BagProxy* _bagProxy = (BagProxy*)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
				std::map<int32, GoodsInfo*>* bagDictionary = &_bagProxy->_goodsList;
				creatEquipmentList(bagDictionary);
			}
			else
			{
				refreshBeHeritageGoods(_goodsInfo1);
			}
		}
		break;
	case 3:	//"_goods3":
		if( _picNew )
		{
			CC_SAFE_DELETE(_goodsInfo3);
			if (_goodsInfo1 && _goodsInfo2)
			{
				float fRate = 0.0f;
				if (_gridSelect1 && _gridSelect1->getIsVisible())
				{
					fRate = 0.75f;
				} 
				else
				{
					fRate = 1.0f;
				}
				
				_goodsInfo3 = new GoodsInfo();
				_goodsInfo3->id = _goodsInfo2->id;			//物品唯一编号					
				_goodsInfo3->goodId = _goodsInfo2->goodId;		//类型ID 物品编号
				_goodsInfo3->sitGrid = _goodsInfo2->sitGrid;		//格子坐标
				_goodsInfo3->name = _goodsInfo2->name;		//名称
				_goodsInfo3->type = _goodsInfo2->type;		//类型 	2 
				_goodsInfo3->subtype = _goodsInfo2->subtype;		//子类型
				_goodsInfo3->equip_type = _goodsInfo2->equip_type;	//(装备的位置 头.项...))
				_goodsInfo3->number = _goodsInfo2->number;		//数量
				_goodsInfo3->quality = _goodsInfo1->quality;		//品质
				_goodsInfo3->strengthen = m_strengUplev;	//强化数
				_goodsInfo3->holds = _goodsInfo1->holds;		//打洞数
				_goodsInfo3->explain = _goodsInfo2->explain;	//说明 kkk

				_goodsInfo3->explain.u_stamina = (int32)(_goodsInfo1->explain.u_stamina*fRate);
				_goodsInfo3->explain.v_wrist = (int32)(_goodsInfo1->explain.v_wrist*fRate);
				_goodsInfo3->explain.w_intellect = (int32)(_goodsInfo1->explain.w_intellect*fRate);

				_goodsInfo3->stamina = (int32)(_goodsInfo1->stamina*fRate);		//魔化体格数
				_goodsInfo3->wrist = (int32)(_goodsInfo1->wrist*fRate);			//魔化腕力数
				_goodsInfo3->intellect = (int32)(_goodsInfo1->intellect*fRate);		//魔化腕力数

				StrengVo* strengVo = new StrengVo();
				StrengManage::Instance()->getGoodsStrengInfo( _goodsInfo2->goodId, m_strengUplev, strengVo );
				GoodsBasic* goodBasic = g_pGoodsManager->getBasicGood( _goodsInfo2->goodId );
				if( strengVo->hp > 0 )
				{
					_goodsInfo3->explain.hp[0] = strengVo->hp;
					_goodsInfo3->explain.hp[1] = goodBasic->hp;
				}

				if( strengVo->att > 0 )
				{
					_goodsInfo3->explain.att[0] = strengVo->att;
					_goodsInfo3->explain.att[1] = goodBasic->att;
				}
				if( strengVo->magicAtt > 0 )
				{
					_goodsInfo3->explain.magicAtt[0] = strengVo->magicAtt;
					_goodsInfo3->explain.magicAtt[1] = goodBasic->magicAtt;
				}
				if( strengVo->def > 0 )
				{
					_goodsInfo3->explain.def[0] = strengVo->def;
					_goodsInfo3->explain.def[1] = goodBasic->def;
				}
				if(strengVo->magicDef > 0)
				{
					_goodsInfo3->explain.magicDef[0] = strengVo->magicDef;
					_goodsInfo3->explain.magicDef[1] = goodBasic->magicDef;
				}

				CC_SAFE_DELETE(strengVo);
			}

			//??TIPS
			this->myInfo = _goodsInfo3;
			if (!_tips)
			{
				_tips = new TipHelps();
			}
			_tips->init(true, TipConst::STRENG);
			_tips->setToolTips(this, this);
			_tips->rollOverHander();
		}
		break;
	}
	//if(_materialsNum < 2)
	//{
	//	_sparNumText->setString("");
	//	_rateText->setString("");
	//}
}

CCSize HeritagePanel::getSrcContentSize()
{
	//CCSize size = CCSizeMake(POSX(25*2), POSX( (640-152)*2));
	CCSize size = CCSizeMake( POSX(680+180), POSX(550) );
	return size;
}

void HeritagePanel::caculateCost()
{
	if (!_goodsInfo1)
	{
		return;
	}
	if (!_goodsInfo2)
	{
		return;
	}
	
	
	if (_gridSelect1 && _gridSelect1->getIsVisible())
	{
		_goldTxt->setString( LangManager::getText("HRT14").c_str() );

		switch (_goodsInfo2->quality)
		{
		case 4:
			_cost = 10000;
			break;
		case 5:
			_cost = 100000;
			break;
		case 6:
			_cost = 1000000;
			break;
		default:
			_cost = 1000;
			break;
		}

		int EQUIPMENT_BASIC_STRENGTHEN_FEE			= 100;  // 强化初始费用
		int STREN_LEVEL_RADIX						= 10;	// 级别
		float EQUIPMENT_STRENGTHEN_FAIL_RETURN_PERC = 0.7f;
		//原装备降级所得额
		int nGetSilver = StrengManage::Instance()->getGoodsUpStrengpriceToLv(_goodsInfo1->goodId,
			_goodsInfo1->strengthen);
		int nHaveMoney = nGetSilver;
		int nCanbeLv = 0;
		while ( nHaveMoney > 0 )
		{
			nHaveMoney -= StrengManage::Instance()->getGoodsUpStrengprice( _goodsInfo2->goodId, nCanbeLv );
			nCanbeLv++;
		}
		m_strengUplev = nCanbeLv;
	} 
	else
	{
		_goldTxt->setString( LangManager::getText("HRT05").c_str() );

		int nRiseLevel = _goodsInfo1->strengthen;
		m_strengUplev = nRiseLevel;
		int nNeedSilver = 0;
		for (int i = 0; i < nRiseLevel; i++)
		{
			nNeedSilver += StrengManage::Instance()->getGoodsUpStrengprice( _goodsInfo2->goodId, i );
		}
		//原装备降级所得额
		int nGetSilver = StrengManage::Instance()->getGoodsUpStrengpriceToLv(_goodsInfo1->goodId, nRiseLevel);
		int goldRate = 10000;
		_cost = (nNeedSilver - int(nGetSilver*1.1f))/goldRate;
		int mod = (nNeedSilver - int(nGetSilver*1.1f))%goldRate;
		if (mod>0)
		{
			_cost++;
		}
		if (_cost<10)
		{
			_cost = 10;
		}
		
	}

	if (_pGoldSpd)
	{
		char txt[128]={0};
		sprintf( txt, "%d", _cost );
		_pGoldSpd->setString(txt);
	}
}

HeritagePanel::~HeritagePanel()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/streng/res_heritage2.plist");

	//CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/streng/res_heritage2.pvr.ccz");

	CC_SAFE_DELETE(_goodsInfo3);
}

void HeritagePanel::updateTip( uint32 id )
{
	_strengCreate->updateTip( id );
}

void HeritagePanel::refreshWithoutOne( int32 goodId )
{
	if (!_goodsInfo1)
	{
		return;
	}
	
	_strengCreate->removeSkinChild();

	//			
	BagProxy* _bagProxy = (BagProxy*)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
	std::map<int32, GoodsInfo*>* bagDictionary = &_bagProxy->_goodsList;
	vector<StrengGoodsVo*> infos;
	vector<StrengGoodsVo*> swordInfos;
	std::map<int32, GoodsInfo*>::iterator it;
	for ( std::map<int32, GoodsInfo*>::iterator it = bagDictionary->begin(); it != bagDictionary->end(); it++ )
	{
		GoodsInfo* pGoodsInfo = it->second;
		if ( pGoodsInfo )
		{
			if( pGoodsInfo->id == _goodsInfo2->id ) //self
				continue;

			if( pGoodsInfo->type != 2 )
				continue;

			if ( pGoodsInfo->strengthen >= 40 )	// strength = 0
			{
				continue;
			}

			if (pGoodsInfo->equip_type != _goodsInfo1->equip_type )	// must same pos
			{
				continue;
			}


			if ( pGoodsInfo->quality < _goodsInfo1->quality )	// quality condition
				continue;

			if ( pGoodsInfo->quality > (_goodsInfo1->quality+1) )
			{
				continue;
			}

			StrengManage* pStrengManage = StrengManage::Instance();
			RoleManage* pRoleManage = RoleManage::Instance();
			if( pGoodsInfo->equip_type == 5 )
			{
				swordInfos.push_back( pStrengManage->returnStrengGoodsVo(  pGoodsInfo,
					pGoodsInfo->sitGrid, pRoleManage->accountInfo()->roleId )  );	
			}
			else
			{
				infos.push_back(  pStrengManage->returnStrengGoodsVo( pGoodsInfo,
					pGoodsInfo->sitGrid, pRoleManage->accountInfo()->roleId )  );
			}
		}
	}

	int iSize = infos.size();
	if ( iSize != 0 )
	{
		for ( int i = 0; i < iSize-1; i++ )		//infos.sortOn(["quality"], [Array.DESCENDING]);
		{
			for ( int j = 0; j < iSize-i-1; j++ )
			{
				if ( infos[j]->quality > infos[j+1]->quality )
				{
					StrengGoodsVo* temp = infos[j];
					infos[j] = infos[j+1];
					infos[j+1] = temp;
				}

			}		
		}
	}

	iSize = swordInfos.size();
	if ( iSize != 0 )
	{
		for ( int i = 0; i < iSize-1; i++ )		//swordInfos.sortOn(["quality"], [Array.DESCENDING]);
		{
			for ( int j = 0; j < iSize-i-1; j++ )
			{
				if ( swordInfos[j]->quality > swordInfos[j+1]->quality )
				{
					StrengGoodsVo* temp = swordInfos[j];
					swordInfos[j] = swordInfos[j+1];
					swordInfos[j+1] = temp;
				}
			}		
		}
	}

	int length = swordInfos.size()+infos.size(), pagesize = 6;
	_strengCreate->pages = (length%pagesize==0) ? (length/pagesize) : (length/pagesize + 1);
	for (int i = 0; i < _strengCreate->pages; i++)
	{
		_strengCreate->addLayerByTag(i);
	}

	int sitNum(0);
	bool bHasEquip(false);
	for ( vector<StrengGoodsVo*>::iterator itGoodsVo = swordInfos.begin(); itGoodsVo != swordInfos.end(); itGoodsVo++ )
	{
		{
			sitNum = _strengCreate->i%6;
			_strengCreate->createGood( *itGoodsVo, sitNum );
			bHasEquip = true;
		}
	}
	swordInfos.clear();

	for ( vector<StrengGoodsVo*>::iterator itGoodsVo = infos.begin(); itGoodsVo != infos.end(); itGoodsVo++ )
	{
		{
			sitNum = _strengCreate->i%6;
			_strengCreate->createGood( *itGoodsVo, sitNum );
			bHasEquip = true;
		}
	}
	infos.clear();
}
