#include "TaskProxy.h"
#include "../dialog/vo/TaskNodeVo.h"
#include "view/task/components/TaskStrConcat.h"
#include "view/task/components/TaskState.h"
#include "../shop/ShopManager.h"
#include "../shop/vo/shopVo.h"
#include "view/task/TaskMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "TaskManager.h"
#include "../dialog/DialogManager.h"
#include "view/task/TaskFollowMediator.h"
#include "view/scene/SceneMediator.h"
#include "view/newhand/NewhandMediator.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "utils/ValuesUtil.h"
#include "AutoTaskManager.h"
#include "manager/GlobalManage.h"

TaskProxy::TaskProxy()
{
	_taskManager = TaskManager::Instance();
}


TaskProxy::~TaskProxy()
{
}

/**
* 初始化完成任务列表 
* @param taskIds
* 
*/	
void TaskProxy::initFinishLists( std::list<int> finishList )
{
	_taskFinishList.clear();
	std::list<int>::iterator it;
	for(it = finishList.begin(); it != finishList.end(); ++it)
	{
		int temp = (int) *it;

		CCLog("%d" , temp);
		//_taskFinishList.push_back(temp);
		_taskFinishList.insert(MAP_INT_INT::value_type(temp, temp));
	}

	// by LONGHUI 20121012
	AutoTaskManager::Instance()->startNewAutoTaskTimer(0);
}

/**
* 初始化已接任务列表 
* @param taskIds
* 
*/		
void TaskProxy::initRecTaskList( std::vector<TaskVo *> receiveTaskList )
{
	_receivedTaskList.clear();
	_receivedTaskList.assign(receiveTaskList.begin(), receiveTaskList.end());

	// by LONGHUI 20121012
	AutoTaskManager::Instance()->startNewAutoTaskTimer(0);
	/*std::list<TaskVo *>::iterator it;
	for(it = receiveTaskList.begin(); it != receiveTaskList.end(); ++it)
	{
		TaskVo *taskVo = *it;
		_receivedTaskList.insert(MAP_INT_TASKVO::value_type(taskVo->_id, taskVo));
	}*/
}

/**
* 添加完成任务 
* @param taskId
* 
*/		
void TaskProxy::addFinishList( int taskId, int level )
{
	_taskFinishList.insert(MAP_INT_INT::value_type(taskId, level));
	refreshCanTaskListByTask(taskId, level);

	// by LONGHUI 20121012
	AutoTaskManager::Instance()->startNewAutoTaskTimer(taskId);


	// LH20121016 newhand
	if (ViewManager::getInstance()->taskFollowView)
	{
		ViewManager::getInstance()->taskFollowView->_canTaskList = _canTaskList;
		ViewManager::getInstance()->taskFollowView->setCanTaskList();
	}

	// LH20121026 newhand
	if (ViewManager::getInstance()->_taskUIView)
	{
		ViewManager::getInstance()->_taskUIView->_canTaskList = _canTaskList;
		ViewManager::getInstance()->_taskUIView->resetScrollView();
	}
}

