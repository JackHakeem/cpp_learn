#ifndef _TASK_VIEW_H_
#define _TASK_VIEW_H_

#include "BaseType.h"
#include "PopContainer.h"
#include "UIListView/CCUIListView.h"
#include "model/task/vo/TaskVo.h"
#include "UITaskPanelListView/CCUITaskPanelListView.h"
#include "UICheckButton/UICheckButton.h"

#define TASK_TYPE_CAN 0
#define TASK_TYPE_REC 1

class TaskView : public PopContainer, CCUIListViewAdapter, CCUIListViewItemActionListener
{
public:
	static TaskView *initWithRect(const cocos2d::CCRect &rect);
	
	virtual bool init();

	// action callbacks
	void closeButtonClick(CCObject* pSender);
	void canTaskButtonClick(CCObject* pSender);
	void receiveTaskButtonClick(CCObject* pSender);

	//virtual int32 getSelfTag();


	virtual int getCount();

	virtual LayerNode * getView( int position );

	virtual void onItemClickListener( LayerNode *itemCell, int position );

	virtual void onItemTouchListener( LayerNode *itemCell, int position );

	virtual void onItemTouchCancelListener( LayerNode *itemCell, int position );

	void initCanTree(std::vector<TaskVo *> &taskList);
	void initReceivedTree(std::vector<TaskVo *> &taskList);
	
	void selectNode();

	void refresh();
	string conditionHtmlString(TaskVo *pTaskVo);
	void close();
	void showTaskListItemByID(int id);

protected:
	CC_SYNTHESIZE(int, currentTaskTypeOnList, CurrentTaskTypeOnList);
	CC_SYNTHESIZE(std::vector<TaskVo *>, canTaskList, CanTakList);
	CC_SYNTHESIZE(std::vector<TaskVo *>, recTaskList, RecTakList);
private:
	TaskView();
	~TaskView();

	virtual void listItemTaskMenuSelector(CCObject* pSender);
	LayerNode *buildListItemCell( TaskVo *taskVo, int position );
	CCUITaskPanelListView *_pListView;

	UICheckButton *_pTaskCanMenu, *_pTaskReceiveMenu;
};
#endif