#ifndef _DAILY_TASK_EX_VIEW_H_
#define _DAILY_TASK_EX_VIEW_H_

#include "cocos2d.h"
#include "PopContainer.h"
#include "BaseType.h"
#include "UIListView/CCUIListViewAdapter.h"
#include "model/dailyTaskEx/DailyTaskExProxy.h"
#include "model/dailyTaskEx/vo/DailyTaskExVo.h"
#include "UIListView/CCUIListViewItemActionListener.h"

class DailyTaskExView : public PopContainer, CCUIListViewAdapter, CCUIListViewItemActionListener
{
public:
	DailyTaskExView();
	~DailyTaskExView();

	virtual bool init();

	void onRefreshClick(CCObject* pSender);
	void onAcceptOrSubmitClick(CCObject* pSender);
	void onGoldConfirmOk(CCObject* pSender);
	void onGoldConfirmCancel(CCObject* pSender);
	void onAcceptConfirmOk(CCObject* pSender);
	void onAcceptConfirmCancel(CCObject* pSender);
	void onGiveUpConfirmOk(CCObject* pSender);
	void onGiveUpConfirmCancel(CCObject* pSender);
	void onATaskConfirmOk(CCObject* pSender);
	void onATaskConfirmCancel(CCObject* pSender);

	virtual int getCount();
	virtual LayerNode * getView( int position );
	virtual void onItemTouchListener( LayerNode *itemCell, int position );

	void updateCurrentSelectTask();
	void refresh();
	void onOpenFinished();
	void updateAccpetTask(int taskId);
	void updateGiveupTask();
	void updateProgress(bool canSubmit);
	void updateSubmitTask();
	void updateRefreshTask(bool canSubmit);
	void onAllATaskSelect(CCObject* pSender);
	void onVipChanged();

private:
	DailyTaskExProxy *_pDailyTaskExProxy;
	DailyTaskExVo *_pCurrentDailyTaskExVo;
	bool _notifyGoldCost;
	bool _hasUnFinishTask;
	bool _allATaskSelect;
	bool _canShowAllATaskSelect; // base on vip level

	void showLeftButtonsAndLables(bool isShow);
};
#endif