#include "MagicPanel.h"
#include "model/figure/vo/EquipmentVo.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "model/backpack/vo/GoodsBasic.h"
#include "model/com/vo/GoodsDynamic.h"
#include "FigureItem.h"
#include "../MainStrengMediator.h"
#include "model/figure/EquipmentManager.h"
#include "model/player/RoleManage.h"
#include "model/streng/StrengManage.h"
#include "utils/ValuesUtil.h"
#include "model/backpack/GoodsManager.h"
#include "model/com/GoodsDynamicManager.h"
#include "utils/ColorUtil.h"
#include "view/mainStreng/components/StrengGoods.h"
#include "model/streng/vo/StrengGoodsVo.h"
#include "events/GameDispatcher.h"
#include "utils/Utils.h"
#include "model/magic/vo/MagicLimitVo.h"
#include "model/magic/MagicManage.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "manager/LangManager.h"

#define StrengGoodSize CCSizeMake(POSX(307),POSX(119))
#define PanelListSize CCSizeMake(POSX(341), POSX(428))

MagicPanel::MagicPanel()
{
	_bgEquip = 0;

	_sparInfo = 0;
	_comCheckBox = 0;
	_costText = 0;
	_figureCreate = 0;
	_magicCreate = 0;
	_equipName = 0;

	_MagicItem = 0;
	_btnMagic = 0;

	_fangkuang = 0;
	_pic = 0;

	_attribute1 = 0;
	_attribute2 = 0;
	_attribute3 = 0;

	_curMagicGoods= 0;
	_curId = 0;
	_curGoodsId = 0;

	_magicLev = 0;
	_roleVipLev = 0;
	_sparNum = 0;

	_item = 0;
	m_bShowBag  = false;

	m_selectedSpriteImage = 0;
}

