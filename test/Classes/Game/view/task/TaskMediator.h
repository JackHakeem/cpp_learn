#ifndef _TASK_VIEW_MEDIATOR_H_
#define _TASK_VIEW_MEDIATOR_H_
#include "cocos2d.h"
#include "mvc/Mediator.h"
#include "components/TaskView.h"
#include "model/task/TaskProxy.h"
class TaskMediator : public Mediator
{
public:
	TaskMediator();
	~TaskMediator();

	enum
	{
		TASK_VIEW_POP = 0,
	};

	void openTaskView();
	void openTaskHandler();
	void create();
	void layoutEntrustData();
	void layoutCanData(std::vector<TaskVo *> &taskList);
	void layoutRecData(std::vector<TaskVo *> &taskList);

	virtual void handleNotification( int M2Vcmd, char* data );
	void findElement(CCNode *pNode, void *data);

public:
	TaskView *_pTaskView;
	TaskProxy *_pTaskProxy;
};
#endif