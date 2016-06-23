#include "TweenLiteObject.h"
#include "utils/loader/KKAnimationFactory.h"
#include "../BitmapMovieClip.h"
#include "FightEffectGroup.h"

void TweenLiteObject::onStart( ccTime ct )
{
	CCScheduler::sharedScheduler()->unscheduleSelector( schedule_selector(TweenLiteObject::onStart), this );

	if ( vars )
	{
		if ( vars->onStartParams.count() < 2 )
		{
		}
		else
		{
			CCNode* pSprite = vars->onStartParams.getObjectAtIndex(0);
			BitmapMovieClip* effectMC = (BitmapMovieClip*)vars->onStartParams.getObjectAtIndex(1);
			if ( pSprite && pSprite->getParent() && effectMC )
			{
				if (!pSprite->getParent())
				{
					return;
				}
				pSprite->getParent()->addChild( effectMC, 1000 );
				effectMC->release();
				//CCSize rectSize = pSprite->getContentSize();
				//effectMC->setPosition(ccpAdd(ccp(25, 40), pSprite->getPosition()));//kevine

				cocos2d::CCCallFunc *callBack = cocos2d::CCCallFuncN::actionWithTarget(this, callfuncN_selector(TweenLiteObject::endHandler));
				effectMC->runActionPVRCommon( callBack );
			}
		}
	}
	
	if ( m_pSelectorTarget && m_pCallFunc )
	{
		(m_pSelectorTarget->*m_pCallFunc)();
	}

	//if ( !vars )
	//	FightEffectGroup::Instance()->completeOneAction();
}

void TweenLiteObject::endHandler( CCNode* pnode )
{
	if ( !pnode || !vars )
	{
		FightEffectGroup::Instance()->completeOneAction();
		return;
	}

	CCNode* pSprite = vars->onStartParams.getObjectAtIndex(0);
	BitmapMovieClip* effectMC = (BitmapMovieClip*)vars->onStartParams.getObjectAtIndex(1);
	if ( pSprite && pSprite->getParent() && effectMC )//kevine
	{
		//effectMC->playeSprite->stopAllActions();
		//effectMC->removeChild( effectMC->playeSprite, false );
		//effectMC->playeSprite->release();

		pSprite->getParent()->removeChild( effectMC, false );
		effectMC->dispose(true);
		effectMC->release();
	}
	vars->onStartParams.removeAllObjects(false);
	//pSprite->release();

	FightEffectGroup::Instance()->completeOneAction();
}

TweenLiteObject::~TweenLiteObject()
{
	//BitmapMovieClip* effectMC = (BitmapMovieClip*)vars.onStartParams.getObjectAtIndex(1);
	//if ( effectMC )
	//{
	//	effectMC->release();
	//}
	duration = 0;
	CC_SAFE_DELETE( vars );
}

void TweenLiteObject::registerCallback( SEL_CallFunc selector, CCObject* pTarget )
{
	m_pCallFunc = selector;
	m_pSelectorTarget = pTarget;
}

TweenLiteObject::TweenLiteObject( CCObject* pTarget, Number dur, TweenLiteObjectVars* tweenVars )
{
	m_pSelectorTarget = 0;
	duration = dur;
	vars = tweenVars;
}


TweenLiteObjectVars::~TweenLiteObjectVars()
{
	onStartParams.removeAllObjects(false);
}
