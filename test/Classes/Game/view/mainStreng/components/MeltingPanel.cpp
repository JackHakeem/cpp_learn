#include "MeltingPanel.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "MeltingBagCreate.h"
#include "model/com/vo/GoodsDynamic.h"
#include "model/com/GoodsDynamicManager.h"
#include "utils/ValuesUtil.h"
#include "MeltingBagGoods.h"
#include "model/backpack/GoodsManager.h"
#include "Message.h"
#include "MainStrengView.h"
#include "events/GameDispatcher.h"
#include "../MainStrengMediator.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"
#include "manager/TouchLayerEnum.h"
#include "manager/LangManager.h"
#include "MeltingTips.h"
#include "manager/LayerManager.h"
#include "Confirm.h"
#include "model/streng/StrengManage.h"

static const int Tag_Pic1 = 100;
static const int Tag_Pic2 = 101;
static const int Tag_Pic3 = 102;

MeltingPanel::MeltingPanel()
{
	_goodsInfo1 = 0;
	_goodsInfo2 = 0;
	_goodsInfo3 = 0;
	_sit1 = 0;
	_sit2 = 0;
	_sit3 = 0;
	_goodsId1 = 0;
	_goodsId2 = 0;
	_goodsId3 = 0;

	_sparInfo = 0;

	_roleVipLev = 1;
	_crystalLev = 1;
	_goldNum = 0;
	_materialsNum = 0;
	_curPage = 1;
	
	bagCreate = 0;

	_sparNumText = 0;
	_rateText = 0;
	_meltingBtn = 0;

	_bagProp = 0;

	_vipLevel = 0;

	m_canGetSpar = 0;
	m_canGetExtraSpar = 0;
	m_returnPrice = 0;
}

MeltingPanel::~MeltingPanel()
{

}

bool MeltingPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	this->setPosition( ccp(POSX(17), POSX(0)) );
	this->setContentSize( CCSizeMake( POSX(923), POSX(562) ) );
	initView();

	setIsTouchEnabled( true );

	return true;
}


