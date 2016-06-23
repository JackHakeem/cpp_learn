#include "HeritageCreate.h"
#include "model/player/RoleManage.h"
#include "StrengGoods.h"
#include "model/streng/vo/StrengGoodsVo.h"
#include "events/GameDispatcher.h"
#include "CCUIBackground.h"
#include "manager/TouchLayerEnum.h"
#include "HeritagePanel.h"
#include "../MainStrengMediator.h"

static int State_Touch = 1;
static int State_Move = 2;
static int State_End = 3;

HeritageCreate::HeritageCreate( const CCRect& mRect ):CCUIPartialScrollView(mRect)
{
	i = 0;
	pages = 0;
	m_iTouchState = State_Touch;


	m_fStep = 0.0f;
	m_bDraded = false;
	m_pClickGood = 0;
	m_fYMove = 0.0f;

	//CCLayerColor* pColor = CCLayerColor::layerWithColorWidthHeight( ccc4(0,0,255,100), mRect.size.width, mRect.size.height );
	//this->addChild( pColor );
}


bool HeritageCreate::init()
{
	if ( !CCUIPartialScrollView::init() )
	{
		return false;
	}

	return true;
}

void HeritageCreate::createGood(  StrengGoodsVo* strengGoodsVo,int sitNum  )
{
	if ( !strengGoodsVo )
	{
		return;
	}
	int index(0);
	GoodsInfo* pGoodsInfo = strengGoodsVo->StrengGoodsInfo;

	if(!pGoodsInfo)
		return;

	if ( pGoodsInfo )
	{
		index = strengGoodsVo->StrengGoodsInfo->id;
	}

	int pagesize = 6;
	std::map<int, HeritageGoods*>::iterator it = _goodsDic.find( index );
	if ( it == _goodsDic.end() )
	{
		CCLayer* layer = getLayerByTag( i/pagesize );

		CCRect rect( POSX(20 + (sitNum%2)*250), POSX(285 - (sitNum/2)*135), POSX(245), POSX(120) );

		HeritageGoods* strengGoods = HeritageGoods::StrengGoodsWithRect( rect );
		strengGoods->initStrengGoodsVo( strengGoodsVo, sitNum );
		strengGoods->setTag(sitNum);
		layer->addChild( strengGoods );
		strengGoods->release();

		strengGoods->setIsTouchEnabled(false);

		_goodsDic.insert( make_pair(index, strengGoods) );
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

	if(i==0)
	{
		s.UseType = 6;	// {UseType:6/* 6 click get info */
		s.sdataStrengGoodsVo = strengGoodsVo;
		GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::SHOW_STRENG_CLICK, &s );
	}

	i++;
}

HeritageGoods* HeritageCreate::getGoods( int index )
{
	std::map<int, HeritageGoods*>::iterator it = _goodsDic.find( index );
	if ( it != _goodsDic.end() )
	{
		return it->second;
	}
	return 0;
}

void HeritageCreate::removeSkinChild()
{
	this->moveToPage( 1 );
	for (int j = 0; j < pages; j++)
	{
		CCLayer* layer = getLayerByTag(j);
		if (layer)
		{
			layer->removeAllChildrenWithCleanup(true);
			layer->removeFromParentAndCleanup(true);
			totalScreens--;
		}
	}
	totalScreens = 0;
	currentScreen = 0;

	_goodsDic.clear();

	i = 0;
}

HeritageGoods* HeritageCreate::getStrengGoods( int id )
{
	std::map<int, HeritageGoods*>::iterator it = _goodsDic.find( id );
	if ( it != _goodsDic.end() )
	{
		return it->second;
	}

	return 0;
}

HeritageCreate::~HeritageCreate()
{

}

HeritageCreate* HeritageCreate::HeritageCreateWithCCRect( const CCRect& mRect )
{
	HeritageCreate *pScrollView = new HeritageCreate(mRect);
	if( pScrollView && pScrollView->init() )
	{
		pScrollView->setIsTouchEnabled( true );//That may not be the touch
		return pScrollView;
	}

	CC_SAFE_DELETE(pScrollView)
		return 0;
}

