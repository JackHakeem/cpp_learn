#include "TaskListenerMediator.h"
#include "view/task/components/TaskCatType.h"
#include "socket/command/c15/CCMD154.h"
#include "socket/command/c15/CCMD156.h"
#include "socket/command/c15/CCMD159.h"
#include "socket/command/c15/CCMD15B.h"
#include "socket/command/c15/CCMD15D.h"
#include "control/task/TaskProxyCommand.h"
#include "model/task/vo/TaskVo.h"
#include "model/task/TaskManager.h"
#include "events/GameDispatcher.h"
#include "events/TaskEvent.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "TaskMediator.h"
#include "manager/PopEventName.h"
#include "MessageInfoBox.h"
#include "model/backpack/BagProxy.h"
#include "utils/ValuesUtil.h"
#include "components/TaskAutoFindNpc.h"
#include "components/TaskUtil.h"

void TaskListenerMediator::receiveHandler( CCNode *pNode , void *data ) //int8 taskType, int16 id )
{
	if(!data)
	{
		return;
	}

	TaskEvent *pTaskEvent = (TaskEvent *) data;
	if(!pTaskEvent)
	{
		return;
	}

	int taskType = pTaskEvent->taskType;
	int id = pTaskEvent->id;

    //CC_SAFE_DELETE(pTaskEvent);
    
	if(taskType == TaskCatType::ENTRUST_TASK)
	{
		// 委托任务
		/*if(_taskProxy.finishEntrustNum == _taskProxy.entrustLim){
			Message.show("今日的委托任务已达到上限！", 0xff0000);
			return;
		}*/
	}
	CCMD154 *cCMD154 = new CCMD154();
	cCMD154->_type = taskType;
	cCMD154->_id = id;

	_wSocket->sendMessage(cCMD154);
	CC_SAFE_DELETE(cCMD154); // LH0712LEAK

}

TaskListenerMediator::TaskListenerMediator()
{
	this->startListener();
}

TaskListenerMediator::~TaskListenerMediator()
{

}

/**
* Accept task to return to pack
* 
*/		
void TaskListenerMediator::recTaskHandler( char *data )
{
	sendNotification(Facade_Command, AppFacade_TASK_COMMAND, data,TaskProxyCommand::REC_TASK);
}

void TaskListenerMediator::immidiateFinishHandler( CCNode *pNode , void *data ) //( int8 taskType, int16 id )
{
	if(!data)
	{
		return;
	}

	TaskEvent *pTaskEvent = (TaskEvent *) data;
	if(!pTaskEvent)
	{
		return;
	}

	int taskType = pTaskEvent->taskType;
	int id = pTaskEvent->id;

	CCMD156 *cCMD156 = new CCMD156();
	cCMD156->_type = taskType;
	cCMD156->_id = id;
	_wSocket->sendMessage(cCMD156);
	CC_SAFE_DELETE(cCMD156); // LH0712LEAK
}

/**
* Submit task
* @param e
* 
*/		
void TaskListenerMediator::submitHandler( CCNode *pNode , void *data ) //( int8 taskType, int16 id )
{
	if(!data)
	{
		return;
	}

	TaskEvent *pTaskEvent = (TaskEvent *) data;
	if(!pTaskEvent)
	{
		return;
	}

	int taskType = pTaskEvent->taskType;
	int id = pTaskEvent->id;

	int goodsNum = 0;
	//var enTaskVo:EntrTaskVo = _taskProxy.getAcceptedEntrustTask();

	/*if(enTaskVo && enTaskVo.id == e.id) {
		if(enTaskVo.goodId>5) goodsNum++;
	}
	else{*/
		TaskVo *task = TaskManager::Instance()->getTask(id);
		if(!task)
		{
			return;
		}
		std::vector<int>::iterator it;
		for(it = task->_fixedGoods.begin(); it != task->_fixedGoods.end(); ++it)
		{
			int goodId = *it;
			if(goodId > 5) goodsNum ++;
		}
	//}

	BagProxy *pBagProxy = (BagProxy *) g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
	if(pBagProxy->getSpaceGridNum() <= 0 && goodsNum > 0)
	{
		MessageInfoBox::Instance()->show(ValuesUtil::Instance()->getString("BAG003").c_str(),
			ccc3(255, 0, 0));
		return;
	}

		CCMD159 *cCMD159 = new CCMD159();
		cCMD159->_type = taskType;
		cCMD159->_id = id;
		_wSocket->sendMessage(cCMD159);
		CC_SAFE_DELETE(cCMD159); // LH0712LEAK
}

