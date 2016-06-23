#ifndef _FightEffect_H_
#define _FightEffect_H_

#include "BaseType.h"
#include "TweenLiteObject.h"

#include "cocos2d.h"
USING_NS_CC;

class FightEffectGroup;

class FightEffect
{
public:
	FightEffect();
	~FightEffect();
	void addTween( TweenLiteObject* tween );
	void play();
	void dispose();
	//void doAllComplete( ccTime ct );
	void setFightEffectGroup( FightEffectGroup* FightEffectGroup )
	{
		m_FightEffectGroup = FightEffectGroup;
	}
	void stop();
public:
	CCMutableArray<TweenLiteObject *> tweens; // 播放内容数组
	FightEffectGroup* m_FightEffectGroup;
	int m_completedActionCount;
};

#endif