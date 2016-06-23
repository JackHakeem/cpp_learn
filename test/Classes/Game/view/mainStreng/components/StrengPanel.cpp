#include "StrengPanel.h"
#include "StrengFigureCreate.h"
#include "../MainStrengMediator.h"
#include "model/figure/vo/EquipmentVo.h"
#include "model/figure/EquipmentManager.h"
#include "model/streng/StrengManage.h"
#include "model/player/RoleManage.h"
#include "model/figure/vo/EquipmentVo.h"
#include "model/backpack/GoodsManager.h"
#include "StrengGoods.h"
#include "model/streng/vo/StrengGoodsVo.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "FigureItem.h"
#include "utils/ColorUtil.h"
#include "model/com/GoodsDynamicManager.h"
#include "model/com/vo/GoodsDynamic.h"
#include "model/streng/vo/StrengVo.h"
#include "events/GameDispatcher.h"
#include "MainStrengView.h"
#include "Message.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "PopUIBg.h"
#include "manager/LangManager.h"
#include "CCUIBackground.h"
#include "CustomCD.h"
#include "manager/CDManage.h"
#include "utils/loader/KKAnimationFactory.h"
#include "model/newhand/NewhandManager.h"

#define GOOD_PIC_X POSX(560)
#define GOOD_PIC_Y POSX(332)

static const int BTN_IMAGE_TAG = 1 ;
static const int BTN_UP_TAG = 1001 ;
static const int CD_TAG = 1002 ;
static const int StrengEff_TAG = 1003 ;
static const int StrengCriEff_TAG = 1004 ;
   
StrengPanel::StrengPanel()
{
	_figureCreate = 0;
	_strengCreate = 0;
	_curStrengGoods = 0;
	
	_CDState = 0;
	_item = 0;

	_pic = 0;
	_sItemsName= 0;
	_txtLevel = 0;
	_sItemsAttribute = 0;

	_txtTime = 0;
	_txtTrend = 0;
	_mcVIP = 0;

	_txtRate = 0;
	//_buyRate = 0;

	_CD = 0;

	_btnStrengUp = 0;
	_btnStrengDown = 0;

	_sBtInfo = 0;

	_curStrengProb = 100;
	_curStrengLev = 0;

	_rateBar = 0;
	_comCheckBox = 0;
	m_bShowBag  = false;

	_strengCreateBag = 0;
	m_selectedSpriteImage = 0;

	m_vipLv = 0;
	m_MenuCombox = 0;
}

