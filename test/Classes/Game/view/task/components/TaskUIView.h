#ifndef _TASK_UIVIEW_H_
#define _TASK_UIVIEW_H_

#include "cocos2d.h"
#include "events/GameDispatcher.h"

USING_NS_CC;

class TaskVo;

class TaskUIView : public CCLayer , public GameDispatcher
{
public:
	TaskUIView();
	~TaskUIView();

	virtual bool init();

	void loadItem();

	void resetScrollView();

	void onClickShowTaskView(CCObject * pSender);
	void onClick2Left(CCObject * pSender);
	void onClick2Right(CCObject * pSender);

	void showHightLight(bool var);

	CCNode * getNewHandItem( int id );

	void runMyAction(CCNode * pNode , CCAction * pAction);
	void stopMyAction(CCNode * pNode );
	CCAction * getMyAction(int type);

	void setCurTaskId(int id);
	void setCurTaskIcon();
	void handleTaskListPriority();

	void onClickHideUI(CCObject * pSender);
	void showUI(bool var);

	void showDirs(bool var);
	void updateTaskButtonInfo(TaskVo * taskVo);
	void onClickShowTask(CCObject * pSender);

	std::vector<TaskVo *> * getAllTaskList();

public:
	enum
	{
		ZOrder_back = 0,
		ZOrder_item = 10,
	};

	enum
	{
		Tag_back = 10,
		Tag_HighLight,
		Tag_ButtonStr = 50,
		Tag_ScrollView = 121,
		Tag_TaskBtn,
		Tag_RightDir,
		Tag_LeftDir,
	};

	enum
	{
		Size_ScrWidth = 90 + 30,
		Size_ScrHight = 95 + 70, 
	};

	enum
	{
		Action_Fade = 0,
	};

	CC_SYNTHESIZE(bool , _isHide , IsHide);

	std::vector<TaskVo *> _canTaskList;
	std::vector<TaskVo *> _finTaskList;
	std::vector<TaskVo *> _recTaskList;
	std::vector<TaskVo *> _allTaskList;
	int _curTaskId;
	CCPoint _pos;
	CCMenuItemSprite * _pMenuSpriteName;

};
#endif