#include "RecruitPanel.h"
#include "RecruitItem.h"
#include "RecruitView.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"
#include "manager/ViewManager.h"

#define RECRUIT_ITEM_COUNT_PER_PAGE 8

RecruitPanel::RecruitPanel( const CCRect& mRect ):CCUIPartialScrollView(mRect)
{
	_item = 0;
	isList = false;

 	//CCLayerColor* pColor = CCLayerColor::layerWithColorWidthHeight( ccc4(0,0,255,100), mRect.size.width, mRect.size.height );
 	//this->addChild( pColor );

}

bool RecruitPanel::init()
{
	return CCUIPartialScrollView::init();
}

RecruitPanel* RecruitPanel::recruitPanelScrollViewWithCCRect( const CCRect& mRect )
{
	RecruitPanel *pScrollView = new RecruitPanel(mRect);
	if( pScrollView && pScrollView->init() )
	{
		pScrollView->setIsTouchEnabled( true );//That may not be the touch
		return pScrollView;
	}

	CC_SAFE_DELETE(pScrollView)
	
	return 0;
}

/**
* clean and repain list
* @param infos: array
* @param page: cur page
* @param pagesize
*/
void RecruitPanel::createItems( vector<RecruitInfo> infos, int page, uint totalPage, int pagesize )
{
	setIsTouchEnabled( true );
	
	removeAllChild();
		
	RecruitView* pRecruitView = ViewManager::getInstance()->recruitView; 
	pRecruitView->_totalPage = totalPage;
	for (int i = 0; i < totalPage; i++)
	{
		addLayerByTag(i);
	}

	isList = false;

	reBuildItems( infos, page, pagesize );
}

void RecruitPanel::reBuildItems( vector<RecruitInfo> infos, int page, int pagesize )
{
	int startNum;

	//join
	for ( int i = 0; i < infos.size(); i++ )
	{
		CCLayer* layer = getLayerByTag( i/RECRUIT_ITEM_COUNT_PER_PAGE );
		startNum = i%RECRUIT_ITEM_COUNT_PER_PAGE;

		RecruitInfo info = infos[i];
		RecruitItem* item = RecruitItem::RecruitItemWithRect(
			CCRectMake( POSX(15 + (startNum%2)*235), POSX(405 - 105/2 - (startNum/2)*110), POSX(215), POSX(105) ) );
		item->initRecruitInfo( info, startNum );
		layer->addChild( item, 1, startNum );
		item->release();
		_dic.insert( make_pair( item->id(), item ) );

		if( !isList && !info.isHired )
		{
			RecruitView* pRecruitView = ViewManager::getInstance()->recruitView;
			if ( pRecruitView )
			{
				pRecruitView->recItemHandler(item);
			}
			//item.highlight = true;
			_item = item;
			isList = true;
		}
	}

}

/** 
* ¼àÌýItemµã»÷
* @param event
*/ 
void RecruitPanel::onSingleClickHandler( RecruitItem* item )
{
	//if(_item)	_item.highlight = false;
	//item.highlight = true;
	_item = item;
	RecruitView* pRecruitView = ViewManager::getInstance()->recruitView;
	if ( pRecruitView )
	{
		pRecruitView->recItemHandler(item);
	}
	//dispatchEvent(new ParamEvent(CURRENT_ITEM, {item: item}));
}

void RecruitPanel::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_Common, true);
}

bool RecruitPanel::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return CCUIPartialScrollView::ccTouchBegan(pTouch,pEvent);
}

void RecruitPanel::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCUIPartialScrollView::ccTouchMoved(pTouch,pEvent);
}

void RecruitPanel::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
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
	if (pPageLayer)
	{
		RecruitItem* pItem = (RecruitItem*)pPageLayer->getChildByTag(0);
		if (pItem)
		{
			pItem->ccTouchEnded(pTouch, pEvent);
		}			
	}

	CCUIPartialScrollView::ccTouchEnded(pTouch,pEvent);
}

void RecruitPanel::removeAllChild()
{
	map<int, RecruitItem*>::iterator it = _dic.begin();
	for ( ; it != _dic.end(); it++ )
	{
		RecruitItem* child = it->second;
		if ( child->getParent() )
		{
			child->removeFromParentAndCleanup(true);
		} 
		//child->release();

		child = 0;
	}
	_dic.clear();

	this->moveToPage( 1 );
	RecruitView* pRecruitView = ViewManager::getInstance()->recruitView; 
	for (int i = 0; i < pRecruitView->_totalPage; i++)
	{
		CCLayer* layer = getLayerByTag(i);
		if (layer)
		{
			layer->removeAllChildrenWithCleanup(true);
			layer->removeFromParentAndCleanup(true);
			totalScreens--;
		}
	}
	totalScreens = 0;
	currentScreen = 0;

	_item = 0;
}

void RecruitPanel::visit()
{
	RecruitView* pPanel = (RecruitView*)ViewManager::getInstance()->recruitView;
	if (pPanel)
	{
		if (pPanel->m_selectedSpriteImage)
		{
			CCPoint cpImage = CCPointZero;
			CCNode* pNodeParent = (CCNode*)_item;
			if ( pNodeParent )
			{
				pPanel->m_selectedSpriteImage->setIsVisible(true);
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