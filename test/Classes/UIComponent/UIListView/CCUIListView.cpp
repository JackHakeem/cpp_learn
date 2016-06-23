#include "utils/ScaleUtil.h"
#include "CCUIListView.h"
#define DISTANCE_CLICK 10
CCUIListView::~CCUIListView()
{
	_childViewList->removeAllObjects();
	_childViewList->release();
}

CCUIListView* CCUIListView::listViewWithCCRect(const CCRect& mRect, bool isHorizontal)
{
	CCUIListView *pListView = new CCUIListView();
	if(pListView)
	{
		pListView->setIsLockHorizontal(isHorizontal);
		pListView->setRect(mRect);
		pListView->init();
		//pListView->autorelease(); kevin modified
		return pListView;
	}
	CC_SAFE_DELETE(pListView);
	return NULL;
}

void CCUIListView::setAdapter( CCUIListViewAdapter *adapter )
{
	if(contentLayer && contentLayer->getParent())
	{
		//contentLayer->removeAllChildrenWithCleanup(true);
		contentLayer->removeFromParentAndCleanup(true);
		contentLayer = NULL;
	}

	_childViewList->removeAllObjects();

	this->_pAdapter = adapter;
	int childSize = _pAdapter->getCount();
	if(childSize <= 0)
	{
		return;
	}
	listHeight = listWidth = 0;

	CCSize contentSize = this->getContentSize();
	
	// Initialize layers.
	// Initialize listItems layer.
	listItemsLayer = CCLayerColor::layerWithColorWidthHeight(ccc4(255, 0, 0, 0), contentSize.width, contentSize.height);

	// Initialize content layer.
	contentLayer = CCLayerColor::layerWithColorWidthHeight(ccc4(120, 120, 120, 0), contentSize.width, contentSize.height);

	// Initialize each child.
	for(int i=0; i<childSize; ++i)
	{
		LayerNode *itemCell = _pAdapter->getView(i);
		if(!itemCell) continue;
		if(this->getIsLockHorizontal())
		{
			listWidth += itemCell->getvisibleSize().width;
			listWidth += this->getSpacingHorizontal();
		}
		else
		{
			listHeight += itemCell->getvisibleSize().height;
			listHeight += this->getSpacingVertical();
		}
		_childViewList->addObject(itemCell);
	}

	listWidth -= this->getSpacingHorizontal();
	listHeight -= this->getSpacingVertical();

	if(this->getIsLockHorizontal())
	{
		listWidth = listHeight +headerSize + footerSize;
	}
	else
	{
		listHeight = listHeight + headerSize + footerSize;
	}

	// Reset contentlayer's params.
	contentLayer->setAnchorPoint(ccp(0,0));
	contentLayer->setIsRelativeAnchorPoint(true);

	resetEdgePosition();

	if(this->getIsLockHorizontal())
	{
		if(backgroundSprite)
			backgroundSprite->setContentSize(CCSizeMake(listWidth, contentSize.height - paddingTop - paddingBottom));
		contentLayer->setContentSize(CCSizeMake(listWidth, contentSize.height - paddingTop - paddingBottom));
		listItemsLayer->setContentSize(CCSizeMake(listWidth, contentSize.height - paddingTop - paddingBottom));
		CCPoint newPosition = CCPointMake(leftEdgePosition, paddingBottom);
		// Reset contentLayer layer's position.
		contentLayer->setPosition(newPosition);
	}
	else
	{
		if(backgroundSprite)
			backgroundSprite->setContentSize(CCSizeMake(contentSize.width - paddingLeft - paddingRight, listHeight));
		contentLayer->setContentSize(CCSizeMake(contentSize.width - paddingLeft - paddingRight, listHeight));
		listItemsLayer->setContentSize(CCSizeMake(contentSize.width - paddingLeft - paddingRight, listHeight));
		CCPoint newPosition = CCPointMake(paddingLeft, topEdgePosition);
		// Reset contentLayer layer's position.
		contentLayer->setPosition(newPosition);
	}

	// add each child to contentlayer.
	childSize = _childViewList->count();
	float childPositionY = listHeight - headerSize;
	float childPositionX = listWidth - headerSize;
	float tempSpacingHorizontal = 0, tempSpacingVertical = 0;


	for(int i=0; i<childSize; ++i)
	{
		LayerNode *itemCell = _childViewList->getObjectAtIndex(i);
		//itemCell->setIsRelativeAnchorPoint(true);
		itemCell->setTag(i);
		if(this->getIsLockHorizontal())
		{
			itemCell->setPosition(ccp(childPositionX - itemCell->getContentSize().width - tempSpacingHorizontal, 0));
			childPositionX -= itemCell->getvisibleSize().width;
			childPositionX -= tempSpacingHorizontal;
			tempSpacingHorizontal = this->getSpacingHorizontal();
		}
		else
		{
			itemCell->setPosition(ccp(0, childPositionY - itemCell->getContentSize().height - tempSpacingVertical));
			childPositionY -= itemCell->getvisibleSize().height;
			childPositionY -= tempSpacingVertical;
			tempSpacingVertical = this->getSpacingVertical();
		}
		if(itemCell && !itemCell->getParent())
		{
			listItemsLayer->addChild(itemCell);
		}
	}

	// add content layer to listview.
	listItemsLayer->setPosition(CCPointZero);
	contentLayer->addChild(listItemsLayer);
	this->addChild(contentLayer, 0);
	this->setContentLayer(contentLayer);
	
	// Vertical dir handle By LONGHUI
	if ( CCPoint::CCPointEqualToPoint(getTouchMoveContentLayerPosition() , CCPOINT_DEFAULT)
		|| getRect().size.height > contentLayer->getContentSize().height)
	{
		setTouchMoveContentLayerPosition(contentLayer->getPosition());
	}
}

