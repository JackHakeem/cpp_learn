#ifndef _STORY_FOLLOW_NOTIFY_H_
#define _STORY_FOLLOW_NOTIFY_H_
#include "view/fight/interfaces/BaseAction.h"

using namespace cocos2d;

class IAction;

class StoryFollowNotifyAction : public BaseAction
{
public:
	StoryFollowNotifyAction(int type);
	virtual ~StoryFollowNotifyAction(){}

	virtual void doAction();
	virtual void delAction(IAction* action);

public:
	int _type;
};

#endif