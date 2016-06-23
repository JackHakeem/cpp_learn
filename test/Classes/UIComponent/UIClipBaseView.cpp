#include "UIClipBaseView.h"
#include "utils/ScaleUtil.h"

void UIClipBaseView::visit()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	float scale = ScaleUtil::Instance()->getScaleFactoryOnAndroid(); 
	cocos2d::CCPoint convertedLocationLowerLeft = this->getParent()->convertToWorldSpace(this->getPosition());
	glEnable(GL_SCISSOR_TEST);
	glScissor(convertedLocationLowerLeft.x * scale, convertedLocationLowerLeft.y * scale,
              this->getContentSize().width * scale, this->getContentSize().height * scale);
	cocos2d::CCLayer::visit();
	glDisable(GL_SCISSOR_TEST);
#else
	cocos2d::CCPoint convertedLocationLowerLeft = this->getParent()->convertToWorldSpace(this->getPosition());
	glEnable(GL_SCISSOR_TEST);
	glScissor(convertedLocationLowerLeft.x, convertedLocationLowerLeft.y,
              this->getContentSize().width, this->getContentSize().height);
	cocos2d::CCLayer::visit();
	glDisable(GL_SCISSOR_TEST);
#endif
}
