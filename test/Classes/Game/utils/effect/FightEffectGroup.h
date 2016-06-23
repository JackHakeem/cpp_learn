#ifndef _FIGHTEFFECTGROUP_H_
#define _FIGHTEFFECTGROUP_H_

#include <list>
#include "FightEffect.h"
#include "utils/Singleton.h"
using namespace std;

class FightEffectGroup : public Singleton<FightEffectGroup>, public CCObject
{
public:
	FightEffectGroup();
public:
	std::list< FightEffect* > tweens;
	FightEffect* m_fightEffect;
public:
	void nextEffect( ccTime dt = 1.0f );
	void addTween( FightEffect* tween, string name );
	void play( bool first = true );
	void stop();
	void dispose();

	void registerCallback( SEL_CallFunc selector, CCObject* pTarget );
	void completeOneAction();
private:
	SEL_CallFunc m_pCallFunc;
	CCObject* m_pSelectorTarget;
};

#endif