bool MagicPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	this->setPosition( ccp(POSX(17), POSX(0)) );
	this->setContentSize( CCSizeMake( POSX(923), POSX(562) ) );

	_figureCreate = StrengFigureCreate::figureCreatScrollViewWithCCRect(
		CCRectMake( POSX(271), POSX(458), POSX(395), POSX(83) ) );
	_figureCreate->setAnchorPoint(CCPointZero);
	this->addChild( _figureCreate );
	//_figureCreate->release(); //LH20120108

	// equipment info background
	_bgEquip = new CCUIBackground();
	_bgEquip->initWithSpriteFrame( "popuibg/bg2.png",
		ccp(POSX(17), POSX(27)), ccp(0,0), PanelListSize );
	this->addChild( _bgEquip );
	_bgEquip->release();

	CCSprite* pDirUp = new CCSprite;
	if ( pDirUp && pDirUp->initWithSpriteFrameName("streng/direct_up.png") )
	{
		pDirUp->setAnchorPoint(CCPointZero);
		pDirUp->setPosition(ccp(POSX(188), POSX(429)));
		this->addChild( pDirUp );
		pDirUp->release();
	}
	CCSprite* pDirDown = new CCSprite;
	if ( pDirDown && pDirDown->initWithSpriteFrameName("streng/direct_up.png") )
	{
		pDirDown->setAnchorPoint(CCPointZero);
		pDirDown->setFlipY(true);
		pDirDown->setPosition(ccp(POSX(188), POSX(32)));
		this->addChild( pDirDown );
		pDirDown->release();
	}

	CCUIBackground* bgEquipInfoBg = new CCUIBackground();
	bgEquipInfoBg->initWithSpriteFrame( "popuibg/bg2.png",
		ccp(POSX(365), POSX(27)), ccp(0,0), CCSizeMake(POSX(541), POSX(428)) );
	this->addChild( bgEquipInfoBg );
	bgEquipInfoBg->release();

	CCSprite* pSparSp = new CCSprite;
	if ( pSparSp && pSparSp->initWithSpriteFrameName("streng/stone.png") )
	{
		pSparSp->setAnchorPoint(CCPointZero);
		pSparSp->setPosition(ccp(POSX(5), POSX(391)));
		bgEquipInfoBg->addChild(pSparSp);
		pSparSp->release();
	}

	CCSprite* pYuanBg = new CCSprite;
	if ( pYuanBg && pYuanBg->initWithSpriteFrameName("streng/yuan.png") )
	{
		pYuanBg->setAnchorPoint(CCPointZero);
		pYuanBg->setPosition(ccp(POSX(155), POSX(196)));
		bgEquipInfoBg->addChild(pYuanBg);
		pYuanBg->release();
	}
	_fangkuang = new CCSprite;
	if ( _fangkuang && _fangkuang->initWithSpriteFrameName("streng/fangkuang.png") )
	{
		_fangkuang->setAnchorPoint(CCPointZero);
		_fangkuang->setPosition(ccp(POSX(202), POSX(248)));
		bgEquipInfoBg->addChild(_fangkuang);
		_fangkuang->release();
	}

	//spar info
	_sparInfo = CCLabelTTF::labelWithString( "",
		CCSizeMake( POSX(188), POSX(24) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(24) );
	_sparInfo->setColor(  ccc3( 254, 248, 220 )  );
	_sparInfo->setPosition( ccp(POSX(50), POSX(394) ) );
	_sparInfo->setAnchorPoint(CCPointZero);
	bgEquipInfoBg->addChild( _sparInfo );
	
	// name
	_equipName = CCLabelTTF::labelWithString( "",
		CCSizeMake( POSX(221), POSX(24) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
	_equipName->setPosition( ccp( POSX(155), POSX(212) ) );
	_equipName->setAnchorPoint(CCPointZero);
	bgEquipInfoBg->addChild( _equipName );

	// _attribute1 bg
	CCUIBackground* bginfo = new CCUIBackground();
	bginfo->initWithSpriteFrame("ui2.png",
		ccp(POSX(8), POSX(145)), ccp(0,0), CCSizeMake(POSX(169), POSX(42)) );
	bgEquipInfoBg->addChild( bginfo );
	bginfo->release();

	// _attribute1
	_attribute1 = CCLabelTTF::labelWithString( "",
		CCSizeMake(POSX(185), POSX(25)), CCTextAlignmentLeft, g_sSimHeiFont, POSX(24) );
	_attribute1->setPosition( ccp( POSX(0), POSX(9) ) );
	_attribute1->setAnchorPoint(CCPointZero);
	bginfo->addChild( _attribute1 );
	_attribute1->setColor(ccc3(40,201,254));

	// _attribute2 bg
	bginfo = new CCUIBackground();
	bginfo->initWithSpriteFrame("ui2.png",
		ccp(POSX(181), POSX(145)), ccp(0,0), CCSizeMake(POSX(169), POSX(42)) );
	bgEquipInfoBg->addChild( bginfo );
	bginfo->release();

	// _attribute2
	_attribute2 = CCLabelTTF::labelWithString( "",
		CCSizeMake(POSX(185), POSX(25)), CCTextAlignmentLeft, g_sSimHeiFont, POSX(24) );
	_attribute2->setPosition( ccp( POSX(0), POSX(9) ) );
	_attribute2->setAnchorPoint(CCPointZero);
	bginfo->addChild( _attribute2 );
	_attribute2->setColor(ccc3(40,201,254));

	// _attribute3 bg
	bginfo = new CCUIBackground();
	bginfo->initWithSpriteFrame("ui2.png",
		ccp(POSX(348), POSX(145)), ccp(0,0), CCSizeMake(POSX(169), POSX(42)) );
	bgEquipInfoBg->addChild( bginfo );
	bginfo->release();
	
	// _attribute3
	_attribute3 = CCLabelTTF::labelWithString( "",
		CCSizeMake(POSX(185), POSX(25)), CCTextAlignmentLeft, g_sSimHeiFont, POSX(24) );
	_attribute3->setPosition( ccp( POSX(0), POSX(9) ) );
	_attribute3->setAnchorPoint(CCPointZero);
	bginfo->addChild( _attribute3 );
	_attribute3->setColor(ccc3(40,201,254));
	//CCLayerColor* pCl = CCLayerColor::layerWithColorWidthHeight(ccc4(0,0,255,100),POSX(169),POSX(24));
	//_attribute3->addChild(pCl);

	// grid image btn
	CCSprite* pNormal = CCSprite::spriteWithSpriteFrameName("streng/grid.png");
	CCSprite* pPress = CCSprite::spriteWithSpriteFrameName("streng/grid.png");
	CCMenuItemSprite *pGridItem = cocos2d::CCMenuItemImage::itemFromNormalSprite(
		pNormal,
		pPress,
		this,
		menu_selector(MagicPanel::gridClickHandler) );
	pGridItem->setPosition( ccp(POSX(63+39/2), POSX(102+39/2)) );
	CCMenu* pMenuGrid = CCMenu::menuWithItems(pGridItem, 0);
	pMenuGrid->setTouchLayer( TLE::WindowLayer_Common_btn );
	pMenuGrid->setPosition( CCPointZero );
	bgEquipInfoBg->addChild( pMenuGrid );
	//select
	_gridSelect = new CCSprite;
	if (_gridSelect && _gridSelect->initWithSpriteFrameName("streng/select.png"))
	{
		_gridSelect->setAnchorPoint(CCPointZero);
		_gridSelect->setPosition(ccp(POSX(63), POSX(102)));
		bgEquipInfoBg->addChild(_gridSelect);
		_gridSelect->release();
		_gridSelect->setIsVisible(false);
	}
	
	//lock rate
	int goldNeed = 50;//VipManager::Instance()->getVipContent(23,3).info2;
	_comCheckBox = CCLabelTTF::labelWithString( LangManager::getText("STG082", goldNeed).c_str(),
		CCSizeMake( POSX(405), POSX(24) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(24) );
	_comCheckBox->setPosition( ccp( POSX(124), POSX(109) ) );
	_comCheckBox->setAnchorPoint(CCPointZero);
	bgEquipInfoBg->addChild( _comCheckBox );
	_comCheckBox->setColor(ccYELLOW);

	//up line or cost
	_costText = CCLabelTTF::labelWithString( "",
		CCSizeMake( POSX(405), POSX(24) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(24) );
	_costText->setPosition( ccp( POSX(124), POSX(79) ) );
	_costText->setAnchorPoint(CCPointZero);
	bgEquipInfoBg->addChild( _costText );
	_costText->setColor(ccRED);

	// update btn
	CCSize csBt( POSX(121), POSX(49) );
	{
		
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			_MagicItem = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this,
				menu_selector(MagicPanel::onClickHandler) );
			_MagicItem->setPosition( ccp( POSX(211.0f)+csBt.width/2, POSX(10.0f)+csBt.height/2 ) );
			_btnMagic = CCMenu::menuWithItems(_MagicItem, 0);
			_btnMagic->setTouchLayer( TLE::WindowLayer_Common_btn );
			_btnMagic->setPosition( CCPointZero );
			bgEquipInfoBg->addChild( _btnMagic );
			string txt = ValuesUtil::Instance()->getString( "StTab3" );
			CCLabelTTF* txtLabel = CCLabelTTF::labelWithString( txt.c_str(), csBt, CCTextAlignmentCenter, g_sSimHeiFont, POSX(20) );
			txtLabel->setPosition( ccp( csBt.width/2, csBt.height/2 ) );
			_MagicItem->addChild( txtLabel );
			_btnMagic->setIsVisible(false);
		}
		
	}

	// bag image btn
	pNormal = CCSprite::spriteWithSpriteFrameName("streng/bag.png");
	pPress = CCSprite::spriteWithSpriteFrameName("streng/bag_select.png");
	CCMenuItemSprite *pBagItem = cocos2d::CCMenuItemImage::itemFromNormalSprite(
		pNormal,
		pPress,
		this,
		menu_selector(MagicPanel::bagClickHandler) );
	pBagItem->setPosition( ccp( POSX(17+95/2), POSX(461+74/2) ) );
	CCMenu* pMenuBag = CCMenu::menuWithItems(pBagItem, 0);
	pMenuBag->setTouchLayer( TLE::WindowLayer_Common_btn );
	pMenuBag->setPosition( CCPointZero );
	this->addChild( pMenuBag );

	// left direct image btn
	CCSize csImageSize( 41, 63 );
	pNormal = CCSprite::spriteWithSpriteFrameName("streng/direct.png");
	pPress = CCSprite::spriteWithSpriteFrameName("streng/direct_pressed.png");
	CCMenuItemSprite *pDirectItem = cocos2d::CCMenuItemImage::itemFromNormalSprite(
		pNormal,
		pPress,
		this,
		menu_selector(MagicPanel::directClickHandler) );
	pDirectItem->setPosition( ccp(POSX(138+csImageSize.width/2-11), POSX(468+csImageSize.height/2-10)) );
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
		menu_selector(MagicPanel::directRightClickHandler) );
	CCSprite* pS = (CCSprite*)pDirectItem->getNormalImage();
	pS->setFlipX( true );
	pS = (CCSprite*)pDirectItem->getSelectedImage();
	pS->setFlipX( true );
	pDirectItem->setPosition( ccp(POSX(762+csImageSize.width/2-11), POSX(468+csImageSize.height/2-10)) );
	pMenuDirect = CCMenu::menuWithItems(pDirectItem, 0);
	pMenuDirect->setTouchLayer( TLE::WindowLayer_Common_btn );
	pMenuDirect->setPosition( CCPointZero );
	this->addChild( pMenuDirect );
	
	return true;
}

MagicPanel::~MagicPanel()
{

}

/**
* 首次打开魔化面板
* @param cdState
*/		
void MagicPanel::openMagic()
{
	clear();
	if ( _figureCreate )
		_figureCreate->buildList();  // creat figure 
}

int MagicPanel::getCount()
{
	return _listViewItemsList.size();
}

LayerNode * MagicPanel::getView( int position )
{
	return _listViewItemsList[position];
}

void MagicPanel::onItemClickListener( LayerNode *itemCell, int position )
{
	StrengGoods* pStrengGoods = (StrengGoods*)itemCell;
	if ( pStrengGoods )
	{
		struct sdata
		{
			int UseType;
			StrengGoodsVo* sdataStrengGoodsVo;
		} s;
		s.UseType = 6;	// {UseType:6/* 6 Check prop when click */
		s.sdataStrengGoodsVo = pStrengGoods->_equpInfo;
		GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::SHOW_STRENG_CLICK, &s );
	}
	
	if (
		m_selectedSpriteImage &&
		( m_selectedSpriteImage->getParent() != pStrengGoods )
		)
	{
		m_selectedSpriteImage->removeFromParentAndCleanup(true);

		if ( pStrengGoods )
		{
			m_selectedSpriteImage = new CCUIBackground();
			m_selectedSpriteImage->initWithSpriteFrame( "train/gold_back.png",
				ccp(0, POSX(2)), CCPointZero, StrengGoodSize );
			pStrengGoods->addChild( m_selectedSpriteImage );
			m_selectedSpriteImage->release();
		}
	}
}

