#include "UITaskFollowListContentLayer.h"
#include "utils/ScaleUtil.h"

UITaskFollowListContentLayer::UITaskFollowListContentLayer(cocos2d::CCSize layerSize)
{
	this->setAnchorPoint(cocos2d::CCPointZero);
	this->setContentSize(layerSize);
}

UITaskFollowListContentLayer * UITaskFollowListContentLayer::initWithWidthHeight(cocos2d::CCSize layerSize)
{
	UITaskFollowListContentLayer *layer = new UITaskFollowListContentLayer(layerSize);
	if(layer && layer->init())
	{
		return layer;
	}
	return NULL;
}

bool UITaskFollowListContentLayer::init()
{
	return true;
}

void UITaskFollowListContentLayer::visit()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	float scale = ScaleUtil::Instance()->getScaleFactoryOnAndroid(); 
	cocos2d::CCPoint convertedLocationLowerLeft = this->getParent()->convertToWorldSpace(this->getPosition());
	glEnable(GL_SCISSOR_TEST);
	glScissor(convertedLocationLowerLeft.x * scale, convertedLocationLowerLeft.y * scale,
              this->getContentSize().width * scale, this->getContentSize().height * scale);
	glDisable(GL_SCISSOR_TEST);
    
#else
	cocos2d::CCPoint convertedLocationLowerLeft = this->getParent()->convertToWorldSpace(this->getPosition());
	glEnable(GL_SCISSOR_TEST);
	glScissor(convertedLocationLowerLeft.x, convertedLocationLowerLeft.y,
              this->getContentSize().width, this->getContentSize().height);
	glDisable(GL_SCISSOR_TEST);
#endif
}


