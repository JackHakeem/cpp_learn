#include "MeltingBagGoods.h"
#include "BaseType.h"
#include "manager/ViewManager.h"
#include "utils/ColorUtil.h"
#include "events/GameDispatcher.h"
#include "utils/ValuesUtil.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "../MainStrengMediator.h"
#include "MeltingPanel.h"
#include "MeltingBagCreate.h"
#include "MeltingUIListView.h"

MeltingBagGoods::MeltingBagGoods( const CCRect& rect)
{
	m_rect = rect;

	_leveEquipment = 0;
	_nameEquipment = 0;

	_myInfo = 0;

	_isMove = false;

	_clickNum= 0;
	_mySitNum = 0;
	_page = 1;

	_pic = 0;
	_picClone = 0;
	_EquipCnt = 0;
}

MeltingBagGoods::~MeltingBagGoods()
{
	CC_SAFE_DELETE(_myInfo);
}

MeltingBagGoods* MeltingBagGoods::MeltingBagGoodsWithRect(  const CCRect& rect )
{
	MeltingBagGoods* pItem = new MeltingBagGoods(rect);
	if (!pItem->init())
	{
		return NULL;
	}
	pItem->setContentSize( rect.size );
	pItem->setPosition( rect.origin );
	pItem->setAnchorPoint(CCPointZero);
	
	return pItem;
}

void MeltingBagGoods::initMeltingBagGoodsVo( GoodsInfo* goodsInfo, int id )
{
	CC_SAFE_DELETE(_myInfo);
	_myInfo = new GoodsInfo;

	//*_myInfo = *goodsInfo;
	if ( goodsInfo )
	{
		_myInfo->id = goodsInfo->id; // items only Numbers
		_myInfo->goodId = goodsInfo->goodId; // type ID items Numbers
		_myInfo->sitGrid = goodsInfo->sitGrid; // grid coordinates
		_myInfo->name = goodsInfo->name; // name
		_myInfo->type = goodsInfo->type; // type 2
		_myInfo->subtype = goodsInfo->subtype; // child type
		_myInfo->equip_type = goodsInfo->equip_type; // (equipment position. A head...) )
		_myInfo->number = goodsInfo->number; // quantity
		_myInfo->quality = goodsInfo->quality; // quality
		_myInfo->strengthen = goodsInfo->strengthen; // strengthen number
		_myInfo->holds = goodsInfo->holds; // make hole number
		_myInfo->explain = goodsInfo->explain; // that
		_myInfo->stamina = goodsInfo->stamina; // enchantment physical number
		_myInfo->wrist = goodsInfo->wrist; // enchantment number of achievement
		_myInfo->intellect = goodsInfo->intellect; // enchantment number of achievement
	}

	_mySitNum = id;

	GoodsInfo* pGoodsInfo = goodsInfo;
	if ( !pGoodsInfo )
	{
		return;
	}
	
	if( pGoodsInfo->id != 0 )
	{
		//CCUIBackground* selectedSpriteImage = new CCUIBackground();
		//selectedSpriteImage->initWithSpriteFrame( "ui.png",
		//	ccp(POSX(0), POSX(0)), ccp(POSX(0),POSX(0)), CCSizeMake( m_rect.size.width, m_rect.size.height ) );
		//this->addChild( selectedSpriteImage );
		//selectedSpriteImage->release();
		SpriteNode* unlock = new SpriteNode();
		unlock->initWithSpriteFrameName("pack/unlock.png");
		this->addChild(unlock);
		//unlock->setPosition(ccp(POSX(10),POSX(10+5)));
		unlock->setAnchorPoint(CCPointZero);
		unlock->release();

		// Equiment icon
		char strFormat[54];
		sprintf( strFormat, "assets/icon/goods/%d.png", pGoodsInfo->goodId );
		_pic = CCSprite::spriteWithFile( strFormat );

		if ( !_pic )
		{
		//	assert(!"pic: %s not exist!", strFormat.);
			return;
		}

		//CCSize cs = getContentSize();
		//_pic->setPosition( ccp( cs.width/2, cs.height/2 ) );
		_pic->setAnchorPoint(CCPointZero);
		addChild(_pic);
		
		if ( _myInfo->type == 3 )
		{
			sprintf( strFormat, "%d", _myInfo->number );
			_EquipCnt =  CCLabelTTF::labelWithString( strFormat,
				CCSizeMake( POSX(24), POSX(24) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(24) );
			_EquipCnt->setColor(  ccWHITE  );
			_EquipCnt->setPosition( ccp(POSX(64), POSX(10) ) );
			_EquipCnt->setAnchorPoint(CCPointZero);
			addChild( _EquipCnt );
		}		
	}
}

void MeltingBagGoods::updateStrength( int strengthen )
{
	//_myInfo->MeltingBagGoodsInfo->strengthen = strengthen;
	char suffix[128];
	//sprintf( suffix, ValuesUtil::Instance()->getString( "StLev" ).c_str(), _myInfo->MeltingBagGoodsInfo->strengthen );
	string strLev = suffix;
	_leveEquipment->setString( strLev.c_str() );

	//updateTip();
}

void MeltingBagGoods::onEnter()
{
	//CCPoint cpRow = getParent()->boundingBox().origin;
	//MeltingUIListView* pList = (MeltingUIListView*)getParent()->getParent();
	//CCPoint cpList = pList->boundingBox().origin;// pList->getWorldSpaceLeftBottomPoint();//; pList.origin;
	//m_initPoint = ccpAdd(this->boundingBox().origin, cpRow );
	//m_initPoint = ccpAdd( m_initPoint, cpList );
	//m_initPoint = ccpAdd( m_initPoint, pList->getParent()->boundingBox().origin );
	//m_initPoint.y += POSX(29);
	//m_initPoint = ccpAdd( m_initPoint, g_pMainStrengMediator->_meltingPanel->getPosition() );
	//m_initPoint = ccpAdd( m_initPoint, g_pMainStrengMediator->_mainStrengView->getPosition() );


	//m_initPoint.y += g_pMainStrengMediator->_meltingPanel->bagCreate->_meltingCreate->m_fYMove;

	//CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_Common, true);
	CCLayer::onEnter();
}
/*
void MeltingBagGoods::onExit()
{
CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
CCLayer::onExit();
}*/	

CCRect MeltingBagGoods::rect()
{
	CCSize s = this->getContentSize();
	return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}

bool MeltingBagGoods::containsTouchLocation(CCTouch* touch)
{
	return CCRect::CCRectContainsPoint(rect(), convertTouchToNodeSpaceAR(touch));
}

bool MeltingBagGoods::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	//if ( !containsTouchLocation(touch) ) return false;
	
	//if ( (_myInfo->number-1)==0 )
	//{
	//	_pic->setIsVisible(false);
	//}
	//else
	//	_picClone = 0;
	
	if ( !_picClone )
	{
		m_initPoint = this->getPosition();
		CCNode* pNode = (CCNode*)this;
		while ( pNode != (CCNode*)g_pMainStrengMediator->_meltingPanel )
		{
			if ( pNode && (pNode = pNode->getParent()) )
			{
				m_initPoint = ccpAdd( m_initPoint, pNode->getPosition() );
			}
		}

		_picClone = new CCSprite;
		char strFormat[54];
		sprintf( strFormat, "assets/icon/goods/%d.png", _myInfo->goodId );
		if (_picClone && _picClone->initWithFile(strFormat))
		{
			_picClone->setAnchorPoint(CCPointZero);
			m_initPoint.x -= POSX(17);
			m_initPoint.y -= POSX(4);
			_picClone->setPosition( m_initPoint );
			g_pMainStrengMediator->_meltingPanel->addChild(_picClone);

			_picClone->runAction(CCScaleTo::actionWithDuration(0.2f, 1.2f));//Increasingly large

			_picClone->release();
		}
		
	}	

	return true;
}