void StrengPanel::initView()
{
	CCSize size = this->getContentSize();

	CCSize strengSize( STRENG_CREATE_W, STRENG_CREATE_H );	// Equiment board size
	_strengCreate = StrengCreate::node();
	_strengCreate->setPosition( ccp( POSX(11), POSX(15) ) );
	_strengCreate->setContentSize( strengSize );
	this->addChild( _strengCreate );
	//_strengCreate->release(); //LH20120108
	//CCLayerColor* pLayerColor1 = CCLayerColor::layerWithColorWidthHeight( ccc4( 0, 255, 0, 100 ), strengSize.width, strengSize.height );
	//_strengCreate->addChild( pLayerColor1 );

	_strengCreateBag = StrengCreateBagListView::strengCreateBagListViewWithCCRect(
		CCRectMake( POSX(11), POSX(11), STRENG_CREATE_W, STRENG_CREATE_H ) );
	this->addChild( _strengCreateBag );
	_strengCreateBag->release(); //LH20120108

	_figureCreate = StrengFigureCreate::figureCreatScrollViewWithCCRect( CCRectMake( POSX(265), POSX(439), POSX(395), POSX(83) ) );
	this->addChild( _figureCreate );
	_figureCreate->release(); //LH20120108

	// equipment info background
	CCUIBackground* bgEquip = new CCUIBackground();
	bgEquip->initWithSpriteFrame( "popuibg/bg2.png",
		ccp(POSX(554), POSX(15)), ccp(0,0), CCSizeMake(POSX(351), POSX(428)) );
	this->addChild( bgEquip );
	//Doyang 20120712
	bgEquip->release();

	CCUIBackground* bgGood = new CCUIBackground();
	bgGood->initWithSpriteFrame( "popuibg/bg2.png",
		ccp( GOOD_PIC_X, GOOD_PIC_Y ), ccp(0,0), CCSizeMake(POSX(100), POSX(100)) );
	this->addChild( bgGood );
	//Doyang 20120712
	bgGood->release();

	// name
	_sItemsName = CCLabelTTF::labelWithString( "", CCSizeMake( POSX(200), POSX(24) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(24));
	_sItemsName->setPosition( ccp( POSX(660), POSX(390+15) ) );
	_sItemsName->setAnchorPoint( CCPointZero );
	addChild( _sItemsName );

	// level
	_txtLevel = CCLabelTTF::labelWithString( "", CCSizeMake( POSX(196), POSX(18) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );
	_txtLevel->setPosition( ccp( POSX(660), POSX(356+15) ) );
	_txtLevel->setAnchorPoint( CCPointZero );
	addChild( _txtLevel );

	// attr
	_sItemsAttribute = CCLabelTTF::labelWithString( "",
		CCSizeMake( POSX(234), POSX(75) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );
	_sItemsAttribute->setPosition( ccp( POSX(660), POSX(298+10+10)) );
	_sItemsAttribute->setAnchorPoint( CCPointZero );
	ccColor3B colorgreen = { 0, 254, 36 };
	_sItemsAttribute->setColor( colorgreen );
	addChild( _sItemsAttribute );
// 	CCLayerColor* pLayerColor = CCLayerColor::layerWithColorWidthHeight( ccc4( 0, 0, 255, 50 ), POSX(234), POSX(57) );
// 	_sItemsAttribute->addChild( pLayerColor );

	// change per time
	_txtTime = CCLabelTTF::labelWithString( ValuesUtil::Instance()->getString("STG050").c_str(),
		CCSizeMake( POSX(160), POSX(30) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );
	_txtTime->setPosition( ccp( POSX(565), POSX(261) ) );
	_txtTime->setAnchorPoint( CCPointZero );
	addChild( _txtTime );

	// trend
	_txtTrend = CCLabelTTF::labelWithString( "", CCSizeMake(POSX(106), POSX(30 )), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );
	_txtTrend->setPosition( ccp( POSX(723), POSX(261)) );
	_txtTrend->setAnchorPoint( CCPointZero );
	_txtTrend->setColor( colorgreen );
	addChild( _txtTrend );

	// VIP
	_mcVIP = CCLabelTTF::labelWithString( "", CCSizeMake( POSX(80), POSX(30) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );
	_mcVIP->setPosition( ccp( POSX(800.0f), POSX(275.0f) ) );
	_mcVIP->setAnchorPoint( CCPointZero );
	addChild( _mcVIP );

	//// buy rate to success
	//_buyRate = CCLabelTTF::labelWithString( "", CCSizeMake( 185, 30 ), CCTextAlignmentLeft, g_sSimHeiFont, 18 );
	//_buyRate->setPosition( ccp( 590.0f+185.0f/2, 240.0f ) );
	//addChild( _buyRate );

	// success rate bar
	CCSprite* spBgProgress = CCSprite::spriteWithSpriteFrameName("streng/expBg.png");
	spBgProgress->setPosition( ccp( POSX(564), POSX(237) ) );
	spBgProgress->setAnchorPoint( CCPointZero );
	this->addChild( spBgProgress );
	_rateBar = CCSprite::spriteWithSpriteFrameName( "streng/up.png" );
	_rateBar->setPosition( ccp( POSX(2), POSX(9) ) );
	_rateBar->setAnchorPoint( CCPointZero );
	spBgProgress->addChild( _rateBar );
	_rateBar->setScaleX( 100 * 0.01f );

	// success rate
	_txtRate = CCLabelTTF::labelWithString( "", CCSizeMake( POSX(313), POSX(19) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );
	_txtRate->setColor( ccWHITE );
	_txtRate->setAnchorPoint( CCPointZero );
	_txtRate->setPosition( ccp( POSX(570), POSX(244) ) );
	addChild( _txtRate );

	// spend gold to lock success
	_comCheckBox = CCLabelTTF::labelWithString( "", CCSizeMake( POSX(375), POSX(25) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );//257
	_comCheckBox->setPosition( ccp( POSX(565), POSX(202) ) );
	_comCheckBox->setAnchorPoint( CCPointZero );
	ccColor3B color = { 255, 180, 0 };
	_comCheckBox->setColor( color );
	addChild( _comCheckBox );
	// check image combox
	CCSprite* pNormal = CCSprite::spriteWithSpriteFrameName("train/radio.png");
	CCSprite* pPress = CCSprite::spriteWithSpriteFrameName("train/radio.png");
	CCMenuItemSprite *pComItem = cocos2d::CCMenuItemImage::itemFromNormalSprite(
		pNormal,
		pPress,
		this,
		menu_selector(StrengPanel::clickCombox) );
	pComItem->setPosition( ccp( POSX(600), POSX(202) ) );
	pComItem->setAnchorPoint( CCPointZero );
	m_MenuCombox = CCMenu::menuWithItems(pComItem, 0);
	m_MenuCombox->setTouchLayer( TLE::WindowLayer_Common_btn );
	m_MenuCombox->setPosition( CCPointZero );
	this->addChild( m_MenuCombox );
	m_spCombox = CCSprite::spriteWithSpriteFrameName("train/radioSelected.png");
	m_spCombox->setAnchorPoint( CCPointZero );
	m_spCombox->setPosition( ccp(POSX(1), POSX(3)) );
	pComItem->addChild( m_spCombox );
	m_spCombox->setIsVisible(false);

	AccountInfoVo* accountInfo = RoleManage::Instance()->accountInfo();
	if ( accountInfo )
	{
		m_vipLv = accountInfo->vipLev();
		if( m_vipLv != 0 )//|| accountInfo->trialVip()
		{
			_comCheckBox->setIsVisible( false );
			m_MenuCombox->setIsVisible( false );
		}
		else
		{
			_comCheckBox->setIsVisible( true );
			m_MenuCombox->setIsVisible( false );
		}
	}

	
	// update info
	_sBtInfo = CCLabelTTF::labelWithString( "", CCSizeMake( POSX(341), POSX(102) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );
	_sBtInfo->setPosition( ccp( POSX(565), POSX(21 )) );
	_sBtInfo->setAnchorPoint( CCPointZero );
	_sBtInfo->setColor( color );
	addChild( _sBtInfo );

	m_selectedSpriteImage = new CCUIBackground();
	m_selectedSpriteImage->initWithSpriteFrame( "train/gold_back.png",
		ccp(0, POSX(2)), CCPointZero, CCSizeMake( POSX(245), POSX(120) ) );
	this->addChild( m_selectedSpriteImage );
	m_selectedSpriteImage->release();
}

void StrengPanel::setAttriVisible( bool bVar )
{
	_rateBar->getParent()->setIsVisible(bVar);
	_btnStrengUp->setIsVisible(bVar);
	//_btnStrengDown->setIsVisible(bVar);

	_txtTrend->setIsVisible(bVar);
	_txtRate->setIsVisible(bVar);
	_txtTime->setIsVisible(bVar);
}

void StrengPanel::initButton()
{
	CCSize size = this->getContentSize();
	CCSize csBt( POSX(121), POSX(49 ));
	// update btn
	
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			_StrengUpItem = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this,
				menu_selector(StrengPanel::onClickStrengUp) );
			_StrengUpItem->setPosition( ccp( POSX(591+(756-591)/2)+csBt.width/2, POSX(118)+csBt.height/2 ) );
			_StrengUpItem->setTag( BTN_IMAGE_TAG );
			_btnStrengUp = CCMenu::menuWithItems(_StrengUpItem, 0);
			_btnStrengUp->setTouchLayer( TLE::WindowLayer_Common_btn );
			_btnStrengUp->setTag(BTN_UP_TAG);
			_btnStrengUp->setPosition( CCPointZero );
			this->addChild( _btnStrengUp );
			string txt = ValuesUtil::Instance()->getString( "StUp" );
			CCLabelTTF* txtLabel = CCLabelTTF::labelWithString( txt.c_str(), csBt, CCTextAlignmentCenter, g_sSimHeiFont, POSX(20) );
			txtLabel->setPosition( ccp( csBt.width/2, csBt.height/2 ) );
			_StrengUpItem->addChild( txtLabel );
		}
	}

	//// degrete btn
	//{
	//	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
	//	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
	//	CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
	//	if(pNormalSprite && pPressedSprite && pSelectdSprite)
	//	{
	//		_StrengDownItem = CCMenuItemSprite::itemFromNormalSprite(
	//			pNormalSprite,
	//			pPressedSprite,
	//			pSelectdSprite,
	//			this,
	//			menu_selector(StrengPanel::onClickStrengDown) );
	//		_StrengDownItem->setTag( BTN_IMAGE_TAG );
	//		_StrengDownItem->setPosition( ccp( POSX(756)+csBt.width/2, POSX(118)+csBt.height/2 ) );
	//		_btnStrengDown = CCMenu::menuWithItems(_StrengDownItem, 0);
	//		_btnStrengDown->setTouchLayer( TLE::WindowLayer_Common_btn );
	//		_btnStrengDown->setPosition( CCPointZero );
	//		this->addChild( _btnStrengDown );
	//		string txt = ValuesUtil::Instance()->getString( "StDe" );
	//		CCLabelTTF* txtLabel = CCLabelTTF::labelWithString( txt.c_str(), csBt, CCTextAlignmentCenter, g_sSimHeiFont, POSX(20) );
	//		txtLabel->setPosition( ccp( csBt.width/2, csBt.height/2 ) );
	//		_StrengDownItem->addChild( txtLabel );
	//	}
	//}
	//

	// bag image btn
	CCSprite* pNormal = CCSprite::spriteWithSpriteFrameName("streng/bag.png");
	CCSprite* pPress = CCSprite::spriteWithSpriteFrameName("streng/bag_select.png");
	CCMenuItemSprite *pBagItem = cocos2d::CCMenuItemImage::itemFromNormalSprite(
		pNormal,
		pPress,
		this,
		menu_selector(StrengPanel::bagClickHandler) );
	pBagItem->setPosition( ccp( POSX(21+95/2), POSX(439+77/2) ) );
	CCMenu* pMenuBag = CCMenu::menuWithItems(pBagItem, 0);
	pMenuBag->setTouchLayer( TLE::WindowLayer_Common_btn );
	pMenuBag->setPosition( CCPointZero );
	this->addChild( pMenuBag );

	//Custom CD
	CustomCD* _cd = new CustomCD( CDManage::STRENGTHEN );
	_cd->setPosition( ccp(POSX(550), POSX(175)) );
	_cd->setTag(CD_TAG);
	this->addChild( _cd );
	_cd->release(); //LH20120116 memory

	// left direct image btn
	CCSize csImageSize( 63, 82 );
	pNormal = CCSprite::spriteWithSpriteFrameName("streng/direct.png");
	pPress = CCSprite::spriteWithSpriteFrameName("streng/direct_pressed.png");
	CCMenuItemSprite* pDirectItem = cocos2d::CCMenuItemImage::itemFromNormalSprite(
		pNormal,
		pPress,
		this,
		menu_selector(StrengPanel::directClickHandler) );
	pDirectItem->setPosition( ccp(POSX(149+csImageSize.width/2), POSX(439-5+csImageSize.height/2)) );
	CCMenu* pMenuDirect = CCMenu::menuWithItems(pDirectItem, 0);
	pMenuDirect->setTouchLayer( TLE::WindowLayer_Common_btn );
	pMenuDirect->setPosition( CCPointZero );
	this->addChild( pMenuDirect );

	// right direct image btn
	pNormal = CCSprite::spriteWithSpriteFrameName("streng/direct.png");
	pPress = CCSprite::spriteWithSpriteFrameName("streng/direct_pressed.png");
	pDirectItem = cocos2d::CCMenuItemImage::itemFromNormalSprite(
		pNormal,
		pPress,
		this,
		menu_selector(StrengPanel::directRightClickHandler) );
	CCSprite* pS = (CCSprite*)pDirectItem->getNormalImage();
	pS->setFlipX( true );
	pS = (CCSprite*)pDirectItem->getSelectedImage();
	pS->setFlipX( true );
	pDirectItem->setPosition( ccp(POSX(770+csImageSize.width/2), POSX(439-5+csImageSize.height/2)) );
	pMenuDirect = CCMenu::menuWithItems(pDirectItem, 0);
	pMenuDirect->setTouchLayer( TLE::WindowLayer_Common_btn );
	pMenuDirect->setPosition( CCPointZero );
	this->addChild( pMenuDirect );
}

bool StrengPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	CCSize panelSize( w_bg2, h_bg2 );
	this->setPosition( ccp(POSX(23), POSX(31)) );
	this->setContentSize( CCSizeMake( w_bg2, h_bg2 ) );

	
	initView();
	initButton();
	return true;
}

void StrengPanel::directClickHandler( CCObject* pObj )
{
	if (_figureCreate)
	{
		_figureCreate->moveToPreviousPageClick();
	}
	
}

void StrengPanel::directRightClickHandler( CCObject* pObj )
{
	if (_figureCreate)
	{
		_figureCreate->moveToNextPageClick();

		// LH20121108
		if (_figureCreate->currentScreen == 3)
		{
			NewhandManager::Instance()->touchNextEvent(119);
		}
	}
}

void StrengPanel::figureSelectHandler( FigureItem* item )
{
	//if ( item == _item )
	//{
	//	return;
	//}

	clear();
	_item = item;
	_strengCreate->setDefaultGoodIndex(0);

	if(_item)
	{
		//this.dispatchEvent(new ParamEvent(TYPE_TAB_CLICK, _item.id ));
		g_pMainStrengMediator->onTabClick( _item->id() );
	}

}

 void StrengPanel::bagClickHandler( CCObject* pObject ) 
 {
	clear();
	if( _item )
	{
		_item = 0;
	}
	
	g_pMainStrengMediator->onTabClick( 0 );
}

/**
* first time open streng
* cdState = CD state   bagDic = bag data（when no equip on ）
* */
void StrengPanel::openStreng( int cdState )
{
	clear();
	_CDState = cdState;
	//_strengCreate->setIsTouchEnabled(true);

	CustomCD* _cd = (CustomCD*)this->getChildByTag(CD_TAG);
	if ( _cd )
	{
		_cd->reinit();
	}

	if ( _figureCreate )
		_figureCreate->buildList();  // creat figure

	AccountInfoVo* accountInfo = RoleManage::Instance()->accountInfo();
	if ( accountInfo )
	{
		if ( m_vipLv != accountInfo->vipLev() )
		{
			m_vipLv = accountInfo->vipLev();

			if (_comCheckBox && m_vipLv != 0)
			{
				_comCheckBox->setIsVisible( false );
			}		
			if (m_MenuCombox)
			{
				m_MenuCombox->setIsVisible(false);		
			}				
		}
	}
	
}

/**
* initial equip list
* @param id role ID 
* */
bool StrengPanel::creatRoleEquipmentList( int id )
{
	m_bShowBag = false;
	_strengCreate->removeSkinChild();
	_strengCreateBag->setIsTouchEnabled(false);
	_strengCreateBag->removeSkinChild();

	bool ishasEquipment = false;
	EquipmentVo* roleEquipment = EquipmentManager::Instance()->getEquipment(id);
	int sitNum = 0;

	vector<GoodsInfo*> arr = sortedArr( roleEquipment );

	for ( vector<GoodsInfo*>::iterator it = arr.begin(); it != arr.end(); it++ )
	{
		GoodsInfo* info = *it;
		if ( info )
		{
			_strengCreate->createGood(
				StrengManage::Instance()->returnStrengGoodsVo( info, info->sitGrid, id, 3 ), sitNum  );
			sitNum++;
			ishasEquipment = true;
		}
	}
	if(ishasEquipment)
	{
		RoleManage::Instance()->currentId( id );
	}
	m_selectedSpriteImage->setIsVisible(ishasEquipment);
			
	return ishasEquipment;
}

/**
* sort by need，wepon first，then quality 
*/	
vector<GoodsInfo*> StrengPanel::sortedArr( EquipmentVo* roleEquipment)
{
	std::map<int, GoodsInfo>* arr = roleEquipment->getAll();
	vector<GoodsInfo*> equipArr;
	vector<GoodsInfo*> equipArrResult;
	if ( !arr )
	{
		return equipArr;
	}

	if ( roleEquipment )
	{
		std::map<int, GoodsInfo>::iterator it = arr->begin();
		int iVecSize(0);
		for ( ;it != arr->end(); it++ )
		{
			GoodsInfo* goodsInfo = &it->second;
			if ( goodsInfo->id == 0 )
			{
				continue;
			}
			equipArr.push_back( goodsInfo );
			++iVecSize;
			if ( iVecSize > 5 )
			{
				break;
			}			
		}
	}

	int iSize = equipArr.size();
	for ( int i = 0; i < iSize-1; i++ )		//	equipArr.sortOn(["quality"], [Array.DESCENDING]);
	{
		for ( int j = 0; j < iSize-i-1; j++ )
		{
			if ( equipArr[j]->quality > equipArr[j+1]->quality )
			{
				GoodsInfo* temp = equipArr[j];
				equipArr[j] = equipArr[j+1];
				equipArr[j+1] = temp;
			}

		}		
	}

	for ( int i = 0; i < iSize; i++ )
	{
		GoodsInfo* temp = equipArr[i];
		if ( temp->sitGrid == 5 )	//weapon
		{
			equipArrResult.push_back( temp );;
		}
	}	
	
	for ( int i = 0; i < iSize; i++ )
	{
		GoodsInfo* temp = equipArr[i];
		if ( temp->sitGrid == 3 )	//xiongjia
		{
			equipArrResult.push_back( temp );;
		}
	}

	for ( int i = 0; i < iSize; i++ )
	{
		GoodsInfo* temp = equipArr[i];
		if ( temp->sitGrid == 1 )	//toukui
		{
			equipArrResult.push_back( temp );;
		}
	}

	for ( int i = 0; i < iSize; i++ )
	{
		GoodsInfo* temp = equipArr[i];
		if ( temp->sitGrid == 6 )	//jiezhi
		{
			equipArrResult.push_back( temp );;
		}
	}

	for ( int i = 0; i < iSize; i++ )
	{
		GoodsInfo* temp = equipArr[i];
		if ( temp->sitGrid == 4 )	//pifeng
		{
			equipArrResult.push_back( temp );;
		}
	}

	for ( int i = 0; i < iSize; i++ )
	{
		GoodsInfo* temp = equipArr[i];
		if ( temp->sitGrid == 2 )	//xianglian
		{
			equipArrResult.push_back( temp );;
		}
	}
	
	return equipArrResult;
}
		
/**
* initial bag equip list
* */
void StrengPanel::creatBagEquipmentList( std::map<int32, GoodsInfo*>* bagDictionary )
{
	m_bShowBag = true;

	_strengCreate->removeSkinChild();
	_strengCreateBag->setIsTouchEnabled(true);
	_strengCreateBag->removeSkinChild();
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

			StrengManage* pStrengManage = StrengManage::Instance();
			RoleManage* pRoleManage = RoleManage::Instance();
			if( pGoodsInfo->equip_type == 5 )
			{
				swordInfos.push_back( pStrengManage->returnStrengGoodsVo(  pGoodsInfo, pGoodsInfo->sitGrid, pRoleManage->accountInfo()->roleId )  );	
			}
			else
			{
				infos.push_back(  pStrengManage->returnStrengGoodsVo( pGoodsInfo, pGoodsInfo->sitGrid, pRoleManage->accountInfo()->roleId )  );
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
	_strengCreateBag->pages = (length%pagesize==0) ? (length/pagesize) : (length/pagesize + 1);
	for (int i = 0; i < _strengCreateBag->pages; i++)
	{
		_strengCreateBag->addLayerByTag(i);
	}

	int sitNum(0);
	bool bHasEquip(false);
	for ( vector<StrengGoodsVo*>::iterator itGoodsVo = swordInfos.begin(); itGoodsVo != swordInfos.end(); itGoodsVo++ )
	{
		//if( sitNum <= 4 )
		{
			sitNum = _strengCreateBag->i%6;
			_strengCreateBag->createGood( *itGoodsVo, sitNum );
			//sitNum++;
			bHasEquip = true;
		}
		//else
		//{
		//	StrengGoodsVo* ptrengGoodsVo = *itGoodsVo;
		//	CC_SAFE_DELETE( ptrengGoodsVo );
		//}
	}
	swordInfos.clear();

	for ( vector<StrengGoodsVo*>::iterator itGoodsVo = infos.begin(); itGoodsVo != infos.end(); itGoodsVo++ )
	{
		//if( sitNum <= 4 )
		{
			sitNum = _strengCreateBag->i%6;
			_strengCreateBag->createGood( *itGoodsVo, sitNum );
			//sitNum++;
			bHasEquip = true;
		}
		//else
		//{
		//	StrengGoodsVo* ptrengGoodsVo = *itGoodsVo;
		//	CC_SAFE_DELETE( ptrengGoodsVo );
		//}
	}
	infos.clear();

	setAttriVisible(bHasEquip);

	m_selectedSpriteImage->setIsVisible(bHasEquip);
}
		
//private function pageLayout():void{
//_txtNum.text = _curPage + "/" + _totalPage;
//}

/**
* check equip info
* */
void StrengPanel::viewEquipmentInfo( int id, int goodID )
{	
	GoodsBasic* goodsBasic = g_pGoodsManager->getBasicGood( goodID );
	if(!goodsBasic)return;

	_curStrengGoods = _strengCreate->getStrengGoods(id);
	if (!_curStrengGoods)
	{
		_curStrengGoods = _strengCreateBag->getStrengGoods(id);
	}
	
	if( _curStrengGoods )
	{
		StrengGoodsVo* equpInfo = _curStrengGoods->_equpInfo;
		if ( equpInfo )
		{
			GoodsInfo* pGoodsInfo = equpInfo->StrengGoodsInfo;
			if ( pGoodsInfo->id == id )
			{
				if ( _sItemsName )
				{
					ccColor3B textColor = ColorUtil::getGoodColor( goodsBasic->quality );
					_sItemsName->setString( goodsBasic->goodName.c_str() );
					_sItemsName->setColor( textColor );
				}
				if( _pic )
				{
					//CCTexture2D *texture = _curStrengGoods->_pic->getTexture();
					//_pic->setTexture( texture );
					_pic->removeFromParentAndCleanup(true);
				}

				// icon
				char strFormat[54];
				sprintf( strFormat, "assets/icon/goods/%d.png", goodsBasic->goodId );

				//CCTexture2D *texture = _curStrengGoods->_pic->getTexture();
				_pic = CCSprite::spriteWithFile( strFormat );
				_pic->setPosition( ccp(GOOD_PIC_X+POSX(4), GOOD_PIC_Y+POSX(4)) );
				_pic->setAnchorPoint( CCPointZero );
				this->addChild( _pic );

				viewEquipmentDynamicInfo( id, goodID );

				btnHasVisble();
			}
		}
	}
}
		
/**
* view equiment dynamic info
* */
void StrengPanel::viewEquipmentDynamicInfo( int id, int goodID )
{
	GoodsDynamic* goodsDynamic = g_pGoodsDynamicManager->getGoodsDynamic( id );

	GoodsBasic* goodBasic = g_pGoodsManager->getBasicGood( goodID ); 
	string strAttribute= "";
	string strAttributeNext ="";
	if( goodsDynamic )
	{
		_curStrengLev = goodsDynamic->e_strengthen;

		ValuesUtil* pValuesUtil = ValuesUtil::Instance();
		char suffix[128];
		if ( goodsDynamic->j_att > 0 )
		{
			int add = goodsDynamic->j_att - goodBasic->att;
			if ( add > 0 )
			{
				sprintf( suffix, " +%d(+%d)", goodBasic->att, add );
			} 
			else
			{
				sprintf( suffix, " +%d", goodBasic->att );
			}
			strAttribute.append( "\n" + LangManager::getText("STG035") + suffix );
		}
		if ( goodsDynamic->l_magicAtt > 0 )
		{ 
			int add = goodsDynamic->l_magicAtt - goodBasic->magicAtt;
			if ( add > 0 )
			{
				sprintf( suffix, " +%d(+%d)", goodBasic->magicAtt, add );
			} 
			else
			{
				sprintf( suffix, " +%d", goodBasic->magicAtt );
			}
			strAttribute.append( "\n" + LangManager::getText("STG036") + suffix );
		}

		if (goodsDynamic->k_def > 0)
		{ 
			int add = goodsDynamic->k_def - goodBasic->def;
			if ( add > 0 )
			{
				sprintf( suffix, " +%d(+%d)", goodBasic->def, add );
			} 
			else
			{
				sprintf( suffix, " +%d", goodBasic->def );
			}
			strAttribute.append( "\n" + LangManager::getText("STG037") + suffix );
		}
		if (goodsDynamic->m_magicDef > 0)
		{ 
			int add = goodsDynamic->m_magicDef - goodBasic->magicDef;
			if ( add > 0 )
			{
				sprintf( suffix, " +%d(+%d)", goodBasic->magicDef, add );
			} 
			else
			{
				sprintf( suffix, " +%d", goodBasic->magicDef );
			}
			strAttribute.append( "\n" + LangManager::getText("STG038") + suffix );
		}
		if( goodsDynamic->r_hp > 0 )
		{
			int add = goodsDynamic->r_hp - goodBasic->hp;
			if ( add > 0 )
			{
				sprintf( suffix, " +%d(+%d)", goodBasic->hp, add );
			} 
			else
			{
				sprintf( suffix, " +%d", goodBasic->hp );
			}
			strAttribute.append( "\n" + LangManager::getText("STG039") + suffix );
		}

		// updata property
		_sItemsAttribute->setString( strAttribute.c_str() );

		strAttributeNext = stringStrengAfter( goodID, goodsDynamic->e_strengthen );
		_sBtInfo->setString( strAttributeNext.c_str() );

		btnHasVisble();

		_txtTime->setString( pValuesUtil->getString("STG050").c_str() );

		sprintf( suffix, pValuesUtil->getString("STG040").c_str(), goodsDynamic->e_strengthen );
		string strLev = suffix;
		_txtLevel->setString( strLev.c_str() );

		if(  _curStrengGoods && _curStrengGoods->_equpInfo && _curStrengGoods->_equpInfo->StrengGoodsInfo->id == id  )
		{
			_curStrengGoods->updateStrength( goodsDynamic->e_strengthen );
		}
	}	
}
		
/**
* caculate attribut after streng
* goodID=prob ID lev = current lev
* */
string StrengPanel::stringStrengAfter( int goodID, int lev  )
{
	StrengManage* pStrengManager = StrengManage::Instance();
	if ( !pStrengManager || !g_pGoodsManager )
	{
		return "";
	}

	string strAttributeNext ="";
	char suffix[128];

	StrengVo strengVoTemp;
	memset( &strengVoTemp, 0, sizeof( strengVoTemp ) );
	StrengVo* strengVo = &strengVoTemp;
	pStrengManager->getGoodsStrengInfo( goodID, lev + 1, strengVo );
	GoodsBasic* goodBasic = g_pGoodsManager->getBasicGood( goodID );

	if ( !goodBasic )
	{
		return "";
	}

	ValuesUtil* pValuesUtil = ValuesUtil::Instance();
	int price = pStrengManager->getGoodsUpStrengprice( goodID, lev );
	sprintf( suffix, pValuesUtil->getString( "STG041" ).c_str(), price );
	strAttributeNext.append( suffix );

	if( strengVo->hp > 0 )
	{
		int add = strengVo->hp - goodBasic->hp;
		if ( add > 0 )
		{
			sprintf( suffix,  "+%d(+%d)", goodBasic->hp, add );
		} 
		else
		{
			sprintf( suffix, "+%d", goodBasic->hp );
		}
		strAttributeNext.append( "\n" + LangManager::getText("STG042") + suffix );
	}

	if( strengVo->att > 0 )
	{ 
		int add = strengVo->att - goodBasic->att;
		if ( add > 0 )
		{
			sprintf( suffix, "+%d(+%d)", goodBasic->att, add );
		} 
		else
		{
			sprintf( suffix, "+%d", goodBasic->att );
		}
		strAttributeNext.append( "\n" + LangManager::getText("STG043") + suffix );
	}
	if( strengVo->magicAtt > 0 )
	{ 
		int add = strengVo->magicAtt - goodBasic->magicAtt;
		if ( add > 0 )
		{
			sprintf( suffix, "+%d(+%d)", goodBasic->magicAtt, add );
		} 
		else
		{
			sprintf( suffix, "+%d", goodBasic->magicAtt );
		}
		strAttributeNext.append( "\n" + LangManager::getText("STG044") + suffix );
	}
	if( strengVo->def > 0 )
	{ 
		int add = strengVo->def - goodBasic->def;
		if ( add > 0 ) 
		{
			sprintf( suffix, "+%d(+%d)", goodBasic->def, add );
		} 
		else
		{
			sprintf( suffix, "+%d", goodBasic->def );
		}
		strAttributeNext.append( "\n" + LangManager::getText("STG045") + suffix );
	}
	if(strengVo->magicDef > 0)
	{ 
		int add = strengVo->magicDef - goodBasic->magicDef;
		if ( add > 0 )
		{
			sprintf( suffix, "+%d(+%d)", goodBasic->magicDef, add );
		} 
		else
		{
			sprintf( suffix, "+%d", goodBasic->magicDef );
		}
		strAttributeNext.append( "\n" + LangManager::getText("STG046") + suffix );
	}
	return strAttributeNext;
}
		
/**
*streng update  or degrete
* strengtype　＝　１up  strengtype　＝　0 decrese 
* */
void StrengPanel::sendSocket(  int strengtype  )
{
	RoleManage* pRoleManage = RoleManage::Instance();

	if( !_curStrengGoods || !pRoleManage ) return;
	StrengGoodsVo* strengGoods = _curStrengGoods->_equpInfo;

	AccountInfoVo* accountInfo = pRoleManage->accountInfo();
	ValuesUtil* pValuesUtil = ValuesUtil::Instance();
	if( m_spCombox->getIsVisible() && strengtype == 1 )
	{
		if(  accountInfo->gold() < ((100 - _curStrengProb) / 10 )  )
		{
			ccColor3B color  = { 255, 0, 0 };
			Message::Instance()->show( pValuesUtil->getString("StGlodNeed"), color );
			return;
		}
	}
	else
	{
		int price = StrengManage::Instance()->getGoodsUpStrengprice( strengGoods->StrengGoodsInfo->goodId, _curStrengLev );
		if(  accountInfo->silver() < price && strengtype == 1  )
		{
			ccColor3B color  = { 255, 0, 0 };
			Message::Instance()->show( pValuesUtil->getString("StYinNeed"), color );
			return;
		}
	}
	struct sdata
	{
		int UseType;
		int probability;
		int strengtype;
		int vip;
		StrengGoodsVo* sdataStrengGoodsVo;
	};
	sdata s;
	s.UseType = 2;
	s.sdataStrengGoodsVo = strengGoods;
	s.vip = ( m_spCombox->getIsVisible() == true ? 1: 0 );
	s.strengtype = strengtype;
	s.probability = _curStrengProb;
	GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::SHOW_STRENG_CLICK, &s );
	//dispatcher.dispatchEvent(new ParamEvent(GameDispatcher.SHOW_STRENG_CLICK,{UseType:2, type:type, ssit:sit, svip:vip,stype:strengType,spro:probability,srole:roleid}));
}

void StrengPanel:: playStrengEffect(  bool isCrit /*= false*/  )
{
	CCAnimation* clickEffect = g_pKKAnimationFactory->registAni(
		"assets/effect/strengEff/strengEff.plist",
		"streng%02d.png", 20, 0.1f);

	if ( !clickEffect )
	{
		return;
	}

	CCSprite* _clickEffectMc = (CCSprite*)this->getChildByTag(StrengEff_TAG);
	if (_clickEffectMc)
	{
		_clickEffectMc->removeFromParentAndCleanup(true);
		_clickEffectMc = 0;
	}

	if ( !_clickEffectMc )
	{
		_clickEffectMc = new CCSprite();
		_clickEffectMc->init();
		this->addChild(_clickEffectMc, 10);
		_clickEffectMc->setTag(StrengEff_TAG);
		_clickEffectMc->release();

		_clickEffectMc->setPosition(  ccp(GOOD_PIC_X+POSX(54), GOOD_PIC_Y+POSX(54))  );

		cocos2d::CCCallFunc *callBack = cocos2d::CCCallFuncN::actionWithTarget(this,
			callfuncN_selector(StrengPanel::PlayEffectComplete));
		cocos2d::CCFiniteTimeAction *action = cocos2d::CCSequence::actions(
			cocos2d::CCAnimate::actionWithAnimation( clickEffect ), 
			callBack, 
			NULL );
		_clickEffectMc->runAction( action );
	}
	else
	{
		if (_clickEffectMc->getIsVisible())
		{
			return;
		}
		
		cocos2d::CCCallFunc *callBack = cocos2d::CCCallFuncN::actionWithTarget(this,
			callfuncN_selector(StrengPanel::PlayEffectComplete));
		cocos2d::CCFiniteTimeAction *action = cocos2d::CCSequence::actions(
			cocos2d::CCAnimate::actionWithAnimation( clickEffect ), 
			callBack, 
			NULL );
		_clickEffectMc->runAction( action );

		_clickEffectMc->setIsVisible(true);
	}

	//Critical
	if (isCrit)
	{
		clickEffect = g_pKKAnimationFactory->registAni(
			"assets/effect/strengEff/strengCriEff.plist",
			"strengCrit%02d.png", 20, 0.1f);
		if ( !clickEffect )
		{
			return;
		}

		_clickEffectMc = (CCSprite*)this->getChildByTag(StrengCriEff_TAG);
		if (_clickEffectMc)
		{
			_clickEffectMc->removeFromParentAndCleanup(true);
			_clickEffectMc = 0;
		}

		if ( !_clickEffectMc )
		{
			_clickEffectMc = new CCSprite();
			_clickEffectMc->init();
			this->addChild(_clickEffectMc, 10);
			_clickEffectMc->setTag(StrengCriEff_TAG);
			_clickEffectMc->release();

			_clickEffectMc->setPosition(  ccp(GOOD_PIC_X+POSX(54), GOOD_PIC_Y+POSX(54))  );

			cocos2d::CCCallFunc *callBack = cocos2d::CCCallFuncN::actionWithTarget(this,
				callfuncN_selector(StrengPanel::PlayEffectComplete));
			cocos2d::CCFiniteTimeAction *action = cocos2d::CCSequence::actions(
				cocos2d::CCAnimate::actionWithAnimation( clickEffect ), 
				callBack, 
				NULL );
			_clickEffectMc->runAction( action );
		}
		else
		{
			cocos2d::CCCallFunc *callBack = cocos2d::CCCallFuncN::actionWithTarget(this,
				callfuncN_selector(StrengPanel::PlayEffectComplete));
			cocos2d::CCFiniteTimeAction *action = cocos2d::CCSequence::actions(
				cocos2d::CCAnimate::actionWithAnimation( clickEffect ), 
				callBack, 
				NULL );
			_clickEffectMc->runAction( action );

			_clickEffectMc->setIsVisible(true);
		}
	}
	
}

void StrengPanel::PlayEffectComplete( CCNode* pnode )
{
	CCSprite* _clickEffectMc = (CCSprite*)this->getChildByTag(StrengEff_TAG);
	CCTexture2D* p1 = CCTextureCache::sharedTextureCache()->textureForKey("assets/effect/strengEff/strengEff.pvr.ccz");
	if ( _clickEffectMc )
	{
		_clickEffectMc->stopAllActions();
		_clickEffectMc->removeFromParentAndCleanup(true);
	}
	_clickEffectMc = (CCSprite*)this->getChildByTag(StrengCriEff_TAG);
	if ( _clickEffectMc )
	{
		_clickEffectMc->stopAllActions();
		_clickEffectMc->removeFromParentAndCleanup(true);
	}

	g_pKKAnimationFactory->removeUnusedTextureForKey("assets/effect/strengEff/strengEff");
	//CCAnimationCache::sharedAnimationCache()->removeAnimationByName( "assets/effect/strengEff/strengEff.plist" );
	//if ( CCTexture2D* p = CCTextureCache::sharedTextureCache()->textureForKey("assets/effect/strengEff/strengEff.pvr.ccz"))
	//{
	//	if (p->retainCount()>1)
	//	{
	//		CCScheduler::sharedScheduler()->scheduleSelector( schedule_selector(CDManage::removeUnusedTexturesLater),
	//			CDManage::Instance(), 1.5f, false);
	//	}
	//	else
	//	{
	//		CCTextureCache::sharedTextureCache()->removeUnusedTextureForKey("assets/effect/strengEff/strengEff.plist");
	//	}
	//}

	g_pKKAnimationFactory->removeUnusedTextureForKey("assets/effect/strengEff/strengCriEff");
	//CCAnimationCache::sharedAnimationCache()->removeAnimationByName( "assets/effect/strengEff/strengCriEff.plist" );
	//if ( CCTexture2D* p = CCTextureCache::sharedTextureCache()->textureForKey("assets/effect/strengEff/strengCriEff.pvr.ccz"))
	//{
	//	if (p->retainCount()>1)
	//	{
	//		CCScheduler::sharedScheduler()->scheduleSelector( schedule_selector(CDManage::removeUnusedTexturesLater),
	//			CDManage::Instance(), 1.5f, false);
	//	}
	//	else
	//	{
	//		CCTextureCache::sharedTextureCache()->removeUnusedTextureForKey("assets/effect/strengEff/strengCriEff.pvr.ccz");
	//	}
	//}
}
		
void StrengPanel::onEnterFrame()
{
	//if(event.target.currentFrame >= event.target.totalFrames){
	//	event.target.removeEventListener(Event.ENTER_FRAME, onEnterFrame);
	//	event.target.visible = false;
	//	event.target.gotoAndStop(1);
	//}
}
		
/**
* update ToolTip 
* @param id prob key ID
* 
*/		
void StrengPanel::updateTip( uint id )
{
	_strengCreate->updateTip( id );
	if( _curStrengGoods && _curStrengGoods->_equpInfo )
	{
		GoodsInfo* info = _curStrengGoods->_equpInfo->StrengGoodsInfo;
		if ( info->id == id )
		{
			GoodsDynamic* goodsDynamic = g_pGoodsDynamicManager->getGoodsDynamic( id );
			viewEquipmentInfo( goodsDynamic->a_id, goodsDynamic->b_goodID );
		}		
	}
}
		
/**
*  
* player level smaller than 20 ,update with this function 
*/		
void StrengPanel::updateStriengPropAtFirst( int Prob /*= 100*/  )
{
	_curStrengProb = Prob;
	//_rateBar.width = 2.48 * _curStrengProb;
	_rateBar->setScaleX( Prob * 0.01f );

	char txtProp[54];
	sprintf( txtProp, ValuesUtil::Instance()->getString("STG049").c_str(), _curStrengProb );
	_txtRate->setString( txtProp );
	_txtTime->setString( "" );	// hide

	_txtTrend->setString( "" );
	
	_comCheckBox->setIsVisible( true );
	_comCheckBox->setString( "" );
}
		
/**
* change streng prob
* */
void StrengPanel::updateStrengProp( int Prob,int Trend )
{
	_curStrengProb = Prob;
	_rateBar->setScaleX( Prob * 0.01f );

	ValuesUtil* pValuesUtil = ValuesUtil::Instance();
	char txtProp[54];
	sprintf( txtProp, pValuesUtil->getString("STG049").c_str(), _curStrengProb );
	string str = txtProp;
	_txtRate->setString( str.c_str() );

	str = pValuesUtil->getString("STG050");
	_txtTime->setString( str.c_str() );

	str = (Trend == 1) ?( pValuesUtil->getString("STG051") ):( pValuesUtil->getString("STG052") );
	_txtTrend->setString( str.c_str() );
	ccColor3B col = (Trend == 1) ?( ccGREEN ):( ccRED );
	_txtTrend->setColor( col );

	sprintf( txtProp, pValuesUtil->getString("StSpLock").c_str());//, (100 - _curStrengProb) / 10 
	str = txtProp;
	_comCheckBox->setString( str.c_str() );
}
		
void StrengPanel::clear()
{
	//_curPage = 1;
	//_totalPage = 1;
	if ( _curStrengGoods )
	{
		_sItemsName->setString("");
		_txtLevel->setString("");
		if ( _pic )
		{
			this->removeChild(_pic, true);
			_pic = 0;
		}
		_sItemsAttribute->setString("");
		_sBtInfo->setString("");
		_curStrengGoods = 0;
		_curStrengLev = 0;
	}
	
	if (_strengCreate)
	{
		_strengCreate->removeSkinChild();
		_item = 0;
	}
	
	CCSprite* _clickEffectMc = (CCSprite*)this->getChildByTag(StrengEff_TAG);
	if (_clickEffectMc)
	{
		_clickEffectMc->removeFromParentAndCleanup(true);
		_clickEffectMc = 0;
	}
}	
/**
* CD change
* */
void StrengPanel::CDchange( int show )
{
	_CDState = show;

    //Doyang 20120718
//	if( !_curStrengGoods && !_curStrengGoods->_equpInfo )
    if( _curStrengGoods && _curStrengGoods->_equpInfo )
	{
		GoodsInfo* pInfo = _curStrengGoods->_equpInfo->StrengGoodsInfo;
		if ( pInfo )
		{
			viewEquipmentInfo( pInfo->id, pInfo->goodId );
		}
	}
}
		
//////////////////////////////////////btn event refferece/////////////////////////////////////////////

//void onClickPre(e:MouseEvent)
//{
//	_curPage = Math.min(_totalPage, Math.max(1, _curPage-1));
//	pageLayout();
//	dispatchEvent(new ParamEvent(PAGECHANGE, 1));
//}
//		
//private function onClickNext(e:MouseEvent):void
//{
//	_curPage = Math.max(1, Math.min(_totalPage, _curPage+1));
//	pageLayout();
//	dispatchEvent(new ParamEvent(PAGECHANGE, -1));
//}
		
void StrengPanel::onClickStrengUp(CCObject* pSender)
{
	if( _btnStrengUp->getIsVisible() )
	{
		sendSocket(1);

		_StrengUpItem->setIsEnabled(false);
		CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(StrengPanel::lockBtnStrengUp),
			this,0.2f,false);
	}

}
		
void StrengPanel::onClickStrengDown(CCObject* pSender)
{
	if( _btnStrengDown->getIsVisible() )
	{
		sendSocket(0);

		_StrengDownItem->setIsEnabled(false);
		CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(StrengPanel::lockBtnStrengDown),
			this,0.2f,false);
	}
}

void StrengPanel::lockBtnStrengUp(ccTime dt)
{
	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(StrengPanel::lockBtnStrengUp), this);
	if (_StrengUpItem)
	{
		//_StrengUpItem->setIsEnabled(true);
		btnHasVisble(true, false/*_StrengDownItem->getIsEnabled()*/);
	}
}

void StrengPanel::lockBtnStrengDown(ccTime dt)
{
	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(StrengPanel::lockBtnStrengDown), this);
	if (_StrengUpItem)
	{
		//_StrengUpItem->setIsEnabled(true);
		btnHasVisble(_StrengUpItem->getIsEnabled(), true);
	}
}
	
