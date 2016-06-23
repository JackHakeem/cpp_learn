
#include "KKCCUIListView.h"
#include "utils/ScaleUtil.h"
#define DISTANCE_CLICK 10
//#define ITEM_MAX 50

KKCCUIListView::~KKCCUIListView()
{
	_childViewList->release();
}

KKCCUIListView* KKCCUIListView::listViewWithCCRect(const CCRect& mRect, int ITEM_MAX){
	KKCCUIListView *pListView = new KKCCUIListView();
	if(pListView)
	{
		pListView->setRect(mRect);
		pListView->init(ITEM_MAX);
		//pListView->autorelease(); kevin modified
		return pListView;
	}
	CC_SAFE_DELETE(pListView);
	return NULL;
}

void KKCCUIListView::cleanLayer()
{
	if (!contentLayer)
		return;
	if (!contentLayer->getParent())
		return;
	if (!_childViewList)
		return;

	for (int i = 0; i < _childViewList->count(); i++)
	{
		//_childViewList->getObjectAtIndex(i)->release();
	}
	_childViewList->removeAllObjects();
	contentLayer->removeAllChildrenWithCleanup(true);

	
	listHeight = 0;
	listWidth = 0;

}

bool KKCCUIListView::add(KKCCUIListViewAdapter *adapter)
{
	if (!contentLayer)
		return false;
	if (!contentLayer->getParent())
		return false;
	if (!_childViewList)
		return false;
	if (!adapter)
		return false;
	//if(!contentLayer || !contentLayer->getParent() || !_childViewList || !adapter)
	//	return false;

	int oldSize = _childViewList->count();
	int dTmpSize = 0;
	int childSize = 0;
	//listHeight = 0;
	//listWidth = 0;
	
	CCSize contentSize = this->getContentSize();

	this->_pAdapter = adapter;
	
	if (!_pAdapter->getViewList())
		return false;
	std::vector<LayerNode*>* pitemCellList = _pAdapter->getViewList();//内容
	std::vector<LayerNode*> itemCellList;
	//先节流 最多只插入ITEM_MAX个 begin
	if (pitemCellList->size() > ITEM_MAX)
	{
		for (int i = pitemCellList->size()-ITEM_MAX; i < pitemCellList->size(); i++)//只取最后ITEM_MAX个准备加入的
			itemCellList.push_back((*pitemCellList)[i]);
	}
	else
	{
		itemCellList = *pitemCellList;
	}
	//先节流 最多只插入ITEM_MAX个 end

	childSize = itemCellList.size();//内容数
	if(childSize <= 0)
		return false;
	
	contentLayer = (CCLayerColor*)this->getChildByTag(1);//容器
	if (!contentLayer)
		return false;

	int realAddCounter = 0;//实际要加的新的itemCellList是几个

	//计算高度begin
	for(int i=0; i<childSize; i++)
	{
		LayerNode* itemCell = itemCellList[i];
		if(!itemCell) continue;

		//加高度
		if (_childViewList->count() < ITEM_MAX)
		{//超过ITEM_MAX则只加入_childViewList而不再提升，下面代码会进行“清理”处理
			listHeight += itemCell->getvisibleSize().height;
			listHeight += this->getSpacingVertical();		
		}
		else
			dTmpSize++;
		//
		_childViewList->addObject(itemCell);
		//itemCell->release();//kevink
		realAddCounter++;
		
	}
	//如果多于allItemUpY则要清理  begin
	int deleteSize = _childViewList->count() - ITEM_MAX;		
	if (deleteSize > 0)
	{
		float allItemUpY = 0;
		//1. 组织整体上升allItemUpY是多少
		for (int i = 0; i < deleteSize; i++)
		{
			LayerNode* itemCell = _childViewList->getObjectAtIndex(i+oldSize);
			if (itemCell)
			{
				allItemUpY += itemCell->getvisibleSize().height;
				allItemUpY += this->getSpacingVertical();
			}
		}
		//2. 清除0~deleteSize
		for (int i = 0; i < deleteSize; i++)
		{
			LayerNode* itemCell = _childViewList->getObjectAtIndex(i);
			if (itemCell)
			{
				if (itemCell->getParent())
				{
					itemCell->removeFromParentAndCleanup(true);//删除已经存在的旧的
					if (oldSize > 0)
						oldSize--;
				}
				else
					realAddCounter--;//删除刚才加进去的新的
			}

			_childViewList->removeObjectAtIndex(i);//_childViewList->count()-realAddCounter-1-i
			
		}
		//3. 对旧的早已存在的ITEM进行整体上升allItemUpY
		if (oldSize > 0)
		for (int i = 0; i < oldSize/*_childViewList->count()*/; i++)
		{
			LayerNode* itemCell = _childViewList->getObjectAtIndex(i);
			if (itemCell)
				itemCell->setPosition(ccpAdd(itemCell->getPosition(), ccp(0, allItemUpY)));
		}
	}
	//如果多于allItemUpY则要清理  end
	//listHeight -= this->getSpacingVertical();
	// = childSize - ITEM_MAX;//从第几个开始设置坐标
	//计算高度end

	resetEdgePosition();

	contentLayer->setContentSize(CCSizeMake(contentSize.width , listHeight));
	CCPoint newPosition = ccp(0, listHeight);//ccp(0, topEdgePosition);
	contentLayer->setPosition(newPosition);
	
	// add each child to contentlayer.
	childSize = _childViewList->count();
	float childPositionY = (listHeight)*-1.0f;
	float childPositionX = (listWidth )*-1.0f;

	for(int i=realAddCounter-1; i>=0; i--)
	{
		LayerNode *itemCell = _childViewList->getObjectAtIndex(i+oldSize);

		
		//itemCell->setTag(i);
		{
			float height = itemCell->getContentSize().height + this->getSpacingVertical();
			itemCell->setPosition(ccp(0, childPositionY+height-itemCell->getContentSize().height));
			childPositionY += height;
		}

		if(itemCell && !itemCell->getParent())
		{
			contentLayer->addChild(itemCell, 0);//, i+oldSize
		}
	}

	return true;

}
void KKCCUIListView::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, m_pri, true);
}