void CCUIListView::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, m_pri, true);
}

bool CCUIListView::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint locationInView = pTouch->locationInView(pTouch->view());
	_preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
	if (this->getIsTouchInContentLayer(pTouch)) {
		_clickPosition = _preTouchPoint;//
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
    
    // Fix here. Always swallow the touch. 20120407
    // Doyang
//    return true;
}

void CCUIListView::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	if ( !contentLayer )
	{
		return;
	}

	// LH
	if (!getIsCanTouchMove())
	{
		return;
	}
	
	
	contentLayer->stopAllActions();
	CCPoint locationInView = pTouch->locationInView(pTouch->view());
	_currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
	CCPoint deltaPoint = ccpSub(_currentTouchPoint, _preTouchPoint);
	if(this->getIsLockHorizontal())
		deltaPoint.y=0; 
	else if(this->getIsLockVertical())
		deltaPoint.x=0;
	CCPoint newPosition = ccpAdd(contentLayer->getPosition(), deltaPoint);
	contentLayer->setPosition(newPosition);

	setTouchMoveContentLayerPosition(newPosition);//LH

	_preTouchPoint = _currentTouchPoint;
	//CCLog("------------clickPos,x=%f,y=%f,cur,x=%f,y=%f", _clickPosition.x, _clickPosition.y, _currentTouchPoint.x, _currentTouchPoint.y);
	if(_clickPosition.x - _currentTouchPoint.x > DISTANCE_CLICK
		|| _clickPosition.y - _currentTouchPoint.y > DISTANCE_CLICK)
	{
		_isClick = false;
	}
}

void CCUIListView::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
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

void CCUIListView::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	// On item touch cancel.
	this->onItemTouchCancel(this->getTouchItemId());

	this->onTouchEnd(pTouch, pEvent);
}

bool CCUIListView::getIsTouchInContentLayer( CCTouch *pTouch){
	CCPoint touchNodeSpacePoint = this->convertTouchToNodeSpace(pTouch);
	
	CCRect contentLayerRect = CCRectZero;
	contentLayerRect.origin = CCPointZero;
	contentLayerRect.size = this->getContentSize();

	return CCRect::CCRectContainsPoint(contentLayerRect, touchNodeSpacePoint);
}

