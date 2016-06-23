#include "CCUITaskPanelItem.h"
#include "utils/ScaleUtil.h"

void CCUITaskPanelItem::visit()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	float scale = ScaleUtil::Instance()->getScaleFactoryOnAndroid(); 
	CCSize parentSize = this->getParent()->getParent()->getContentSize();
	CCPoint parentPoint = this->getParent()->getPosition();
	CCSize clipSize = getClipSize();
	clipSize.width *= scale;
	clipSize.height *= scale;
	CCPoint oldParentPoint = this->getParent()->getParent()->getPosition();
	int newHeightPosition = (oldParentPoint.y + parentPoint.y + this->getPosition().y + this->getContentSize().height) * scale - clipSize.height;
    
	cocos2d::CCPoint convertedLocationLowerLeft = ccp(getParentWorldSpaceBottomLeftPoint().x * scale,
                                                      newHeightPosition + getParentWorldSpaceBottomLeftPoint().y * scale);
    
	if(convertedLocationLowerLeft.y > _parentMaxClipHeight
       || convertedLocationLowerLeft.y + clipSize.height < _parentMinClipHeight) 
	{
		//cocos2d::CCLayer::visit();
		return;
	}
    
	float distanceY = convertedLocationLowerLeft.y - _parentMinClipHeight;
	if(distanceY <= 0)
	{
		_clipY = _parentMinClipHeight;
		_clipHeight = clipSize.height + distanceY;
	}
	else
	{
		_clipY = convertedLocationLowerLeft.y;
		float  topDistance = clipSize.height + _clipY - _parentMaxClipHeight;
		if(topDistance > 0)
		{
			_clipHeight = clipSize.height - topDistance;
		}
		else
		{
			_clipHeight = clipSize.height;
		}
		/*_clipHeight = _clipSize.height;
         _clipHeight = _clipHeight > _parentMaxClipHeight ? _parentMaxClipHeight - _clipY : _clipHeight;*/
	}
	//CCLog("x=%f,y=%f,width=%f,height=%f",convertedLocationLowerLeft.x, _clipY, clipSize.width, _clipHeight);
	glEnable(GL_SCISSOR_TEST);
	glScissor(convertedLocationLowerLeft.x, _clipY,
              clipSize.width, _clipHeight);
	cocos2d::CCLayer::visit();
	glDisable(GL_SCISSOR_TEST);

    
#else
	//CCSize parentSize = this->getParent()->getParent()->getContentSizeInPixels();
	CCPoint parentPoint = this->getParent()->getPositionInPixels();
	CCSize clipSize = getClipSize();
	clipSize.width *= CCDirector::sharedDirector()->getContentScaleFactor();
	clipSize.height *= CCDirector::sharedDirector()->getContentScaleFactor();
	CCPoint oldParentPoint = this->getParent()->getParent()->getPositionInPixels();
	int newHeightPosition = oldParentPoint.y + parentPoint.y + this->getPositionInPixels().y + this->getContentSizeInPixels().height - clipSize.height;
    
	cocos2d::CCPoint convertedLocationLowerLeft = ccp(getParentWorldSpaceBottomLeftPoint().x,
                                                      newHeightPosition + getParentWorldSpaceBottomLeftPoint().y);
    
	if(convertedLocationLowerLeft.y > _parentMaxClipHeight
       || convertedLocationLowerLeft.y + clipSize.height < _parentMinClipHeight) 
	{
		//cocos2d::CCLayer::visit();
		return;
	}
    
	float distanceY = convertedLocationLowerLeft.y - _parentMinClipHeight;
	if(distanceY <= 0)
	{
		_clipY = _parentMinClipHeight;
		_clipHeight = clipSize.height + distanceY;
	}
	else
	{
		_clipY = convertedLocationLowerLeft.y;
		float  topDistance = clipSize.height + _clipY - _parentMaxClipHeight;
		if(topDistance > 0)
		{
			_clipHeight = clipSize.height - topDistance;
		}
		else
		{
			_clipHeight = clipSize.height;
		}
		/*_clipHeight = _clipSize.height;
         _clipHeight = _clipHeight > _parentMaxClipHeight ? _parentMaxClipHeight - _clipY : _clipHeight;*/
	}
	//CCLog("x=%f,y=%f,width=%f,height=%f",convertedLocationLowerLeft.x, _clipY, clipSize.width, _clipHeight);
	glEnable(GL_SCISSOR_TEST);
	glScissor(convertedLocationLowerLeft.x, _clipY,
              clipSize.width, _clipHeight);
	cocos2d::CCLayer::visit();
	glDisable(GL_SCISSOR_TEST);