bool KKCCUIListView::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint locationInView = pTouch->locationInView(pTouch->view());
	_preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
	if (this->getIsTouchInContentLayer(pTouch)) 
	{
		_clickPosition = _preTouchPoint;
		_isClick = true;
		isScrolling = true;

		// On item touch.
		int touchId = getItemIdWithPosition(_preTouchPoint);
		this->setTouchItemId(touchId);
		this->onItemTouch(touchId);
	}
	else 
		isScrolling = false;

	return isScrolling;
}


void KKCCUIListView::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	if ( !contentLayer )
	{
		return;
	}
	
	contentLayer->stopAllActions();
	CCPoint locationInView = pTouch->locationInView(pTouch->view());
	_currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
	CCPoint deltaPoint = ccpSub(_currentTouchPoint, _preTouchPoint);

	deltaPoint.x=0;

	CCPoint newPosition = ccpAdd(contentLayer->getPosition(), deltaPoint);
	contentLayer->setPosition(newPosition);
	_preTouchPoint = _currentTouchPoint;
	//CCLog("------------clickPos,x=%f,y=%f,cur,x=%f,y=%f", _clickPosition.x, _clickPosition.y, _currentTouchPoint.x, _currentTouchPoint.y);
	if(_clickPosition.x - _currentTouchPoint.x > DISTANCE_CLICK
		|| _clickPosition.y - _currentTouchPoint.y > DISTANCE_CLICK)
	{
		_isClick = false;
	}
}

void KKCCUIListView::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	// On item touch cancel.
	this->onItemTouchCancel(this->getTouchItemId());

	CCPoint locationInView = pTouch->locationInView(pTouch->view());
	CCPoint touchEndPosition = CCDirector::sharedDirector()->convertToGL(locationInView);
	if(touchEndPosition.x - _clickPosition.x < DISTANCE_CLICK
		&& touchEndPosition.y - _clickPosition.y < DISTANCE_CLICK
		&& _isClick)
	{
		int clickPos = getItemIdWithPosition(_clickPosition);
		this->onItemClick(clickPos);
		return;
	}
	this->onTouchEnd(pTouch, pEvent);
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 

void KKCCUIListView::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	// On item touch cancel.
	this->onItemTouchCancel(this->getTouchItemId());

	this->onTouchEnd(pTouch, pEvent);
}

bool KKCCUIListView::getIsTouchInContentLayer( CCTouch *pTouch){
	CCPoint touchNodeSpacePoint = this->convertTouchToNodeSpace(pTouch);
	
	CCRect contentLayerRect = CCRectZero;
	contentLayerRect.origin = CCPointZero;
	contentLayerRect.size = this->getContentSize();

	return CCRect::CCRectContainsPoint(contentLayerRect, touchNodeSpacePoint);
}