StrengGoods* MagicPanel::getStrengGoods( int id )
{
	std::map<int, StrengGoods*>::iterator it = _goodsDic.find( id );
	if ( it != _goodsDic.end() )
	{
		return it->second;
	}

	return 0;
}

void MagicPanel::clearEquipment()
{
	//remove list
	if (m_selectedSpriteImage)
	{
		m_selectedSpriteImage->removeFromParentAndCleanup(true);
		m_selectedSpriteImage = 0;
	}
	std::vector<LayerNode *>::iterator listItemIt;
	for(listItemIt = _listViewItemsList.begin();
		listItemIt != _listViewItemsList.end();
		++listItemIt)
	{
		LayerNode *tmp = (LayerNode *) *listItemIt;
		if(tmp && tmp->getParent())
		{
			tmp->removeFromParentAndCleanup(true);
			tmp->release();
		}
	}
	_listViewItemsList.clear();
	if ( _magicCreate )
	{
		_magicCreate->setAdapter(this);
	}
	_goodsDic.clear();
}

/**
* 初始角色装备列表
* @param id 角色ID 
* @return 
*/	
bool MagicPanel::creatRoleEquipmentList( int id )
{
	m_bShowBag  = false;
	clearEquipment();
	 
	bool ishasEquipment = false;
	StrengGoods* strengGoodsFirst = 0;
	EquipmentVo* roleEquipment = EquipmentManager::Instance()->getEquipment(id);
	int sitNum = 0;
	vector<GoodsInfo*> arr;
	arr = sortedArr(roleEquipment);
	for ( vector<GoodsInfo*>::iterator it = arr.begin(); it != arr.end(); it++ )
	{
		GoodsInfo* info = *it;
		if ( info )
		{
			StrengGoodsVo* strengGoodsVo = StrengManage::Instance()->returnStrengGoodsVo( info, info->sitGrid, id, 3 );
			GoodsInfo* pGoodsInfo = strengGoodsVo->StrengGoodsInfo;
			if(!pGoodsInfo)
				continue;

			int index(0);
			if ( pGoodsInfo )
			{
				index = strengGoodsVo->StrengGoodsInfo->id;
			}

			std::map<int, StrengGoods*>::iterator it = _goodsDic.find( index );
			if ( it == _goodsDic.end() )
			{
				CCRect rect( POSX(15 + (sitNum%2)*250),
					POSX(285 - (sitNum/2)*135), StrengGoodSize.width, StrengGoodSize.height );
				StrengGoods* strengGoods = StrengGoods::StrengGoodsWithRect( rect );
				strengGoods->initStrengGoodsVo( strengGoodsVo, sitNum );
				//strengGoods->retain();
				_listViewItemsList.push_back( strengGoods );

				_goodsDic.insert( make_pair(index, strengGoods) );

				if ( sitNum == 0 )
				{
					strengGoodsFirst = strengGoods;
				}				
			}

			struct sdata
			{
				int UseType;
				StrengGoodsVo* sdataStrengGoodsVo;
			};
			sdata s;
			// reget dynamic 
			if( pGoodsInfo->id != 0 )
			{
				s.UseType = 1;	// {UseType:1/* 1 get dynamic info*/
				s.sdataStrengGoodsVo = strengGoodsVo;
				GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::SHOW_STRENG_CLICK, &s );
			}

			if(sitNum==0)
			{
				s.UseType = 6;	// {UseType:6/* 6 click get info */
				s.sdataStrengGoodsVo = strengGoodsVo;
				GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::SHOW_STRENG_CLICK, &s );
			}

			sitNum++;
			ishasEquipment = true;
		}
	}
	if(ishasEquipment)
	{
		RoleManage::Instance()->currentId( id );
	}

	//add new list
	CCSize listSize = CCSizeMake(POSX(320), POSX(381));
	CCRect listRect = CCRectMake(POSX(16),
		POSX(29),
		listSize.width,
		listSize.height );
	if(!_magicCreate)
	{
		_magicCreate = CCUIListView::listViewWithCCRect(listRect, false);
		_magicCreate->setAnchorPoint(CCPointZero);
		_magicCreate->setWorldSpaceLeftBottomPoint(ccp(this->getParent()->getPosition().x + this->getPosition().x + _bgEquip->getPosition().x + listRect.origin.x, 
			this->getParent()->getPosition().y + this->getPosition().y + _bgEquip->getPosition().y + listRect.origin.y));
		_magicCreate->setHeaderSize( POSX(13.0f) );
		_magicCreate->setSpacingVertical(POSX(8));
		_magicCreate->setOnItemActionListener(this);
		_bgEquip->addChild(_magicCreate);
		_magicCreate->release();// Kenfly 20130125
		//_magicCreate->release(); //LH20120108
	}
	_magicCreate->setAdapter(this);

	if (!m_selectedSpriteImage)
	{
		if ( strengGoodsFirst )
		{
			m_selectedSpriteImage = new CCUIBackground();
			m_selectedSpriteImage->initWithSpriteFrame( "train/gold_back.png",
				ccp(0, POSX(2)), CCPointZero, StrengGoodSize );
			strengGoodsFirst->addChild( m_selectedSpriteImage );
			m_selectedSpriteImage->release();
		}
	}

	return ishasEquipment;
}
		
