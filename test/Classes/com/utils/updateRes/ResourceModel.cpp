#include "ResourceModel.h"

#include "cocos2d.h"
USING_NS_CC;

bool loadPvr(const AnimationResource &resource,
    CCMutableArray<CCSpriteFrame *> *frames)
{
    assert(resource.nframes > 0);
    //first test if we have loaded it yet
    size_t pos = resource.file.rfind('/');
	char buf[128] = {0};      //should be enough
    sprintf(buf, "%s/00000.png", resource.file.c_str() + pos + 1);

    if(!CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buf))
    {
        cocos2d::CCTexture2DPixelFormat defaultFormat = CCTexture2D::defaultAlphaPixelFormat();
        CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(
            (resource.file + ".plist").c_str());
        CCTexture2D::setDefaultAlphaPixelFormat(defaultFormat);
    }

    for(int i = 0; i < resource.nframes; ++i)
    {
        sprintf(buf, "%s/%05d.png", resource.file.c_str() + pos + 1, i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->
            spriteFrameByName(buf);
        frames->addObject(frame);
    }

    return true;
}

cocos2d::CCAnimation *loadAnimation(const AnimationResource &resource,
	float delay)
{
	CCMutableArray<cocos2d::CCSpriteFrame *> frames;
	bool ok = loadPvr(resource, &frames);
	assert(ok);
	(void)ok;

	return CCAnimation::animationWithFrames(&frames, delay);
}

cocos2d::CCAnimation *loadAnimation(const char *file, int nframes, float delay)
{
    AnimationResource ar = { file, nframes };
    return loadAnimation(ar, delay);
}