bool KKCCUIListView::init(int item_max)
{
	this->contentLayer = 0;
	//this->listItemsLayer = 0;
	this->onItemActionListener = 0;
	this->setSpacingVertical(0);
	this->setPosition(getRect().origin);
	this->setContentSize(getRect().size);
	this->setIsTouchEnabled(true);

	this->setIsScrolling(false);
	this->ITEM_MAX = item_max;

	this->setClipLayerRect(getRect());

	listHeight = 0;
	listWidth = 0;

	_childViewList = new CCMutableArray<LayerNode *>();
	//
	contentLayer = CCLayerColor::layerWithColorWidthHeight(
		ccc4(120, 255, 120, 0), 
		this->getContentSize().width, 
		this->getContentSize().height);
	contentLayer->setAnchorPoint(ccp(0,0));
	contentLayer->setIsRelativeAnchorPoint(true);

	this->addChild(contentLayer, 0, 1);
	
	return true;
}

void KKCCUIListView::onTouchEnd( CCTouch *pTouch, CCEvent *pEvent )
{
	CCLayerColor *contentLayer = this->getContentLayer();
	if(!contentLayer)
	{
		return;
	}
	contentLayer->stopAllActions();

	CCPoint locationInView = pTouch->locationInView(pTouch->view());
	CCPoint currentPosition = contentLayer->getPosition();
	
	{
		if(currentPosition.y > topEdgePosition)
		{
			CCActionInterval *resetPositionAction = CCMoveTo::actionWithDuration(0.5, ccp(currentPosition.x, topEdgePosition));
			CCAction *action = CCEaseOut::actionWithAction(resetPositionAction, 3);
			contentLayer->runAction(action);
		}
		else if(currentPosition.y < bottomEdgePosition)
		{
			CCActionInterval *resetPositionAction = CCMoveTo::actionWithDuration(0.5, ccp(currentPosition.x, bottomEdgePosition));
			CCAction *action = CCEaseOut::actionWithAction(resetPositionAction, 3);
			contentLayer->runAction(action);
		}
		else
		{
			// gesture velocity

		}
	}
}


void KKCCUIListView::visit()
{
	if(getVisitType() == 1)
	{
		setWorldSpaceLeftBottomPoint(ccpAdd(this->getPosition(), this->getParent() ? this->getParent()->getPosition() : CCPointZero));
	}
	

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	float scale = ScaleUtil::Instance()->getScaleFactoryOnAndroid(); 
	glEnable(GL_SCISSOR_TEST);
	glScissor(_worldSpaceLeftBottomPoint.x * scale, _worldSpaceLeftBottomPoint.y * scale,
              this->getContentSize().width * scale, this->getContentSize().height * scale);
	CCLayer::visit();
	glDisable(GL_SCISSOR_TEST);
#else
	glEnable(GL_SCISSOR_TEST);
	glScissor(_worldSpaceLeftBottomPoint.x, _worldSpaceLeftBottomPoint.y,
              this->getContentSizeInPixels().width, this->getContentSizeInPixels().height);
	CCLayer::visit();
	glDisable(GL_SCISSOR_TEST);
#endif
	
	
	/*CCLayer::visit();*///kevint
}


void KKCCUIListView::scrollToEnd(ccTime duration)
{
	//return;
	CCLayerColor *contentLayer = this->getContentLayer();
	if(listHeight < this->getContentSize().height
       || !contentLayer)
        return;
	setContentLayerPosition(ccp(contentLayer->getPosition().x, bottomEdgePosition), duration);
	

}

void KKCCUIListView::scrollToTop(ccTime duration)
{
	CCLayerColor *contentLayer = this->getContentLayer();
	if(listHeight < this->getContentSize().height
       || !contentLayer)
        return;
	setContentLayerPosition(ccp(contentLayer->getPosition().x, topEdgePosition), duration);
}

void KKCCUIListView::setContentLayerPosition( CCPoint destPosition, ccTime duration )
{
	CCLayerColor *contentLayer = this->getContentLayer();
	if(duration <= 0)
	{
		contentLayer->setPosition(destPosition);
		return;
	}
	CCPoint currentPosition = contentLayer->getPosition();
	CCActionInterval *resetPositionAction = CCMoveTo::actionWithDuration(duration, destPosition);
	contentLayer->runAction(resetPositionAction);
}