//private function onOverStrengUp(e:MouseEvent):void{
//	var button:SimpleButton = e.target as SimpleButton; 
//	if(_curStrengGoods == null) return;
//	var accountInfo:AccountInfoVo = RoleManage.getInstance().accountInfo;
//			
//	if(!_btnStrengUp.enabled){
//		if(_CDState == 1)
//			_sBtInfo.htmlText="强化处于CD冷却中！";
//		else if(accountInfo.crystalLev <= _curStrengLev)
//			_sBtInfo.htmlText="主水晶等级不够，请先升级主水晶！";
//		if(accountInfo.crystalLev<=20){
//			if(RoleManage.getInstance().roleInfo.playerBaseInfo.lev <= _curStrengLev){
//				_sBtInfo.htmlText="主角等级不够，请先提升主角等级！";
////						continue;
//			}
//		}
//	}
//			
//}
//		
//private function onOverStrengDown(e:MouseEvent):void{
//	var button:SimpleButton = e.target as SimpleButton; 
//	if(_curStrengGoods == null) return;
//	var accountInfo:AccountInfoVo = RoleManage.getInstance().accountInfo;
//			
//	showStrengDownTip();
//			
//	_view["_selectInfoArr"].x = 505;
//}
//		
//private function showStrengDownTip():void
//{
//	if(_curStrengLev > 0){
//		var price:int = StrengManage.getInstance().getGoodDownStrengprice(_curStrengGoods._equpInfo.StrengGoodsInfo.goodId,_curStrengLev);
//		_sBtInfo.htmlText="降级成功将返回："+ price+"银币";
//	}
//	else{
//		_btnStrengDown.enabled = false;
//		_btnStrengDown.mouseEnabled = true;
//		_sBtInfo.htmlText="强化已是最低等级，无法降级！";
//	}
//}
//		
//		
///**
//	* mouse roll out event
//	* */
//private function onRollOutHandler(event:MouseEvent):void{
//	if(_curStrengGoods != null){
//		_sBtInfo.htmlText = stringStrengAfter(_curStrengGoods._equpInfo.StrengGoodsInfo.goodId,_curStrengLev);
//	}
//	_view["_selectInfoArr"].x = 425;
//}
//		
//private function onMouseRollOver(event:MouseEvent):void{
//	_toolTips.setToolTips(_mcVIP,"【VIP3享有金币锁定100%成功率的福利】");
//}
//		
void StrengPanel::strengLevLow()
{
	btnHasVisble(true, false);
}

