#ifndef _TASK_AUTO_FIND_NPC_H
#define _TASK_AUTO_FIND_NPC_H
#include "utils/Singleton.h"
#include "model/task/vo/TaskVo.h"
#include "model/task/vo/TaskTipVo.h"

class TaskAutoFindNpc : public Singleton<TaskAutoFindNpc>
{
public:
	TaskAutoFindNpc();
	~TaskAutoFindNpc() {}

	std::string taskFollowStr(TaskVo *pTaskVo);
	std::string getDialogType(TaskVo *pTaskVo, TaskTipVo *pTaskTipVo);
	std::string getBehaviorType(TaskVo *pTaskVo, TaskTipVo *pTaskTipVo);
	std::string getUpGradeType(TaskVo *pTaskVo, TaskTipVo *pTaskTipVo);

	std::string conditionHtmlString( TaskVo *pTaskVo );

	int _progress;
};
#endif