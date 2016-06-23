#include "RecruitItem.h"
#include "BaseType.h"
#include "manager/ViewManager.h"
#include "utils/ColorUtil.h"
#include "events/GameDispatcher.h"
#include "utils/ValuesUtil.h"
#include "RecruitPanel.h"
#include "RecruitView.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"

RecruitItem::RecruitItem( const CCRect& rect)
{
	m_rect = rect;
	m_ItemIndex = 0;

	_name = 0;
	_level = 0;

	_pic = 0;

	//_info = 0;

// 	CCLayerColor* pLayer = new CCLayerColor();
// 	pLayer->initWithColorWidthHeight(  ccc4( 120, 255, 120, 10 ), (GLfloat)rect.size.width, (GLfloat)rect.size.height  );
// 	addChild( pLayer );
}

RecruitItem::~RecruitItem()
{

}

RecruitItem* RecruitItem::RecruitItemWithRect(  const CCRect& rect )
{
	RecruitItem* pItem = new RecruitItem(rect);
	if (!pItem->init())
	{
		return 0;
	}
	pItem->setContentSize( rect.size );
	pItem->setPosition( rect.origin );

	pItem->setIsTouchEnabled(true);
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(pItem, TLE::WindowLayer_Common, true);

	return pItem;
}

void RecruitItem::initRecruitInfo( RecruitInfo recruitInfo, int id )
{    
	_info = recruitInfo;
	m_ItemIndex = id;

	CCUIBackground* bgItem = new CCUIBackground();
	if ( bgItem && bgItem->initWithSpriteFrame( "popuibg/bg2.png",
		ccp(0, 0), ccp(0,0), m_rect.size ) )
	{
		this->addChild( bgItem );
		bgItem->release();
	}

	CCUIBackground* bgPic = new CCUIBackground();
	if ( bgPic && bgPic->initWithSpriteFrame( "ui.png",
		ccp(0, POSX(-2)), ccp(0,0), CCSizeMake( POSX(105), POSX(105) ) ) )
	{
		this->addChild( bgPic );
		bgPic->release();
	}

	char strFormat[54];
	ccColor3B color = setTextColor( _info.color );
	if ( !_name )
	{
		// name
		string str = _info.name;
		_name = CCLabelTTF::labelWithString( str.c_str(),
			CCSizeMake( POSX(180), POSX(25) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );
		_name->setColor(  color  );
		_name->setPosition( ccp(POSX(105.0f+180/2), POSX(65.0f) ) );
		addChild( _name );
	}


	if( _info.isGray != 2 )
	{
		sprintf( strFormat, ValuesUtil::Instance()->getString( "RCR008" ).c_str(), _info.level );
		_level = CCLabelTTF::labelWithString( strFormat, CCSizeMake( POSX(125), POSX(25) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );
		_level->setColor(  color  );
		_level->setPosition( ccp(POSX(105.0f+125/2), POSX(20.0f) ) );
		addChild( _level );

		//_isEnlist.visible = info.isHired;

		sprintf( strFormat, "assets/icon/head/%d.png", _info.cloth );
		_pic = CCSprite::spriteWithFile( strFormat );
		if ( !_pic )
		{
			_pic = CCSprite::spriteWithFile( "assets/icon/head/unknown.png" );
		}
		
		_pic->setPosition( ccp( POSX(105/2-1.5), POSX(105/2+3) ) );
		bgPic->addChild(_pic);

		if ( _info.isHired )
		{
			CCSprite* pHiredTag = new CCSprite;
			if ( pHiredTag && pHiredTag->initWithSpriteFrameName("train/checkbox.png") )
			{
				pHiredTag->setAnchorPoint(CCPointZero);
				pHiredTag->setPosition(ccp(POSX(188-10),POSX(35)));
				this->addChild( pHiredTag );
                pHiredTag->release();
			}
		}
	}
	else
	{
		_level = CCLabelTTF::labelWithString( " - ", CCSizeMake( POSX(125), POSX(25) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(18) );
		_level->setColor(  color  );
		_level->setPosition( ccp(POSX(105.0f+125/2), POSX(20.0f) ) );
		addChild( _level );

		_pic = CCSprite::spriteWithFile( "assets/icon/head/unknown.png" );
		if ( !_pic )
		{
			return;
		}
		_pic->setPosition( ccp( POSX(105/2-1.5), POSX(105/2+3) ) );
		bgPic->addChild(_pic);
	}
}

/**
*  set color by figure color id
* @param id
* @return 
*/		
ccColor3B RecruitItem::setTextColor( uint id )
{
	ccColor3B color;
	switch (id)
	{
		case 0:
			color = ccc3( 0xFF,0xD3,0x06 );
			break;
		case 1:
			color = ccc3( 0xFF,0xFF,0xFF );
			break;
		case 2:
			color = ccc3( 0x00,0xEC,0x00 );
			break;
		case 3:
			color = ccc3( 0x00,0x72,0xE3 );
			break;
		case 4:
			color = ccc3( 0xAE,0x00,0xAE );
			break;
		case 5:
			color = ccc3( 0xF7,0x50,0x00 );
			break;
		case 6:
			color = ccc3( 0xFF,0x00,0x00 );
			break;
		default:
			break;
	}
	return color;
}
// 
// void RecruitItem::onEnter()
// {
// 	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_Common, true);
// 	CCLayer::onEnter();
// }

void RecruitItem::onExit()
{
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

CCRect RecruitItem::rect()
{
	CCSize s = this->getContentSize();
	return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}

bool RecruitItem::containsTouchLocation(CCTouch* touch)
{
	return CCRect::CCRectContainsPoint(rect(), convertTouchToNodeSpaceAR(touch));
}

bool RecruitItem::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if ( !containsTouchLocation(touch) ) return false;


    //Doyang 20120924
    CCPoint locationInView = touch->locationInView(touch->view());
    mTouchBeganPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	setTouchStat(STATE_TOUCH_0);
	RecruitPanel* pRecruitPanel = ViewManager::getInstance()->recruitView->_recPanel;
	if ( pRecruitPanel )
	{
		return pRecruitPanel->RecruitPanel::ccTouchBegan( touch, event );
	}

	return true;
}

void RecruitItem::ccTouchMoved( CCTouch* touch, CCEvent* event )
{

    //Doyang 20120924
    CCPoint locationInView = touch->locationInView(touch->view());
    CCPoint movePoint = CCDirector::sharedDirector()->convertToGL(locationInView);
    if(abs(mTouchBeganPoint.x - movePoint.x) < 5)
    {
        return ;
    }

	RecruitPanel* pRecruitPanel = ViewManager::getInstance()->recruitView->_recPanel;
	if ( pRecruitPanel )
	{
		pRecruitPanel->RecruitPanel::ccTouchMoved( touch, event );
	}
	setTouchStat(STATE_TOUCH_1);
}

void RecruitItem::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	RecruitPanel* pRecruitPanel = ViewManager::getInstance()->recruitView->_recPanel;
	if (getTouchStat() == STATE_TOUCH_1)
	{
		setTouchStat(STATE_TOUCH_2); 
		pRecruitPanel->RecruitPanel::ccTouchEnded(touch,event);
		return;
	}

	if ( pRecruitPanel )
	{
		pRecruitPanel->onSingleClickHandler( this );
	}	
} 


// void RecruitItem::touchDelegateRetain()
// {
// 	this->retain();
// }
// 
// void RecruitItem::touchDelegateRelease()
// {
// 	this->release();
// }

RecruitInfo* RecruitItem::info()
{
	return &_info;
}

int RecruitItem::id()
{
	return _info.mercId;
}
