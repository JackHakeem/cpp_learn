#ifndef _TASK_EVENT_H_
#define _TASK_EVENT_H_


class TaskEvent 
{
public:
	TaskEvent() 
	{
		npcId = id = taskType = 0;
	}
	~TaskEvent() {}

	enum
	{
		RECEIVE = GameDispatcher::DEFAULT_FLAG_TASK_EVENT,
		SUBMIT,
		GIVEUP,
		FINISH,
		IMMIDIATE_FINISH,
		FRESH_ENTRUST
	};

	int npcId;
	int id;
	int taskType;
};
#endif