bool CCUIListView::init()
{
	this->contentLayer = 0;
	this->listItemsLayer = 0;
	this->backgroundSprite = 0;
	this->onItemActionListener = 0;
	this->setSpacingHorizontal(0);
	this->setSpacingVertical(0);
	this->setPosition(getRect().origin);
	this->setContentSize(getRect().size);
	this->setIsTouchEnabled(true);
	if(this->getIsLockHorizontal())
	{
		this->setIsLockHorizontal(true);
		this->setIsLockVertical(false);
	}
	else
	{
		this->setIsLockHorizontal(false);
		this->setIsLockVertical(true);
	}
	this->setIsScrolling(false);
	this->setPaddingRight(0);
	this->setPaddingLeft(0);
	this->setPaddingTop(0);
	this->setPaddingBottom(0);
	this->setHeaderSize(0);
	this->setFooterSize(0);
	this->setClipLayerRect(getRect());

	_childViewList = new CCMutableArray<LayerNode *>();

	return true;
}

void CCUIListView::onTouchEnd( CCTouch *pTouch, CCEvent *pEvent )
{
	CCLayerColor *contentLayer = this->getContentLayer();
	if(!contentLayer)
	{
		return;
	}
	contentLayer->stopAllActions();

	CCPoint locationInView = pTouch->locationInView(pTouch->view());
	CCPoint currentPosition = contentLayer->getPosition();
	if(this->getIsLockHorizontal())
	{
		if(currentPosition.x > leftEdgePosition)
		{
			CCActionInterval *resetPositionAction = CCMoveTo::actionWithDuration(0.5, ccp(leftEdgePosition, currentPosition.y));
			CCAction *action = CCEaseOut::actionWithAction(resetPositionAction, 3);
			contentLayer->runAction(action);
		}
		else if(currentPosition.x < rightEdgePosition)
		{
			CCActionInterval *resetPositionAction = CCMoveTo::actionWithDuration(0.5, ccp(rightEdgePosition, currentPosition.y));
			CCAction *action = CCEaseOut::actionWithAction(resetPositionAction, 3);
			contentLayer->runAction(action);
		}
		else
		{
			// gesture velocity

		}
	}
	else
	{
		if(currentPosition.y < topEdgePosition)
		{
			CCActionInterval *resetPositionAction = CCMoveTo::actionWithDuration(0.5, ccp(currentPosition.x, topEdgePosition));
			CCAction *action = CCEaseOut::actionWithAction(resetPositionAction, 3);
			contentLayer->runAction(action);

			setTouchMoveContentLayerPosition(ccp(currentPosition.x , topEdgePosition)); //LH
		}
		else if(currentPosition.y > bottomEdgePosition)
		{
			CCActionInterval *resetPositionAction = CCMoveTo::actionWithDuration(0.5, ccp(currentPosition.x, bottomEdgePosition));
			CCAction *action = CCEaseOut::actionWithAction(resetPositionAction, 3);
			contentLayer->runAction(action);

			setTouchMoveContentLayerPosition(ccp(currentPosition.x , bottomEdgePosition)); //LH
		}
		else
		{
			// gesture velocity

		}
	}
}

void CCUIListView::setBackgroundWithFile( const char *pFileName )
{
	if(backgroundSprite && backgroundSprite->getParent())
	{
		backgroundSprite->removeFromParentAndCleanup(true);
	}
	backgroundSprite = CCSprite::spriteWithFile(pFileName, CCRectMake(this->getPosition().x,
		this->getPosition().y,
		this->getContentSize().width,
		this->getContentSize().height));
	backgroundSprite->setAnchorPoint(CCPointZero);
	this->addChild(backgroundSprite, -1);
}

