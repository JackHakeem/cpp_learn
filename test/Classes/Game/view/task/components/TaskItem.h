#ifndef _TASK_ITEM_H_
#define _TASK_ITEM_H_

#include "cocos2d.h"

USING_NS_CC;

class TaskVo;

class TaskItem : public CCLayer
{
public:
	TaskItem(TaskVo * taskVo);
	~TaskItem();

	void onClickShowTask(CCObject * pSender);
	void setNameTouchPriority(int pri);
	void ennableNameButtonTouch(bool var);

public:

	enum
	{
		Tag_NameBtn = 21,
	};

	TaskVo * _taskVo;
};
#endif