void TaskProxy::refreshCanTaskListByTask( int taskId, int level )
{
	std::list<int> tempNPCs;
	std::list<int> frontTasksList = _taskManager->getTaskIdsByFrontTaskId(taskId);
	std::list<int>::iterator it;
	for(it = frontTasksList.begin(); it != frontTasksList.end(); ++it)
	{
		int itTaskId = *it;
		TaskVo *taskVo = _taskManager->getTask(itTaskId);
		if(!taskVo)
		{
			continue;
		}
		if(taskVo->_level > level)
		{
			continue;
		}

		std::list<int>::iterator itNPC;
		for(itNPC = taskVo->_pNpcs.begin(); itNPC != taskVo->_pNpcs.end(); ++itNPC)
		{
			tempNPCs.push_back(*itNPC);
		}
		/*tempNPCs.push_back(taskVo->_pNpcs[0]);
		tempNPCs.push_back(taskVo->_pNpcs[1]);*/
		addCanTaskList(itTaskId, false);
	}
	//_receivedTaskList.erase(taskId);
	eraseReceivedTask(taskId);
	

	TaskVo *taskVo1 = _taskManager->getTask(taskId);
	int index = 0;
	std::list<int>::iterator itNPC;
	for(itNPC = taskVo1->_pNpcs.begin(); itNPC != taskVo1->_pNpcs.end(); ++itNPC)
	{
		if(index == 1)
		{
			tempNPCs.push_back(*itNPC);
			break;
		}
		++ index;
	}
	//tempNPCs.push_back(taskVo1->_pNpcs[1]);

	const int npcsCount = tempNPCs.size();
	if(npcsCount > 0)
	{
		/*int *pNpcs = new int[npcsCount];
		std::list<int>::iterator npcsIt;
		int index = 0;
		for(npcsIt = tempNPCs.begin(); npcsIt != tempNPCs.end(); ++ npcsIt)
		{
		pNpcs[index] = *npcsIt;
		index ++;
		}*/
		updateIco(tempNPCs);

		//Doyang 20120710
		//CC_SAFE_DELETE_ARRAY(pNpcs);
	}
	

	//GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::REC_TASK_DATA_CHANGE, &_receivedTaskList);
	//_dispatcher.dispatchEvent(new ParamEvent(GameDispatcher.CAN_TASK_DATA_CHANGE,getCanTasks()));//here

	this->sendNofiticationUpdateCanTask();
	this->sendNofiticationUpdateReceiveTask();

	// 20120611
	// Doyang.
	// For auto find next can task npc when finish a task.
	/*TaskVo *pNextTask = NULL;
	if(_canTaskList.size() > 0)
	{
		pNextTask = _canTaskList[0];
	}
	if(pNextTask)
	{
		GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::TASK_AUTO_FIND_NPC, pNextTask);
	}*/
}

void TaskProxy::addCanTaskList( int taskId, bool ref )
{
	bool isCanTask = false;
	std::vector<TaskVo *>::iterator itCanTask;
	for(itCanTask = _canTaskList.begin(); itCanTask != _canTaskList.end(); ++itCanTask)
	{
		TaskVo *task = *itCanTask;
		if(task->_id == taskId)
		{
			isCanTask = true;
			break;
		}
	}
	//MAP_INT_INT::iterator itCanTaskList = _canTaskList.find(taskId);

	bool isReceiveTask = false;
	std::vector<TaskVo *>::iterator itRecTask;
	for(itRecTask = _receivedTaskList.begin(); itRecTask != _receivedTaskList.end(); ++itRecTask)
	{
		TaskVo *task = *itRecTask;
		if(task->_id == taskId)
		{
			isReceiveTask = true;
			break;
		}
	}
	//MAP_INT_TASKVO::iterator itReceivedTaskList = _receivedTaskList.find(taskId);
	
	MAP_INT_INT::iterator itFinishTaskList = _taskFinishList.find(taskId);

	TaskVo *task = _taskManager->getTask(taskId);

	if(!isCanTask
		&& itFinishTaskList == _taskFinishList.end()
		&& !isReceiveTask
		&& task)
	{
		if (task->_type == 1)
		{
			std::vector<TaskVo *> tmpCanTask = _canTaskList;
			_canTaskList.clear();
			_canTaskList.push_back(task);
			std::vector<TaskVo *>::iterator iter = tmpCanTask.begin();
			for (iter ; iter != tmpCanTask.end() ; )
			{
				_canTaskList.push_back(*tmpCanTask.begin());
				tmpCanTask.erase(tmpCanTask.begin());
				iter = tmpCanTask.begin();
			}
		}
		else
		{
			_canTaskList.push_back(task);
		}
		//_canTaskList.insert(MAP_INT_INT::value_type(taskId, taskId));
	}
	
	if(ref)
	{
		// 不会走到这里~
		// yangliangjie

		this->updateIco(task->_pNpcs);

		this->sendNofiticationUpdateCanTask();

		/*updateIco([task.npcs[0]]);
		_dispatcher.dispatchEvent(new ParamEvent(GameDispatcher.CAN_TASK_DATA_CHANGE,getCanTasks()));*/

	}
}