CCMutableArray<LayerNode *>* KKCCUIListView::getChilds()
{
	return _childViewList;
}

void KKCCUIListView::onItemClick(int position )
{
	if(position < 0 || position >= _childViewList->count())
		return;

	if(this->getOnItemActionListener())
	{
		this->getOnItemActionListener()->onItemClickListener(_childViewList->getObjectAtIndex(position), position);
	}
}

void KKCCUIListView::onItemTouch(int position)
{
	if(position < 0 || position >= _childViewList->count())
		return;

	if(this->getOnItemActionListener())
	{
		this->getOnItemActionListener()->onItemTouchListener(_childViewList->getObjectAtIndex(position), position);
	}
}

void KKCCUIListView::onItemTouchCancel(int position)
{
	if(position < 0 || position >= _childViewList->count())
		return;

	if(this->getOnItemActionListener())
	{
		this->getOnItemActionListener()->onItemTouchCancelListener(_childViewList->getObjectAtIndex(position), position);
	}
}

void KKCCUIListView::resetContentLayerSize(const CCSize& newSize)
{
	CCLayerColor *contentLayer = this->getContentLayer();
	CCSize currentSize = contentLayer->getContentSize();
	contentLayer->setContentSize(newSize);
	
	listWidth = newSize.width;
	listHeight = newSize.height;

	resetEdgePosition();

	CCPoint currentListItemsLayerPosition = contentLayer->getPosition();

	{
		float increaseHeight = newSize.height - currentSize.height;
		currentListItemsLayerPosition.y += increaseHeight;
		contentLayer->setPosition(currentListItemsLayerPosition);
		
		CCPoint currentContentLayerPosition = contentLayer->getPosition();
		currentContentLayerPosition.y -= increaseHeight;
		/*if(currentContentLayerPosition.y < 0) 
			currentContentLayerPosition.y = 0;*/
		if(currentContentLayerPosition.y > bottomEdgePosition)
			currentContentLayerPosition.y = bottomEdgePosition;
		contentLayer->setPosition(currentContentLayerPosition);
	}
}

void KKCCUIListView::resetEdgePosition()
{
	CCSize contentSize = this->getContentSize();

	{
		//topEdgePosition =  listHeight;//contentSize.height -
		//bottomEdgePosition = contentSize.height;// - listHeight;
		//if(bottomEdgePosition < 0) 
		//	bottomEdgePosition = 0;
		if (listHeight < contentSize.height)
		{
			topEdgePosition = listHeight;//contentSize.height - 
			bottomEdgePosition = listHeight;// - listHeight   listHeight-
		}
		else
		{
			topEdgePosition = listHeight;//contentSize.height - 
			bottomEdgePosition = contentSize.height;// - listHeight   listHeight-	
		}

	}
}

int KKCCUIListView::getItemIdWithPosition(CCPoint& position)
{
	CCLayerColor *contentLayer = this->getContentLayer();
	if ( !contentLayer )
	{
		return -1;
	}
	
	CCPoint nodePoint = this->convertToNodeSpace(_clickPosition);
	int itemId = -1;

	{
		if (!contentLayer)
			return 0;//KEVINBUG
		float contentY = contentLayer->getPosition().y;

		float clickHeight = nodePoint.y + (listHeight - contentLayer->getPosition().y);//listHeight - (nodePoint.y - contentLayer->getPosition().y);
		//int itemsSize = _listItemsHeight.size();
		int itemsSize = _childViewList->count();
		float heightSum = 0 ;
	//	for(int i=0; i<itemsSize; ++i)
		for (int i = itemsSize-1; i>=0; i--)
		{
			//heightSum += _listItemsHeight[i];
			heightSum += _childViewList->getObjectAtIndex(i)->getvisibleSize().height;
			if(clickHeight < heightSum)
			{
				itemId = i;
				break;
			}
			heightSum += this->getSpacingVertical();
		}
	}
	return itemId;


}

void KKCCUIListView::setWorldSpaceLeftBottomPoint( CCPoint pos )
{
	float scale = CCDirector::sharedDirector()->getContentScaleFactor();
	_worldSpaceLeftBottomPoint.x = pos.x * scale;
	_worldSpaceLeftBottomPoint.y = pos.y * scale;
}

cocos2d::CCPoint KKCCUIListView::getWorldSpaceLeftBottomPoint()
{
	return _worldSpaceLeftBottomPoint;
}

