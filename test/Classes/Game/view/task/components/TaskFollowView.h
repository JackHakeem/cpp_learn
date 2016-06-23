#ifndef _TASK_FOLLOW_VIEW_H_
#define _TASK_FOLLOW_VIEW_H_

#include "model/task/TaskProxy.h"
#include "model/task/vo/EntrTaskVo.h"
#include "BaseType.h"
#include "UIListView/CCUIListView.h"
#include "LayerNode.h"
#include "utils/flash/CCIEventDispatcher.h"


USING_NS_CC;

class TaskFollowView : public LayerNode, CCUIListViewAdapter, CCUIListViewItemActionListener
{
public:
	TaskFollowView();
	virtual ~TaskFollowView();

	bool init();
	void registerWithTouchDispatcher();

	virtual void controlButtonClick(CCObject* pSender);
	virtual void canTaskButtonClick(CCObject* pSender);

	//void initData(EntrTaskVo *enTaskVo, MAP_INT_TASKVO recTaskList, MAP_INT_INT canTaskList);
	void initData(std::vector<TaskVo *> &recTaskList);
	void initCanTaskData( std::vector<TaskVo *> &canTaskList );

	virtual int getCount();

	virtual LayerNode * getView( int position );

	virtual void onItemClickListener( LayerNode *itemCell, int position );

	virtual void onItemTouchListener( LayerNode *itemCell, int position );

	virtual void onItemTouchCancelListener( LayerNode *itemCell, int position );

	virtual void setReceiveTaskList();
	virtual void setCanTaskList();
	void doAfterTaskListViewActions();

	void refresh();

	void runLightAction(CCNode * pNode , CCAction * pAction);
	CCAction * getLightAction();

	void showTaskFollowLayer();
	void dismissTaskFollowLayer();
	CCNode *getNewHandItem(int taskId);

public:
	std::vector<TaskVo *> _recList;
	std::vector<TaskVo *> _canTaskList;
	MAP_INT_INT _canList;
	EntrTaskVo *_enTaskVo;

	CCLayer *_pTaskLayer;
	CCUIListView *_pListView;
	bool _isTaskListViewShowing;
	bool _isDuringAction;
	TaskVo * _pTaskVo;
	int _nFlag;

};

#endif