void TaskProxy::giveUpTask( int taskId )
{
	TaskProxy::eraseReceivedTask(taskId);
	/*if(ViewManager.getInstance().dialogView){
		ViewManager.getInstance().dialogView.npcId = 0;
	}*/

	addCanTaskList(taskId, false);
	TaskVo *taskVo = _taskManager->getTask(taskId);
	if(taskVo)
	{

	}
	updateIco(taskVo->_pNpcs);

	this->sendNofiticationUpdateCanTask();
	this->sendNofiticationUpdateReceiveTask();


	////触发更新已接任务事件
	//GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::REC_TASK_DATA_CHANGE, &_receivedTaskList);
	//_dispatcher.dispatchEvent(new ParamEvent(GameDispatcher.CAN_TASK_DATA_CHANGE,getCanTasks()));
}

void TaskProxy::finishTask( TaskVo *taskVo )
{
	int receiveListSize = _receivedTaskList.size();
	for(int i=0; i<receiveListSize; ++i)
	{
		if(_receivedTaskList[i]->_id == taskVo->_id)
		{
			_receivedTaskList[i] = taskVo;
			break;
		}
	}
	updateIco(taskVo->_pNpcs);

	DialogView *pDialogView = ViewManager::getInstance()->dialogView;
	if(pDialogView && pDialogView->_autoPop && pDialogView->_noStory){
		if(/*taskVo->_pNpcs->length() > 1 && */taskVo->getFinishTaskNpc() == pDialogView->_npcId){
			GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_DIALOGUE, &pDialogView->_npcId);
		}
	}

	this->sendNofiticationUpdateReceiveTask();

	// by LONGHUI 20121012
	AutoTaskManager::Instance()->startNewAutoTaskTimer(taskVo->_id);

	//
	if (ViewManager::getInstance()->taskFollowView)
	{
		ViewManager::getInstance()->taskFollowView->_canTaskList = _canTaskList;
		ViewManager::getInstance()->taskFollowView->setCanTaskList();
	}

	//
	if (ViewManager::getInstance()->_taskUIView)
	{
		ViewManager::getInstance()->_taskUIView->_canTaskList = _canTaskList;
		ViewManager::getInstance()->_taskUIView->resetScrollView();
	}
	

	//_receivedTaskList.insert(MAP_INT_TASKVO::value_type(taskVo->_id, taskVo));
	//updateIco(task.npcs);
	/*var dialogView:DialogView = ViewManager.getInstance().dialogView;
	if(dialogView && dialogView.autoPop && dialogView.noStory){
	if(task.npcs.length>1 && task.npcs[1]==dialogView.npcId){
	_dispatcher.dispatchEvent(new ParamEvent(PopEventName.SHOW_UI_DIALOGUE, {id: dialogView.npcId}));
	}
	}*/
	//			//触发更新已接任务事件
	//GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::REC_TASK_DATA_CHANGE, &_receivedTaskList);
}

/**
*  根据NPC获取相应的任务状态
* @param npcId
* @return TaskState 0为没有相关任务
* 
*/
int TaskProxy::getIcoByNPC( int npcId )
{
	bool has = false;
	//TaskNodeVo *taskNodeVo;
	TaskVo *task;
	std::vector<TaskVo *>::iterator itReceiveTask;
	for(itReceiveTask = _receivedTaskList.begin(); itReceiveTask != _receivedTaskList.end(); ++itReceiveTask)
	{
		//taskNodeVo = new TaskNodeVo();
		task = *itReceiveTask;
		bool isFinish = TaskStrConcat::checkTaskFinish(task->_taskTip);
	//	int taskNpcId = task->_pNpcs[1];
		if(task->getFinishTaskNpc() == npcId)
		{
			if(isFinish)
				return FINISH_ICON;
			else 
			{
				has = true;
				continue;
			}
		}
	}

	std::vector<TaskVo *>::iterator itCanTask;
	for(itCanTask = _canTaskList.begin(); itCanTask != _canTaskList.end(); ++itCanTask)
	{
		task = _taskManager->getTask((*itCanTask)->_id);
		if(task != NULL)
		{
			if(task->getRecTaskNpc() == npcId)
				return CANREC_ICON;
		}
	}

	if(has)
		return NOFINISH_ICON;
	else
	{
		ShopVo *pShopVo = ShopManager::Instance()->getShopsByNPCId(npcId);
		if(!pShopVo) return 0;

		return ShopManager::Instance()->getIconByType(pShopVo->type);
	}
}