void HeritageCreate::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_Common-1, true);
}

bool HeritageCreate::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	m_iTouchState = State_Touch;


	CCPoint locationInView = pTouch->locationInView(pTouch->view());
	preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	m_fStep = 0.0f;
	m_bDraded = false;
	m_pClickGood = 0;
	m_state = State_Touch;
	this->unschedule(schedule_selector(HeritageCreate::update));

	if (currentScreen>0)
	{
		CCNode* pPageLayer = getLayerByTag(currentScreen-1);
		if (pPageLayer)
		{
			for ( int i = 0; i < pPageLayer->getChildrenCount(); i++ )
			{
				HeritageGoods* pGood = (HeritageGoods*)pPageLayer->getChildren()->objectAtIndex(i);

				CCPoint itemPoint = getScreenPos(pGood);
				CCSize itemSize = pGood->getContentSize();
				CCPoint locationInView = pTouch->locationInView(pTouch->view());
				CCPoint currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
				if ( CCRect::CCRectContainsPoint(CCRectMake(itemPoint.x,itemPoint.y, itemSize.width,itemSize.height), currentTouchPoint) )
				{
					m_pTouch = pTouch;
					m_pEvent = pEvent;

					m_pClickGood = pGood;
					this->schedule(schedule_selector(HeritageCreate::update), 0);
					break;
				}
			}
		}
	}
	

	return CCUIPartialScrollView::ccTouchBegan(pTouch,pEvent);
}

void HeritageCreate::update( ccTime dt )
{
	if ( m_state == State_Touch )
	{
		m_fStep += dt;
		if ( m_fStep > 0.1f )
		{
			m_pClickGood->ccTouchBegan(m_pTouch, m_pEvent);
			g_pMainStrengMediator->_inheritPanel->fadeAct();

			this->unschedule(schedule_selector(HeritageCreate::update));
			m_fStep = 0.0f;
			m_bDraded = true;
		}
	}
}

void HeritageCreate::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint locationInView = pTouch->locationInView(pTouch->view());
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	if (abs(touchPoint.x - preTouchPoint.x) < 5)
	{
		return;
	}
	m_state = State_Move;

	this->unschedule(schedule_selector(HeritageCreate::update));
	m_fStep = 0.0f;

	if (m_bDraded)
	{
		if(!m_pClickGood)
			return;
		m_pClickGood->ccTouchMoved(pTouch, pEvent);
	} 
	else
	{
		CCUIPartialScrollView::ccTouchMoved(pTouch,pEvent);
	}
}

void HeritageCreate::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	int index = 0;
	CCPoint touchPoint = pTouch->locationInView(pTouch->view());
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);

	int newX = (int)touchPoint.x;

	if ( (newX - startSwipe) < -scrollWidth / 3 && (currentScreen+1) <= totalScreens )
	{
		index = currentScreen+1;
	}
	else if ( (newX - startSwipe) > scrollWidth / 3 && (currentScreen-1) > 0 )
	{
		index = currentScreen-1;
	}
	else
	{
		index = currentScreen;	
	}

	if ((m_state!=State_Move) && m_pClickGood &&!m_bDraded)
	{
		m_pClickGood->onRollOverHandler();
	}
	

	m_state = State_End;
	if (m_bDraded)
	{
		if( m_pClickGood )
		{
			g_pMainStrengMediator->_inheritPanel->StopfadeAct();
			return m_pClickGood->ccTouchEnded(pTouch, pEvent);
		}
	}
	else
		CCUIPartialScrollView::ccTouchEnded(pTouch, pEvent);
}

void HeritageCreate::updateGoods( GoodsInfo* _goodsInfo1, int type )
{
	if( !_goodsInfo1 )	return;
	HeritageGoods* good = getGoods( _goodsInfo1->id );
	if( !good )	return;

	if( type == 1)
	{ // +
		good->resetPic();
	}
	if(type == 2)
	{ // -
		good->resetPic();
	}
}

void HeritageCreate::updateTip( uint32 id )
{
	HeritageGoods* strengGoods = getStrengGoods( id );
	if(strengGoods)
		strengGoods->updateTip();
}
