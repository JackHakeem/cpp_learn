#ifndef _DAILY_TASK_EX_MEDIATOR_H_
#define _DAILY_TASK_EX_MEDIATOR_H_

#include "mvc/Mediator.h"
#include "components/DailyTaskExView.h"

class DailyTaskExMediator : public Mediator
{
public:
	enum DailyTaskExEvent
	{
		DAILY_TASK_EX_EVENT_REFRESH = 2000,
		DAILY_TASK_EX_EVENT_ACCEPT,
		DAILY_TASK_EX_EVENT_SUBMIT,
		DAILY_TASK_EX_EVENT_GIVEUP,
		DAILY_TASK_EX_EVENT_PROGRESS,
	};
	DailyTaskExMediator();
	~DailyTaskExMediator(){}

	void openDailyTaskExView();
	void createDailyTaskExView();
	void onDailyTaskExProgressChanged(CCNode *pNode, void *pData);
	void onDailyTaskExRefreshed(CCNode *pNode, void *pData);
	void onDailyTaskExShow(CCNode *pNode, void *pData);
	void onDailyTaskExAccept(CCNode *pNode, void *pData);
	void onDailyTaskExSubmit(CCNode *pNode, void *pData);
	void onDailyTaskExGiveup(CCNode *pNode, void *pData);
private:

	DailyTaskExView *_pDailyTaskExView;
};

#endif