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

	///*�ɽ����� �������Ŵ��*/
	//private var _canTaskList:Dictionary;
	///*�ѽ����� �������Ŵ��  ��ŵĶ���TaskTipVO*/
	//private var _receivedTaskList:Dictionary;
	///*�Ѿ���ɲ��ύ������ �������Ŵ�� ��ŵĶ�����������*/
	//private var _taskFinishList:Dictionary;
	///*������ί������*/
	//private var _canEntrustTaskList:Array;
	///*��ǰ���ܵ�ί������*/
	//private var _acceptedEntrustTask:EntrTaskVo;


	///*�ɽ����� �������Ŵ��*/
	std::vector<TaskVo *> _canTaskList;
	/*�Ѿ���ɲ��ύ������ �������Ŵ�� ��ŵĶ�����������*/
	MAP_INT_INT _taskFinishList;
	/*�ѽ����� �������Ŵ��  ��ŵĶ���TaskTipVO*/
	/************************************************************************/
	/* C++�汾��������Ŷ���ΪTaskVo                                        */
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
