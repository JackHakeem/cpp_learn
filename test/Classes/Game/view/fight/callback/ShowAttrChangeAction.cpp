#include "ShowAttrChangeAction.h"
#include "view/notify/NotifyManager.h"
#include "Message.h"

ShowAttrChangeAction::ShowAttrChangeAction(std::string content , ccColor3B color , float delay) : _content(content) , _color(color) , _delay(delay)
{
}

void ShowAttrChangeAction::doAction()
{
	Message::Instance()->show(_content , _color , _delay);
}

void ShowAttrChangeAction::delAction(IAction* action)
{
	action->release();
	action = 0;
}
