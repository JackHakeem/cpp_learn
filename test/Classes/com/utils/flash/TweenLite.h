#ifndef HLQS_TweenLite_H_
#define HLQS_TweenLite_H_
#include "cocos2d.h"

USING_NS_CC;

class Parm
{
public:
	CCPoint startPos;
	CCPoint endPos;
	float delay;
	CCNode* tar;
	SEL_CallFuncND onComplete;
	char onCompleteParams[1024];
	int parmSize;
	
public:
	Parm()
	{
		delay = 0;
		tar = NULL;
		onComplete = NULL;
		//onCompleteParams = NULL;
		memset(onCompleteParams, 0, 1024);
	}

	void execute()
	{
		if (tar && onComplete)
		{
			(tar->*onComplete)(tar, onCompleteParams);
		}
	}
};

class TweenLite: public CCNode
{
public:
	Parm* _parm;
public:
	TweenLite();
	~TweenLite();
	void endHandle();
	void to(CCNode* tar, float duration, Parm* parm);
};

#endif