#include "CustomCD.h"
#include "events/GameDispatcher.h"
#include "manager/CDManage.h"
#include "socket/network/GameServerSocket.h"
#include "CCMenuItem.h"
#include "manager/TimerManage.h"
#include "socket/command/c18/CCMD182.h"
#include "socket/command/s19/SCMD19F.h"
#include "model/player/RoleManage.h"
#include "socket/command/c19/CCMD19E.h"
#include "events/CDEvent.h"
#include "utils/ScaleUtil.h"
#include "Confirm.h"
#include "manager/LangManager.h"

static const int TAG_SKIN_CONTENER = 1;
static const int TAG_MENU_ITEM = 2;

/**
* view CD com
* @param type cd type
*/		
CustomCD::CustomCD( int type )
{
	_tf = 0;
	_preLabel = "";
	_hasStep = false;

	_type = type;
	m_needGolds = 0;
	m_cpBtOffset = CCPointZero;

	init();
	
	CDManage::Instance()->addCustomCD( _type, this );
}

CustomCD::~CustomCD()
{
	CDManage::Instance()->removeEventListener(CDManage::CDCHANGED, this, callfuncND_selector(CustomCD::cdChangedHandler));
	CDManage::Instance()->deleteCustomCD(_type);
}

bool CustomCD::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	this->setContentSize( CCSizeMake(POSX(320), POSX(33)) );

	CCLayer* m_ContentLayer = new CCLayer;
	m_ContentLayer->init();
	m_ContentLayer->setAnchorPoint(CCPointZero);
	m_ContentLayer->setTag( TAG_SKIN_CONTENER );
	m_ContentLayer->setContentSize( CCSizeMake(POSX(320), POSX(33)) );
	this->addChild( m_ContentLayer );
    m_ContentLayer->release();

	_timer = CDManage::Instance()->getCDTimeBytype( _type );
	_lock = CDManage::Instance()->getLockBytype( _type );

	_preLabel = CDManage::Instance()->CDlockTimeName[_type];
	_preLabel.append( " " );
	string tmp = _preLabel + "  00:00:00";

	// CDlockTimeName
	CCMenuItemFont *pCDlockTimeNameItem = CCMenuItemFont::itemFromString( tmp.c_str(), this, menu_selector(CustomCD::reqMoney) );
	pCDlockTimeNameItem->setAnchorPoint( CCPointZero );
	pCDlockTimeNameItem->setFontSizeObj( POSX(24) );
	pCDlockTimeNameItem->setFontName( g_sSimHeiFont );
	pCDlockTimeNameItem->setColor( ccc3(255, 104, 44) );
	pCDlockTimeNameItem->setTag( TAG_MENU_ITEM );

	CCSize csCDNameSize = pCDlockTimeNameItem->getContentSize();
	//CCLayerColor* PCOLOR = CCLayerColor::layerWithColorWidthHeight( ccc4(255, 255, 0, 100), csCDNameSize.width, csCDNameSize.height );
	//pCDlockTimeNameItem->addChild( PCOLOR );
	pCDlockTimeNameItem->setString( "" );

	// _btnClear
	CCSprite* pNormal = CCSprite::spriteWithSpriteFrameName("npcdialog/point.png");
	CCSprite* pPress = CCSprite::spriteWithSpriteFrameName("npcdialog/point.png");
	CCMenuItemSprite *pBtnItem = cocos2d::CCMenuItemImage::itemFromNormalSprite(
	pNormal,
	pPress,
	this,
	menu_selector(CustomCD::reqMoney) );
	pBtnItem->setAnchorPoint( CCPointZero );
	pBtnItem->setIsRelativeAnchorPoint(true);
	pBtnItem->setPosition( ccp(csCDNameSize.width + POSX(5), POSX(3)) );//200
	pBtnItem->setTag( TAG_MENU_ITEM+1 );
	// create menu, it's an autorelease object
	_tf = CCMenu::menuWithItems( pCDlockTimeNameItem, pBtnItem, 0 );
	_tf->setPosition( ccp( POSX(30), 0) );
	_tf->setTouchLayer(-500);

	if ( (_type == CDManage::ARENA_OPPS_CD) || (_type == CDManage::RobTraderCD) )
	{
		pCDlockTimeNameItem->setIsEnabled(false);
		pBtnItem->setIsEnabled(false);
	}

	//_tf->alignItemsHorizontallyWithPadding( POSX(30.0f) );
	m_ContentLayer->addChild( _tf );
	m_ContentLayer->setIsVisible( false );

	CDManage::Instance()->addEventListener(CDManage::CDCHANGED, this, callfuncND_selector(CustomCD::cdChangedHandler));

	//CCLayerColor* pColor = CCLayerColor::layerWithColorWidthHeight( ccc4(0,0,255,100), 400, 25 );
	//this->addChild( pColor );
	
	//_tips = new TipHelps();
	//_tips.setToolTips(this, "使用金币清除冷却时间");

	//TimerManage::Instance()->add( 1,schedule_selector( CustomCD::layout ), this );
	
	return true;
}

