//
//  KKAnimationFactory.cpp
//  HLQS_IPAD
//
//  Created by keminghua on 12-3-2.
//  Copyright (c) 2012 4399. All rights reserved.
//

#include "KKAnimationFactory.h"
#include "manager/SourceCacheManage.h"
#include "manager/CDManage.h"

KKAnimationFactory* g_pKKAnimationFactory = 0;

KKAnimationFactory::KKAnimationFactory():m_pAnimFrames(0)
{
}

KKAnimationFactory::~KKAnimationFactory()
{
	CC_SAFE_RELEASE(m_pAnimFrames);
}

CCAnimation* KKAnimationFactory::registAni(const char* aniName, const char* frameName, int frameCount, float interval)
{
	if (!aniName||!frameName||frameCount<=0||interval<=0.f) 
		return 0;
    
 	CCAnimationCache *animationCache = CCAnimationCache::sharedAnimationCache();
	if (! animationCache)
	{
		return 0;
	}
	CCAnimation *animation = animationCache->animationByName(aniName);
	if (animation)
		return animation;

	CCSpriteFrameCache* frameCache =CCSpriteFrameCache::sharedSpriteFrameCache();
	if (! frameCache)
		return 0;

	int result = frameCache->addSpriteFramesWithFile(aniName);
	if(result == -1)
		return 0;

    char str[100] = {0};

	animation = new CCAnimation();
	animation->init();

    for(int i = 0; i < frameCount; i++)
    {
        sprintf(str, frameName, i);
        CCSpriteFrame *frame = 0;
		frame = frameCache->spriteFrameByName(str);
		if (frame)
		{
			frame->getTexture()->retainCount();

			animation->addFrame(frame);
			frameCache->removeSpriteFrameByName(str);

			frame->getTexture()->retainCount();
		}
    }
    
	if(animation->getFrames()->count() == 0)
	{
		CC_SAFE_DELETE(animation);
		return 0;
	}

	animation->setDelay(interval);
    animationCache->addAnimation(animation, aniName);
	animation->release();

	return animation;
}

CCAnimation* KKAnimationFactory::registModelAnimationOneFrame(int index, const char* aniName, const char* frameName, int frameCount, float interval/*=DEFAULT_INTERVAL*/ )
{
	if (!aniName||!frameName||frameCount<=0||interval<=0.0f) 
		return 0;

	if (!m_pAnimFrames)
	{
		int maxFrames = MAX_ANI_FRAMES;
		m_pAnimFrames = new CCMutableArray<CCSpriteFrame*>(maxFrames);
	}

	CCAnimationCache *aniCache = CCAnimationCache::sharedAnimationCache();
	if (!aniCache)
	{

		return 0;
	}
	CCAnimation *dstAni = aniCache->animationByName(aniName);

	//if (dstAni)
	//	return dstAni;

	if ( !dstAni )
	{
		int result = CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(aniName);
		if(result == -1)
			return 0;
	}

	char str[100] = {0};
	int cnt = 0;

	CCSpriteFrame *frame = 0;
	CCSpriteFrame* targetFrame = 0;
	for(int i = 0; i < 5; i++)
	{//ֻҪһ֡
		//int i = index;
		sprintf(str, frameName,i);
		
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		
		if (!frame)
		{
			continue;
		}
		targetFrame = frame;
		cnt ++;
	//	m_pAnimFrames->addObject(frame);
	}

	if (cnt == 2)
	{
		m_pAnimFrames->addObject(targetFrame);
	}
	else if (cnt == 1)
	{
		m_pAnimFrames->addObject(targetFrame);
	}

	if(cnt == 0)
		return 0;

	CCAnimation *animation = CCAnimation::animationWithFrames(m_pAnimFrames, interval);
	if (!animation)
	{
		return 0;
	}

	aniCache->addAnimation(animation, frameName);

	m_pAnimFrames->removeAllObjects(true);

	dstAni = aniCache->animationByName(frameName);
	if (!dstAni)
	{

		return 0;
	}
	return dstAni;
}


