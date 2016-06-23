#ifndef _DISPLAY_OBJECT_MANAGER_H_
#define _DISPLAY_OBJECT_MANAGER_H_
#include "cocos2d.h"
#include "utils/Singleton.h"

USING_NS_CC;

class DisplayObjectManager : public CCObject
{
public:
	DisplayObjectManager() {}
	~DisplayObjectManager() {}
	static DisplayObjectManager *getInstance();
	void showFirstGoldEffect();
	void onGoldEffComplete();
	void fineNpcHandle();

	void loadPassGiftSkin( int honorId );

	void PlayRecvTaskEffect();
	void PlayRecvTaskEffectComplete( CCNode* pnode );
	void PlayFinTaskEffect();
	void PlayFinTaskEffectComplete( CCNode* pnode );

	void showAwardEffect();
	void onGoldAwardEffComplete();
private:
	CCSprite *_pGoldSprite;
};

#endif