void MeltingPanel::initView()
{
	CCSize size = this->getContentSize();
	ValuesUtil* pValuesUtil = ValuesUtil::Instance();
	
	// equipment background
	_bgEquip = new CCUIBackground();
	_bgEquip->initWithSpriteFrame( "popuibg/bg2.png",
		ccp(POSX(12), POSX(29)), ccp(0,0), CCSizeMake( POSX(346), POSX(504) ) );
	this->addChild( _bgEquip );
	_bgEquip->release();

	// bag explain
	_bagProp = CCLabelTTF::labelWithString( pValuesUtil->getString( "MelBag" ).c_str(),
		CCSizeMake( POSX(135), POSX(23) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(24) );
	_bagProp->setAnchorPoint(CCPointZero);
	_bagProp->setColor(  ccWHITE  );
	_bagProp->setPosition( ccp(POSX(115), POSX(460) ) );
	_bgEquip->addChild( _bagProp );

	CCSprite* pLine = new CCSprite;
	if (pLine && pLine->initWithSpriteFrameName("streng/line.png"))
	{
		pLine->setAnchorPoint(CCPointZero);
		pLine->setPosition( ccp(POSX(21), POSX(441)) );
		_bgEquip->addChild(pLine);
		pLine->release();
	}
	
	// equipment info background
	_bgEquipInfo = new CCUIBackground();
	_bgEquipInfo->initWithSpriteFrame( "popuibg/bg2.png",
		ccp(POSX(365), POSX(29)), ccp(0,0), CCSizeMake( POSX(543), POSX(504) ) );
	this->addChild( _bgEquipInfo );
	_bgEquipInfo->release();

	CCSprite* pMeltingBg = new CCSprite;
	if (pMeltingBg && pMeltingBg->initWithSpriteFrameName("streng/jiaqiang.png"))
	{
		pMeltingBg->setAnchorPoint(CCPointZero);
		pMeltingBg->setPosition( ccp(POSX(32), POSX(55)) );
		_bgEquipInfo->addChild(pMeltingBg);
		pMeltingBg->release();
	}

	CCSprite* pSparSp = new CCSprite;
	if ( pSparSp && pSparSp->initWithSpriteFrameName("streng/stone.png") )
	{
		pSparSp->setAnchorPoint(CCPointZero);
		pSparSp->setPosition(ccp(POSX(5), POSX(461)));
		_bgEquipInfo->addChild(pSparSp);
		pSparSp->release();
	}

	_sparInfo = CCLabelTTF::labelWithString( "",
		CCSizeMake( POSX(206), POSX(24) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(24) );
	_sparInfo->setAnchorPoint(CCPointZero);
	_sparInfo->setColor(  ccWHITE  );
	_sparInfo->setPosition( ccp(POSX(55), POSX(465) ) );
	_bgEquipInfo->addChild( _sparInfo );

	_sparNumText = CCLabelTTF::labelWithString( "",
		CCSizeMake( POSX(219), POSX(24) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(22) );
	_sparNumText->setAnchorPoint(CCPointZero);
	_sparNumText->setColor(  ccc3( 238, 192, 64 )  );
	_sparNumText->setPosition( ccp(POSX(157), POSX(239) ) );
	_bgEquipInfo->addChild( _sparNumText);
	
	_rateText = CCLabelTTF::labelWithString( "",
		CCSizeMake( POSX(317), POSX(25) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(22) );
	_rateText->setAnchorPoint(CCPointZero);
	_rateText->setColor(  ccc3( 254, 155, 117 )  );
	_rateText->setPosition( ccp(POSX(108), POSX(147) ) );
	_bgEquipInfo->addChild( _rateText );


	// btn
	CCSize csBt( POSX(121), POSX(49) );
	{
		{
			CCMenuItemSprite *pItem = CCMenuItemSprite::itemFromNormalSprite(
				CCSprite::spriteWithSpriteFrameName("button.png"),
				CCSprite::spriteWithSpriteFrameName("button1.png"),
				this,
				menu_selector(MeltingPanel::meltingHandler) );
			pItem->setPosition( ccp( POSX(221)+csBt.width/2, POSX(95)+csBt.height/2 ) );
			_meltingBtn = CCMenu::menuWithItems( pItem, 0 );
			_meltingBtn->setTouchLayer( TLE::WindowLayer_Common_btn );
			_meltingBtn->setPosition( CCPointZero );
			_bgEquipInfo->addChild( _meltingBtn, 10 );
			string txt = pValuesUtil->getString( "MelClick" );
			CCLabelTTF* txtLabel = CCLabelTTF::labelWithString( txt.c_str(), csBt, CCTextAlignmentCenter, g_sSimHeiFont, POSX(20) );
			txtLabel->setPosition( ccp( csBt.width/2, csBt.height/2 ) );
			pItem->addChild( txtLabel );
		}
		
	}


	// help btn
	{
		{
			CCMenuItemSprite *pItem = CCMenuItemSprite::itemFromNormalSprite(
				CCSprite::spriteWithSpriteFrameName("button.png"),
				CCSprite::spriteWithSpriteFrameName("button1.png"),
				this,
				menu_selector(MeltingPanel::meltingHelpHandler) );
			pItem->setPosition( ccp( POSX(431-50)+csBt.width/2, POSX(443)+csBt.height/2 ) );
			CCMenu* helpBtn = CCMenu::menuWithItems( pItem, 0 );
			helpBtn->setTouchLayer( TLE::WindowLayer_Common_btn );
			helpBtn->setPosition( CCPointZero );
			_bgEquipInfo->addChild( helpBtn, 10 );
			string txt = pValuesUtil->getString( "STG104" );
			CCLabelTTF* txtLabel = CCLabelTTF::labelWithString( txt.c_str(),
				csBt, CCTextAlignmentCenter, g_sSimHeiFont, POSX(20) );
			txtLabel->setPosition( ccp( csBt.width/2, csBt.height/2 ) );
			pItem->addChild( txtLabel );
		}

	}


	// grid1 image btn
	CCSprite* pNormal = CCSprite::spriteWithSpriteFrameName("streng/grid.png");
	CCSprite* pPress = CCSprite::spriteWithSpriteFrameName("streng/grid.png");
	CCMenuItemSprite *pGridItem = cocos2d::CCMenuItemImage::itemFromNormalSprite(
		pNormal,
		pPress,
		this,
		menu_selector(MeltingPanel::grid1ClickHandler) );
	pGridItem->setPosition( ccp(POSX(5+39/2), POSX(11+39/2)) );
	_menuGrid1 = CCMenu::menuWithItems(pGridItem, 0);
	_menuGrid1->setTouchLayer( TLE::WindowLayer_Common_btn );
	_menuGrid1->setPosition( CCPointZero );
	_bgEquipInfo->addChild( _menuGrid1 );
	//select
	_gridSelect1 = new CCSprite;
	if (_gridSelect1 && _gridSelect1->initWithSpriteFrameName("streng/select.png"))
	{
		_gridSelect1->setAnchorPoint(CCPointZero);
		_gridSelect1->setPosition(ccp(POSX(1), POSX(11)));
		_bgEquipInfo->addChild(_gridSelect1);
		_gridSelect1->release();
		_gridSelect1->setIsVisible(false);
	}

	_radioText1 = CCLabelTTF::labelWithString( LangManager::getText("STG063", 15).c_str(),
		CCSizeMake( POSX(172), POSX(21) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );
	_radioText1->setAnchorPoint(CCPointZero);
	_radioText1->setColor(  ccYELLOW  );
	_radioText1->setPosition( ccp(POSX(40), POSX(17) ) );
	_bgEquipInfo->addChild( _radioText1 );

	// grid2 image btn
	pNormal = CCSprite::spriteWithSpriteFrameName("streng/grid.png");
	pPress = CCSprite::spriteWithSpriteFrameName("streng/grid.png");
	pGridItem = cocos2d::CCMenuItemImage::itemFromNormalSprite(
		pNormal,
		pPress,
		this,
		menu_selector(MeltingPanel::grid2ClickHandler) );
	pGridItem->setPosition( ccp(POSX(181+39/2), POSX(11+39/2)) );
	_menuGrid2 = CCMenu::menuWithItems(pGridItem, 0);
	_menuGrid2->setTouchLayer( TLE::WindowLayer_Common_btn );
	_menuGrid2->setPosition( CCPointZero );
	_bgEquipInfo->addChild( _menuGrid2 );
	//select
	_gridSelect2 = new CCSprite;
	if (_gridSelect2 && _gridSelect2->initWithSpriteFrameName("streng/select.png"))
	{
		_gridSelect2->setAnchorPoint(CCPointZero);
		_gridSelect2->setPosition(ccp(POSX(181), POSX(11)));
		_bgEquipInfo->addChild(_gridSelect2);
		_gridSelect2->release();
		_gridSelect2->setIsVisible(false);
	}

	_radioText2 = CCLabelTTF::labelWithString(LangManager::getText("STG064", 30).c_str(),
		CCSizeMake( POSX(172), POSX(21) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );
	_radioText2->setAnchorPoint(CCPointZero);
	_radioText2->setColor(  ccYELLOW  );
	_radioText2->setPosition( ccp(POSX(220), POSX(17) ) );
	_bgEquipInfo->addChild( _radioText2 );

	// grid3 image btn
	pNormal = CCSprite::spriteWithSpriteFrameName("streng/grid.png");
	pPress = CCSprite::spriteWithSpriteFrameName("streng/grid.png");
	pGridItem = cocos2d::CCMenuItemImage::itemFromNormalSprite(
		pNormal,
		pPress,
		this,
		menu_selector(MeltingPanel::grid3ClickHandler) );
	pGridItem->setPosition( ccp(POSX(352+39/2), POSX(11+39/2)) );
	_menuGrid3 = CCMenu::menuWithItems(pGridItem, 0);
	_menuGrid3->setTouchLayer( TLE::WindowLayer_Common_btn );
	_menuGrid3->setPosition( CCPointZero );
	_bgEquipInfo->addChild( _menuGrid3 );
	//select
	_gridSelect3 = new CCSprite;
	if (_gridSelect3->initWithSpriteFrameName("streng/select.png"))
	{
		_gridSelect3->setAnchorPoint(CCPointZero);
		_gridSelect3->setPosition(ccp(POSX(352), POSX(11)));
		_bgEquipInfo->addChild(_gridSelect3);
		_gridSelect3->release();
		_gridSelect3->setIsVisible(false);
	}

	_radioText3 = CCLabelTTF::labelWithString( LangManager::getText("STG065", 75).c_str(),
		CCSizeMake( POSX(172), POSX(21) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );
	_radioText3->setAnchorPoint(CCPointZero);
	_radioText3->setColor(  ccYELLOW  );
	_radioText3->setPosition( ccp(POSX(390), POSX(17) ) );
	_bgEquipInfo->addChild( _radioText3 );
	
	CCSize bagSize = this->getContentSize();
	bagCreate = MeltingBagCreate::node();
	bagCreate->setContentSize( bagSize );
	this->addChild( bagCreate );
	//bagCreate->release(); //LH20120108
}

void MeltingPanel::grid1ClickHandler(CCObject * obj)
{
	if (_gridSelect1)
	{
		_gridSelect1->setIsVisible(!_gridSelect1->getIsVisible());

		if(_gridSelect1->getIsVisible()){
			_vipLevel = 3;						
		}else{
			_vipLevel = 0;
		}
	}
	_gridSelect2->setIsVisible(false);
	_gridSelect3->setIsVisible(false);

	if(_materialsNum == 3){
		updateRate(_goodsId1,_goodsId2,_goodsId3,_vipLevel);
	}
}
void MeltingPanel::grid2ClickHandler(CCObject * obj)
{

	if (_gridSelect2)
	{
		_gridSelect2->setIsVisible(!_gridSelect2->getIsVisible());

		if(_gridSelect2->getIsVisible()){
			_vipLevel = 5;						
		}else{
			_vipLevel = 0;
		}
	}
	_gridSelect1->setIsVisible(false);
	_gridSelect3->setIsVisible(false);

	if(_materialsNum == 3){
		updateRate(_goodsId1,_goodsId2,_goodsId3,_vipLevel);
	}
}
void MeltingPanel::grid3ClickHandler(CCObject * obj)
{
	if (_gridSelect3)
	{
		_gridSelect3->setIsVisible(!_gridSelect3->getIsVisible());

		if(_gridSelect3->getIsVisible()){
			_vipLevel = 7;						
		}else{
			_vipLevel = 0;
		}
	}

	_gridSelect1->setIsVisible(false);
	_gridSelect2->setIsVisible(false);

	if(_materialsNum == 3){
		updateRate(_goodsId1,_goodsId2,_goodsId3,_vipLevel);
	}
}

/**
* createMeltingList array
* @param goodDic
*/
void MeltingPanel::createMeltingList( std::map<int32, GoodsInfo*> goodDic )
{
	std::map<int32, GoodsInfo*>::iterator it = goodDic.begin();
	_goodsArr.clear();
	for ( ; it != goodDic.end(); it++ )
	{
		GoodsInfo* goodsInfo = it->second;
		// pass through is not equipment, is not piece, quality worse than Zise
		if(  !( (goodsInfo->type == 2) || (goodsInfo->type == 3) )  )
		{
			continue;		
		}
		if (  (goodsInfo->quality < 4) || (goodsInfo->equip_type == 7)  )
		{
			continue;	
		}
		// pass through strengthen or magiced equipment
		if( goodsInfo->type == 2 && g_pGoodsDynamicManager )
		{
			GoodsDynamic* goodsDynamic = g_pGoodsDynamicManager->getGoodsDynamic( goodsInfo->id );
			//if(  goodsDynamic->e_strengthen > 0  )
			//{
			//	continue;	
			//}
			if ( ( goodsDynamic->u_stamina + goodsDynamic->v_wrist + goodsDynamic->w_intellect ) > 0 )
			{
				continue;	
			}
		}
		 
		_goodsArr.push_back( goodsInfo );
	}

	createBagList( 1 );
}
/**
*  createBagList
* @param goodDic
* 
*/		
void MeltingPanel::createBagList( int page )
{
	_curPage = page;
	bagCreate->createMeltingBag( _goodsArr,_curPage );
}
		

		
/**
	* double clicked¡¢draged Grid 
	* @param goods
	* @param sitNum
	* 
	*/		
void MeltingPanel::dragGrid( GoodsInfo* info, int sitNum, int page, int type )
{
	if( !info )	return;
	//MeltingBagGoods* good = bagCreate->getMeltingGoods( sitNum + (page -1)*24 );
	//if( !good )	return;

	CCSprite* pSprite = 0;
	char tmp[128];
	sprintf( tmp, "assets/icon/goods/%d.png", info->goodId );

	switch(type)
	{
		case 0: // drag to place outside grid
			{
				if( _materialsNum == 3 )
				{
					LangManager::msgShow("STG067");
					return;
				}

				pSprite = new CCSprite;
				if ( pSprite && pSprite->initWithFile(tmp))
				{
					pSprite->setAnchorPoint(CCPointZero);
					_bgEquipInfo->addChild(pSprite);
					pSprite->release();
				}

				if( !_goodsInfo1 )
				{
					pSprite->setPosition(ccp(POSX(218+8), POSX(369+12)));
					pSprite->setTag(Tag_Pic1);

					bagCreate->updateGoods( info, sitNum, page, 2 );
					_goodsInfo1 = info;
					_goodsId1 = info->id;
					_sit1 = sitNum;
					_page1 = page;
					_materialsNum++;
				}
				else if( !_goodsInfo2 ) 
				{
					pSprite->setPosition(ccp(POSX(108+8), POSX(290+12)));
					pSprite->setTag(Tag_Pic2);

					bagCreate->updateGoods( info, sitNum, page, 2 );
					_goodsInfo2 = info;
					_goodsId2 = info->id;
					_sit2 = sitNum;
					_page2 = page;
					_materialsNum++;
				}
				else
				{
					pSprite->setPosition(ccp(POSX(322+8), POSX(290+12)));
					pSprite->setTag(Tag_Pic3);

					bagCreate->updateGoods( info, sitNum, page, 2 );
					_goodsInfo3 = info;
					_goodsId3 = info->id;
					_sit3 = sitNum;
					_page3 = page;
					_materialsNum++;
				}

			}
			break;
	}
	if(_materialsNum == 3)
	{
		updateRate( _goodsId1,_goodsId2,_goodsId3,_roleVipLev );
	}
			
}
		
/**
* updateTip
* @param mc
* @param id
* @param goodsId
* 
*/		
//void MeltingPanel::updateTip( mc:MovieClip, GoodsInfo* info,TipHelps* tip )
//{
//	if(mc.numChildren > 0){
//		if(info.type == 2){
//			var myBasic:GoodsBasic = GoodsManager.getInstance().getBasicGood(info.goodId);
//			var myDynamic:GoodsDynamic = GoodsDynamicManager.getInstance().getGoodsDynamic(info.id);
//			tip.setToolTips(mc,GoodsToolTips.getGoodsTooltips(myBasic,myDynamic));
//		}
//		if(info.type == 3){
//			tip.setToolTips(mc,info.explain);
//		}
//	}
//}

/**
	* updateRate 
	* @param id1
	* @param id2
	* @param id3
	* @param vip
	* 
	*/		
void MeltingPanel::updateRate( int id1, int id2, int id3, int vip/* = 0*/ )
{
	if( _materialsNum != 3 || !g_pGoodsManager
		|| !_goodsInfo1 || !_goodsInfo2 || !_goodsInfo3 )
	{
		return;
	}
	GoodsBasic* goods1 = g_pGoodsManager->getBasicGood( _goodsInfo1->goodId );
	GoodsBasic* goods2 = g_pGoodsManager->getBasicGood( _goodsInfo2->goodId );
	GoodsBasic* goods3 = g_pGoodsManager->getBasicGood( _goodsInfo3->goodId );
	if ( !goods1 || !goods2 || !goods3 )
	{
		return;
	}
	int rate1 = goods1->enchant_Rate;
	int rate2 = goods2->enchant_Rate;
	int rate3 = goods3->enchant_Rate;
	//int vipRate  = VipManager.getInstance().getVipContent(21,vip).info1;
	int vipRate( 0 );
	if (vip==3)
	{
		vipRate = 35;
	}
	else if (vip==5)
	{
		vipRate = 75;
	}
	else if (vip==7)
	{
		vipRate = 140;
	}
	
	m_canGetSpar = ( rate1 + rate2 + rate3 + vipRate ) / 100;
	m_canGetExtraSpar = m_canGetSpar+1;
	int extra = ( rate1 + rate2 + rate3 + vipRate ) % 100;

	m_returnPrice = 0;
	GoodsDynamic* goodsDynamic1 = g_pGoodsDynamicManager->getGoodsDynamic( _goodsInfo1->id );
	if (goodsDynamic1)
	{
		m_returnPrice += StrengManage::Instance()->getGoodsUpStrengpriceToLv(_goodsInfo1->goodId, goodsDynamic1->e_strengthen);
	}	
	GoodsDynamic* goodsDynamic2 = g_pGoodsDynamicManager->getGoodsDynamic( _goodsInfo2->id );
	if (goodsDynamic2)
	{
		m_returnPrice += StrengManage::Instance()->getGoodsUpStrengpriceToLv(_goodsInfo2->goodId, goodsDynamic2->e_strengthen);
	}
	GoodsDynamic* goodsDynamic3 = g_pGoodsDynamicManager->getGoodsDynamic( _goodsInfo3->id );
	if (goodsDynamic3)
	{
		m_returnPrice += StrengManage::Instance()->getGoodsUpStrengpriceToLv(_goodsInfo3->goodId, goodsDynamic3->e_strengthen);
	}	

	ValuesUtil* pValuesUtil = ValuesUtil::Instance();
	char txt[128];
	if( m_canGetSpar != 0 )
	{
		if( extra != 0 )
		{
			sprintf( txt, pValuesUtil->getString("STG071").c_str(), m_canGetSpar );
			_sparNumText->setString(txt);
			sprintf( txt, pValuesUtil->getString("MelRate").c_str(), extra );
			_rateText->setString(txt);
		}
	}
	else
	{
		_sparNumText->setString("");
		sprintf( txt, pValuesUtil->getString("STG070").c_str(), extra );
		_rateText->setString(txt);
	}
			
}
/**
* ²¥·ÅÈÛÁ¶¶¯»­ 
* 
*/		
//void playEffect()
//{
//	var pid:int = setTimeout(delayFunction, 50);
//	function delayFunction():void{
//		clearTimeout(pid);
//		_ef.visible = true;
//		_ef.gotoAndPlay(1);
//		_ef.addEventListener(Event.ENTER_FRAME, onEnterFrame);
//	}
//}
		
//private function onEnterFrame(e:Event):void{
//	if(e.target.currentFrame >= e.target.totalFrames){
//		e.target.removeEventListener(Event.ENTER_FRAME, onEnterFrame);
//		e.target.visible = false;
//		e.target.gotoAndStop(1);
//	}
//}
		
/**
* show spar info£¨count£©
* @param num
*/		
void MeltingPanel::updateSparInfo( int num )
{
	//_sparInfo.text = LangManager.getText("STG071",num);
	//char txt[20];
	//sprintf( txt, ValuesUtil::Instance()->getString( "STG071" ).c_str(), num );
	_sparInfo->setString( LangManager::getText("STG071",num).c_str() );
	_sparNum = num;
}
		
/**
	* roleVipLev
	* @param lev
	* 
	*/		
void MeltingPanel::roleVipLev( int lev )
{
	_roleVipLev = lev;
	if(_roleVipLev < 3){
		_menuGrid1->setIsVisible(false);
		_menuGrid2->setIsVisible(false);
		_menuGrid3->setIsVisible(false);
		_radioText1->setIsVisible(false);
		_radioText2->setIsVisible(false);
		_radioText3->setIsVisible(false);
	}else if(_roleVipLev >=3 && _roleVipLev <= 4){
		_menuGrid1->setIsVisible(true);
		_menuGrid2->setIsVisible(false);
		_menuGrid3->setIsVisible(false);
		_radioText1->setIsVisible(true);
		_radioText2->setIsVisible(false);
		_radioText3->setIsVisible(false);
	}else if(_roleVipLev >=5 && _roleVipLev <= 6){
		_menuGrid1->setIsVisible(true);
		_menuGrid2->setIsVisible(true);
		_menuGrid3->setIsVisible(false);
		_radioText1->setIsVisible(true);
		_radioText2->setIsVisible(true);
		_radioText3->setIsVisible(false);
	}else{
		_menuGrid1->setIsVisible(true);
		_menuGrid2->setIsVisible(true);
		_menuGrid3->setIsVisible(true);
		_radioText1->setIsVisible(true);
		_radioText2->setIsVisible(true);
		_radioText3->setIsVisible(true);
	}
}
		
/**
	* clear 
	* 
	*/		
void MeltingPanel::clear()
{
	_materialsNum = 0;
	//_sparNumText.text = "";
	//_rateText.text = "";
	_goodsId1 = 0;
	_goodsId2 = 0;
	_goodsId3 = 0;
	_sit1 = 0;
	_sit2 = 0;
	_sit3 = 0;
	_page1 = 0;
	_page2 = 0;
	_page3 = 0;
	_goodsInfo1 = 0;
	_goodsInfo2 = 0;
	_goodsInfo3 = 0;
	
	if ( _bgEquipInfo )
	{
		CCNode* pic1 = _bgEquipInfo->getChildByTag(Tag_Pic1);
		CCNode* pic2 = _bgEquipInfo->getChildByTag(Tag_Pic2);
		CCNode* pic3 = _bgEquipInfo->getChildByTag(Tag_Pic3);
		if (pic1 && pic1->getParent())
		{
			pic1->removeFromParentAndCleanup(true);
		}
		if (pic2 && pic2->getParent())
		{
			pic2->removeFromParentAndCleanup(true);
		}
		if (pic3 && pic3->getParent())
		{
			pic3->removeFromParentAndCleanup(true);
		}		
	}
}

void MeltingPanel::setIsVisible( bool bIsVisible )
{
	CCNode::setIsVisible( bIsVisible );

	if ( _bgEquipInfo )
	{
		CCNode* pic1 = _bgEquipInfo->getChildByTag(Tag_Pic1);
		CCNode* pic2 = _bgEquipInfo->getChildByTag(Tag_Pic2);
		CCNode* pic3 = _bgEquipInfo->getChildByTag(Tag_Pic3);
		if (pic1 && pic1->getParent())
		{
			pic1->removeFromParentAndCleanup(true);
		}
		if (pic2 && pic2->getParent())
		{
			pic2->removeFromParentAndCleanup(true);
		}
		if (pic3 && pic3->getParent())
		{
			pic3->removeFromParentAndCleanup(true);
		}		
	}

	_goodsInfo1 = 0;
	_goodsInfo2 = 0;
	_goodsInfo3 = 0;
	_sit1 = 0;
	_sit2 = 0;
	_sit3 = 0;
	_goodsId1 = 0;
	_goodsId2 = 0;
	_goodsId3 = 0;
	
	_roleVipLev = 1;
	_crystalLev = 1;
	_goldNum = 0;
	_materialsNum = 0;
	_curPage = 1;
}

void MeltingPanel::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_Common, true);
}

bool MeltingPanel::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{

	MeltingTips* pTips = (MeltingTips*)LayerManager::tipsLayer->getChildByTag(
		TipsLayer::TipsLayerTAG_tipHelpMelting);
	if (pTips)
	{ 
		pTips->removeFromParentAndCleanup(true);
	}


	CCPoint locationInView = pTouch->locationInView( pTouch->view() );
	CCPoint currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	CCNode* pic1 = _bgEquipInfo->getChildByTag(Tag_Pic1);
	CCNode* pic2 = _bgEquipInfo->getChildByTag(Tag_Pic2);
	CCNode* pic3 = _bgEquipInfo->getChildByTag(Tag_Pic3);
	if ( pic1 )
	{
		CCPoint itemPoint = getScreenPos(pic1);
		CCSize itemSize = pic1->getContentSize();
		if ( CCRect::CCRectContainsPoint(CCRectMake(itemPoint.x,itemPoint.y, itemSize.width,itemSize.height), currentTouchPoint) )
		{
			gridClick( 1 );
		}
	}
	if ( pic2 )
	{
		CCPoint itemPoint = getScreenPos(pic2);
		CCSize itemSize = pic2->getContentSize();
		if ( CCRect::CCRectContainsPoint(CCRectMake(itemPoint.x,itemPoint.y, itemSize.width,itemSize.height), currentTouchPoint) )
		{
			gridClick( 2 );
		}
	}
	if ( pic3 )
	{
		CCPoint itemPoint = getScreenPos(pic3);
		CCSize itemSize = pic3->getContentSize();
		if ( CCRect::CCRectContainsPoint(CCRectMake(itemPoint.x,itemPoint.y, itemSize.width,itemSize.height), currentTouchPoint) )
		{
			gridClick( 3 );
		}
	}

	return true;
}


void MeltingPanel::meltingHandler( CCObject* pSender )
{
	Confirm* pConfirm = new Confirm();
	char tmp[128]={0};
	sprintf( tmp, ValuesUtil::Instance()->getString("STG105").c_str(),
		m_canGetSpar, m_canGetExtraSpar, m_returnPrice );
	pConfirm->initWithParam( tmp,
		this, menu_selector(MeltingPanel::meltingOkFunction),
		menu_selector(MeltingPanel::meltingCancelFunction));

	if (LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame))
	{
		LayerManager::windowLayer->removeChildByTag(WindowLayer::WindowLayerTAG_confirmFrame,true);
	}
	LayerManager::windowLayer->addChild(pConfirm,WindowLayer::WindowLayerZ_confirmFrame, WindowLayer::WindowLayerTAG_confirmFrame);
	pConfirm->release();	

	bagCreate->_meltingCreate->setIsTouchEnabled(false);
}

void MeltingPanel::meltingOkFunction(CCObject* dt)
{
	CCNode* pic1 = _bgEquipInfo->getChildByTag(Tag_Pic1);
	CCNode* pic2 = _bgEquipInfo->getChildByTag(Tag_Pic2);
	CCNode* pic3 = _bgEquipInfo->getChildByTag(Tag_Pic3);

	if( pic1 && pic2 && pic3 )
	{
		struct sdata
		{
			int id1;
			int id2;
			int id3;
			int vip;
		} s;
		s.id1 = _goodsId1;
		s.id2 = _goodsId2;
		s.id3 = _goodsId3;
		s.vip = _vipLevel;
		g_pMainStrengMediator->_mainStrengView->dispatchEvent( MainStrengView::MELTING_CLICK, &s );
	}
	else
	{
		LangManager::msgShow("STG072");
		//Message::Instance()->show( ValuesUtil::Instance()->getString("MelFail") );
	}

	if ( CCNode* pNode = LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame) )
	{
		pNode->removeFromParentAndCleanup(true);
	}
	bagCreate->_meltingCreate->setIsTouchEnabled(true);
}

void MeltingPanel::meltingCancelFunction(CCObject* dt)
{
	if ( CCNode* pNode = LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame) )
	{
		pNode->removeFromParentAndCleanup(true);
	}
	bagCreate->_meltingCreate->setIsTouchEnabled(true);
}

void MeltingPanel::onClickHandler( int radioNo )
{
	//var _radio:CustomCheckBox = e.target as CustomCheckBox;
	//switch(_radio.name){
	//case "meltingRadio1":
	//	if(_roleVipLev >= 3){
	//		_radio2.selected = false;
	//		_radio3.selected = false;
	//	}else{
	//		_radio1.selected = false;
	//		LangManager.msgShow("STG073");
	//	}
	//	if(_radio1.selected){
	//		_vipLevel = 3;						
	//	}else{
	//		_vipLevel = 0;
	//	}
	//	break;
	//case "meltingRadio2":
	//	if(_roleVipLev >= 5){
	//		_radio1.selected = false;
	//		_radio3.selected = false;
	//		_vipLevel = 5;
	//	}else{
	//		_radio2.selected = false;
	//		LangManager.msgShow("STG074");
	//	}
	//	if(_radio2.selected){
	//		_vipLevel = 5;						
	//	}else{
	//		_vipLevel = 0;
	//	}
	//	break;
	//case "meltingRadio3":
	//	if(_roleVipLev >= 7){
	//		_radio1.selected = false;
	//		_radio2.selected = false;
	//		_vipLevel = 7;
	//	}else{
	//		_radio3.selected = false;
	//		LangManager.msgShow("STG075");
	//	}
	//	if(_radio3.selected){
	//		_vipLevel = 7;						
	//	}else{
	//		_vipLevel = 0;
	//	}
	//	break;
	//}
	//if(_materialsNum == 3){
	//	updateRate(_goodsId1,_goodsId2,_goodsId3,_vipLevel);
	//}
}


void MeltingPanel::gridClick( int type )
{
	CCNode* pic1 = _bgEquipInfo->getChildByTag(Tag_Pic1);
	CCNode* pic2 = _bgEquipInfo->getChildByTag(Tag_Pic2);
	CCNode* pic3 = _bgEquipInfo->getChildByTag(Tag_Pic3);

	switch( type )
	{
	case 1:	//"_goods1":
		if( pic1 )
		{
			pic1->removeFromParentAndCleanup(true);
		//	_toolTips1.dispose();

			bagCreate->updateGoods( _goodsInfo1, _sit1, _page1, 1 );
			_goodsInfo1 = 0;
			_goodsId1 = 0;
			_sit1 = 0;
			_page1 = 0;
			_materialsNum --;
		}
		break;
	case 2:	//"_goods2":
		if( pic2 )
		{
			pic2->removeFromParentAndCleanup(true);
			//_toolTips2.dispose();
			bagCreate->updateGoods( _goodsInfo2, _sit2, _page2, 1 );
			_goodsInfo2 = 0;
			_goodsId2 = 0;
			_sit2 = 0;
			_page2 = 0;
			_materialsNum --;
		}
		break;
	case 3:	//"_goods3":
		if( pic3 )
		{
			pic3->removeFromParentAndCleanup(true);
			//_toolTips3.dispose();
			bagCreate->updateGoods( _goodsInfo3, _sit3, _page3, 1 );
			_goodsInfo3 = 0;
			_goodsId3 = 0;
			_sit3 = 0;
			_page3 = 0;
			_materialsNum --;
		}
		break;
	}
	if(_materialsNum < 3)
	{
		_sparNumText->setString("");
		_rateText->setString("");
	}
}

int MeltingPanel::getSparNum()
{
	return _sparNum;
}

void MeltingPanel::meltingHelpHandler( CCObject* pSender )
{
	MeltingTips* pTips = (MeltingTips*)LayerManager::tipsLayer->getChildByTag(
		TipsLayer::TipsLayerTAG_tipHelpMelting);
	if (!pTips)
	{
		pTips = new MeltingTips;
		pTips->init();
		LayerManager::tipsLayer->addChild(pTips,
			TipsLayer::TipsLayerZ_tipHelpMelting, TipsLayer::TipsLayerTAG_tipHelpMelting);
		pTips->release();
	}
	
}
