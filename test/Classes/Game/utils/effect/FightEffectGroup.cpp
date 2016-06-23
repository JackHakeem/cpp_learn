#include "FightEffectGroup.h"


FightEffectGroup::FightEffectGroup()
{
	m_fightEffect = 0;
	tweens.clear();
	m_pSelectorTarget = 0;
}

void FightEffectGroup::addTween( FightEffect* tween, string name )
{
	if( tween->tweens.count()>0 )
	{
		tweens.push_back( tween );
		tween->setFightEffectGroup( this);
	}
}

void FightEffectGroup::play(bool first)
{
	if( tweens.size()>0 )
	{
		if ( m_fightEffect )
		{
			m_fightEffect->dispose();
		}		
		CC_SAFE_DELETE( m_fightEffect ); 

		m_fightEffect = *tweens.begin();
		tweens.pop_front();
		//fightEffect.addEventListener(FightEffect.EFFECT_END,nexteffect); // 
		m_fightEffect->play();
	}
}

void FightEffectGroup::nextEffect( ccTime dt /*= 1.0f*/ )
{
	if( tweens.size()>0 )
	{
		play(false);
	}
	else 
	{
		//this.dispatchEvent(new ParamEvent(EFFECT_END));
		dispose();

		if ( m_pSelectorTarget && m_pCallFunc )
		{
			(m_pSelectorTarget->*m_pCallFunc)();
		}
	}
}

void FightEffectGroup::stop()
{
	if ( m_fightEffect )
	{
		m_fightEffect->stop();
	}
}

void FightEffectGroup::dispose()
{	
	std::list< FightEffect* >::iterator it = tweens.begin();
	while ( it != tweens.end() )
	{
		FightEffect* fightEffect = *it;
		fightEffect->dispose();
		CC_SAFE_DELETE( fightEffect );
		it++;
	}
	tweens.clear();
}

void FightEffectGroup::registerCallback( SEL_CallFunc selector, CCObject* pTarget )
{
	m_pCallFunc = selector;
	m_pSelectorTarget = pTarget;
}

void FightEffectGroup::completeOneAction()
{
	if(!m_fightEffect)
		return;

	int cnt = --(m_fightEffect->m_completedActionCount);
	CCLog("--......................................cnt=%d", m_fightEffect->m_completedActionCount);
	if ( cnt <= 0 )
	{
		
		nextEffect();
	}
}