CCAnimation* KKAnimationFactory::registModelAnimation( const char* aniName, const char* frameName, int frameCount, float interval/*=DEFAULT_INTERVAL*/ )
{
	if (!aniName||!frameName||frameCount<=0||interval<=0.0f) 
		return 0;

	if (!m_pAnimFrames)
	{
		int maxFrames = MAX_ANI_FRAMES;
		m_pAnimFrames = new CCMutableArray<CCSpriteFrame*>(maxFrames);
	}

	CCAnimationCache *aniCache = CCAnimationCache::sharedAnimationCache();
	if (!aniCache)
	{

		return 0;
	}
	//check by frame name
	CCAnimation *dstAniByFrame = aniCache->animationByName(frameName);
	if (dstAniByFrame)
		return dstAniByFrame;

	//check by plist name
	CCAnimation *dstAni = aniCache->animationByName(aniName);
	if (dstAni)
		return dstAni;

	if ( !dstAni )
	{
		int result = CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(aniName);
		if(result == -1)
			return 0;
	}

	char str[100] = {0};
	int cnt = 0;
	for(int i = 0; i < frameCount; i++)
	{
		sprintf(str, frameName,i);
		CCSpriteFrame *frame = 0;
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		if (!frame)
		{
			continue;
		}
		cnt ++;
		m_pAnimFrames->addObject(frame);
	}

	if(cnt == 0)
		return 0;
	
	CCAnimation *animation = CCAnimation::animationWithFrames(m_pAnimFrames, interval);
	if (!animation)
	{
		return 0;
	}

	aniCache->addAnimation(animation, frameName);

	m_pAnimFrames->removeAllObjects(true);

	dstAni = aniCache->animationByName(frameName);
	if (!dstAni)
	{

		return 0;
	}
	return dstAni;
}


CCAnimation* KKAnimationFactory::registModelAniDirection( int iResId,
	const char* aniName, const char* frameName, int frameCount, float interval/*=DEFAULT_INTERVAL*/ )
{
	if (!aniName||!frameName||frameCount<=0||interval<=0.0f) 
		return 0;

	if (!m_pAnimFrames)
	{
		int maxFrames = MAX_ANI_FRAMES;
		m_pAnimFrames = new CCMutableArray<CCSpriteFrame*>(maxFrames);
	}

	CCAnimationCache *aniCache = CCAnimationCache::sharedAnimationCache();
	if (!aniCache)
	{

		return 0;
	}
	//check by frame name
	CCAnimation *dstAniByFrame = aniCache->animationByName(frameName);
	if (dstAniByFrame)
		return dstAniByFrame;

	//check by plist name
	CCAnimation *dstAni = aniCache->animationByName(aniName);

	if ( !dstAni )
	{
		int result = CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(aniName);
		if(result == -1)
			return 0;
	}

	char str[100] = {0};
	int cnt = 0;
	for(int i = 0; i < frameCount; i++)
	{
		sprintf(str, frameName,i);
		CCSpriteFrame *frame = 0;
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		if (!frame)
		{
			continue;
		}
		cnt ++;
		m_pAnimFrames->addObject(frame);
	}

	if(cnt == 0)
		return 0;

	CCAnimation *animation = CCAnimation::animationWithFrames(m_pAnimFrames, interval);
	if (!animation)
	{
		return 0;
	}

	aniCache->addAnimation(animation, frameName);

	m_pAnimFrames->removeAllObjects(true);

	dstAni = aniCache->animationByName(frameName);
	if (!dstAni)
	{

		return 0;
	}
	return dstAni;
}

