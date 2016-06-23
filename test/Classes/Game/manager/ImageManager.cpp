
#include "ImageManager.h"

ImageManager::ImageManager()
{

}

CCSprite * ImageManager::getRealSpriteFromImagePath(char * path)
{
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(path);
	CCSpriteFrame *pTempFrame = CCSpriteFrame::frameWithTexture(pFrame->getTexture(), pFrame->getRect());

	CCTexture2D *texture = pTempFrame->getTexture();

#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
	CCSize original = pTempFrame->getOriginalSizeInPixels();

	CCSize size = CCSizeMake(original.width / CCDirector::sharedDirector()->getContentScaleFactor(),
		original.height / CCDirector::sharedDirector()->getContentScaleFactor());
	CCPoint pos = pTempFrame->getRect().origin;
#else
	CCSize size = pTempFrame->getOriginalSizeInPixels();
	CCPoint pos = pTempFrame->getRectInPixels().origin;
#endif

	CCSpriteFrame * pRealFrame = CCSpriteFrame::frameWithTexture(texture , CCRectMake(pos.x , pos.y , size.width , size.height));
	CCSprite * pSprite = CCSprite::spriteWithSpriteFrame(pRealFrame);

	return pSprite;
}