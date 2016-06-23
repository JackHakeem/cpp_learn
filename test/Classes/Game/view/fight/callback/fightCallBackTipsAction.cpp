#include "fightCallBackTipsAction.h"
#include "../../../events/GameDispatcher.h"
#include "../../newhand/NewhandMediator.h"

fightCallBackTipsAction::fightCallBackTipsAction(StepVo * pStep) : _pStep(*pStep)
{

}

void fightCallBackTipsAction::doAction()
{
	NewhandMediator * pNewhandm = (NewhandMediator *)g_pFacade->retrieveMediator(AppFacade_NEWHAND_MEDIATOR);
	if (pNewhandm)
	{
		pNewhandm->paperPop((StepVo *)&_pStep);
	}
}

void fightCallBackTipsAction::delAction(IAction* action)
{
	action->release();
	action = 0;
}
