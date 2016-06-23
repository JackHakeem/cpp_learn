#ifndef _TASK_STATE_H_
#define _TASK_STATE_H_

enum TaskState
{
	//May meet the task
	CANREC = 1,
	//Already quests, not been completed
	NOFINISH,
	//Has been completed, and fails to submit
	FINISH,
	// May meet mission ICON
	CANREC_ICON = 2,
	// Already quests, not been completed ICON
	NOFINISH_ICON,
	// Has been completed, and fails to submit  ICON
	FINISH_ICON
};
#endif