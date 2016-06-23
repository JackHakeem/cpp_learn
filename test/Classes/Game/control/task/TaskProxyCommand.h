#pragma once
#include "mvc/SimpleCommand.h"
#include "model/task/TaskProxy.h"
#include "model/crystal/CrystalProxy.h"

class TaskProxyCommand : public SimpleCommand
{
public:
	TaskProxyCommand(void);
	~TaskProxyCommand(void);

	enum
	{
		/*Init finish task*/
		INIT_FINISH_TASK_DATA = 0,
		/*Init receive tasks*/
		INIT_REC_TASK_DATA,
		/*Can receive entrust task */
		CAN_ENTRUST_TASK,
		/*Receive task return package*/
		REC_TASK,
		/*Finish task return package*/
		FINISH_TASK,
		/*Update task return package */
		UPDATE_TASK,
		/*Submit task return package */
		SUBMIT_TASK,
		/*Giveup task return package*/
		GIVIUP_TASK,
		/*Refresh task return package */
		REF_TASK
	};


	TaskProxy *_taskProxy;
	CrystalProxy *_crystalProxy;

	virtual void execute(int32 command, char* data);

	virtual void initTaskIsFinish(char* data);
	virtual void initRecTaskData(char* data);
	virtual void canEntrustTask(char* data);
	virtual void recTaskHandler(char* data);
	virtual void finishTaskHandler(char* data);
	virtual void updateTaskHandler(char* data);
	virtual void submitTaskHandler(char* data);
	virtual void giviUPTaskHandler(char* data);
	virtual void refTaskHandler(char* data);

	virtual void refreshCanTaskListByTask(int taskId, int level);

	virtual void startStory(TaskVo *taskVo, int type);
};