void CustomCD::reinit()
{
	_timer = CDManage::Instance()->getCDTimeBytype( _type );
	//scheduleUpdate();
	TimerManage::Instance()->remove( schedule_selector( CustomCD::layout ), this );
	TimerManage::Instance()->add( 1,schedule_selector( CustomCD::layout ), this );
}

/* 请求CD清零所需金币 */
void CustomCD::reqMoney( CCObject* pSender )
{
	if (_type == CDManage::ARENA_OPPS_CD)
	{
		return;
	}
	//GameServerSocket::getInstance().addCmdListener(SocketCMDConst.WMSG_WORLD_CLEAR_CD_COST, clearCD);
	//GameServerSocket::getInstance().sendMessage(SocketCMDConst.CMSG_WORLD_CLEAR_CD_COST, new Int8(_type));
	CCMD19E cmd;
	cmd.a_type = _type;
	GameServerSocket::getInstance()->sendMessage( &cmd );	//CMSG_WORLD_CLEAR_CD_COST
}

/* response CD clear gold process */
void CustomCD::clearCD( SCMD19F* cmd )	//WMSG_WORLD_CLEAR_CD_COST
{
	if( cmd->a_type != _type ) return;

	m_needGolds = cmd->b_cost;

	Confirm* pConfirm = new Confirm();
	std::string stdstr = LangManager::getText( "CD013", m_needGolds );
	pConfirm->initWithParam(stdstr.c_str(), this, menu_selector(CustomCD::okFunction), menu_selector(CustomCD::cancelFunction));

	// LH0717
	if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_cdmanage))
	{
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_cdmanage, true);
	}

	LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_cdmanage, TipsLayer::TipsLayerTAG_cdmanage);

	pConfirm->release();	
}

/* process after confirm */
void CustomCD::okFunction( CCObject* pObject )
{
	int hasGold = RoleManage::Instance()->accountInfo()->gold();
	if( hasGold < m_needGolds  )
	{
		LangManager::msgShow( "CD014" );
	}
	else
	{
		CCMD182 cmd;
		cmd.a_type = _type; 
		cmd.b_free = 0;
		GameServerSocket::getInstance()->sendMessage( &cmd );	// CMSG_WORLD_CLEAR_CD
	}

	Confirm* pConfirm = (Confirm*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_cdmanage);
	if (pConfirm && pConfirm->getParent())
		pConfirm->getParent()->removeChild(pConfirm, true);
}

void CustomCD::cancelFunction( CCObject* pObject )
{
	Confirm* pConfirm = (Confirm*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_cdmanage);
	if (pConfirm && pConfirm->getParent())
		pConfirm->getParent()->removeChild(pConfirm, true);
}

void CustomCD::cdChangedHandler( CCNode* n, void* data )
{
	CDEvent* e = (CDEvent*)data;
	if( e->cdType == _type ) 
	{
		_timer = e->time;
		_lock = e->lock;
		if(!_hasStep) 
		{
			TimerManage::Instance()->add( 1,schedule_selector( CustomCD::layout ), this );
			_hasStep = true;
		}
		layout();
	}
}