/**
* Submit task to return
* @param param
* 
*/		
void TaskListenerMediator::submitTaskHandler( char *data )
{
	sendNotification(Facade_Command, AppFacade_TASK_COMMAND, data,TaskProxyCommand::SUBMIT_TASK);
}

void TaskListenerMediator::giveupHandler( CCNode *pNode , void *data ) //( int8 taskType, int16 id )
{
	if(!data)
	{
		return;
	}

	TaskEvent *pTaskEvent = (TaskEvent *) data;
	if(!pTaskEvent)
	{
		return;
	}

	int taskType = pTaskEvent->taskType;
	int id = pTaskEvent->id;

	CCMD15B *cCMD15B = new CCMD15B();
	cCMD15B->_type = taskType;
	cCMD15B->_id = id;
	_wSocket->sendMessage(cCMD15B);
	CC_SAFE_DELETE(cCMD15B); // LH0712LEAK
}

void TaskListenerMediator::giviUPTaskHandler( char *data )
{
	sendNotification(Facade_Command, AppFacade_TASK_COMMAND, data,TaskProxyCommand::GIVIUP_TASK);
}

/**
* Refresh task
* @param param
* 
*/		
void TaskListenerMediator::refTaskHandler( char *data )
{
	sendNotification(Facade_Command, AppFacade_TASK_COMMAND, data,TaskProxyCommand::REC_TASK);
}

/**
*Refresh Entrust task
*/
void TaskListenerMediator::freshEntrustHandler( int8 taskType )
{
	if(hasDifficultLev())
	{
		//Alert.show("是否刷新委托任务列表","",1, reFreshTaskList, null, null, null, e.taskType);
	}
	else
	{
		reFreshTaskList(taskType);
	}
}

bool TaskListenerMediator::hasDifficultLev()
{
	bool hasMoreDifficult = false;
	//int topLevel = _taskProxy->weekTopLev;
	//var entrDic:Dictionary = _taskProxy.getAllEntrustTask();
	//for each(var enTask:EntrTaskVo in entrDic){
	//	if(enTask.lev>topLev){   // 当前难度 1~6 对应 EDCBAS
	//		hasMoreDifficult = true;
	//		break;
	//	}
	//}
	return hasMoreDifficult;
}

void TaskListenerMediator::reFreshTaskList( int8 taskType )
{

	CCMD15D *cCMD15D = new CCMD15D();
	cCMD15D->_type = taskType;
	_wSocket->sendMessage(cCMD15D);
	CC_SAFE_DELETE(cCMD15D); // LH0712LEAK
}

void TaskListenerMediator::finishTaskHandler( char *data )
{
	sendNotification(Facade_Command, AppFacade_TASK_COMMAND, data,TaskProxyCommand::FINISH_TASK);
}

void TaskListenerMediator::updateTaskHandler( char *data )
{
	sendNotification(Facade_Command, AppFacade_TASK_COMMAND, data, TaskProxyCommand::UPDATE_TASK);
}

