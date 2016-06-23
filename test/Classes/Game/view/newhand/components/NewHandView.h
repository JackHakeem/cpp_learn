#ifndef _NEWHAND_VIEW_H_
#define _NEWHAND_VIEW_H_
#include "model/newhand/vo/ScriptVo.h"
#include "model/newhand/NewhandManager.h"
#include "manager/ViewManager.h"
#include "ObjectGlow.h"
#include "model/newhand/vo/TestNewhand.h"
#include "utils/Singleton.h"
#include "utils/flash/CCIEventDispatcher.h"

class NewHandView : public Singleton<NewHandView>, CCNode, CCIEventDispatcher
{
public:
	NewHandView();
	~NewHandView() {}

	void testScript(CCNode *pNode, void *data);
	void nextScriptTriggerHandle(string trigger);
	void onTaskFollowChange(CCNode *pNode, void *data);
	void popCloseTrigger(CCNode *pNode, void *data);
	void dlgNextTrigger();
	void dialogPopTrigger(CCNode *pNode, void *data);
	void viewPopTrigger(CCNode *pNode, void *data);
	void clearArrowRectangle();
	void clearAll();
	void eventTrigger(TestNewhand *pData);
	CCNode * getObject(int loc_type, int id, string viewName);
	void autoClosePopContainer();
	void sendPopCloseEvent(CCNode *pNode, void *data);
	void sendPopOpenEvent(CCNode *pNode, void *data);
	void onMainNavigateChange(bool isShow);

public:
	ScriptVo *_pCurScript;
	ScriptVo *_pNextScript;
	NewhandManager *_pNewhandManager;
	ViewManager *_pViewManager;
	int _firstDlgScriptId;
	ObjectGlow::ObjectParentType _objectParentType;
	std::list<ObjectGlow *> _paintArr;

	int _newhandTaskFollowId;
	int _newhandMainNavigateId;
};
#endif