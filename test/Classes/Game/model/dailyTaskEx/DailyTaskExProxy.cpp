#include "DailyTaskExProxy.h"
#include "events/GameDispatcher.h"
#include "view/dailyTaskEx/DailyTaskExMediator.h"
#include "manager/LangManager.h"
#include "manager/ViewManager.h"
#include "view/notify/NotifyManager.h"
#include "view/notify/NotifyType.h"

DailyTaskExProxy::DailyTaskExProxy()
{
	_dailyTaskExList.clear();
	_remainTaskCount = 0;
	_remainFreeRefreshCount = 0;
	_FinishTaskToast = true;
	_hasUnFinishTask = false;
}

void DailyTaskExProxy::onDailyTaskExChanged( SCMD421 *pPacket )
{
	if(!pPacket)
	{
		return;
	}
	setRemainFreeRefreshCount(pPacket->b_remainFreeCount);
	setRemainTaskCount(pPacket->a_remainTaskCount);

	std::vector<DailyTaskExVo *>::iterator listIter = _dailyTaskExList.begin();
	for(; listIter != _dailyTaskExList.end(); ++listIter)
	{
		CC_SAFE_DELETE(*listIter);
	}
	_dailyTaskExList.clear();

	bool hasFinishTask = false;
	bool hasUnFinishTask = false;
	std::vector<SCMD421::SCMD421Node>::iterator iter = pPacket->d_nodeList.begin();
	for(; iter != pPacket->d_nodeList.end(); ++iter)
	{
		DailyTaskExVo *pTaskVo = new DailyTaskExVo();
		pTaskVo->taskId = iter->a_taskId;
		pTaskVo->quailty = iter->b_quality;
		pTaskVo->count = iter->c_count;
		pTaskVo->finishCount = iter->d_finishCount;
		pTaskVo->type = iter->e_taskType;
		pTaskVo->monsterGroup = iter->f_monsterGroup;
		pTaskVo->hasAccepted = iter->g_hasAccepted;

		if(iter->c_count == iter->d_finishCount)
		{
			hasFinishTask = true;
		}
		if(1 == iter->g_hasAccepted)
		{
			hasUnFinishTask = true;
		}
		// Award
		std::vector<SCMD421::SCMD421Node2>::iterator iter2 = iter->h_awardList.begin();
		for(; iter2 != iter->h_awardList.end(); ++ iter2)
		{
			pTaskVo->awardList.push_back(std::make_pair(iter2->a_goodsId, iter2->b_goodsNum));
		}

		_dailyTaskExList.push_back(pTaskVo);
	}
	_FinishTaskToast = true;
	_hasUnFinishTask = hasUnFinishTask;
	if(hasFinishTask)
	{
		GameDispatcher::getInstance()->dispatchEvent(DailyTaskExMediator::DAILY_TASK_EX_EVENT_REFRESH, (void *) 1);
	}
	else
	{
		GameDispatcher::getInstance()->dispatchEvent(DailyTaskExMediator::DAILY_TASK_EX_EVENT_REFRESH, NULL);
	}

	// notify // LH20121113
	if (pPacket->a_remainTaskCount > 0
		&& !ViewManager::getInstance()->_pDailyTaskExView && RoleManage::Instance()->roleLev()>=30)
	{
		NotifyManager::Instance()->addNotification(NotifyType::NType_DailyTask);
	}	
}

void DailyTaskExProxy::onDailyTaskExAccept( SCMD423 *pPacket )
{
	bool acceptTaskResult = false;
	if(!pPacket || pPacket->a_taskId <= 0 || pPacket->b_result == 0)
	{
		acceptTaskResult = false;
	}
	else
	{
		std::vector<DailyTaskExVo *>::iterator iter = _dailyTaskExList.begin();
		while(iter != _dailyTaskExList.end())
		{
			if((*iter)->taskId == pPacket->a_taskId)
			{
				acceptTaskResult = true;
				(*iter)->hasAccepted = 1;
				(*iter)->finishCount = 0;
			}
			else
			{
				(*iter)->finishCount = 0;
				(*iter)->hasAccepted = 0;
			}
			++ iter;
		}
	}

	if(acceptTaskResult)
	{
		// Accept task success
		_FinishTaskToast = true;
		_hasUnFinishTask = true;
        ViewManager::getInstance()->_secNavigate->fadeDailyTaskExBtn(false);
		LangManager::msgShow("DTE203");
		int* pTaskId = new int;
		*pTaskId = pPacket->a_taskId;
		GameDispatcher::getInstance()->dispatchEvent(DailyTaskExMediator::DAILY_TASK_EX_EVENT_ACCEPT, pTaskId);
		CC_SAFE_DELETE(pTaskId);
	}
	else
	{
		// Accept task failed
		LangManager::msgShow("DTE204");
	}
}

void DailyTaskExProxy::onDailyTaskExSubmit( SCMD425 *pPacket )
{
	bool submitTaskResult = true;
	if(!pPacket || pPacket->a_taskId <= 0 || pPacket->b_result == 0)
	{
		submitTaskResult = false;
	}

	if(submitTaskResult)
	{
		// Submit task success
		_FinishTaskToast = true;
        ViewManager::getInstance()->_secNavigate->fadeDailyTaskExBtn(false);
		LangManager::msgShow("DTE205");
		GameDispatcher::getInstance()->dispatchEvent(DailyTaskExMediator::DAILY_TASK_EX_EVENT_SUBMIT, NULL);
	}
	else
	{
		// Submit task failed
		LangManager::msgShow("DTE206");
	}
}

void DailyTaskExProxy::onDailyTaskExProgress( SCMD427 *pPacket )
{
	if(!_FinishTaskToast)
	{
		return;
	}
	if(!pPacket)
	{
		return;
	}
	std::vector<DailyTaskExVo *>::iterator iter = _dailyTaskExList.begin();
	for(; iter != _dailyTaskExList.end(); ++ iter)
	{
		if((*iter)->taskId == pPacket->a_taskId)
		{
			(*iter)->finishCount = pPacket->b_finishCount;
			(*iter)->count = pPacket->c_count;
			if(pPacket->b_finishCount == pPacket->c_count)
			{
				LangManager::msgShow("DTE018");
                ViewManager::getInstance()->_secNavigate->fadeDailyTaskExBtn(true);
				_FinishTaskToast = false;
			}
			break;
		}
	}
	if(!_FinishTaskToast)
	{
		// can submit
		GameDispatcher::getInstance()->dispatchEvent(DailyTaskExMediator::DAILY_TASK_EX_EVENT_PROGRESS, (void *) 1);
	}
	else
	{
		GameDispatcher::getInstance()->dispatchEvent(DailyTaskExMediator::DAILY_TASK_EX_EVENT_PROGRESS, NULL);
	}
}

void DailyTaskExProxy::onDailyTaskExGiveup( SCMD42B *pPacket )
{

	if(!pPacket || pPacket->a_result == 0)
	{
		LangManager::msgShow("DTE022");
	}
	else
	{
		_hasUnFinishTask = false;
		LangManager::msgShow("DTE021");
		std::vector<DailyTaskExVo *>::iterator iter = _dailyTaskExList.begin();
		for(; iter != _dailyTaskExList.end(); ++ iter)
		{
			(*iter)->finishCount = 0;
			(*iter)->hasAccepted = 0;
		}
		_FinishTaskToast = true;
		GameDispatcher::getInstance()->dispatchEvent(DailyTaskExMediator::DAILY_TASK_EX_EVENT_GIVEUP, NULL);
	}
}


