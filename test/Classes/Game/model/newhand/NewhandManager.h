#ifndef _NEWHAND_MANAGER_H_
#define _NEWHAND_MANAGER_H_
#include "utils/Singleton.h"
#include "vo/FightLeaderVo.h"
#include "vo/StepVo.h"
#include "vo/ScriptVo.h"
#include "utils/flash/CCIEventDispatcher.h"
#include "../player/vo/PlayerInfoVo.h"

class HelpScriptVo;

class NewhandManager : public Singleton<NewhandManager>
{
public:
	NewhandManager();
	~NewhandManager();

	void initNewhandStep();
	void initNewhand();
	FightLeaderVo *getFightLeadInfo(int map, int progress);
	std::list<StepVo *> getRcvTaskStepVo(int taskId);
	std::list<StepVo *> getSmtTaskStepVo(int taskId);
	std::list<StepVo *> getLevelStepVo(int lev);
	ScriptVo *getNewhandScript(int id);
	ScriptVo *getCanTaskScript(int taskId);
	ScriptVo *getOwnTaskScript(int taskId);
	ScriptVo *getFinTaskScript(int taskId);
	void touchNextScript(string type, int id);
	void touchNextScript(string type, string id);
	ScriptVo *getMapScriptById(int scriptId, int mapId);
	void closeLayer();
	void openLayer();
	bool isOpenButton(int btnId);
	void touchNextEvent(int evtId);

	void addCallBack(int id, CCNode *pTarget, SEL_CallFuncND selector, void *data);
	void touchCallBack(int id);

	// Custom
	bool addStep(StepVo *pStep);
	bool addFightLead(FightLeaderVo *pFightLeader);
	bool addScript(ScriptVo *pScript);

public:
	void addNewHandHelpScript(HelpScriptVo *pScript);
	int getIDByProcessID(int processid);

	void createImagePathMap();
	std::string getImagePathByButtonId(int id);
	void initNewHandStateMap();
	int getNewHandStateByType(int type);
	void setNewHandStateByType(int type , int state);
	void doTaskFollow();

public:
	void setNavigateType(int type);
	int getNavigateType();

public:
	enum
	{
		Navigate_BottomMain = 0,
		Navigate_LeftVscroll,
		Navigate_TopSecMain,
	};

	enum
	{
		Flag_New = 0,
		Flag_Done,
		Flag_Close,
	};

	int _navigateType;

	PlayerInfoVo *_pInfoVo;
	int _deltaAttacPoint;
	bool _isGetEquipment;
	bool _isNewAcount;
	int _nextEventId;
	std::list<int> _nextEventIdList;

	std::map<int, std::list<StepVo *> > _rcvTaskStepDic;
	std::map<int, std::list<StepVo *> > _smtTaskStepDic;
	std::map<int, std::list<StepVo *> > _levStepDic;
	std::map<int, FightLeaderVo *> _fightLeadDic;

	std::map<int, ScriptVo *> _scriptDic;
	std::map<int, int> _isOpenDic;	

	std::map<int, int> _canTaskTriggerDic;
	std::map<int, int> _ownTaskTriggerDic;
	std::map<int, int> _finTaskTriggerDic;
	std::map<int, int> _addBtnTriggerDic;
	std::map<int, int> _evtTriggerDic;
	std::map<std::string, int> _pTriggerDic;

	//std::vector<KKCallfunc> _callBackDic;
	KKCallfunc _callBackFunc;
	ScriptVo *_pCurScript;
	ScriptVo *_pNextScript;

	std::map<int, HelpScriptVo *> _helpScriptDic;
	std::map<int , std::string> _imagePathMap;
	std::map<int , int> _newHandStateMap;
	
};
#endif