void CCUIListView::visit()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	float scale = ScaleUtil::Instance()->getScaleFactoryOnAndroid(); 
	glEnable(GL_SCISSOR_TEST);
	glScissor(_worldSpaceLeftBottomPoint.x * scale, _worldSpaceLeftBottomPoint.y * scale,
		this->getContentSize().width * scale, this->getContentSize().height * scale);/**/
	CCLayer::visit();
	glDisable(GL_SCISSOR_TEST);//
#else
	float scale = CCDirector::sharedDirector()->getContentScaleFactor();
	glEnable(GL_SCISSOR_TEST);
	glScissor(_worldSpaceLeftBottomPoint.x, _worldSpaceLeftBottomPoint.y,
		this->getContentSize().width * scale, this->getContentSize().height * scale);/**/
	CCLayer::visit();
	glDisable(GL_SCISSOR_TEST);//
#endif
}


void CCUIListView::scrollToEnd(ccTime duration)
{
	//return;
	CCLayerColor *contentLayer = this->getContentLayer();
	if(listHeight < this->getContentSize().height
       || !contentLayer)
        return;
	//if(this->getIsLockHorizontal())
	setContentLayerPosition(ccp(contentLayer->getPosition().x, bottomEdgePosition), duration);
	//else
	setTouchMoveContentLayerPosition(ccp(contentLayer->getPosition().x , bottomEdgePosition)); // LH
}

void CCUIListView::scrollToTop(ccTime duration)
{
	CCLayerColor *contentLayer = this->getContentLayer();
	if(listHeight < this->getContentSize().height
       || !contentLayer)
        return;
	setContentLayerPosition(ccp(contentLayer->getPosition().x, topEdgePosition), duration);
	setTouchMoveContentLayerPosition(ccp(contentLayer->getPosition().x , topEdgePosition)); //LH
}

void CCUIListView::scrollToItemByIndex(int index , ccTime duration)
{
	if (!_childViewList || ! _childViewList->count()  || index > _childViewList->count()-1 || index < 0)
	{
		return;
	}

	CCMutableArray<LayerNode *>* pList = getChilds();
	if (pList)
	{

		LayerNode * pLayer = pList->getObjectAtIndex(index);
		if (pLayer)
		{

			scrollToTop(/*duration*/0);

			CCSize itemSize = pLayer->getContentSize();
			CCSize viewSize = getRect().size;
			float deltaY = (index+1) * itemSize.height + (index) * getSpacingVertical()  - viewSize.height;
			if ( deltaY <= 0)
			{
				return;
			}
			else
			{
				CCLayerColor *contentLayer = this->getContentLayer();
				if(listHeight < this->getContentSize().height
					|| !contentLayer)
					return;
				setContentLayerPosition(ccp(contentLayer->getPosition().x, contentLayer->getPosition().y + deltaY), /*duration*/0);
				setTouchMoveContentLayerPosition(ccp(contentLayer->getPosition().x , contentLayer->getPosition().y /*+ deltaY*/)); 
			}			
		}		
	}
	else
	{
		return;
	}
}

void CCUIListView::moveContentLayerToPosition(CCPoint position)
{
	CCLayerColor *contentLayer = this->getContentLayer();
	if (contentLayer)
	{
		contentLayer->setPosition(position);
		setTouchMoveContentLayerPosition(position);
	}
}

void CCUIListView::setContentLayerPosition( CCPoint destPosition, ccTime duration )
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

CCMutableArray<LayerNode *>* CCUIListView::getChilds()
{
	return _childViewList;
}

void CCUIListView::onItemClick(int position )
{
	if(position < 0 || position >= _childViewList->count())
		return;

	if(this->getOnItemActionListener())
	{
		this->getOnItemActionListener()->onItemClickListener(_childViewList->getObjectAtIndex(position), position);
	}
}

void CCUIListView::onItemTouch(int position)
{
	if(position < 0 || position >= _childViewList->count())
		return;

	if(this->getOnItemActionListener())
	{
		this->getOnItemActionListener()->onItemTouchListener(_childViewList->getObjectAtIndex(position), position);
	}
}

