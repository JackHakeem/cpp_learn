#include "FightEffect.h"
#include "TweenLiteObject.h"
#include "utils/effect/FightEffectGroup.h"
#include "../BitmapMovieClip.h"

FightEffect::FightEffect()
{
	m_FightEffectGroup = 0;
	m_completedActionCount = 0; 
	CCLog("=FightEffect::FightEffect()......................................cnt=%d", m_completedActionCount);
}

void FightEffect::addTween( TweenLiteObject* tween )
{
	if( tween )
	{
		if ( tween->vars && tween->vars->onStartParams.count() < 2 )
		{
			//kevinhCCLog( " TweenLiteObject::onStartParams < 2 ! " );
			//return;
		}
		tweens.addObject( tween );
		tween->release();
		++m_completedActionCount;
		CCLog("++addTween......................................cnt=%d", m_completedActionCount);
	}
}

// 
void FightEffect::play()
{
	if( tweens.count()>0 )
	{
		for ( int i = 0; i < tweens.count(); i++ )
		{
			TweenLiteObject* pObject = tweens.getObjectAtIndex(i);
			if ( !pObject )
			{
				continue;
			}

			float delay = 0.0f;
			if ( pObject->vars )
			{
				delay = pObject->vars->delay;
			}
			CCScheduler::sharedScheduler()->scheduleSelector( schedule_selector(TweenLiteObject::onStart), pObject, delay, false );
			//pObject->onStart( 0.1f );

			//CCScheduler::sharedScheduler()->unscheduleSelector( pfnSelector, pTarget );
		}
	}
	else
	{
		dispose();
		//this.dispatchEvent(new ParamEvent(EFFECT_END));
		if ( m_FightEffectGroup )
		{
			m_FightEffectGroup->nextEffect();
		}
	}
}

void FightEffect::stop()
{
	for ( int i = 0; i < tweens.count(); i++ )
	{
		TweenLiteObject* pObject = tweens.getObjectAtIndex(i);
		if ( !pObject )
		{
			continue;
		}

		CCScheduler::sharedScheduler()->unscheduleSelector( schedule_selector(TweenLiteObject::onStart), pObject );
	}
}

void FightEffect::dispose()
{
	if ( tweens.count() > 0 )
	{
		tweens.removeAllObjects(true);
	}
}

FightEffect::~FightEffect()
{
	m_FightEffectGroup = 0;
	m_completedActionCount = 0;
	CCLog("=FightEffect::~FightEffect()......................................cnt=%d", m_completedActionCount);
}

//void FightEffect::doAllComplete( ccTime ct )
//{
//
//}
