#include "StoryFollowNotifyAction.h"
#include "view/fight/interfaces/IAction.h"
#include "view/notify/NotifyManager.h"

StoryFollowNotifyAction::StoryFollowNotifyAction(int type)
{
	_type = type;
}

void StoryFollowNotifyAction::doAction()
{
	NotifyManager::Instance()->addNotification(_type);
}

void StoryFollowNotifyAction::delAction(IAction* action)
{
	action->release();
	action = 0;
}
