#include "HeritageGoods.h"
#include "model/streng/vo/StrengGoodsVo.h"
#include "BaseType.h"
#include "manager/ViewManager.h"
#include "utils/ColorUtil.h"
#include "events/GameDispatcher.h"
#include "utils/ValuesUtil.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "../MainStrengMediator.h"

HeritageGoods::HeritageGoods( const CCRect& rect)
{
	m_rect = rect;
	m_ItemIndex = 0;

	_leveEquipment = 0;
	_nameEquipment = 0;

	_equpInfo = 0;

	_isMove = false;

	_picClone = 0;
	_pic = 0;

	myTip = 0;
}

HeritageGoods::~HeritageGoods()
{
	CC_SAFE_DELETE(_equpInfo);
}

HeritageGoods* HeritageGoods::StrengGoodsWithRect(  const CCRect& rect )
{
	HeritageGoods* pItem = new HeritageGoods(rect);
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

void HeritageGoods::initStrengGoodsVo( StrengGoodsVo* heritageGoodsVo, int id )
{
	_equpInfo = heritageGoodsVo;
	m_ItemIndex = id;

	GoodsInfo* pGoodsInfo = heritageGoodsVo->StrengGoodsInfo;
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
		//sprintf( strFormat, "goods/%d.png", pGoodsInfo->goodId );
		sprintf( strFormat, "assets/icon/goods/%d.png", pGoodsInfo->goodId );
		//_pic = CCSprite::spriteWithSpriteFrameName( strFormat );
		_pic = CCSprite::spriteWithFile( strFormat );
		if ( !_pic )
		{
			_pic = CCSprite::spriteWithFile( "assets/icon/goods/unknown.png" );
			if ( !_pic )
			{
				return;
			}
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

void HeritageGoods::updateStrength( int strengthen )
{
	_equpInfo->StrengGoodsInfo->strengthen = strengthen;
	char suffix[128];
	sprintf( suffix, ValuesUtil::Instance()->getString( "STG040" ).c_str(), _equpInfo->StrengGoodsInfo->strengthen );
	string strLev = suffix;
	_leveEquipment->setString( strLev.c_str() );

	//updateTip();
}

void HeritageGoods::onEnter()
{
	//CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_Common, true);
	CCLayer::onEnter();
}

void HeritageGoods::onExit()
{
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}	

CCRect HeritageGoods::rect()
{
	CCSize s = this->getContentSize();
	return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}

bool HeritageGoods::containsTouchLocation(CCTouch* touch)
{
	return CCRect::CCRectContainsPoint(rect(), convertTouchToNodeSpaceAR(touch));
}

bool HeritageGoods::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if ( !_picClone )
	{
		m_initPoint = this->getPosition();
		CCNode* pNode = (CCNode*)this;
		while ( pNode != (CCNode*)g_pMainStrengMediator->_inheritPanel )
		{
			if ( pNode = pNode->getParent() )
			{
				m_initPoint = ccpAdd( m_initPoint, pNode->getPosition() );
			}
		}

		_picClone = new CCSprite;
		char strFormat[54];
		if (_equpInfo)
		{
			GoodsInfo* pGoodsInfo = _equpInfo->StrengGoodsInfo;
			if (pGoodsInfo)
			{
				sprintf( strFormat, "assets/icon/goods/%d.png", pGoodsInfo->goodId );
				if (_picClone && _picClone->initWithFile(strFormat))
				{
					_picClone->setAnchorPoint(CCPointZero);
					m_initPoint.x -= POSX(17);
					m_initPoint.y -= POSX(4);
					_picClone->setPosition( m_initPoint );
					g_pMainStrengMediator->_inheritPanel->addChild(_picClone);

					_picClone->runAction(CCScaleTo::actionWithDuration(0.2f, 1.2f));//Increasingly large

					_picClone->release();
				}
			}			
		}		

	}

	return true;
}

void HeritageGoods::ccTouchMoved( CCTouch* touch, CCEvent* event )
{
	if (_pic)
	{
		_pic->setIsVisible(false);
	}

	if (_picClone)
	{
		CCPoint locationInView = touch->locationInView(touch->view());
		CCPoint currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

		locationInView = touch->previousLocationInView(touch->view());
		CCPoint preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
		_picClone->setPosition( ccpAdd( _picClone->getPosition(), ccpSub( currentTouchPoint, preTouchPoint ) ) );
	}	

	_isMove = true;
}

void HeritageGoods::ccTouchEnded(CCTouch* touch, CCEvent* event)
{

	
	if (_picClone)
	{
		_picClone->removeFromParentAndCleanup(true);
		_picClone = 0;
	}

	if ( g_pMainStrengMediator->_inheritPanel->_materialsNum == 2 )
	{
		_pic->setIsVisible(true);
		_isMove = false;
		return;
	}	

	g_pMainStrengMediator->_inheritPanel->dragGrid( _equpInfo->StrengGoodsInfo, 0, this );

	//struct sdata
	//{
	//	int UseType;
	//	StrengGoodsVo* sdataHeritageGoodsVo;
	//} s;
	//s.UseType = 6;	// {UseType:6/* 6 Check prop when click */
	//s.sdataHeritageGoodsVo = _equpInfo;
	//GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::SHOW_STRENG_CLICK, &s );
} 

void HeritageGoods::touchDelegateRetain()
{
	this->retain();
}

void HeritageGoods::touchDelegateRelease()
{
	this->release();
}

void HeritageGoods::resetPic()
{
	_pic->setIsVisible(true);

}

void HeritageGoods::updateTip()
{
	if ( _leveEquipment )
	{
		// level
		char strFormat[128]={0};
		sprintf( strFormat,
			ValuesUtil::Instance()->getString( "STG040" ).c_str(), _equpInfo->StrengGoodsInfo->strengthen );
		_leveEquipment->setString(strFormat);
	}
}

void HeritageGoods::onRollOverHandler()
{
	//if (!_isMove)
	{
		//??TIPS
		this->myInfo = _equpInfo->StrengGoodsInfo;
		if (!myTip)
		{
			myTip = new TipHelps();
		}
		myTip->init(true, TipConst::STRENG);
		myTip->setToolTips(this, this);
		myTip->rollOverHander();
	}
}
