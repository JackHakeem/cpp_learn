#ifndef _TASK_CAT_TYPE_H_
#define _TASK_CAT_TYPE_H_

class TaskCatType
{
public:
	enum
	{
		//quests
		MAIN_TASK = 1,
		//Side quests
		BRANCH_TASK,
		//Daily tasks
		DAILY_TASK,
		//Entrust task
		ENTRUST_TASK
	};
};
#endif