void TaskProxy::eraseReceivedTask( int taskId )
{
	std::vector<TaskVo *>::iterator it;
	for(it = _receivedTaskList.begin(); it != _receivedTaskList.end(); ++it)
	{
		TaskVo *taskVo = *it;
		if(taskVo->_id == taskId)
		{
			_receivedTaskList.erase(it);
			break;
		}
	}
}

std::vector<TaskVo *> TaskProxy::getAllRecTask()
{
	return _receivedTaskList;
}

void TaskProxy::initCanTaskList( int level )
{
	TaskManager *pTaskManager = TaskManager::Instance();
	MAP_INT_LIST_INT leveDic =  pTaskManager->getTaskList_Leve();
	MAP_INT_LIST_INT frontDic =  pTaskManager->getTaskList_FrontTask();

	//According to the level that can refresh quests
	MAP_INT_LIST_INT::iterator levelIt;
	for(levelIt = leveDic.begin(); levelIt != leveDic.end(); ++ levelIt)
	{
		if((*levelIt).first <= level)
		{
			LIST_INT tempList = (*levelIt).second;
			LIST_INT::iterator tempListIt;
			for(tempListIt = tempList.begin(); tempListIt != tempList.end(); ++tempListIt)
			{
				int taskId = (int) *tempListIt;
				TaskVo *pTaskVo = pTaskManager->getTask(taskId);
				if(!pTaskVo)
				{
					continue;
				}
				bool isFinish = false;
				MAP_INT_INT::iterator isFinishIt = _taskFinishList.find(pTaskVo->_frontTaskId);
				if(isFinishIt != _taskFinishList.end())
				{
					isFinish = true;
				}

				if(pTaskVo->_frontTaskId == 0 || isFinish)
				{
					addCanTaskList(taskId, false);
				}
			}
		}
	}

	//_canTaskList;

	//According to the preceding task refreshes the may meet task
	MAP_INT_LIST_INT::iterator frontIt;
	for(frontIt = frontDic.begin(); frontIt != frontDic.end(); ++ frontIt)
	{
		int taskId = (*frontIt).first;

		bool isFinish = false;
		MAP_INT_INT::iterator isFinishIt = _taskFinishList.find(taskId);
		if(isFinishIt != _taskFinishList.end())
		{
			isFinish = true;
		}

		if(isFinish)
		{
			LIST_INT tempList = (*frontIt).second;
			LIST_INT::iterator tempListIt;
			for(tempListIt = tempList.begin(); tempListIt != tempList.end(); ++ tempListIt)
			{
				int taskId = (int) *tempListIt;
				TaskVo *pTaskVo = pTaskManager->getTask(taskId);
				if(!pTaskVo)
				{
					continue;
				}

				if(pTaskVo->_level <= level)
				{
					addCanTaskList(taskId, false);
				}
			}
		}

	}

	this->sendNofiticationUpdateCanTask();

	// by LONGHUI 20121012
	AutoTaskManager::Instance()->startNewAutoTaskTimer(0);
}

/**
*getFinishOrRecvTask id list（for btn start） 
* @return 
* 
*/		
vector<int> TaskProxy::getFinishOrRecvTask()
{
	vector<int> arr;

	MAP_INT_INT::iterator it = _taskFinishList.begin();
	for ( ;it != _taskFinishList.end(); it++ )
	{
		arr.push_back( it->first );
	}

	for ( size_t i = 0; i < _receivedTaskList.size(); i++ )
	{
		if ( TaskVo* pTaskVo = _receivedTaskList[i] )
		{
			arr.push_back( pTaskVo->_id );
		}
	}
	return arr;
}

std::vector<TaskNodeVo *> TaskProxy::getCanAndRecTasks( int npcId )
{
	std::vector<TaskNodeVo *> taskList;
	std::vector<TaskVo *>::iterator recListIt;
	for( recListIt = _receivedTaskList.begin(); recListIt != _receivedTaskList.end(); ++ recListIt)
	{
		TaskVo *task = *recListIt;
		if(!task) continue;

		bool isFinish = TaskStrConcat::checkTaskFinish(task->_taskTip);
		bool has = false;
		if(task->getFinishTaskNpc() == npcId)
		{
			has = true;
		}
		if(has)
		{
			int state = isFinish ? 2 : 3;
			taskList.push_back(createTaskNodeVo(task, state));
		}
	}

	std::vector<TaskVo *>::iterator canListIt;
	for( canListIt = _canTaskList.begin(); canListIt != _canTaskList.end(); ++ canListIt)
	{
		TaskVo *canTask = *canListIt;
		TaskVo *task = _taskManager->getTask(canTask->_id);
		if(!task) continue;

		if(task->getRecTaskNpc() == npcId)
		{
			taskList.push_back(createTaskNodeVo(task, 0));
		}
	}
	return taskList;
}

