#ifndef _NEWHAND_MEDIATOR_H_
#define _NEWHAND_MEDIATOR_H_
#include "model/task/vo/TaskVo.h"
#include "../BaseMediator.h"
#include "model/newhand/vo/ScriptVo.h"
#include "model/newhand/vo/StepVo.h"
#include "model/newhand/NewhandManager.h"
#include "model/newhand/vo/TestNewhand.h"
#include "components/NewHandView.h"

class NewhandMediator : public BaseMediator
{
public:
	NewhandMediator();

	virtual void handleNotification(int M2Vcmd, char* data); 

	void startEventListener();
	void canTaskTrigger(CCNode *pNode, void *data);//std::vector<TaskVo *> canTaskList);
	void ownTaskTrigger(CCNode *pNode, void *data);//std::vector<TaskVo *> recTaskList);
	void receiveTaskTrigger(CCNode *pNode, void *data);
	void submitTaskTrigger(CCNode *pNode, void *data);
	void initButtonsHandle();
	void sendHandle(CCNode *pNode, void *data);
	void cryLevTrigger(CCNode *pNode, void *data);
	void roleLevTrigger(CCNode *pNode, void *data);
	void testNewHand(CCNode *pNode, void *data);
	void movieToAddButton(StepVo *pStep, bool isTween);
	void addButton(StepVo *pStep, bool isTween);
	void paperPop(StepVo *pStep);
	void afterMovie(CCNode *pNode, void *data);
	void crystalUpdateInfo(StepVo *pStep);
	void newHandTipsByLevel(CCNode *pNode, void *data);

public:
	enum NewhandType
	{
		CAN_TASKFOLLOW_TIP = 0,
		OWN_TASKFOLLOW_TIP,
		INIT_BUTTONS,
		FIGHT_LEADER
	};

	int _count;
	bool _buttonInit;

	NewhandManager *_pNewhandManager;
	NewHandView *_pNewhandView;
};
#endif