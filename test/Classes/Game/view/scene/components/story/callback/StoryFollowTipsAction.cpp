#include "StoryFollowTipsAction.h"
#include "view/fight/interfaces/IAction.h"
#include "view/newhand/NewhandMediator.h"

StoryFollowTipsAction::StoryFollowTipsAction(StepVo * pStep)
{
	_pStep = pStep;
}

void StoryFollowTipsAction::doAction()
{
	NewhandMediator * pNewhandm = (NewhandMediator *)g_pFacade->retrieveMediator(AppFacade_NEWHAND_MEDIATOR);
	if (pNewhandm)
	{
		pNewhandm->paperPop(_pStep);
	}
}

void StoryFollowTipsAction::delAction(IAction* action)
{
	action->release();
	action = 0;
}
