#include "StrengFigureCreate.h"
#include "FigureItem.h"
#include "model/player/RoleManage.h"
#include "../MainStrengMediator.h"
#include "StrengPanel.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"

#define FIGURE_ITEM_COUNT_PER_PAGE 1

StrengFigureCreate::StrengFigureCreate( const CCRect& mRect ):CCUIPartialScrollView(mRect)
{
	_totalPage = 0;
	_item = 0;
}

StrengFigureCreate* StrengFigureCreate::figureCreatScrollViewWithCCRect( const CCRect& mRect )
{
	StrengFigureCreate *pScrollView = new StrengFigureCreate(mRect);
	if( pScrollView && pScrollView->init() )
	{
		pScrollView->setIsTouchEnabled( true );//That may not be the touch
		//pScrollView->contentLayer->setOpacity( 1.0f );
		return pScrollView;
	}

	CC_SAFE_DELETE(pScrollView)
	return 0;
}

bool StrengFigureCreate::init()
{
	if ( !CCUIPartialScrollView::init() )
	{
		return false;
	}

	return true;
}

void StrengFigureCreate::buildList()
{
	RoleManage* pRoleManager = RoleManage::Instance();
	if ( !pRoleManager )
	{
		return;
	}
	PlayerInfoVo* pPlayerInfoVo = pRoleManager->roleInfo();
	if ( !pPlayerInfoVo )
	{
		return;
	}

	delList();
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_Common, true);

	//std::map<int, PlayerInfoVo>* mercList = pRoleManager->mercList();
	//std::map<int, PlayerInfoVo>::iterator it = mercList->begin();
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* mercList = RoleManage::Instance()->mercListEx();  // LH20121019listorder
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator it = mercList->begin();

	int length = mercList->size();
	_totalPage = ( length%FIGURE_ITEM_COUNT_PER_PAGE==0 ) ? (length/FIGURE_ITEM_COUNT_PER_PAGE) : (length/FIGURE_ITEM_COUNT_PER_PAGE + 1);
	for ( int i = 0; i < _totalPage; i++ )
	{
		addLayerByTag(i);
	}

	CCSize cs = this->getContentSize();

	int startNum = 0;		// 0 begin
	int i = 0;
	for ( it ; it != mercList->end(); it++ )
	{
		i++;
		CCLayer* layer = getLayerByTag( i-1 );
		startNum = i%FIGURE_ITEM_COUNT_PER_PAGE;

		PlayerInfoVo* playerInfo = &(it->second);
		CCRect rect1( POSX( 10 + (startNum-1)*395 ), 0, POSX(395), POSX(83) );
		FigureItem* pFigureItem = FigureItem::FigureItemlWithRect( rect1 );	// figure
		pFigureItem->initPlayerVo( playerInfo, startNum );

		m_figures.push_back(pFigureItem);
		layer->addChild( pFigureItem, 1, startNum );
		pFigureItem->release();
	}

	if ( m_figures.size()>0 )
	{
		FigureItem* child = m_figures[0];
		itemClickHandler( child );
	}
	
}

void StrengFigureCreate::delList()
{
	for ( vector<FigureItem *>::iterator it = m_figures.begin(); it != m_figures.end(); it++ )
	{
		FigureItem* child = *it;
		//child->removeAllChildrenWithCleanup(true);
		child->removeFromParentAndCleanup(true);
	}
	m_figures.clear();
	_item = 0;

	this->moveToPageImmediately(1);
	for ( int i = 0; i < _totalPage; i++ )
	{
		CCLayer* layer = getLayerByTag(i);
		if ( layer )
		{
			layer->removeAllChildrenWithCleanup(true);
			layer->removeFromParentAndCleanup(true);
			//contentLayer->removeChildByTag( i, true );
			totalScreens--;
		}
	}
	totalScreens = 0;
	currentScreen = 0;
}

void StrengFigureCreate::itemClickHandler( FigureItem* item )
{
	StrengPanel* panel = g_pMainStrengMediator->_strengPanel;
	MagicPanel* pMagicPanel = g_pMainStrengMediator->_magicPanel;
	if ( item == _item )
	{
		if ( panel && panel->getIsVisible()  )
		{
			if (!panel->m_bShowBag)
			{ 
				return;
			}		
		}
		if ( pMagicPanel && pMagicPanel->getIsVisible() && !pMagicPanel->m_bShowBag )
		{
			return;
		}
	}
	_item = item;

	if ( panel && panel->getIsVisible() )
	{
		panel->figureSelectHandler( item );
	}
	
	if ( pMagicPanel && pMagicPanel->getIsVisible() )
	{
		pMagicPanel->figureSelectHandler( item );
	}
	
}

// void StrengFigureCreate::registerWithTouchDispatcher()
// {
// 	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_Common, true);
// }

void StrengFigureCreate::onExit()
{
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

void StrengFigureCreate::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint touchPoint = pTouch->locationInView(pTouch->view());
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);

	int newX = (int)touchPoint.x;

	FigureItem* child = 0;
	if ( (newX - startSwipe) < -scrollWidth / 3 && (currentScreen+1) <= totalScreens )
	{
		this->moveToNextPage();
	}
	else if ( (newX - startSwipe) > scrollWidth / 3 && (currentScreen-1) > 0 )
	{
		this->moveToPreviousPage();
	}
	else
	{
		this->moveToPage(currentScreen);	
	}

	int index = currentScreen -1;
	if ( ( index >= 0 ) && ( index < (int)m_figures.size() ) )
	{
		child = m_figures[index];
		itemClickHandler( child );
	}
}

void StrengFigureCreate::moveToNextPageClick()
{	
	FigureItem* child = 0;
	if ( (currentScreen+1) <= totalScreens )
	{
		this->moveToNextPage();
	}

	int index = currentScreen -1;
	if ( ( index >= 0 ) && ( index < (int)m_figures.size() ) )
	{
		child = m_figures[index];
		itemClickHandler( child );
	}
}

void StrengFigureCreate::moveToPreviousPageClick()
{
	FigureItem* child = 0;
	if ( (currentScreen-1) > 0 )
	{
		this->moveToPreviousPage();
	}

	int index = currentScreen -1;
	if ( ( index >= 0 ) && ( index < (int)m_figures.size() ) )
	{
		child = m_figures[index];
		itemClickHandler( child );
	}	
}

CCNode * StrengFigureCreate::getNewHandItem( int mercId )
{
	std::vector<FigureItem *>::iterator it;
	for(it = m_figures.begin(); it != m_figures.end(); ++it)
	{
		FigureItem *pFigureItem = *it;
		if(!pFigureItem)
			continue;

		if(pFigureItem->_playerInfoVo->figureBaseInfo.mercId = mercId)
		{
			return pFigureItem;
		}
	}
	return NULL;
}

StrengFigureCreate::~StrengFigureCreate()
{

}
