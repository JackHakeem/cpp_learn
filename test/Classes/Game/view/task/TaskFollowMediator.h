#ifndef _TASK_FOLLOW_MEDIATOR_H_
#define _TASK_FOLLOW_MEDIATOR_H_

#include "mvc/Mediator.h"
#include "view/task/components/TaskFollowView.h"
#include "model/task/TaskProxy.h"
#include "events/GameDispatcher.h"

class TaskFollowMediator : public Mediator
{
public:
	TaskFollowMediator();
	~TaskFollowMediator();

	enum
	{
		ADD_TO_STAGE = GameDispatcher::DEFAULT_FLAG_TASK_FOLLOW,
		SHOW_TASK_FOLLOW_LIST,
		DISMISS_TASK_FOLLOW_LIST,
		ON_TASK_FOLLOW_LIST_SHOW,
		ON_TASK_FOLLOW_LIST_DISMISS,
	};

	void refRecTask(std::vector<TaskVo *> &recList);
	
	void addToStage();

	virtual void handleNotification( int M2Vcmd, char* data );

	void autoFindNpc(CCNode *pNode, void *data);
	void func();
	void func2();
	void findElement(CCNode *pNode, void *data);
	void showTaskFollowList(CCNode *pNode, void *data);
	void dismissTaskFollowList(CCNode *pNode, void *data);
public:
	TaskProxy *_pTaskProxy;
	TaskFollowView *_pFollowView;
	TaskVo *_autoFindTaskVo;
	
};

#endif