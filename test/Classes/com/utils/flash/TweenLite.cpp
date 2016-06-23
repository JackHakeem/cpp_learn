#include "TweenLite.h"

TweenLite::TweenLite()
{
	_parm = NULL;
}

TweenLite::~TweenLite()
{
	if(_parm)
		delete _parm;
}

void TweenLite::to(CCNode* tar, float duration, Parm* parm)
{
	if(!tar || !parm)
		return;

	CCPoint pos;
	pos.x = parm->endPos.x - parm->startPos.x;
	pos.y = parm->endPos.y - parm->startPos.y;

	if(_parm)
	{
		delete _parm;
	}
	_parm = new Parm();
	*_parm = *parm;
	memcpy(_parm->onCompleteParams, parm->onCompleteParams, parm->parmSize);
	CCCallFunc *callBack = CCCallFunc::actionWithTarget(this, callfunc_selector(TweenLite::endHandle));
	CCAction* action = CCSequence::actions(
									CCSpawn::actions(
												CCMoveBy::actionWithDuration(duration, pos),
												NULL),
												callBack,
												NULL);

	tar->runAction(action);
	if(!parm->tar)
	{
		parm->tar = tar;
	}
}

void TweenLite::endHandle()
{
	if(_parm)
		_parm->execute();
}