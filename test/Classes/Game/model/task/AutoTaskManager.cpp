#include "AutoTaskManager.h"
#include "model/scene/NPCManager.h"
#include "events/GameDispatcher.h"
#include "model/scene/vo/FindVo.h"
#include "manager/ViewManager.h"
#include "view/task/components/TaskStrConcat.h"
#include <vector>

AutoTaskManager::AutoTaskManager()
{
	_taskId = 0;
	_nCount = 0;
}

AutoTaskManager::~AutoTaskManager()
{

}

void AutoTaskManager::startNewAutoTaskTimer(int taskId)
{
	// LH20130128
	if (taskId > 10)
	{
		return; // cancel this function by 20121016
	}

	_taskId = taskId;

	if (RoleManage::Instance()->roleLev() > 30)
	{
		return;
	}

	_nCount = 0;
	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(AutoTaskManager::step) , this );
	CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(AutoTaskManager::step) , this , DELAY_AutoTask ,false);
}

void AutoTaskManager::autoFind()
{
	TaskFollowView * pTaskView = ViewManager::getInstance()->taskFollowView;
	if (!pTaskView)	{return;	}

	pTaskView->getView(0);

	TaskVo *pTaskVo = pTaskView->_pTaskVo;
	if (!pTaskVo)
	{
		return;
	}
	//GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::TASK_AUTO_FIND_NPC, pTaskVo);
	if (1)
	{
		//TaskStrConcat::findNPC(pTaskVo);
	}
}

void AutoTaskManager::step( ccTime dt )
{
	if (_nCount > 3) // auto find no more than two times
	{
		CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(AutoTaskManager::step) , this );
		_nCount = 0;
	}

	autoFind();

	++_nCount;
}