//Begin Kenfly 20121011
CCAnimation* KKAnimationFactory::registAnimationAsync(const char* aniName,
	const char* frameName, int frameCount, float interval/*=DEFAULT_INTERVAL*/,
	CCObject* target, SEL_CallFuncOD selector, void* pData)
{
	do 
	{
		CC_BREAK_IF(! aniName || ! frameName || frameCount <= 0 || interval <= 0.0f);

		CCAnimationCache *aniCache = CCAnimationCache::sharedAnimationCache();
		CC_BREAK_IF(NULL == aniCache);

		//check by frame name.
		CCAnimation *dstAnimation = aniCache->animationByName(aniName);
		if (dstAnimation)
			return dstAnimation;

		//load frames from file async
		typedef struct 
		{
			std::string aniName;
			std::string frameName;
			int frameCount;
			float interval;
			CCObject* target;
			SEL_CallFuncOD selector;
			void* data;
		} FrameInfo;

		FrameInfo* pInfo = new FrameInfo();
		pInfo->aniName = aniName;
		pInfo->frameName = frameName;
		pInfo->frameCount = frameCount;
		pInfo->interval = interval;
		pInfo->target = target;
		pInfo->selector = selector;
		pInfo->data = pData;

		CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
		CC_BREAK_IF(NULL == frameCache);

		/*m_loadingSet.insert(std::string(frameName));*/
		frameCache->addSpriteFramesWithFileAsync(aniName, this, callfuncOD_selector(KKAnimationFactory::addSpriteFramesAsyncCallBack), (void*)pInfo);
	} while (0);
	return 0;
}

//turn the frames into Animation && add to animation cache.
void KKAnimationFactory::addSpriteFramesAsyncCallBack(CCObject* object, void* pData)
{
	if (NULL == pData)
		return;

	typedef struct 
	{
		std::string aniName;
		std::string frameName;
		int frameCount;
		float interval;
		CCObject* target;
		SEL_CallFuncOD selector;
		void* data;
	} FrameInfo;

	FrameInfo* pFrameInfo = (FrameInfo*)pData;

	CCAnimation* animation = NULL;
	do 
	{
		CC_BREAK_IF(NULL == object); //load fail;

		CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
		CC_BREAK_IF(NULL == frameCache);
		CCAnimationCache *aniCache = CCAnimationCache::sharedAnimationCache();
		CC_BREAK_IF(aniCache == NULL);

		animation = new CCAnimation();
		animation->init();

		char str[100] = {0};
		for(int i = 0; i < pFrameInfo->frameCount; i++)
		{
			sprintf(str, pFrameInfo->frameName.c_str(), i);
			CCSpriteFrame *frame = NULL;
			frame = frameCache->spriteFrameByName(str);
			if (frame)
			{
				animation->addFrame(frame);
				frameCache->removeSpriteFrameByName(str); //Kenfly 20130117
			}
		}

		if (animation->getFrames()->count() == 0) //load faild
		{
			CC_SAFE_DELETE(animation);
			break;
		}

		animation->setDelay(pFrameInfo->interval);

		aniCache->addAnimation(animation, pFrameInfo->aniName.c_str());
		animation->release();		
	} while (0);

	CCObject* target = pFrameInfo->target;
	SEL_CallFuncOD selector = pFrameInfo->selector;

	if (target && selector)
	{
		(target->*selector)(animation, pFrameInfo->data);
	}

	CC_SAFE_DELETE(pFrameInfo);
}

//End Kenfly 20121011


void KKAnimationFactory::removeUnusedTextureForKey( const char* key )
{
	string listStr = string(key) + ".plist";
	string pvrStr = string(key) + ".pvr.ccz";
	CCAnimationCache::sharedAnimationCache()->removeAnimationByName( listStr.c_str() );

	if ( CCTexture2D* p = CCTextureCache::sharedTextureCache()->textureForKey(pvrStr.c_str() ) )
	{
		if (p->retainCount()>1)
		{
			CCScheduler::sharedScheduler()->scheduleSelector(
				schedule_selector(KKAnimationFactory::removeUnusedTexturesLater),
				this,
				1.5f, false);
		}
		else
		{
			CCTextureCache::sharedTextureCache()->removeUnusedTextureForKey(listStr.c_str());
		}
	}
}

void KKAnimationFactory::removeUnusedTexturesLater( ccTime dt )
{
	CCTextureCache::sharedTextureCache()->removeUnusedTextures();

	CCScheduler::sharedScheduler()->unscheduleSelector(
	schedule_selector(KKAnimationFactory::removeUnusedTexturesLater),
	this);
}