#include "ShowNotificationAction.h"
#include "view/notify/NotifyManager.h"

ShowNotificationAction::ShowNotificationAction(int type) : _type(type)
{
}

void ShowNotificationAction::doAction()
{
	NotifyManager::Instance()->addNotification(_type);
}

void ShowNotificationAction::delAction(IAction* action)
{
	action->release();
	action = 0;
}
