#ifndef _TASK_LISTENER_MEDIATOR_H_
#define _TASK_LISTENER_MEDIATOR_H_
#include "view/BaseMediator.h"

class TaskListenerMediator : public BaseMediator
{
public:
	TaskListenerMediator();
	~TaskListenerMediator();


	void receiveHandler(CCNode *pNode , void *data);//int8 taskType, int16 id);
	void recTaskHandler(char *data);
	
	void submitHandler(CCNode *pNode , void *data);//int8 taskType, int16 id);
	void submitTaskHandler(char *data);
	
	void giveupHandler(CCNode *pNode , void *data);//int8 taskType, int16 id);
	void giviUPTaskHandler(char *data);

	void freshEntrustHandler(int8 taskType);
	void reFreshTaskList(int8 taskType);
	void refTaskHandler(char *data);
	bool hasDifficultLev();

	// Entrust task
	void immidiateFinishHandler(CCNode *pNode , void *data);//int8 taskType, int16 id);
	void finishTaskHandler(char *data);
	void updateTaskHandler(char *data);

	void startListener();

	void taskAutoRecOrSmt(CCNode* n, void* data);

	void showTaskView(CCNode *pNode, void *data);
};

#endif