/**
* 按需求排序，把武器放第一位，其他按品质排 
* @param roleEquipment
* @return 
*/		
vector<GoodsInfo*> MagicPanel::sortedArr( EquipmentVo* roleEquipment )
{
	vector<GoodsInfo*> equipArr;
	std::map<int, GoodsInfo>* arr = roleEquipment->getAll();
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
/*			if ( iVecSize > 5 )
			{
				break;
			}	*/		
		}
	}
	int iSize = equipArr.size();
	if ( iSize != 0 )
	{
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
	}

	return equipArr;			
}
		
/**
* 初始包裹装备列表 
* @param bagDictionary
*/		
void MagicPanel::creatBagEquipmentList( std::map<int32, GoodsInfo*>* bagDictionary )
{
	m_bShowBag = true;

	clearEquipment();

	vector<StrengGoodsVo*> armorInfos;		//防具
	vector<StrengGoodsVo*> weaponInfos;		//武器
	StrengGoods* strengGoodsFirst = 0;

	std::map<int32, GoodsInfo*>::iterator it;
	for ( std::map<int32, GoodsInfo*>::iterator it = bagDictionary->begin(); it != bagDictionary->end(); it++ )
	{
		GoodsInfo* goodsInfo = it->second;
		if( goodsInfo->type != 2 || goodsInfo->equip_type == 7 )	//装备碎片 和 品质在紫色以下的装备不能魔化
			continue;

		StrengGoodsVo* pStrengGoodsVo =  StrengManage::Instance()->returnStrengGoodsVo( goodsInfo,
			goodsInfo->sitGrid, RoleManage::Instance()->accountInfo()->roleId );
		if( goodsInfo->equip_type==5 )
		{
			weaponInfos.push_back( pStrengGoodsVo );	
		}
		else
		{
			armorInfos.push_back( pStrengGoodsVo );						
		}
	}
	
	int iSize = weaponInfos.size();
	for ( int i = 0; i < iSize-1; i++ )		//weaponInfos.sortOn(["quality"], [Array.DESCENDING]);
	{
		for ( int j = 0; j < iSize-i-1; j++ )
		{
			if ( weaponInfos[j]->quality > weaponInfos[j+1]->quality )
			{
				StrengGoodsVo* temp = weaponInfos[j];
				weaponInfos[j] = weaponInfos[j+1];
				weaponInfos[j+1] = temp;
			}

		}		
	}

	iSize = armorInfos.size();
	for ( int i = 0; i < iSize-1; i++ )			//armorInfos.sortOn(["quality"], [Array.DESCENDING]);
	{
		for ( int j = 0; j < iSize-i-1; j++ )
		{
			if ( armorInfos[j]->quality > armorInfos[j+1]->quality )
			{
				StrengGoodsVo* temp = armorInfos[j];
				armorInfos[j] = armorInfos[j+1];
				armorInfos[j+1] = temp;
			}

		}		
	}
	
	for ( int i = 0; i < iSize; i++ )	//var arr:Array = weaponInfos.concat(armorInfos);
	{
		weaponInfos.push_back( armorInfos[i] );
	}

	int i = 0;
	int sitNum = 0;
	int startNum = 0;
	for ( vector<StrengGoodsVo*>::iterator itGoodsVo = weaponInfos.begin(); itGoodsVo != weaponInfos.end(); itGoodsVo++ )
	{
		StrengGoodsVo* strengGoodsVo = weaponInfos[i];
		//if( i>=startNum && sitNum<=4 )
		{
			GoodsInfo* pGoodsInfo = strengGoodsVo->StrengGoodsInfo;
			if(!pGoodsInfo)
				continue;

			int index(0);
			if ( pGoodsInfo )
			{
				index = strengGoodsVo->StrengGoodsInfo->id;
			}

			std::map<int, StrengGoods*>::iterator it = _goodsDic.find( index );
			if ( it == _goodsDic.end() )
			{
				CCRect rect( POSX(15 + (sitNum%2)*250),
					POSX(285 - (sitNum/2)*135),  StrengGoodSize.width, StrengGoodSize.height );
				StrengGoods* strengGoods = StrengGoods::StrengGoodsWithRect( rect );
				strengGoods->initStrengGoodsVo( strengGoodsVo, sitNum );
				//strengGoods->retain();
				_listViewItemsList.push_back( strengGoods );

				_goodsDic.insert( make_pair(index, strengGoods) );

				if (sitNum == 0)
				{
					strengGoodsFirst = strengGoods;
				}				
			}

			struct sdata
			{
				int UseType;
				StrengGoodsVo* sdataStrengGoodsVo;
			};
			sdata s;
			// reget dynamic 
			if( pGoodsInfo->id != 0 )
			{
				s.UseType = 1;	// {UseType:1/* 1 get dynamic info*/
				s.sdataStrengGoodsVo = strengGoodsVo;
				GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::SHOW_STRENG_CLICK, &s );
			}

			if(sitNum==0)
			{
				s.UseType = 6;	// {UseType:6/* 6 click get info */
				s.sdataStrengGoodsVo = strengGoodsVo;
				GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::SHOW_STRENG_CLICK, &s );
			}

			sitNum++;
		}
		//else
		//{
		//	CC_SAFE_DELETE(strengGoodsVo);
		//}
		i++;
	}
	
	//add new list
	CCSize listSize = CCSizeMake(POSX(320), POSX(381));
	CCRect listRect = CCRectMake(POSX(16),
		POSX(29),
		listSize.width,
		listSize.height );
	if(!_magicCreate)
	{
		_magicCreate = CCUIListView::listViewWithCCRect(listRect, false);
		_magicCreate->setAnchorPoint(CCPointZero);
		//_magicCreate->setHeaderSize( POSX(13.0f) );
		_magicCreate->setSpacingVertical(POSX(8));

		_magicCreate->setWorldSpaceLeftBottomPoint(ccp(this->getParent()->getPosition().x + this->getPosition().x + _bgEquip->getPosition().x + listRect.origin.x, 
			this->getParent()->getPosition().y + this->getPosition().y + _bgEquip->getPosition().y + listRect.origin.y));

		_magicCreate->setOnItemActionListener(this);
		_bgEquip->addChild(_magicCreate);
		_magicCreate->release();
	}
	_magicCreate->setAdapter(this);
	
	if (!m_selectedSpriteImage)
	{
		if ( strengGoodsFirst )
		{
			m_selectedSpriteImage = new CCUIBackground();
			m_selectedSpriteImage->initWithSpriteFrame( "train/gold_back.png",
				ccp(0, POSX(2)), CCPointZero, StrengGoodSize );
			strengGoodsFirst->addChild( m_selectedSpriteImage );
			m_selectedSpriteImage->release();
		}
	}
}
		
