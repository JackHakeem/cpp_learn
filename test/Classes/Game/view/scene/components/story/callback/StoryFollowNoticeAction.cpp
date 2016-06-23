#include "StoryFollowNoticeAction.h"
#include "../../../../broadcast/components/NoticeBanner.h"
#include "view/fight/interfaces/IAction.h"

StoryFollowNoticeAction::StoryFollowNoticeAction()
{
}

void StoryFollowNoticeAction::doAction()
{
	if (g_pSysNotice)
	{
		if (!g_pSysNotice->getIsRun())
		{
			g_pSysNotice->run();
		}	
	}	
}

void StoryFollowNoticeAction::delAction(IAction* action)
{
	action->release();
	action = 0;
}
