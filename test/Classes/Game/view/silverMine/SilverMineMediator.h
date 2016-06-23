#pragma once

#include "mvc/Mediator.h"
#include "utils/Timer.h"

class SilverMineProxy;
class MineView;
class RoleManage;
class CrystalProxy;
class GameDispatcher;
class SCMD2E3;
class SCMD2E6;
class SCMD2E8;
class SCMD2EB;
class SCMD2E9;
class SCMD367;
class SCMD369;
class SilverMineMediator : public Mediator
{
public:
	enum
	{
		TIME_END = 200,
	};
	SilverMineMediator();
	~SilverMineMediator();
public:
	virtual void handleNotification(int M2Vcmd, char* data);
	void openSilverMineHandler(CCNode* node, void* data);
	bool checkCanEnterMine();
	void openSilverMine();
	void sendQuitMine();
	void closeSilverMine(CCNode* node, void* data);
	void roleLevHandler(CCNode* node, void* data);
	void closeSceneUI(bool hide);
	void startSocketListener();
	void sendEnterMine();
	void handleEnterRes(SCMD2E3* param);
	void sendUpdateMineList();
	void handleInfoList(SCMD2E6* param);
	void showNote();
	void handleMoveRes(SCMD2E8* param);
	void moveMineHandler(CCNode* node, void* data);
	Number getserverTime();
	void sendMoveAction(int mineId);
	void digMineHandler(CCNode* node, void* data);
	void sendMiningDig(int digMode);
	void handleDigRes(SCMD2EB* param);
	void confirmToQuit(CCObject* pSender);
	void timeToEnd();
	void confirmToQuitCancel(CCObject* pSender);
	void handleBattle(SCMD2E9* param);
	void handleRank(SCMD367* param);
	void handleInspire(SCMD369* param);
	void doInspireHandler(CCNode* node, void* data);
	void sendInspire(int type);
public:
	SilverMineProxy* _mineProxy;
	MineView* _mineView;
	uint _si;// setInterval的pid
	bool showNoteFlag;// 首次进入银矿战提示 
	RoleManage* _roleManage;
	CrystalProxy* _crystalProxy;
	GameDispatcher* _dispatcher;
};
