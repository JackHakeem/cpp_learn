#include "DailyTaskExMediator.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "manager/ViewManager.h"
#include "bear/manager/DisplayObjectManager.h"

DailyTaskExMediator::DailyTaskExMediator()
{
	GameDispatcher::getInstance()->addEventListener(PopEventName::SHOW_UI_DAILY_TASK_EX,
		this,
		callfuncND_selector(DailyTaskExMediator::onDailyTaskExShow));
	GameDispatcher::getInstance()->addEventListener(DailyTaskExMediator::DAILY_TASK_EX_EVENT_REFRESH,
		this,
		callfuncND_selector(DailyTaskExMediator::onDailyTaskExRefreshed));
	GameDispatcher::getInstance()->addEventListener(DailyTaskExMediator::DAILY_TASK_EX_EVENT_ACCEPT,
		this,
		callfuncND_selector(DailyTaskExMediator::onDailyTaskExAccept));
	GameDispatcher::getInstance()->addEventListener(DailyTaskExMediator::DAILY_TASK_EX_EVENT_SUBMIT,
		this,
		callfuncND_selector(DailyTaskExMediator::onDailyTaskExSubmit));
	GameDispatcher::getInstance()->addEventListener(DailyTaskExMediator::DAILY_TASK_EX_EVENT_PROGRESS,
		this,
		callfuncND_selector(DailyTaskExMediator::onDailyTaskExProgressChanged));
	GameDispatcher::getInstance()->addEventListener(DailyTaskExMediator::DAILY_TASK_EX_EVENT_GIVEUP,
		this,
		callfuncND_selector(DailyTaskExMediator::onDailyTaskExGiveup));
	_pDailyTaskExView = 0;
}

void DailyTaskExMediator::openDailyTaskExView()
{
	if(!_pDailyTaskExView)
	{
		createDailyTaskExView();
	}
	if(_pDailyTaskExView)
	{
		_pDailyTaskExView->setisPop(!_pDailyTaskExView->getisPop());
		_pDailyTaskExView->onOpenFinished();
	}
}

void DailyTaskExMediator::createDailyTaskExView()
{
	_pDailyTaskExView = new DailyTaskExView();
	if(_pDailyTaskExView && _pDailyTaskExView->init())
	{
		ViewManager::getInstance()->_pDailyTaskExView = _pDailyTaskExView;
	}
}

void DailyTaskExMediator::onDailyTaskExProgressChanged( CCNode *pNode, void *pData )
{
	if(_pDailyTaskExView)
	{
		_pDailyTaskExView->updateProgress(pData != NULL);
	}
}

void DailyTaskExMediator::onDailyTaskExRefreshed( CCNode *pNode, void *pData )
{
	if(_pDailyTaskExView)
	{
		_pDailyTaskExView->updateRefreshTask(pData != NULL);
	}
}

void DailyTaskExMediator::onDailyTaskExShow( CCNode *pNode, void *pData )
{
	openDailyTaskExView();
}

void DailyTaskExMediator::onDailyTaskExAccept( CCNode *pNode, void *pData )
{
	if(!pData)
		return;

	if(_pDailyTaskExView)
	{
		_pDailyTaskExView->updateAccpetTask(*(int *) pData);
	}
}

void DailyTaskExMediator::onDailyTaskExSubmit( CCNode *pNode, void *pData )
{
	DisplayObjectManager::getInstance()->PlayFinTaskEffect();

	if(_pDailyTaskExView)
	{
		_pDailyTaskExView->updateSubmitTask();
	}
}

void DailyTaskExMediator::onDailyTaskExGiveup( CCNode *pNode, void *pData )
{
	if(_pDailyTaskExView)
	{
		_pDailyTaskExView->updateGiveupTask();
	}
}
