#ifndef _TweenLiteObject_H_
#define _TweenLiteObject_H_

#include "cocos2d.h"
#include "CCObject.h"
#include "utils/Timer.h"
USING_NS_CC;

class TweenLiteObjectVars /*: public CCObject*/
{
public:
	TweenLiteObjectVars()
	{
		delay = 0.0f;
	}
	~TweenLiteObjectVars();
	CCMutableArray<CCNode*> onStartParams;
	float delay;
};

class TweenLiteObject:public CCObject
{
public:
	TweenLiteObject( CCObject* pTarget, Number dur, TweenLiteObjectVars* tweenVars );
	~TweenLiteObject();
public:
	Number duration; // 效果持续时间 
	TweenLiteObjectVars* vars; // 控制参数
	//bool isTo = true;

	void onStart( ccTime ct );
	void endHandler( CCNode* pnode );

	void registerCallback( SEL_CallFunc selector, CCObject* pTarget );
private:
	SEL_CallFunc m_pCallFunc;
	CCObject* m_pSelectorTarget;
};

#endif