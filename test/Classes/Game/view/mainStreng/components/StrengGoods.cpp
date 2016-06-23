#include "StrengGoods.h"
#include "model/streng/vo/StrengGoodsVo.h"
#include "BaseType.h"
#include "manager/ViewManager.h"
#include "utils/ColorUtil.h"
#include "events/GameDispatcher.h"
#include "utils/ValuesUtil.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"

StrengGoods::StrengGoods( const CCRect& rect)
{
	m_rect = rect;
	m_ItemIndex = 0;

	_leveEquipment = 0;
	_nameEquipment = 0;

	_equpInfo = 0;

	//CCLayerColor* pLayer = new CCLayerColor();
	//pLayer->initWithColorWidthHeight(  ccc4( 120, 255, 120, 10 ), (GLfloat)rect.size.width, (GLfloat)rect.size.height  );
	//addChild(pLayer);
}

StrengGoods::~StrengGoods()
{
	CC_SAFE_DELETE(_equpInfo);
}

StrengGoods* StrengGoods::StrengGoodsWithRect(  const CCRect& rect )
{
	StrengGoods* pItem = new StrengGoods(rect);
	if (!pItem->init())
	{
		return NULL;
	}
	pItem->setContentSize( rect.size );
	pItem->setvisibleSize( rect.size );
	pItem->setPosition( rect.origin );
	//pItem->autorelease();

	return pItem;
}

void StrengGoods::initStrengGoodsVo( StrengGoodsVo* strengGoodsVo, int id )
{
	_equpInfo = strengGoodsVo;
	m_ItemIndex = id;

	GoodsInfo* pGoodsInfo = strengGoodsVo->StrengGoodsInfo;
	if ( !pGoodsInfo )
	{
		return;
	}

	if( pGoodsInfo->id != 0 )
	{
		CCUIBackground* selectedSpriteImage = new CCUIBackground();
		selectedSpriteImage->initWithSpriteFrame( "ui.png",
			CCPointZero, CCPointZero, CCSizeMake( m_rect.size.width, m_rect.size.height ) );
		this->addChild( selectedSpriteImage );
		selectedSpriteImage->release();

		SpriteNode* unlock = new SpriteNode();
		unlock->initWithSpriteFrameName("pack/unlock.png");
		this->addChild(unlock);
		unlock->setPosition(ccp(POSX(10),POSX(10+5)));
		unlock->setAnchorPoint(CCPointZero);
		unlock->release();

		// Equiment icon
		char strFormat[54];
		sprintf( strFormat, "assets/icon/goods/%d.png", pGoodsInfo->goodId );
		_pic = CCSprite::spriteWithFile( strFormat );
		if ( !_pic )
		{
			assert(!"pic: not exist!");
			return;
		}
		
		_pic->setPosition( ccp( POSX(/*58.0f*/14), /*POSX(58.0f)+*/POSX(14+5) ) );
		_pic->setAnchorPoint(CCPointZero);
		addChild(_pic);

		ccColor3B color = ColorUtil::getGoodColor( pGoodsInfo->quality );
		if ( !_nameEquipment )
		{
			// name
			string str = pGoodsInfo->name;
			_nameEquipment = CCLabelTTF::labelWithString( str.c_str(),
				CCSizeMake( POSX(125), POSX(22) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );
			_nameEquipment->setColor(  color  );
			_nameEquipment->setAnchorPoint(CCPointZero);
			_nameEquipment->setPosition( ccp( POSX(110+5), POSX(65) ) );
			addChild( _nameEquipment );
		}

		if ( !_leveEquipment )
		{
			// level
			sprintf( strFormat, ValuesUtil::Instance()->getString( "STG040" ).c_str(), pGoodsInfo->strengthen );
			string str = strFormat;
			_leveEquipment = CCLabelTTF::labelWithString( str.c_str(),
				CCSizeMake( POSX(150), POSX(22) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );
			//ccColor3B col = { 255, 253, 232 };
			_leveEquipment->setColor( ccWHITE );
			_leveEquipment->setAnchorPoint(CCPointZero);
			_leveEquipment->setPosition( ccp( POSX(110+5/*+130/2*/), POSX(22) ) );
			addChild( _leveEquipment );
		}
	}
}

void StrengGoods::updateStrength( int strengthen )
{
	_equpInfo->StrengGoodsInfo->strengthen = strengthen;
	char suffix[128];
	sprintf( suffix, ValuesUtil::Instance()->getString( "STG040" ).c_str(), _equpInfo->StrengGoodsInfo->strengthen );
	string strLev = suffix;
	_leveEquipment->setString( strLev.c_str() );

	//updateTip();
}

void StrengGoods::onEnter()
{
	//CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_Common, true);
	CCLayer::onEnter();
}

void StrengGoods::onExit()
{
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}	

CCRect StrengGoods::rect()
{
	CCSize s = this->getContentSize();
	return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}

bool StrengGoods::containsTouchLocation(CCTouch* touch)
{
	return CCRect::CCRectContainsPoint(rect(), convertTouchToNodeSpaceAR(touch));
}

bool StrengGoods::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if ( !containsTouchLocation(touch) ) return false;

	return true;
}

void StrengGoods::ccTouchMoved( CCTouch* touch, CCEvent* event )
{

}

void StrengGoods::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	struct sdata
	{
		int UseType;
		StrengGoodsVo* sdataStrengGoodsVo;
	} s;
	s.UseType = 6;	// {UseType:6/* 6 Check prop when click */
	s.sdataStrengGoodsVo = _equpInfo;
	GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::SHOW_STRENG_CLICK, &s );
} 

void StrengGoods::touchDelegateRetain()
{
	this->retain();
}

void StrengGoods::touchDelegateRelease()
{
	this->release();
}
