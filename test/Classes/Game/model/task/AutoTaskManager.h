#ifndef _AUTO_TASK_H_
#define _AUTO_TASK_H_

#include "cocos2d.h"
#include "utils/Singleton.h"

#define DELAY_AutoTask (5.0f)

using namespace cocos2d;

class AutoTaskManager : public Singleton<AutoTaskManager> , public CCObject
{
public:
	AutoTaskManager();
	virtual ~AutoTaskManager();
public:
	void startNewAutoTaskTimer(int taskid );
	void autoFind();
	void step( ccTime dt );
public:
	int _taskId;
	int _nCount;
};
#endif