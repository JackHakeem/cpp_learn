#include "CCUIBaseClipLayer.h"
#include "utils/ScaleUtil.h"

CCUIBaseClipLayer * CCUIBaseClipLayer::initWithRect( const cocos2d::CCRect &rect )
{
	CCUIBaseClipLayer *layer = new CCUIBaseClipLayer(rect);
	if(layer && layer->init())
	{
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}

CCUIBaseClipLayer::CCUIBaseClipLayer(const  cocos2d::CCRect &rect )
{
	this->setContentSize(rect.size);
	this->setPosition(rect.origin);
	this->setClipLayerRect(rect);
}

bool CCUIBaseClipLayer::init()
{
	/*if(!CCLayerColor::initWithColor(ccc4(255, 255, 0, 255)))
	{
	return false;
	}*/
	return true;
}

void CCUIBaseClipLayer::visit()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	float scale = ScaleUtil::Instance()->getScaleFactoryOnAndroid(); 
	glEnable(GL_SCISSOR_TEST);
	glScissor(clipLayerRect.origin.x * scale,
              clipLayerRect.origin.y * scale,
              this->getContentSize().width * scale,
              this->getContentSize().height * scale);
	CCLayer::visit();
	glDisable(GL_SCISSOR_TEST);
#else
	float scale = CCDirector::sharedDirector()->getContentScaleFactor();
	glEnable(GL_SCISSOR_TEST);
	glScissor(clipLayerRect.origin.x * scale,
              clipLayerRect.origin.y * scale,
              this->getContentSize().width * scale,
              this->getContentSize().height * scale);
	CCLayer::visit();
	glDisable(GL_SCISSOR_TEST);
#endif
	//CCLayer::visit();
}
