#include "TaskProxyCommand.h"
#include "control/AppFacade.h"
#include "socket/command/s15/SCMD150.h"
#include "socket/command/s15/SCMD151.h"
#include "socket/command/s15/SCMD155.h"
#include "socket/command/s15/SCMD157.h"
#include "socket/command/s15/SCMD15A.h"
#include "socket/command/s15/SCMD15C.h"
#include "socket/command/s15/SCMD15E.h"
#include "model/task/vo/TaskVo.h"
#include "model/task/vo/TaskTipVo.h"
#include "model/task/TaskManager.h"

// Test for receive task and so on.
#include "view/task/TaskListenerMediator.h"
#include "model/crystal/vo/CrystalType.h"
#include "socket/command/s15/SCMD158.h"
#include "view/scene/SceneStoryMediator.h"

#include <bitset>
#include "view/dialog/DialogMediator.h"
#include "manager/GlobalManage.h"
#include "bear/manager/DisplayObjectManager.h"
#include "utils/ValuesUtil.h"
#include "manager/LangManager.h"
#include "view/fight/callback/ShowAttrChangeAction.h"

TaskProxyCommand::TaskProxyCommand(void)
{
	_crystalProxy = (CrystalProxy*) g_pFacade->retrieveProxy(AppFacade_CRYSTAL_PROXY_CHANGE);
}


TaskProxyCommand::~TaskProxyCommand(void)
{
}

void TaskProxyCommand::execute( int32 command, char* data )
{
	_taskProxy = (TaskProxy *) g_pFacade->retrieveProxy(AppFacade_TASK_PROXY);
	/*_crystalProxy = facade.retrieveProxy(CrystalProxy.NAME) as CrystalProxy;*/
	cocos2d::CCLog("============= taskProxyCommand,command=%d", command);
	switch(command){
	case INIT_FINISH_TASK_DATA:
		initTaskIsFinish(data);
		break;
	case INIT_REC_TASK_DATA:
		initRecTaskData(data);
		break;
	case CAN_ENTRUST_TASK:
		canEntrustTask(data);
		break;
	case REC_TASK:
		recTaskHandler(data);
		break;
	case FINISH_TASK:
		finishTaskHandler(data);
		break;
	case UPDATE_TASK:
		updateTaskHandler(data);
		break;
	case SUBMIT_TASK:
		submitTaskHandler(data);
		break;
	case GIVIUP_TASK:
		giviUPTaskHandler(data);
		break;
	case REF_TASK:
		refTaskHandler(data);
		break;

	}
}
// Init all task which is finished.
void TaskProxyCommand::initTaskIsFinish( char* data )
{
	SCMD150 *sCMD150 = (SCMD150 *) data;
	if(!sCMD150)
	{
		return;
	}
	std::list<int> finishList;
	int taskId = 0;
	std::list<int>::iterator it;
	for(it = sCMD150->_taskProcess.begin(); it != sCMD150->_taskProcess.end(); ++it)
	{
		int value = (int)*it;

		bitset<32> bitSet(value);
		for(int i=0; i<32; ++i)
		{
			if(bitSet[i] == 1)
			{
				finishList.push_back( taskId );
			}
			taskId ++;
		}
	}
	
	_taskProxy->initFinishLists(finishList);

}

// Init task which is received.
void TaskProxyCommand::initRecTaskData( char* data )
{
	SCMD151 *sCMD151 = (SCMD151 *) data;
	if(!sCMD151)
	{
		return;
	}
	std::vector<TaskVo *> receiveTaskList;

	std::list<SCMD151::SCMD151Node>::iterator it;
	for(it = sCMD151->_tasks.begin(); it != sCMD151->_tasks.end(); ++it)
	{
		SCMD151::SCMD151Node sCMD151Node = *it;
		TaskVo *taskVo = TaskManager::Instance()->getTask(sCMD151Node._id);
		if(taskVo)
		{
			//taskVo.taskTips.sortOn("id");
			//node.d_taskTip.sortOn("a_id");
			TaskTipVo *taskTipVo = taskVo->_taskTip;
			SCMD151::SCMD151Node1 tip = sCMD151Node._taskTip[0];
			taskTipVo->_nowCount = tip._nowCount;
			if(sCMD151Node._finish == 1)
			{
				taskTipVo->_isFinish = 1;
			}
			else if(taskTipVo->_count > 0
				&& taskTipVo->_nowCount == taskTipVo->_count)
			{
				taskTipVo->_isFinish = 1;
			}
			receiveTaskList.push_back(taskVo);
		}
		else if(sCMD151Node._taskTip.size() > 0) // May be EnTask.
		{
			//_taskProxy.accEntaskTemp = node as SCMD151Node;
		}
	}

	_taskProxy->initRecTaskList(receiveTaskList);
}

