#include "FightFollowLevelUpAction.h"
#include "../interfaces/IAction.h"
#include "manager/ViewManager.h"
#include "model/player/vo/PlayerAniType.h"

FightFollowLevelUpAction::FightFollowLevelUpAction()
{
}

void FightFollowLevelUpAction::doAction()
{
	Scene * pScene = ViewManager::getInstance()->_scene;
	if (pScene && pScene->_role)
	{
		pScene->_role->playEffect(PlayerAniType::TYPE_LevelUp);
	}
}

void FightFollowLevelUpAction::delAction(IAction* action)
{
	action->release();
	action = 0;
}
