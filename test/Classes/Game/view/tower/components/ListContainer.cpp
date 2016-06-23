#include "ListContainer.h"
#include "../TowerMediator.h"
#include "TowerRank.h"
#include "TowerRankItem.h"
#include "utils/ScaleUtil.h"
#include "model/player/RoleManage.h"
#include "manager/LangManager.h"

const float h_interval = 39.0f;
const float w_frame = 602;
const float h_frame = 39.0f;

ListContainer::ListContainer(const CCRect& mRect):CCUIPartialScrollView(mRect)
{
	selectedItem = 0;
	m_selectedSpriteImage = 0;
}

ListContainer::~ListContainer()
{}

ListContainer* ListContainer::ListContainerScrollViewWithCCRect(const CCRect& mRect)
{
	ListContainer *pScrollView = new ListContainer(mRect);
    if(pScrollView && pScrollView->init()){
		// pScrollView->setIsTouchEnabled(false);//That may not be the touch
        //pScrollView->autorelease();
        return pScrollView;
    }
    CC_SAFE_DELETE(pScrollView)
    return NULL;
}

void ListContainer::handleTouchEndPagePre()
{
	CCNode* par = (CCNode*)this->getParent();
	if (par)
	{
		TowerPageNav* pageNav = 0;
		pageNav = (TowerPageNav*)par->getChildByTag(99);
		if (pageNav)
		{
			if (pageNav->_curPage <= 1) 
			{
				this->moveToPage(currentScreen);
			}
			else
				pageNav->onPrevHandler(0);
			
		}
	}
}

void ListContainer::handleTouchEndPageNext()
{
	CCNode* par = (CCNode*)this->getParent();
	if (par)
	{
		TowerPageNav* pageNav = 0;
		pageNav = (TowerPageNav*)par->getChildByTag(99);
		
		if (pageNav)
		{
			if (pageNav->_curPage >= pageNav->_maxPage)
			{
				this->moveToPage(currentScreen);
			}
			else
				pageNav->onNextHandler(0);
		}
	}
}

bool ListContainer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint locationInView = pTouch->locationInView(pTouch->view());
	preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	return CCUIPartialScrollView::ccTouchBegan(pTouch, pEvent);
}

void ListContainer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	return CCUIPartialScrollView::ccTouchMoved(pTouch, pEvent);
}

void ListContainer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint locationInView = pTouch->locationInView(pTouch->view());
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	TowerProxy* _towerProxy = (TowerProxy*)g_pFacade->retrieveProxy( AppFacade_TOWER_PROXY_CHANGE );
	if (!_towerProxy->getpanel1Vo())
	{
		return;
	}
	if (!_towerProxy->getpanel1Vo())
	{
		return;
	}
	int lev = _towerProxy->getpanel1Vo()->maxFloor;

	int pageLimit = 0;
	if(lev <= 40){
		pageLimit = 9;
	}else if(lev <= 60){
		pageLimit = 7;
	}else if(lev <= 80){
		pageLimit = 5;
	}else if(lev <= 100){
		pageLimit = 3;
	}else if(lev <= 120){
		pageLimit = 1;
	}
	int page = pageLimit;
	if ((touchPoint.x - preTouchPoint.x) < -2.0f)
	{
		page = currentScreen + 1;
	}
	if ((touchPoint.x - preTouchPoint.x) > 2.0f)
	{
		page = currentScreen - 1;
	}

	if (lev>40)
	{
		if ( (page<pageLimit) || (page>(pageLimit+1)) )
		{
			LangManager::msgShow("TOWR108");
			this->moveToPage(currentScreen);
			return;
		}
	}
	else
	{
		if ( (page<pageLimit) || (page>(pageLimit+3)) )
		{
			LangManager::msgShow("TOWR108");
			this->moveToPage(currentScreen);
			return;
		}
	}
		
	int newX = (int)touchPoint.x;
		
	stateSscroll = -1;
	if ( (newX - startSwipe) < -scrollWidth / 3 && (currentScreen+1) > totalScreens )
	{
		handleTouchEndPageNext();
		stateSscroll = 0;
	}

	else 
	if ( (newX - startSwipe) < -scrollWidth / 3 && (currentScreen+1) <= totalScreens )
	{
		//this->moveToNextPage();
		handleTouchEndPageNext();
		stateSscroll = 0;
	}
	else if ( (newX - startSwipe) > scrollWidth / 3 && (currentScreen-1) > 0 )
	{
		//this->moveToPreviousPage();
		handleTouchEndPagePre();
		stateSscroll = 1;
	}
	else
	{
		this->moveToPage(currentScreen);
		handleTouchEnd2Page();
		stateSscroll = 2;
	}	
	
	CCNode* pPageLayer = getLayerByTag(currentScreen-1);
	if (pPageLayer)
	{
		int cnt = pPageLayer->getChildrenCount();
		for ( int i = 0; i < cnt; i++ )
		{
			TowerRankItem* pItem = (TowerRankItem*)pPageLayer->getChildren()->objectAtIndex(i);
			if (pItem&&m_selectedSpriteImage)
			{

				CCPoint itemPoint = getScreenPos(pItem);
				CCSize itemSize = pItem->getContentSize();
				CCPoint locationInView = pTouch->locationInView(pTouch->view());
				CCPoint currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
				if ( CCRect::CCRectContainsPoint(
					CCRectMake(itemPoint.x,itemPoint.y, itemSize.width,itemSize.height), currentTouchPoint)
					)
				{
					m_selectedSpriteImage->setPosition(ccp(POSX(5), POSX(389-h_interval-i*h_interval)));
					selectedItem = pItem;

					g_pTowerMediator->_towerRank->checkClickSelf( pItem->itemVo );
				}
			}
		}
	}

	this->setIsTouchingMoving(false);
}