void TaskProxyCommand::canEntrustTask( char* data )
{

}

void TaskProxyCommand::recTaskHandler( char* data )
{
	SCMD155 *sCMD155 = (SCMD155 *) data;
	if(!sCMD155)
	{
		return;
	}

	cocos2d::CCLog("====================== id=%d", sCMD155->_id);
	if(sCMD155->_succ == 1)
	{
		//CCMessageBox("接受任务成功！", "Test");
		TaskVo *pTask = TaskManager::Instance()->getTask(sCMD155->_id);
		_taskProxy->addRecTaskList(pTask);
		//Doyang 20120802
		DisplayObjectManager::getInstance()->PlayRecvTaskEffect();

	}
	else
	{
		//CCMessageBox("接受任务失败！", "Test");
	}
}

void TaskProxyCommand::finishTaskHandler( char* data )
{
	SCMD157 *sCMD157 = (SCMD157 *) data;
	if(!sCMD157)
	{
		return;
	}
	if(sCMD157->_succ  ==1)
	{
		
		//CCMessageBox("完成任务！", "Test");
		//if(_taskProxy.acceptedEntrustTask && _taskProxy.acceptedEntrustTask.id == param.a_id.value){
		//	// 委托任务提交成功应该刷新列表 
		//}
		//else{
		TaskVo *taskVo = TaskManager::Instance()->getTask(sCMD157->_id);
		if(taskVo)
		{
			taskVo->_taskTip->_isFinish = 1;
			/*std::vector<TaskTipVo *>::iterator it;
			for(it = taskVo->_taskTips.begin(); it != taskVo->_taskTips.end(); ++it)
			{
				TaskTipVo *tip = *it;
				tip->_isFinish = 1;
			}
			startStory(taskVo,2);*/
			_taskProxy->finishTask(taskVo);
		}
		//}
		//Doyang 20120802
		//DisplayObjectManager::getInstance()->PlayFinTaskEffect();
	}
	else
	{
		//CCMessageBox("提交任务失败！", "Test");
	}
}

void TaskProxyCommand::updateTaskHandler( char* data )
{
	SCMD158 *sCMD158 = (SCMD158 *) data;
	if(!sCMD158)
	{
		return;
	}
	TaskVo *pTask = TaskManager::Instance()->getTask(sCMD158->_id);
	if(!pTask)
	{
		// EntrTask.

	}
	else
	{
		// NormalTask.
		int taskNowCount = sCMD158->_taskTip._nowCount;
		if(taskNowCount > 0 
			&& taskNowCount == pTask->_taskTip->_count)
		{
			pTask->_taskTip->_isFinish = 1;
		}
		pTask->_taskTip->_nowCount = taskNowCount;

		//Doyang 20121024
		char taskNeedChars[200];
		switch(pTask->_taskTip->_type)
		{
		case 0:
			// monsters
			sprintf(taskNeedChars, "%s (%d/%d)", 
				pTask->_taskTip->_name.c_str(), 
				pTask->_taskTip->_nowCount, 
				pTask->_taskTip->_count);
			break;
		case 1:
			// Collection.
			sprintf(taskNeedChars, "%s(%d/%d)",
				pTask->_taskTip->_name.c_str(), 
				pTask->_taskTip->_nowCount, 
				pTask->_taskTip->_count);
			break;
		default:
			sprintf(taskNeedChars, " ");
			break;
		}

		if (g_pGlobalManage->getisInFight())
		{
			FightProxy * pFightProxy = (FightProxy *)g_pFacade->retrieveProxy(AppFacade_FIGHT_PROXY_CHANGE);
			if (pFightProxy)
			{
				ShowAttrChangeAction * pAction = new ShowAttrChangeAction(taskNeedChars , ccc3(0,255,0) , 2);
				pFightProxy->_bData._callbacks.push_back(pAction);
			}	
		}
		else
		{
			LangManager::msgStr(taskNeedChars);
		}

		_taskProxy->updateRecTaskList(pTask);
	}
}

