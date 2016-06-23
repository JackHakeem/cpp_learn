#ifndef _TASK_MANAGER_H_
#define _TASK_MANAGER_H_
#include "BaseType.h"
#include "utils/Singleton.h"
#include "model/task/vo/TaskVo.h"

typedef std::list<int> LIST_INT;
typedef std::map<int, LIST_INT> MAP_INT_LIST_INT;
typedef std::map<int, TaskVo *> MAP_INT_TASKVO;

class TaskManager : public Singleton<TaskManager>
{
public:
	TaskManager(){}
	~TaskManager();

	void setTask(TaskVo * task);
	TaskVo *getTask(int taskId);
	LIST_INT getTaskIdsByFrontTaskId(int id);
	TaskTipVo *makeTaskTips(std::string taskTipStr);

	MAP_INT_LIST_INT getTaskList_Leve();
	MAP_INT_LIST_INT getTaskList_FrontTask();
	LIST_INT getTaskIdsByLeve(int level);

public:
	/*All the tasks according to the mission Numbers for storage*/
	//private var _taskDic:Dictionary;
	MAP_INT_TASKVO _taskDic;
	/*Task according to task for storage level level of object is Array*/
	MAP_INT_LIST_INT _taskLeveDic;
	/*According to the preceding task lead tasks for the object is stored Numbers Array*/
	MAP_INT_LIST_INT _frontTaskDic;
	/*Entrust task*/
	//private var _entrustDic:Dictionary;


};
#endif