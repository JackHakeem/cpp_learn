#ifndef _STORY_FOLLOW_NOTICE_H_
#define _STORY_FOLLOW_NOTICE_H_
#include "view/fight/interfaces/BaseAction.h"

using namespace cocos2d;

class IAction;

class StoryFollowNoticeAction : public BaseAction
{
public:
	StoryFollowNoticeAction();
	virtual ~StoryFollowNoticeAction(){}

	virtual void doAction();
	virtual void delAction(IAction* action);

public:
};

#endif