#endif
}

CCUITaskPanelItem::CCUITaskPanelItem(float expandedWidth, float expandedHeight, float collapsedWidth, float collapsedHeight,
	const float parentMinClipHeight, const float parentMaxClipHeight)
{
	setContentSize(CCSizeMake(expandedWidth, expandedHeight));
	this->setvisibleSize(CCSizeMake(collapsedWidth, collapsedHeight));
	this->setMinHeight(collapsedHeight);
	this->setMaxHeight(expandedHeight);

	_isExpanded = false;
	_clipSize = CCSizeMake(collapsedWidth, collapsedHeight);

    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	float scale = ScaleUtil::Instance()->getScaleFactoryOnAndroid(); 
	_parentMinClipHeight = parentMinClipHeight * scale;
	_parentMaxClipHeight = parentMaxClipHeight * scale;
#else
	_parentMinClipHeight = parentMinClipHeight;
	_parentMaxClipHeight = parentMaxClipHeight;
#endif

	_frameLayer = new CCUIBackground();
	//_frameLayer->init();
	_frameLayer->setAnchorPoint(ccp(0, 1));
	_frameLayer->setIsRelativeAnchorPoint(true);
	_frameLayer->initWithFile("assets/ui/bg_task_item_frame.png", 
                              ccp(0, expandedHeight),
                              ccp(POSX(6),POSX(7)), 
							  CCSizeMake(collapsedWidth, collapsedHeight));
	this->addChild(_frameLayer, 1);
	_frameLayer->release();
}

bool CCUITaskPanelItem::init()
{
	return true;
}

CCUITaskPanelItem* CCUITaskPanelItem::initWithWidthHeight( float width, float height, float clipWidth, float clipHeight ,
	const float parentMinClipHeight, const float parentMaxClipHeight)
{
	CCUITaskPanelItem *layer = new CCUITaskPanelItem(width, height, clipWidth, clipHeight, parentMinClipHeight, parentMaxClipHeight);
	if(layer && layer->init())
	{
		//Doyang 20120711
		//layer->autorelease();
		return layer;
	}
    return 0;
}

void CCUITaskPanelItem::setClipSize( CCSize clipSize )
{
	_clipSize.height = clipSize.height;
	this->setvisibleSize(clipSize);
	CCSize newSize = CCSizeMake(getContentSize().width, _clipSize.height);
	_frameLayer->setContentSize(newSize);
	_frameLayer->changeSize(newSize);
}

cocos2d::CCSize CCUITaskPanelItem::getClipSize()
{
	return _clipSize;
}

void CCUITaskPanelItem::endExpanded()
{
	setClipSize(CCSizeMake(this->getContentSize().width, this->getMaxHeight()));
	_isExpanded = true;
}

void CCUITaskPanelItem::endCollapsed()
{
	setClipSize(CCSizeMake(this->getContentSize().width, this->getMinHeight()));
	_isExpanded = false;
}

bool CCUITaskPanelItem::isExpand()
{
	return _isExpanded;
}

void CCUITaskPanelItem::setIsFocus(bool isFocus)
{
	_isFocus = isFocus;
	//_frameLayer->setIsFocus(isFocus);
}