/**
* 查看装备具体信息
* @param id
* @param goodID
*/		
void MagicPanel::viewEquipmentInfo( int id, int goodID )
{
	_curId = id;
	_curGoodsId = goodID;

	GoodsBasic* goodsBasic = g_pGoodsManager->getBasicGood( goodID );

	GoodsDynamic* goodsDynamic = g_pGoodsDynamicManager->getGoodsDynamic( id );
	if( !goodsBasic|| !goodsDynamic )	return;
		
	_curMagicGoods = getStrengGoods(id);

	//setHightLine(id);

	if( _curMagicGoods && _curMagicGoods->_equpInfo->StrengGoodsInfo->id == id )
	{
	//	_curMagicGoods.updateStrength(goodsDynamic.e_strengthen);

		if ( _equipName )
		{
			ccColor3B textColor = ColorUtil::getGoodColor( goodsBasic->quality );
			_equipName->setString( goodsBasic->goodName.c_str() );
			_equipName->setColor( textColor );
		}

		if ( _pic )
		{
			_pic->removeFromParentAndCleanup(true);
			_pic = 0;
		}
		
		if ( !_pic && _fangkuang )
		{
			char txtmp[54];
			sprintf( txtmp, "assets/icon/goods/%d.png",goodsBasic->goodId );
			_pic = new CCSprite;
			if ( _pic && _pic->initWithFile(txtmp) )
			{
				_pic->setAnchorPoint(CCPointZero);
				_pic->setPosition(ccp(POSX(14), POSX(20)));
				_fangkuang->addChild(_pic);
				_pic->release();
			}			
		}
		
		viewEquipmentDynamicInfo(goodsBasic, goodsDynamic);
	}
}		
		