void TaskListenerMediator::startListener()
{
	GameDispatcher *_dispatcher = GameDispatcher::getInstance();
	
	_dispatcher->addEventListener(TaskEvent::RECEIVE, this, callfuncND_selector(TaskListenerMediator::receiveHandler));
	_dispatcher->addEventListener(TaskEvent::SUBMIT, this, callfuncND_selector(TaskListenerMediator::submitHandler));
	_dispatcher->addEventListener(TaskEvent::GIVEUP, this, callfuncND_selector(TaskListenerMediator::giveupHandler));
	//_dispatcher->addEventListener(TaskEvent::FINISH, this, callfuncND_selector(TaskListenerMediator::finishHandler));
	_dispatcher->addEventListener(TaskEvent::IMMIDIATE_FINISH, this, callfuncND_selector(TaskListenerMediator::immidiateFinishHandler));
	//_dispatcher.addEventListener(TaskEvent.FRESH_ENTRUST, freshEntrustHandler);
	_dispatcher->addEventListener(PopEventName::SHOW_UI_TASK, this, callfuncND_selector(TaskListenerMediator::showTaskView));
	//_dispatcher.addEventListener(GameDispatcher.CAN_TASK_DATA_CHANGE,refCanTask);
	//_dispatcher.addEventListener(GameDispatcher.REC_TASK_DATA_CHANGE,refRecTask);
	//_dispatcher.addEventListener(GameDispatcher.ENTRUST_TASK_DATA_CHANGE,refEntrustTask);
	_dispatcher->addEventListener(GameDispatcher::TASK_AUTO_REC_OR_SMT, this, callfuncND_selector(TaskListenerMediator::taskAutoRecOrSmt));

	//_wSocket.addCmdListener(SocketCMDConst.WMSG_WORLD_ENTRUST_TASK_VISIBLE,canEntrustTask);
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_WORLD_ACCEPT_TASK,recTaskHandler);
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_WORLD_COMPLETE_TASK,finishTaskHandler);
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_WORLD_TASK_UPDATE,updateTaskHandler);
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_WORLD_SUBMIT_TASK,submitTaskHandler);
	//_wSocket.addCmdListener(SocketCMDConst.WMSG_WORLD_GIVE_UP_TASK,giviUPTaskHandler);
}

void TaskListenerMediator::taskAutoRecOrSmt( CCNode* n, void* data )
{
	//TaskMediator *pTaskMediator = (TaskMediator *) g_pFacade->retrieveMediator(AppFacade_TASK_MEDIATOR);
	int taskId = *(int*) data;
	TaskVo *pTask;

	bool hasTaskExist = false;
	std::vector<TaskVo *>::iterator it;
	std::vector<TaskVo *> canTaskList = _taskProxy->getCanTasks();
	for(it = canTaskList.begin(); it != canTaskList.end(); ++ it)
	{
		pTask = *it;
		if(!pTask)
		{
			continue;
		}
		
		if(pTask->_id == taskId)
		{
			hasTaskExist = true;
			break;
		}
	}

	if(hasTaskExist)
	{
		TaskEvent *pTaskEvent = new TaskEvent();
		pTaskEvent->id = taskId;
		pTaskEvent->taskType = pTask->_type;
		/*if(pTaskMediator && pTaskMediator->_pTaskView)
		{
			std::string findNpcStr = pTaskMediator->_pTaskView->conditionHtmlString(pTask);
			pTaskMediator->_pTaskView->dispatchEvent(TaskUtil::FIND_ELEMENT, &findNpcStr);
		}*/
		_dispatcher->dispatchEvent(TaskEvent::RECEIVE, pTaskEvent);
        CC_SAFE_DELETE(pTaskEvent);
		return;
	}

	std::vector<TaskVo *> allRecTaskList = _taskProxy->getAllRecTask();
	for( it = allRecTaskList.begin(); it != allRecTaskList.end(); ++ it)
	{
		pTask = (TaskVo *) *it;
		if(!pTask)
		{
			continue;
		}
		if(pTask->_id == taskId)
		{
			TaskEvent *pTaskEvent = new TaskEvent();
			pTaskEvent->id = taskId;
			pTaskEvent->taskType = pTask->_type;
			_dispatcher->dispatchEvent(TaskEvent::SUBMIT, pTaskEvent);
            CC_SAFE_DELETE(pTaskEvent);
			/*if(pTaskMediator)
			{
				std::string findNpcStr = pTaskMediator->_pTaskView->conditionHtmlString(pTask);
				pTaskMediator->_pTaskView->dispatchEvent(TaskUtil::FIND_ELEMENT, &findNpcStr);
			}*/
			break;
		}
	}
}

void TaskListenerMediator::showTaskView( CCNode *pNode, void *data )
{
	sendNotification(Facade_Mediator, AppFacade_TASK_MEDIATOR, NULL, TaskMediator::TASK_VIEW_POP);
}