void TaskProxyCommand::submitTaskHandler( char* data )
{
	SCMD15A *sCMD15A = (SCMD15A *) data;
	if(!sCMD15A)
	{
		return;
	}
	if(sCMD15A->_succ == 1)
	{
		//CCMessageBox("提交任务成功！", "Test");
		/*if(_taskProxy.acceptedEntrustTask && _taskProxy.acceptedEntrustTask.id==param.a_id.value){
			_taskProxy.finishedEntrustTask();
		} 
		else{*/
			TaskVo *taskVo = TaskManager::Instance()->getTask(sCMD15A->_id);
			if(taskVo)
			{
				startStory(taskVo,4); 

				//var lev:int = _crystalProxy.getCrystalLev(CrystalType.CRYSTAL_MAIN);
				int lev = _crystalProxy->getCrystalLev(CrystalType::CRYSTAL_MAIN);
				_taskProxy->addFinishList( taskVo->_id, lev);
				//this.sendNotification(TaskMediator.TASK_EFFECT,2);
			}
			//} 
			//Doyang 20120802
			DisplayObjectManager::getInstance()->PlayFinTaskEffect();
	}
	else
	{
		//CCMessageBox("提交任务失败！", "Test");
	}
}

void TaskProxyCommand::giviUPTaskHandler( char* data )
{
	SCMD15C *sCMD15C = (SCMD15C *) data;
	if(!sCMD15C)
	{
		return;
	}

	if(sCMD15C->_succ == 1)
	{
		/*if(_taskProxy.acceptedEntrustTask && _taskProxy.acceptedEntrustTask.id==param.a_id.value){
		_taskProxy.giveUPEntrustTask();
		}
		else{*/
		/*TaskVo *taskVo = TaskManager::Instance()->getTask(sCMD15C->_id);
		if(taskVo) 
		{
		std::vector<TaskTipVo *>::iterator it;
		for(it = taskVo->_taskTips.begin(); it != taskVo->_taskTips.end(); ++it)
		{
		TaskTipVo *tip = *it;
		tip->_nowCount = 0;
		tip->_isFinish = 0;
		}
		_taskProxy->giveUpTask(taskVo->_id);
		}*/
		//}
	}

}

void TaskProxyCommand::refTaskHandler( char* data )
{
	SCMD15E *sCMD15E = (SCMD15E *) data;
	if(!sCMD15E)
	{
		return ;
	}
	if(sCMD15E->_succ == 1) 
	{
		
	}
}

void TaskProxyCommand::refreshCanTaskListByTask( int taskId, int level )
{



}

void TaskProxyCommand::startStory( TaskVo *taskVo, int type )
{
	std::vector<int>::iterator it;
	for(it = taskVo->_storys.begin(); it != taskVo->_storys.end(); ++it)
	{
		int storyType = (int) *it;
		if(storyType == type)
		{
			sendNotification(Facade_Mediator, AppFacade_NPCDIALOGUE_PROXY_CHANGE, NULL, DialogMediator::SET_AUTO_POP); 
			if (!g_pGlobalManage->_isInFight)
			{
				sendNotification(Facade_Mediator, AppFacade_SCENESTORY_PROXY_CHANGE,(char*)(&taskVo->_storys[1]),SceneStoryMediator::ROLE_MOVETOTARGET_STARTSTORY);
			}
			break;
		}
	}
}