TaskNodeVo * TaskProxy::createTaskNodeVo( TaskVo *taskVo, int state )
{
	TaskNodeVo *taskNodeVo = new TaskNodeVo();
	std::vector <DialogueNodeVo * > dialogList;
	
	int dialogType = 0;

	std::vector<int>::iterator dialogsIt;
	for( dialogsIt = taskVo->_dialogs.begin();
		dialogsIt != taskVo->_dialogs.end();
		++ dialogsIt)
	{
		int dialogId = *dialogsIt;
		DialogueVo *dialog = DialogManager::Instance()->getDialogs(dialogId);
		//if(dialog)dialog.content = DialogUtil.replaceColor(dialog.content);
		DialogueNodeVo *dvo = new DialogueNodeVo();
        char newText[512];
        if(dialog == NULL)
        {
			sprintf( newText, "%s", ValuesUtil::Instance()->getString("task_ask").c_str());
        }
        else 
        {
            strcpy(newText, dialog->content.c_str());
        }
        dvo->_text = newText;
		dvo->_type = dialogType++;
		dialogList.push_back(dvo);
	}

	taskNodeVo->_id = taskVo->_id;
	taskNodeVo->_type = taskVo->_type;
	taskNodeVo->_state = state;
	taskNodeVo->_name = taskVo->_taskName;
	taskNodeVo->_list = dialogList;
	return taskNodeVo;
}

void TaskProxy::addRecTaskList( TaskVo *taskVo )
{
	if (!taskVo)
	{
		return;
	}	

	if (taskVo->_type == 1)
	{
		std::vector<TaskVo *> tmpCanTask = _receivedTaskList;
		_receivedTaskList.clear();
		_receivedTaskList.push_back(taskVo);
		std::vector<TaskVo *>::iterator iter = tmpCanTask.begin();
		for (iter ; iter != tmpCanTask.end() ; )
		{
			_receivedTaskList.push_back(*tmpCanTask.begin());
			tmpCanTask.erase(tmpCanTask.begin());
			iter = tmpCanTask.begin();
		}
	}
	else
	{
		_receivedTaskList.push_back(taskVo);
	}

	// LH20121114
	TaskUIView * pTaskView = ViewManager::getInstance()->_taskUIView;
	if (pTaskView)
	{
		pTaskView->setCurTaskId(taskVo->_id);
	}
	

	std::vector<TaskVo *>::iterator canTaskIt;
	for(canTaskIt = _canTaskList.begin(); canTaskIt != _canTaskList.end(); ++canTaskIt)
	{
		TaskVo *pCanTask = *canTaskIt;
		if(pCanTask->_id == taskVo->_id)
		{
			_canTaskList.erase(canTaskIt);
			break;
		}
	}

	this->updateIco(taskVo->_pNpcs);

	// Send notify.
	this->sendNofiticationUpdateReceiveTask();
	this->sendNofiticationUpdateCanTask();

	//  by LH20121120
	if (taskVo->_type == 1)
	{
		GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::TASK_AUTO_FIND_NPC, taskVo);
	}	

	// by LONGHUI 20121012
	AutoTaskManager::Instance()->startNewAutoTaskTimer(taskVo->_id);
}

