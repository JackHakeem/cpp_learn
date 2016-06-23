#include "FightFollowWorldBossAction.h"
#include "../interfaces/IAction.h"
#include "view/worldBoss/WorldBossMediator.h"
#include "manager/ViewManager.h"
#include "view/worldBoss/components/WorldBossMainView.h"
#include "view/worldBoss/components/DeathView.h"

FightFollowWorldBossAction::FightFollowWorldBossAction()
{

}

void FightFollowWorldBossAction::doAction()
{
	WorldBossMediator * pWBMediator = (WorldBossMediator *)g_pFacade->retrieveMediator(AppFacade_WorldBoss_Mediator);
	if (pWBMediator)
	{
		if (ViewManager::getInstance()->_pWBMainView )
		{
			DeathView * pDeathView = (DeathView * )ViewManager::getInstance()->_pWBMainView->getChildByTag(WorldBossMainView::TAG_DeathView);
			if (pDeathView)
			{
					pWBMediator->showDeathView(pDeathView->_isInCD);
			}
		}
	}
}

void FightFollowWorldBossAction::delAction(IAction* action)
{
	action->release();
	action = 0;
}
