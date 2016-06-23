#include "ShowNewHandHelpAction.h"
#include "../../../events/GameDispatcher.h"
#include "manager/ViewManager.h"
#include "view/newhand/components/NewHandHelpView.h"

ShowNewHandHelpAction::ShowNewHandHelpAction(int level) : _level(level)
{
}

void ShowNewHandHelpAction::doAction()
{
	if (!ViewManager::getInstance()->_helpView)
	{
		ViewManager::getInstance()->_helpView = new NewHandHelpView();
		GameDispatcher::getInstance()->addEventListener(GameDispatcher::RESET_NEWHELP_VIEW ,
			ViewManager::getInstance()->_helpView ,callfuncND_selector(NewHandHelpView::resetView));
	}
	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::RESET_NEWHELP_VIEW , (void *)&_level);
}

void ShowNewHandHelpAction::delAction(IAction* action)
{
	action->release();
	action = 0;
}