void ListContainer::handleTouchEndAfter(bool same, int curlayertag)
{
	if (!same && stateSscroll == 0)
	{
		this->moveToNextPage();
	}
	else if (!same && stateSscroll == 1)
	{
		this->moveToPreviousPage();
	}
	else if (same)
	{
		this->moveToPage(curlayertag+1);
		if (stateSscroll == 0)
		{//目标是下一页，但是没下页了，所以要把原来下页的东西都清除
			CCLayer* l = this->getLayerByTag(curlayertag+1);
			if (l)
				l->removeAllChildrenWithCleanup(true);
		}
		else if (stateSscroll == 1)
		{//目标是上一页，但是没上页了，所以要把原来下页的东西都清除
			//this->moveToPage(currentScreen);
			CCLayer* l = this->getLayerByTag(curlayertag-1);
			if (l)
				l->removeAllChildrenWithCleanup(true);
			
		}
	}
	

	stateSscroll = -1;
}

void ListContainer::updateList(std::list<TowerRankItemVo*>& volist, int page)
{
	if (!m_selectedSpriteImage)
	{
		m_selectedSpriteImage = new CCUIBackground();
		m_selectedSpriteImage->initWithSpriteFrame( "train/gold_back.png",
			ccp(0, POSX(2)), CCPointZero, CCSizeMake( POSX(w_frame), POSX(h_frame) ) );
		this->addChild( m_selectedSpriteImage );
		m_selectedSpriteImage->release();
		m_selectedSpriteImage->setPosition(ccp(POSX(5), POSX(389-h_interval-0*h_interval)));
	}

	//int page = g_pTowerMediator->_towerRank->_pageNav->_curPage;
	CCLog("page change:%d", page);
	CCLayer* l = this->getLayerByTag(page-1);
	if (l)
		l->removeAllChildrenWithCleanup(true);
	
	for (int i = 0; i < page; i++)
	{
		CCLayer* lay = this->getLayerByTag(i);
		if (!lay)
		{
			lay = this->addLayerByTag(i);
		}
	}
	l = this->getLayerByTag(page-1);
	
	std::list<TowerRankItemVo*>::iterator it;
	int32 index = 0;
	for (it = volist.begin(); it != volist.end(); it++, index++)
	{
		TowerRankItemVo* gvb = *it;
		if (gvb)
		{
			TowerRankItem* newItem = new TowerRankItem();
			newItem->init(gvb);
			l->addChild(newItem, index, index);
			newItem->release();
			newItem->setPosition(ccp(POSX(5), POSX(389-h_interval-index*h_interval)));
		}
	}

	bool same = (currentScreen == page)?true:false;
	this->handleTouchEndAfter(same, page-1);
	currentScreen = page;

	CCNode* pNode = 0;
	if (pNode = l->getChildByTag(0))
	{
		selectedItem = (TowerRankItem*)pNode;
	}
	
	if (selectedItem && selectedItem->itemVo)
	{
		g_pTowerMediator->_towerRank->checkClickSelf( selectedItem->itemVo );
	}	
}