/**
* 显示装备属性动态信息
* @param id
* @param goodID
*/		
void MagicPanel::viewEquipmentDynamicInfo( GoodsBasic* goodsBasic, GoodsDynamic* goodsDynamic )
{
	if ( !_MagicItem || !_btnMagic )
	{
		return;
	}
	
	_btnMagic->setIsVisible(true);
	if( goodsBasic->quality < 4 )
	{
		if ( _attribute1 )
		{
			_attribute1->setString("     -");
			_attribute2->setString("     -");
			_attribute3->setString("     -");
			_costText->setString( LangManager::getText("STG084").c_str() );

			_MagicItem->setIsEnabled(false);
		}		
	}
	else
	{
		MagicLimitVo* magicLimit = MagicManage::Instance()->getMagicLimit( goodsBasic->equip_type, goodsBasic->level, goodsBasic->quality );
		if( !magicLimit )	return;

		int needLev = magicLimit->crystalLev;
		if( _magicLev < needLev )
		{
			_attribute1->setString("     -");
			_attribute2->setString("     -");
			_attribute3->setString("     -");

			char tmp[128];
			sprintf( tmp, LangManager::getText("STG085").c_str(),
				equiTypeArr[goodsBasic->equip_type].c_str(), needLev );
			_costText->setString( tmp );

			_MagicItem->setIsEnabled(false);
		}
		else
		{
			int staminaLimit = magicLimit->stamina;
			int wristLimit = magicLimit->wrist;
			int intellectLimit = magicLimit->intellect;

			if(staminaLimit == 0){//体格
				_attribute1->setString("     -");
			}else{
				char tmp[54];
				sprintf(tmp, LangManager::getText("PHYSIQUEADD").c_str(), goodsDynamic->u_stamina);
				string str1 = goodsDynamic->u_stamina < staminaLimit ? "":LangManager::getText("STG086");
				string artri_str = tmp + str1;
				_attribute1->setString(artri_str.c_str());
			}
			if(wristLimit == 0){//腕力
				_attribute2->setString("     -");
			}else{
				char tmp[54];
				sprintf(tmp, LangManager::getText("WRISTADD").c_str(), goodsDynamic->v_wrist);
				string str1 = goodsDynamic->v_wrist < wristLimit ? "":LangManager::getText("STG086");
				string artri_str = tmp + str1;
				_attribute2->setString(artri_str.c_str());
			}
			if(intellectLimit == 0){//智力
				_attribute3->setString("     -");
			}else{
				char tmp[54];
				sprintf(tmp, LangManager::getText("INTELLIGENCEADD").c_str(), goodsDynamic->w_intellect);
				string str1 = goodsDynamic->w_intellect < intellectLimit ? "":LangManager::getText("STG086");
				string artri_str = tmp + str1;
				_attribute3->setString(artri_str.c_str());
			}

			//计算花费
			int attrs = goodsDynamic->u_stamina + goodsDynamic->v_wrist + goodsDynamic->w_intellect;//总属性
			int cost = 20000 + attrs * 700;//花费
			if( attrs < staminaLimit + wristLimit + intellectLimit )
			{
				_costText->setString( LangManager::getText("STG087", cost).c_str() );
				_MagicItem->setIsEnabled(true);
			}
			else
			{
				_costText->setString(LangManager::getText("STG029").c_str());

				_MagicItem->setIsEnabled(false);
			}
		}
	}
}
		