void CustomCD::layout( ccTime dt )
{
	Number sTime = CDManage::Instance()->getServerTime();
	string displayTime = formatData( sTime );
	CCMenuItemFont *pCDlockTimeNameItem = (CCMenuItemFont *)_tf->getChildByTag( TAG_MENU_ITEM );
	CCLayer* m_ContentLayer = (CCLayer*)this->getChildByTag( TAG_SKIN_CONTENER );
	if ( !m_ContentLayer )
	{
		return;
	}
	

	if( _timer <= sTime )
	{	//no CD with
		displayTime = "00:00:00";
		m_ContentLayer->setIsVisible( false );
		if ( pCDlockTimeNameItem )
		{
			pCDlockTimeNameItem->setString( displayTime.c_str() );
		}

		//CDCallback();

		dispose();
	}
	else if(_lock)
	{
		// Lock, coding...
		m_ContentLayer->setIsVisible( true );
		displayTime = _preLabel + displayTime;
		if ( pCDlockTimeNameItem )
		{
			pCDlockTimeNameItem->setString( displayTime.c_str() );
			pCDlockTimeNameItem->setColor( ccc3(0xff, 0x66, 0x00) );

			CCMenuItemImage *pBtnItem = (CCMenuItemImage *)_tf->getChildByTag( TAG_MENU_ITEM+1 );
			if ( pBtnItem )
			{
				CCSize cs = pCDlockTimeNameItem->getContentSize();
				pBtnItem->setPositionX( cs.width + POSX(5)+m_cpBtOffset.x );
				pBtnItem->setPositionY( POSX(3)+m_cpBtOffset.y );
				//pBtnItem->setPosition( ccpAdd(pBtnItem->getPosition(),m_cpBtOffset)  );
			}
		}
		CDCallback();
	}
	else
	{
		// not locked
		m_ContentLayer->setIsVisible( true );
		displayTime = _preLabel + displayTime;
		if ( pCDlockTimeNameItem )
		{
			pCDlockTimeNameItem->setString( displayTime.c_str() );
			pCDlockTimeNameItem->setColor( ccc3(0xff, 0xff, 0x99) );

			CCMenuItemImage *pBtnItem = (CCMenuItemImage *)_tf->getChildByTag( TAG_MENU_ITEM+1 );
			if ( pBtnItem )
			{
				CCSize cs = pCDlockTimeNameItem->getContentSize();
				pBtnItem->setPositionX( cs.width  + POSX(5)+m_cpBtOffset.x );
				pBtnItem->setPositionY( POSX(3)+m_cpBtOffset.y );
				//pBtnItem->setPosition( ccpAdd(pBtnItem->getPosition(),m_cpBtOffset)  );
			}
		}
		CDCallback();
	}

	//CDCallback();
}

string CustomCD::formatData( Number serTimer )
{
	Number num = ( _timer - serTimer ) * 0.001;  // second

	int hour = num/3600;
	int minute = ( num/60 )%60;
	int second = num%60;

	char timeStr[28];
	sprintf( timeStr, "%d", hour );
	string sHour = formatTime( timeStr );

	sprintf( timeStr, "%d", minute );
	string sMinute = formatTime( timeStr );

	sprintf( timeStr, "%d", second );
	string sSecond = formatTime( timeStr );

	//string str = sHour.append( ":" ).append( sMinute ).append( ":" ).append( sSecond );
	return sHour.append( ":" ).append( sMinute ).append( ":" ).append( sSecond );
}

string CustomCD::formatTime( string s )
{
	string withZero = "0";
	return s.length() == 1 ? ( withZero.append( s ) ) : s;
}

void CustomCD::stopTips()
{
	//_tips.stopToolTips();
	//_tips.dispose();
}

void CustomCD::setTips()
{
	//_tips = new TipHelps();
	//_tips.setToolTips(this, "使用金币清除冷却时间");
}

void CustomCD::dispose()
{
	_hasStep = false;
	TimerManage::Instance()->remove( schedule_selector( CustomCD::layout ), this );
	//this.dispatchEvent(new Event(Event.CLEAR));  
}

int CustomCD::getType()
{
	return _type;
}

int CustomCD::getIsLock()
{
	return _lock;
}

void CustomCD::setPreLabString(std::string str)
{
	_preLabel = str;
	if (_tf)
	{
		CCMenuItemImage *pBtnItem = (CCMenuItemImage *)_tf->getChildByTag( TAG_MENU_ITEM+1 );
		if (pBtnItem)
		{
			pBtnItem->setIsVisible(false);
		}
		
	}
	
}

void CustomCD::CDCallback()
{


}

//
//void CustomCD::overCdText(e:MouseEvent)
//{
//	_isMouseOver = true;
//	_tf.underline = _isMouseOver;
//	Mouse.cursor="button";
//}
//
//void CustomCD::outCdText(e:MouseEvent)
//{
//	_isMouseOver = false;
//	_tf.underline = _isMouseOver;
//	Mouse.cursor="auto";
//}