void MeltingBagGoods::ccTouchMoved( CCTouch* touch, CCEvent* event )
{
	if ( _myInfo->type==3 )
	{
		if ( (_myInfo->number-1)==0 )
		{
			_pic->setIsVisible(false);
		}		
	}
	else
		_pic->setIsVisible(false);

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

void MeltingBagGoods::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	if (_picClone)
	{
		_picClone->removeFromParentAndCleanup(true);
		_picClone = 0;
	}

	if ( g_pMainStrengMediator->_meltingPanel->_materialsNum == 3 )
	{
		_pic->setIsVisible(true);
		_isMove = false;
		return;
	}	
	
	if ( _isMove )// move
	{
		// drag
		struct sdata
		{
			int UseType;
			GoodsInfo* info;
			int sitNum;
			int page;
			int type;
		} s;
		s.UseType = 2;
		s.info = _myInfo;
		s.sitNum = _mySitNum;
		s.page = _page;

		//CCPoint locationInView = touch->locationInView(touch->view());
		//CCPoint currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
		//int L = 95/2;
		//if ( CCRect::CCRectContainsPoint(  CCRectMake(POSX(550+L/2), POSX(380+L/2), POSX(L/2), POSX(L/2)), currentTouchPoint  ) ) //76,84 convertTouchToNodeSpaceAR(touch)
		//{
		//	s.type = 1;
		//	//m_DragPoint = ccp( 550-10, 355 );
		//}
		//else if ( CCRect::CCRectContainsPoint(  CCRectMake(POSX(435+L/2), POSX(275+L/2), POSX(L/2), POSX(L/2)), currentTouchPoint  ) )
		//{
		//	s.type = 2;
		//	//m_DragPoint = ccp( 435-10, 275 );
		//}
		//else if ( CCRect::CCRectContainsPoint(  CCRectMake(POSX(655+L/2), POSX(275+L/2), POSX(L/2), POSX(L/2)), currentTouchPoint  ) )
		//{
		//	s.type = 3;
		//	//m_DragPoint = ccp( 655-10, 275 );
		//}
		//else
		//{
			s.type = 0;
		//}
		this->setPosition( m_rect.origin );
		GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::MELTING_GOODS_CHANGE, &s );
	} 
	else	// click
	{
		if ( _myInfo->type == 2 ) // Equipment
		{
			struct sdata
			{
				int UseType;
				GoodsInfo* goodInfo;
			} s;
			s.UseType = 1;
			s.goodInfo = _myInfo;
			GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::MELTING_GOODS_CHANGE, &s );
		}		
	}
	_isMove = false;
} 

void MeltingBagGoods::setIcon( bool boolean )
{
	if ( boolean )
	{
		_pic->setIsVisible( true );
	}
	else
		_pic->setIsVisible( false );
}

void MeltingBagGoods::setNum( int cnt )
{
	if ( _EquipCnt )
	{
		if ( cnt == 0 )
		{
			_EquipCnt->setIsVisible(false);
		}
		else
		{
			_EquipCnt->setIsVisible(true);

			char tmp[10];
			sprintf(tmp,"%d", cnt);
			_EquipCnt->setString(tmp);
		}
	}
}