/**
* vip等级 
* @param lev
*/		
void MagicPanel::roleVipLev( int lev )
{
	_roleVipLev = lev;

	if (!_comCheckBox)
	{
		return;
	}	
	//if(_roleVipLev < 3){
	//	_comCheckBox->setIsVisible(false);
	//}else{
	//	_comCheckBox->setIsVisible(true);
	//}
}
		
/**
* 命之水晶等级 
* @param lev
*/		
void MagicPanel::crystalLev( int lev )
{
	if(lev ==0)
	{//如果魔之水晶的等级为0（即没开启），按1级计算
		lev = 1;
	}
	_magicLev = lev;
}
		
/**
* 更新魔晶石信息（数量） 
* @param num
*/	
void MagicPanel::updateSparInfo( int num )
{
	_sparInfo->setString(LangManager::getText("STG071", num).c_str());
	_sparNum = num;
}
		
/**
* 更新物品ToolTip 
* @param id 物品唯一ID
*/
void MagicPanel::updateTip( uint id )
{
//	_magicCreate->updateTip(id);
	if( _curMagicGoods && _curMagicGoods->_equpInfo )
	{
		GoodsInfo* info = _curMagicGoods->_equpInfo->StrengGoodsInfo;
		if ( info->id == id )
		{
			GoodsDynamic* goodsDynamic = g_pGoodsDynamicManager->getGoodsDynamic( id );
			viewEquipmentInfo( goodsDynamic->a_id, goodsDynamic->b_goodID );
		}
	}
}

