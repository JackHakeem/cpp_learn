#ifndef _TASK_PROXY_H_
#define _TASK_PROXY_H_

#pragma once
#include "mvc/Proxy.h"
#include "model/task/vo/TaskVo.h"
#include "model/task/TaskManager.h"
#include "../dialog/vo/TaskNodeVo.h"

typedef std::map<int, int> MAP_INT_INT;

class TaskProxy : public Proxy
{
public:
	TaskProxy();
	virtual ~TaskProxy();

	TaskManager *_taskManager;

	///*可接任务 按任务编号存放*/
	//private var _canTaskList:Dictionary;
	///*已接任务 按任务编号存放  存放的对象TaskTipVO*/
	//private var _receivedTaskList:Dictionary;
	///*已经完成并提交的任务 按任务编号存放 存放的对象是任务编号*/
	//private var _taskFinishList:Dictionary;
	///*存放五个委托任务*/
	//private var _canEntrustTaskList:Array;
	///*当前接受的委托任务*/
	//private var _acceptedEntrustTask:EntrTaskVo;


	///*可接任务 按任务编号存放*/
	std::vector<TaskVo *> _canTaskList;
	/*已经完成并提交的任务 按任务编号存放 存放的对象是任务编号*/
	MAP_INT_INT _taskFinishList;
	/*已接任务 按任务编号存放  存放的对象TaskTipVO*/
	/************************************************************************/
	/* C++版本修正，存放对象为TaskVo                                        */
	/************************************************************************/ 
	std::vector<TaskVo *> _receivedTaskList;

public:

	void initFinishLists(std::list<int> finishList);

	void initRecTaskList(std::vector<TaskVo *> receiveTaskList);

	void initCanTaskList(int level);

	void addFinishList(int taskId, int level);

	void refreshCanTaskListByTask(int taskId, int level);
	void refreshCanTaskListByLeve(int mainLev);

	void addCanTaskList(int taskId, bool ref);

	void giveUpTask(int taskId);

	void finishTask(TaskVo *taskVo);

	int getIcoByNPC(int npcId);

	void addRecTaskList(TaskVo *taskVo);

	bool isTaskFinished(int taskId);

	std::vector<TaskNodeVo *> getCanAndRecTasks(int npcId);

	std::vector<TaskVo *> getAllRecTask();
	vector<int> getFinishOrRecvTask();

	void updateRecTaskList(TaskVo *taskVo);

	//void updateIco(int npcs[]);
	void updateIco(std::list<int> &npcs);

	std::vector<TaskVo *> getCanTasks();

	// Custom
	void sendNofiticationUpdateReceiveTask();
	void sendNofiticationUpdateCanTask();


private:

	void eraseReceivedTask(int taskId);

	TaskNodeVo *createTaskNodeVo(TaskVo *taskvo, int state);
};


#endif
