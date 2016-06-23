#include "TaskManager.h"


/**
* According to the mission Numbers for the task
* @param taskId
* @return 
* 
*/		
TaskVo *TaskManager::getTask( int taskId )
{
	MAP_INT_TASKVO::iterator it = _taskDic.find(taskId);
	if(it != _taskDic.end())
	{
		return it->second;
	}
	return NULL;
}

LIST_INT TaskManager::getTaskIdsByFrontTaskId( int id )
{
	MAP_INT_LIST_INT::iterator it = _frontTaskDic.find(id);
	if(it == _frontTaskDic.end())
	{
		return (LIST_INT)NULL;
	}
	else
	{
		LIST_INT& fontList = it->second;
		return fontList;
	}
}

void TaskManager::setTask( TaskVo *task )
{
	if(task->_type != 4)
	{
		// Entrusted by the task

		//TaskVo *taskVo = new TaskVo();
		_taskDic.insert(MAP_INT_TASKVO::value_type(task->_id, task));

		//cocos2d::CCLog("=========== new Task id=%d,taskDic size=%d", task->_id, _taskDic.size());
		//_taskDic.insert(MAP_INT_TASKVO::value_type(task->_id, ))

		MAP_INT_LIST_INT::iterator itLevelList = _taskLeveDic.find(task->_level);
		if(itLevelList != _taskLeveDic.end())
		{
			(*itLevelList).second.push_back(task->_id);
		}
		else
		{
			LIST_INT levelTaskList;
			levelTaskList.push_back(task->_id);
			_taskLeveDic.insert(MAP_INT_LIST_INT::value_type(task->_level, levelTaskList));
		}

		if(task->_frontTaskId != 0)
		{
			MAP_INT_LIST_INT::iterator itFrontList = _frontTaskDic.find(task->_frontTaskId);
			if(itFrontList != _frontTaskDic.end())
			{
				(*itFrontList).second.push_back(task->_id);
			}
			else
			{
				LIST_INT frontTaskList;
				frontTaskList.push_back(task->_id);
				_frontTaskDic.insert(MAP_INT_LIST_INT::value_type(task->_frontTaskId, frontTaskList));
			}
		}
	}

}

TaskTipVo * TaskManager::makeTaskTips( std::string taskTipStr )
{
	// The cancellation of the function, in TaskVo in dealing with
	// yangliangjie
	return NULL;
}

MAP_INT_LIST_INT TaskManager::getTaskList_Leve()
{
	return _taskLeveDic;
}

MAP_INT_LIST_INT TaskManager::getTaskList_FrontTask()
{
	return _frontTaskDic;
}

LIST_INT TaskManager::getTaskIdsByLeve( int level )
{
	MAP_INT_LIST_INT::iterator it = _taskLeveDic.find(level);
	if(it == _taskLeveDic.end())
	{
		return (LIST_INT)NULL;
	}
	else
	{
		LIST_INT& taskList = it->second;
		return taskList;
	}
}

TaskManager::~TaskManager()
{
	MAP_INT_TASKVO::iterator it;
	for ( it = _taskDic.begin(); it != _taskDic.end(); it++ )
	{
		CC_SAFE_DELETE( it->second );
	}
}