/**
* show btn
* */
void StrengPanel::btnHasVisble( bool upVis /*= true*/, bool downVis /*= true*/ )
{
	if( _CDState == 1 )
	{
		btnEnable(_btnStrengUp, false);
		//btnEnable(_btnStrengDown, true);
		return;
	}
			
	if( !_curStrengGoods )
	{
		btnEnable(_btnStrengUp, false);
		//btnEnable(_btnStrengDown, false);
		return;
	}

	if( _curStrengGoods && _curStrengGoods->_equpInfo )
	{
		GoodsDynamic* goodsDynamic = g_pGoodsDynamicManager->getGoodsDynamic( _curStrengGoods->_equpInfo->StrengGoodsInfo->id );
		if( !goodsDynamic )
			return;
		if( goodsDynamic->e_strengthen == 0 )
		{
			btnEnable(_btnStrengUp, true);
			//btnEnable(_btnStrengDown, false);
			return;
		}

		if( goodsDynamic->e_strengthen == 120 )
		{
			btnEnable(_btnStrengUp, false);
			//btnEnable(_btnStrengDown, true);
			return;
		}
				
		if( RoleManage::Instance()->roleLev() < 28 )
		{
			if( RoleManage::Instance()->roleInfo()->playerBaseInfo.lev() <= _curStrengGoods->_equpInfo->StrengGoodsInfo->strengthen )
			{
				btnEnable(_btnStrengUp, false);
				//btnEnable(_btnStrengDown, true);
				return;
			}
		}

		if( RoleManage::Instance()->roleLev() <= _curStrengGoods->_equpInfo->StrengGoodsInfo->strengthen )
		{
			btnEnable(_btnStrengUp, false);
			//btnEnable(_btnStrengDown, true);
			return;
		}

	}

	btnEnable(_btnStrengUp, upVis);
	//btnEnable(_btnStrengDown, downVis);
}

FigureItem* StrengPanel::figureItem()
{
	return _item;
}

void StrengPanel::btnEnable( CCMenu* btn, bool enabled )
{
	CCMenuItemImage* pBtnImage = (CCMenuItemImage*)btn->getChildByTag( BTN_IMAGE_TAG );
	if ( pBtnImage )
	{
		pBtnImage->setIsEnabled( enabled );
	}
	
}

void StrengPanel::clickCombox( CCObject* pSender )
{
	m_spCombox->setIsVisible( !m_spCombox->getIsVisible() );
	
}

CCNode * StrengPanel::getNewHandItem( int id )
{
	if(id==98){
		return this->getChildByTag(BTN_UP_TAG)->getChildByTag(BTN_IMAGE_TAG);
	}
	else if(id>=1 && id<=6){
		if(_strengCreate)
			return _strengCreate->getNewHandItem(id);
	}
	else{
		if(_figureCreate)
			return _figureCreate->getNewHandItem(id);
	}

	return NULL;
}

StrengPanel::~StrengPanel()
{

}
