
#ifndef HLQS_IPAD_KKAnimationFactory_h
#define HLQS_IPAD_KKAnimationFactory_h

#include "BaseType.h"
using namespace cocos2d;
#define MAX_ANI_FRAMES 20;

#define DEFAULT_INTERVAL 0.2f


class KKAnimationFactory: public CCObject
{
public:
	KKAnimationFactory();
	~KKAnimationFactory();

	CCAnimation* registAni(const char* aniName, const char* frameName, int frameCount, float interval=DEFAULT_INTERVAL);
	CCAnimation* registModelAnimation(const char* aniName, const char* frameName, int frameCount, float interval=DEFAULT_INTERVAL);
	CCAnimation* registModelAnimationOneFrame(int index, const char* aniName, const char* frameName, int frameCount, float interval/*=DEFAULT_INTERVAL*/ );
	CCAnimation* registModelAniDirection( int iResId, const char* aniName, const char* frameName, int frameCount, float interval/*=DEFAULT_INTERVAL*/ );

	//Begin Kenfly 20121101
	CCAnimation* registAnimationAsync(const char* aniName, const char* frameName, int frameCount, float interval=DEFAULT_INTERVAL,
		CCObject* target = NULL, SEL_CallFuncOD selector = NULL, void* pData = NULL);

	void removeUnusedTexturesLater(ccTime dt);
	void removeUnusedTextureForKey( const char* key );
private:
	/*bool isLoading(const char* aniName);*/
	void addSpriteFramesAsyncCallBack(CCObject* object, void* pData);
	/*std::set<std::string> m_loadingSet;*/
	//End Kenfly 20121101
private:
	CCMutableArray<CCSpriteFrame*>* m_pAnimFrames;
};

extern KKAnimationFactory* g_pKKAnimationFactory;

#endif