void CCUIListView::onItemTouchCancel(int position)
{
	if(position < 0 || position >= _childViewList->count())
		return;

	if(this->getOnItemActionListener())
	{
		this->getOnItemActionListener()->onItemTouchCancelListener(_childViewList->getObjectAtIndex(position), position);
	}
}

void CCUIListView::resetContentLayerSize(const CCSize& newSize)
{
	CCLayerColor *contentLayer = this->getContentLayer();
	CCSize currentSize = contentLayer->getContentSize();
	contentLayer->setContentSize(newSize);
	
	listWidth = newSize.width;
	listHeight = newSize.height;

	resetEdgePosition();

	CCPoint currentListItemsLayerPosition = listItemsLayer->getPosition();
	if(this->getIsLockHorizontal())
	{

	}
	else
	{
		float increaseHeight = newSize.height - currentSize.height;
		currentListItemsLayerPosition.y += increaseHeight;
		listItemsLayer->setPosition(currentListItemsLayerPosition);
		
		CCPoint currentContentLayerPosition = contentLayer->getPosition();
		currentContentLayerPosition.y -= increaseHeight;
		/*if(currentContentLayerPosition.y < 0) 
			currentContentLayerPosition.y = 0;*/
		if(currentContentLayerPosition.y > bottomEdgePosition)
			currentContentLayerPosition.y = bottomEdgePosition;
		contentLayer->setPosition(currentContentLayerPosition);
	}
}

void CCUIListView::resetContentLayerPosition() //LH
{
	CCLayerColor *contentLayer = this->getContentLayer();
	if ( !contentLayer )
	{
		return;
	}
	contentLayer->setPosition(getTouchMoveContentLayerPosition());
}

void CCUIListView::resetEdgePosition()
{
	//CCLayerColor *contentLayer = this->getContentLayer();
	CCSize contentSize = this->getContentSize();
	if(this->getIsLockHorizontal())
	{
		leftEdgePosition = 0;
		rightEdgePosition = contentSize.width - listWidth;
	}
	else
	{
		topEdgePosition = contentSize.height - listHeight;
		bottomEdgePosition = contentSize.height - listHeight;
		if(bottomEdgePosition < 0) 
			bottomEdgePosition = 0;
	}
}

int CCUIListView::getItemIdWithPosition(CCPoint& position)
{
	CCLayerColor *contentLayer = this->getContentLayer();
	if ( !contentLayer )
	{
		return -1;
	}
	
	CCPoint nodePoint = this->convertToNodeSpace(_clickPosition);
	int itemId = -1;
	if(this->isLockHorizontal)
	{
		float clickWidth = nodePoint.x - contentLayer->getPosition().x;
		//int itemsSize = _listItemsWidth.size();
		int itemsSize = _childViewList->count();
		float widthSum = 0 + headerSize;
		for(int i=0; i<itemsSize; ++i)
		{
			//widthSum += _listItemsWidth[i];
			widthSum += _childViewList->getObjectAtIndex(i)->getvisibleSize().width;
			if(clickWidth < widthSum)
			{
				itemId = i;
				break;
			}
			widthSum += this->getSpacingHorizontal();
		}
	}
	else
	{
		if (!contentLayer)
			return 0;//KEVINBUG
		float clickHeight = listHeight - (nodePoint.y - contentLayer->getPosition().y);
		//int itemsSize = _listItemsHeight.size();
		int itemsSize = _childViewList->count();
		float heightSum = 0 + headerSize;
		for(int i=0; i<itemsSize; ++i)
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

void CCUIListView::setWorldSpaceLeftBottomPoint( CCPoint pos )
{
	float scale = CCDirector::sharedDirector()->getContentScaleFactor();
	_worldSpaceLeftBottomPoint.x = pos.x * scale;
	_worldSpaceLeftBottomPoint.y = pos.y * scale;
}

cocos2d::CCPoint CCUIListView::getWorldSpaceLeftBottomPoint()
{
	return _worldSpaceLeftBottomPoint;
}
