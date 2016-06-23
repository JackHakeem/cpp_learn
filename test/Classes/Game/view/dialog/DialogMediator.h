#ifndef _DIALOGMEDIATOR_H
#define _DIALOGMEDIATOR_H
#include "components/DialogView.h"
#include "model/dialog/vo/NPCDialogueVo.h"
#include "model/task/TaskProxy.h"
#include "../BaseMediator.h"
#include "../scene/SceneMediator.h"

class DialogMediator:public BaseMediator
{
public:
	enum
	{
		SET_AUTO_POP = 0,
	};
	int id;
	int _state;
	SceneMediator* _sceneMediator;

public:
	DialogMediator();
	~DialogMediator();

	DialogView* _dialogView;

	void dialogPop(int npcId);
	void showDialogue(CCNode*n, void* data);
	NPCDialogueVo* createNPCDialogueVo(int npcId);
	void createList(int npcId);
	void rolePosChangeHandler(CCNode* n, void* data);
	void newTaskToAutoPop(CCNode* n, void* data);
	void tryAutoPopDialog();
	void recTaskDataChangeHandler(CCNode* n, void* data);
	void setAutoPop( bool isAutoPop );
	bool getIsPop();

	void handleNotification( int M2Vcmd, char* data );
private:
	TaskProxy *_taskProxy;
	//public static const NAME:String = "DIALOG_MEDIATOR";

	//public static const SET_AUTO_POP:String = "SET_AUTO_POP" + NAME;

	//private var _dialogView:DialogView;

	//private var id:int;

	//private var _taskManager:TaskManager;

	//private var _chapter:MovieClip;

	//private var _taskVo:TaskVo;
};

#endif