void TaskProxy::updateRecTaskList( TaskVo *taskVo )
{
	std::vector<TaskVo *>::iterator recTaskIt;
	int i=0;
	for(recTaskIt = _receivedTaskList.begin(); recTaskIt != _receivedTaskList.end(); ++ recTaskIt)
	{
		TaskVo *pTask = *recTaskIt;
		if(pTask->_id == taskVo->_id)
		{
			_receivedTaskList[i] = taskVo;
			break;
		}
		i++;
	}
	bool isFinish = TaskStrConcat::checkTaskFinish(taskVo->_taskTip);
	if(isFinish)
	{
		// Update icon.
		updateIco(taskVo->_pNpcs);
	}
	// Send notify receive task changed.
	this->sendNofiticationUpdateReceiveTask();

	if (g_pGlobalManage->getDunGUA() == 0 && g_pGlobalManage->getTowerGUA() == 0)//kevin20121204
	{
		GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::TASK_AUTO_FIND_NPC, taskVo);

		// by LONGHUI 20121012
		AutoTaskManager::Instance()->startNewAutoTaskTimer(taskVo->_id);	
	}
}

void TaskProxy::updateIco(std::list<int> &npcs)
{
	/*struct NpcList
	{
	std::list<int> npcs;
	int length;
	};

	NpcList *pNpcList = new NpcList();
	pNpcList->npcs = npcs;
	pNpcList->length = len;
	*/
	sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*)&npcs, SceneMediator::NPC_ICO_CHANGE);
}

void TaskProxy::sendNofiticationUpdateReceiveTask()
{
	TaskFollowMediator *pTaskFollowMediator = (TaskFollowMediator *) g_pFacade->retrieveMediator(AppFacade_TASK_FOLLOW_MEDIATOR);
	pTaskFollowMediator->refRecTask(_receivedTaskList);

	TaskMediator *pTaskMediator = (TaskMediator *) g_pFacade->retrieveMediator(AppFacade_TASK_MEDIATOR);
	pTaskMediator->layoutRecData(_receivedTaskList);

	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::REC_TASK_DATA_CHANGE, &_receivedTaskList);
	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::CAN_TASK_DATA_CHANGE, &_canTaskList);
}

void TaskProxy::sendNofiticationUpdateCanTask()
{
	TaskMediator *pTaskMediator = (TaskMediator *) g_pFacade->retrieveMediator(AppFacade_TASK_MEDIATOR);
	pTaskMediator->layoutCanData(_canTaskList);

	GameDispatcher *_dispatcher = GameDispatcher::getInstance();
	//Doyang 20120710
//    std::vector<TaskVo *> &list = getCanTasks();
	_dispatcher->dispatchEvent(GameDispatcher::CAN_TASK_DATA_CHANGE, &_canTaskList);

}

void TaskProxy::refreshCanTaskListByLeve( int mainLev )
{
	std::list<int> tempNPCs;

	LIST_INT taskList = TaskManager::Instance()->getTaskIdsByLeve(mainLev);
	bool levelMore = false;

	LIST_INT::iterator taskIt;
	for(taskIt = taskList.begin(); taskIt != taskList.end(); ++ taskIt)
	{
		int taskId = *taskIt;
		TaskVo *pTask = TaskManager::Instance()->getTask(taskId);
		if(!pTask)
		{
			continue;
		}
		int frontId = pTask->_frontTaskId;
		MAP_INT_INT::iterator taskFinishIt = _taskFinishList.find(frontId);
		if(taskFinishIt == _taskFinishList.end()
			&& frontId != 0)
		{
			continue;
		}

		std::list<int>::iterator npcsIt;
		for(npcsIt = pTask->_pNpcs.begin(); npcsIt != pTask->_pNpcs.end(); ++ npcsIt)
		{
			tempNPCs.push_back(*npcsIt);
		}

		this->addCanTaskList(taskId, false);
		if(!levelMore)
		{
			levelMore = true;
		}
	}
	if(levelMore)
	{
		/*const int npcsCount = tempNPCs.size();
		int *pNpcs = new int[npcsCount];
		std::list<int>::iterator npcsIt;
		int index = 0;
		for(npcsIt = tempNPCs.begin(); npcsIt != tempNPCs.end(); ++ npcsIt)
		{
			pNpcs[index] = *npcsIt;
			index ++;
		}*/
		this->updateIco(tempNPCs);
		this->sendNofiticationUpdateCanTask();
	}
}

bool TaskProxy::isTaskFinished( int taskId )
{
	MAP_INT_INT::iterator it = _taskFinishList.find(taskId);
	if(it != _taskFinishList.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::vector<TaskVo *> TaskProxy::getCanTasks()
{
	return _canTaskList;
}
