#include "FightFollowStoryAction.h"
#include "view/scene/SceneStoryMediator.h"
#include "../interfaces/IAction.h"

FightFollowStoryAction::FightFollowStoryAction(int storyID)
{
	_nStoryID = storyID;
}

void FightFollowStoryAction::doAction()
{
	//GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::STORY_CALLBACK,0);
	SceneStoryMediator * pSceneStoryMediator = (SceneStoryMediator *)g_pFacade->retrieveMediator(AppFacade_SCENESTORY_PROXY_CHANGE);
	pSceneStoryMediator->tweenToTargetStartStory(_nStoryID);
}

void FightFollowStoryAction::delAction(IAction* action)
{
	action->release();
	action = 0;
}
