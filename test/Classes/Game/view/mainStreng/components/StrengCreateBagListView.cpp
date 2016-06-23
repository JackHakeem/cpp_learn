#include "StrengCreateBagListView.h"
#include "model/player/RoleManage.h"
#include "StrengGoods.h"
#include "model/streng/vo/StrengGoodsVo.h"
#include "events/GameDispatcher.h"
#include "CCUIBackground.h"
#include "manager/TouchLayerEnum.h"
#include "StrengPanel.h"

static int State_Touch = 1;
static int State_Move = 2;
static int State_End = 3;

StrengCreateBagListView::StrengCreateBagListView( const CCRect& mRect ):CCUIPartialScrollView(mRect)
{
	i = 0;
	pages = 0;
	m_iTouchState = State_Touch;

	//CCLayerColor* pColor = CCLayerColor::layerWithColorWidthHeight( ccc4(0,0,255,100), mRect.size.width, mRect.size.height );
	//this->addChild( pColor );
}


bool StrengCreateBagListView::init()
{
	return CCUIPartialScrollView::init();
}

void StrengCreateBagListView::createGood(  StrengGoodsVo* strengGoodsVo,int sitNum  )
{
	if ( !strengGoodsVo )
	{
		return;
	}
	int index(0);
	GoodsInfo* pGoodsInfo = strengGoodsVo->StrengGoodsInfo;
    
    //Doyang 20120718
    if(!pGoodsInfo)
        return;
        
	if ( pGoodsInfo )
	{
		index = strengGoodsVo->StrengGoodsInfo->id;
	}

	int pagesize = 6;
	std::map<int, StrengGoods*>::iterator it = _goodsDic.find( index );
	if ( it == _goodsDic.end() )
	{
		CCLayer* layer = getLayerByTag( i/pagesize );

		CCRect rect( POSX(20 + (sitNum%2)*250), POSX(285 - (sitNum/2)*135), POSX(245), POSX(120) );

		StrengGoods* strengGoods = StrengGoods::StrengGoodsWithRect( rect );
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

void StrengCreateBagListView::removeSkinChild()
{
	//moveToPage( 1 );
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

void StrengCreateBagListView::updateTip(  int id  )
{
	//StrengGoods* strengGoods = getStrengGoods( id );
	//if(strengGoods)
	//	strengGoods->updateTip();
}

StrengGoods* StrengCreateBagListView::getStrengGoods( int id )
{
	std::map<int, StrengGoods*>::iterator it = _goodsDic.find( id );
	if ( it != _goodsDic.end() )
	{
		return it->second;
	}
	
	return 0;
}

StrengCreateBagListView::~StrengCreateBagListView()
{

}

StrengCreateBagListView* StrengCreateBagListView::strengCreateBagListViewWithCCRect( const CCRect& mRect )
{
	StrengCreateBagListView *pScrollView = new StrengCreateBagListView(mRect);
	if( pScrollView && pScrollView->init() )
	{
		pScrollView->setIsTouchEnabled( true );//That may not be the touch
		return pScrollView;
	}

	CC_SAFE_DELETE(pScrollView)
	return 0;
}

void StrengCreateBagListView::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_Common-1, true);
}

bool StrengCreateBagListView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = pTouch->locationInView(pTouch->view());
	mTouchBeganPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);

	m_iTouchState = State_Touch;
	return CCUIPartialScrollView::ccTouchBegan(pTouch,pEvent);
}

void StrengCreateBagListView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = pTouch->locationInView(pTouch->view());
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	if(abs(mTouchBeganPoint.x - touchPoint.x) < 5)
	{
		return;
	}

	m_iTouchState = State_Move;
	CCUIPartialScrollView::ccTouchMoved(pTouch,pEvent);
}

void StrengCreateBagListView::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
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

	CCNode* pPageLayer = getLayerByTag(index-1);

	if ( m_iTouchState == State_Touch )
	{
		for ( int i = 0; i < pPageLayer->getChildrenCount(); i++ )
		{
			StrengGoods* pGood = (StrengGoods*)pPageLayer->getChildren()->objectAtIndex(i);

			CCPoint itemPoint = getScreenPos(pGood);
			CCSize itemSize = pGood->getContentSize();
			CCPoint locationInView = pTouch->locationInView(pTouch->view());
			CCPoint currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
			if ( CCRect::CCRectContainsPoint(CCRectMake(itemPoint.x,itemPoint.y, itemSize.width,itemSize.height), currentTouchPoint) )
			{
				pGood->ccTouchEnded(pTouch, pEvent);
			}
		}
		

		//std::map<int, StrengGoods*>::iterator it = _goodsDic.begin();
		//for ( ;it != _goodsDic.end();it++ )
		//{
		//	StrengGoods* pGood = it->second;

		//	CCPoint itemPoint = getScreenPos(pGood);
		//	CCSize itemSize = pGood->getContentSize();
		//	CCPoint locationInView = pTouch->locationInView(pTouch->view());
		//	CCPoint currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
		//	if ( CCRect::CCRectContainsPoint(CCRectMake(itemPoint.x,itemPoint.y, itemSize.width,itemSize.height), currentTouchPoint) )
		//	{
		//		pGood->ccTouchEnded(pTouch, pEvent);
		//	}
		//}

		m_iTouchState = State_End;
	}
	else
	{
		if (pPageLayer)
		{
			StrengGoods* pGood = (StrengGoods*)pPageLayer->getChildByTag(0);
			if (pGood)
			{
				pGood->ccTouchEnded(pTouch, pEvent);
			}			
		}
	}
	
	CCUIPartialScrollView::ccTouchEnded(pTouch,pEvent);
}

void StrengCreateBagListView::visit()
{
	StrengPanel* pPanel = (StrengPanel*)this->getParent();
	if (pPanel)
	{
		if (pPanel->m_selectedSpriteImage)
		{
			CCPoint cpImage = ccp(0, POSX(2));
			CCNode* pNodeParent = (CCNode*)pPanel->_curStrengGoods;
			if ( pNodeParent )
			{
				while ( pNodeParent && 
					(pNodeParent != pPanel)
					)
				{
					cpImage = ccpAdd(cpImage, pNodeParent->getPosition());
					pNodeParent = pNodeParent->getParent();
				}
				pPanel->m_selectedSpriteImage->setPosition(cpImage);
			}			
		}
	}
	

	CCUIPartialScrollView::visit();
}


//CCNode * StrengCreateBagListView::getNewHandItem( int eqSitNum )
//{
//	//return this->getStrengGoods(eqSitNum);
//	
//
//	//Doyang 20102727
//	std::map<int, StrengGoods*>::iterator it;
//	for(it = _goodsDic.begin(); it != _goodsDic.end(); ++ it)
//	{
//		if(it->second && 
//			it->second->_equpInfo &&
//			it->second->_equpInfo->sitGrid == eqSitNum)
//		{
//			return it->second;
//		}
//	}
//	return NULL;
//}
