#include "CCUITaskPanelListView.h"
#include "CCUITaskPanelItem.h"
#define HEIGHT_DISTANCE 20

void CCUITaskPanelListView::onItemClick( int position )
{
	int childSize = getChilds()->count();

	if(_actionsRunning 
		|| position < 0
		|| position >= childSize)
		return;


	_actionsRunning = true;
	CCUITaskPanelItem *item = (CCUITaskPanelItem *) getChilds()->getObjectAtIndex(position);
	if(!item) 
	{
		_actionsRunning = false;
		return;
	}
	_heightDistance = item->isExpand() ? -HEIGHT_DISTANCE : HEIGHT_DISTANCE;

	if((_clickPos >= 0 && _clickPos < childSize)
		&& _clickPos != position
		&& !item->isExpand()
		&& _hasExpand)
	{
		CCUITaskPanelItem *pPreItem = (CCUITaskPanelItem *) getChilds()->getObjectAtIndex(_clickPos);
		if(pPreItem && pPreItem->isExpand())
		{
			pPreItem->setClipSize(CCSizeMake(pPreItem->getClipSize().width, pPreItem->getMinHeight()));
			pPreItem->endCollapsed();

			float subHeight = pPreItem->getMaxHeight() - pPreItem->getMinHeight();
			for(int i=_clickPos+1; i<childSize; ++i)
			{
				CCUITaskPanelItem *item = (CCUITaskPanelItem *) getChilds()->getObjectAtIndex(i);
				CCPoint currentPosition = item->getPosition();
				currentPosition.y += subHeight;
				item->setPosition(currentPosition);
			}
			if(!contentLayer)
				return;
			CCSize currentSize = contentLayer->getContentSize();
			CCUIListView::resetContentLayerSize(CCSizeMake(currentSize.width, currentSize.height
				- subHeight));
		}
	}

	_clickPos = position;
	this->schedule(schedule_selector(CCUITaskPanelListView::update), 0);
	CCUIListView::onItemClick(position);
}
//
//void CCUITaskPanelListView::bindView( CCNode *itemCell, int position, CCPoint ccPosition )
//{
//	itemCell->setTag(position);
//	itemCell->setPosition(ccp(0, 50 * position));
//}

void CCUITaskPanelListView::update( ccTime dt )
{
	// scale item
	CCUITaskPanelItem *scaleItem = (CCUITaskPanelItem *) getChilds()->getObjectAtIndex(_clickPos);
	if(!scaleItem)
		return;
	CCSize scaleItemCurrentSize = scaleItem->getClipSize();
	int scaleItemHeight = scaleItemCurrentSize.height + _heightDistance;
	if(scaleItemHeight < scaleItem->getMinHeight())
	{
		scaleItemHeight = scaleItem->getMinHeight();
		_heightDistance = scaleItemHeight - scaleItemCurrentSize.height;
		_actionsRunning = false;
		this->unschedule(schedule_selector(CCUITaskPanelListView::update));
		scaleItem->endCollapsed();
		_hasExpand = false;
	}
	if(scaleItemHeight > scaleItem->getMaxHeight())
	{
		scaleItemHeight = scaleItem->getMaxHeight();
		_heightDistance = scaleItemHeight - scaleItemCurrentSize.height;
		_actionsRunning = false;
		this->unschedule(schedule_selector(CCUITaskPanelListView::update));
		scaleItem->endExpanded();
		_hasExpand = true;
	}
	scaleItem->setClipSize(CCSizeMake(scaleItemCurrentSize.width, scaleItemHeight));

	// action items
	int childSize = getChilds()->count();
	for(int i=_clickPos + 1; i<childSize; ++i)
	{
		CCUITaskPanelItem *item = (CCUITaskPanelItem *) getChilds()->getObjectAtIndex(i);
		CCPoint currentPosition = item->getPosition();
		currentPosition.y -= _heightDistance;
		item->setPosition(currentPosition);
	}
	if(!contentLayer)
		return;
	CCSize currentSize = contentLayer->getContentSize();
	CCUIListView::resetContentLayerSize(CCSizeMake(currentSize.width, currentSize.height + _heightDistance));

	/*CCPoint contentLayerPoint = contentLayer->getPosition();
	contentLayerPoint.y -= _heightDistance;
	contentLayer->setPosition(contentLayerPoint);*/
	/*float newBottomEdge = getBottomEdgePosition();
	newBottomEdge += _heightDistance;
	setBottomEdgePosition(newBottomEdge);
	float newListHeight = getListHeight();
	newListHeight += _heightDistance;
	setListHeight(newListHeight);*/
}

CCUITaskPanelListView* CCUITaskPanelListView::listViewWithCCRect( const CCRect& mRect, bool isHorizontal )
{
	CCUITaskPanelListView *pListView = new CCUITaskPanelListView();
	if(pListView)
	{
		pListView->_actionsRunning = false;
		pListView->setIsLockHorizontal(isHorizontal);
		pListView->setRect(mRect);
		pListView->init();
		pListView->_clickPos = 0;
		pListView->_hasExpand = true;
		pListView->autorelease();
		return pListView;
	}
	CC_SAFE_DELETE(pListView);
	return NULL;
}

void CCUITaskPanelListView::resetContentLayerSize()
{

}