/**
* 播放动画
*/		
/*public function playEffect():void{
var pid:int = setTimeout(delayFunction, 300);
function delayFunction():void{
clearTimeout(pid);
_ef1.visible = true;
_ef2.visible = true;
_ef1.gotoAndPlay(1);
_ef1.addEventListener(Event.ENTER_FRAME, onEnterFrame);
_ef2.gotoAndPlay(1);
_ef2.addEventListener(Event.ENTER_FRAME, onEnterFrame);
}
}
private function onEnterFrame(e:Event):void{
	if(e.target.currentFrame >= e.target.totalFrames){
		e.target.removeEventListener(Event.ENTER_FRAME, onEnterFrame);
		e.target.visible = false;
		e.target.gotoAndStop(1);
	}
}

*/			
/**
* 清理
*/		
void MagicPanel::clear()
{
	_equipName->setString("");
	if( _curMagicGoods )
	{
		_costText->setString("");
		_attribute1->setString("");
		_attribute2->setString("");
		_attribute3->setString("");
		if ( _pic && _pic->getParent() )
		{
			_pic->removeFromParentAndCleanup(true);
			_pic = 0;
		}
		
		_curMagicGoods = 0;
	}
}

FigureItem* MagicPanel::figureItem()
{
	return _item;
}

/** ------------------------------------------------------ 按钮相关事件 ------------------------------------------------------ **/
/**
* 选中某个角色 
* @param e
* 
*/		
void MagicPanel::figureSelectHandler( FigureItem* item )
{
	if ( item == _item )
	{
		return;
	}
	
	clear();

	//if(_item)
	//{
	//	_item.setHightLine(false);
	//}
	_item = item;
			
	if(_item)
	{
		//_item.setHightLine(true);
		//this.dispatchEvent(new ParamEvent(FIGURE_CLICK, _item.id ));
		g_pMainStrengMediator->figureClickHandler( _item->id() );
	}
}


void MagicPanel::bagClickHandler( CCObject* pSender )
{
	if( _item )
	{
		_item = 0;
	}

	g_pMainStrengMediator->figureClickHandler( 0 );
}

void MagicPanel::gridClickHandler( CCObject* pSender )
{
	if ( !_gridSelect )
	{
		return;
	}
	
	_gridSelect->setIsVisible( !_gridSelect->getIsVisible() );
}

void MagicPanel::onClickHandler( CCObject* pSender )
{
	if( !_curMagicGoods )
	{
		return;
	}
	StrengGoodsVo* info = _curMagicGoods->_equpInfo;
	////			if(info.StrengGoodsInfo.equip_type != 5){
	////				Message.show("只有武器才能魔化");
	////				return;
	////			}
	if(_sparNum == 0){
		LangManager::msgShow("STG088");
		return;
	}
	int vip =_gridSelect->getIsVisible() ? 3 : 0;

	struct sdata
	{
		int type;
		int sit;
		int id;
		int vip;
	} s;
	if( info->type == 1 )
	{
		//_dispatcher.dispatchEvent(new ParamEvent(GameDispatcher.MAGIC_REQUEST,
		//{type:info.type,sit:info.sitGrid,id:info.StrengGoodsInfo.id,vip:vip}));
		s.type = info->type;
		s.sit = info->sitGrid;
		s.id = info->StrengGoodsInfo->id;
		s.vip = vip;
		//var vip:int = _comCheckBox.selected ? 3 : 0;
		GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::MAGIC_REQUEST, &s );
	}
	else
	{
		//_dispatcher.dispatchEvent(new ParamEvent(GameDispatcher.MAGIC_REQUEST,
		//{type:info.type,sit:info.sitGrid,id:info.roleId,vip:vip}));
		s.type = info->type;
		s.sit = info->sitGrid;
		s.id = info->roleId;
		s.vip = vip;
		GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::MAGIC_REQUEST, &s );
	}

	if (_MagicItem)
	{
		_MagicItem->setIsEnabled(false);
		CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(MagicPanel::lockBtn),
			this,0.2f,false);
	}
	
}


void MagicPanel::lockBtn(ccTime dt)
{
	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(MagicPanel::lockBtn), this);
	if (_MagicItem)
	{
		_MagicItem->setIsEnabled(true);
	}
}


void MagicPanel::directClickHandler( CCObject* pObj )
{
	_figureCreate->moveToPreviousPageClick();
}

void MagicPanel::directRightClickHandler( CCObject* pObj )
{
	_figureCreate->moveToNextPageClick();
}