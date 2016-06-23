#ifndef HLQS_SceneListenerMediator_H_
#define HLQS_SceneListenerMediator_H_
#include "../BaseMediator.h"
#include "socket/command/s11/SCMD11C.h"
#include "socket/command/s11/SCMD11B.h"
#include "socket/command/s11/SCMD111.h"
#include "socket/command/s11/SCMD112.h"
#include "socket/command/s11/SCMD113.h"
#include "socket/command/s11/SCMD118.h"
#include "socket/command/s11/SCMD11D.h"
#include "socket/command/s13/SCMD131.h"
#include "socket/command/s13/SCMD135.h"
#include "socket/command/s12/SCMD120.h"
#include "socket/command/s12/SCMD124.h"
#include "socket/command/s13/SCMD13C.h"
#include "socket/command/s35/SCMD35D.h"
#include "socket/command/s35/SCMD35F.h"
#include "SceneMediator.h"
#include "model/scene/vo/SceneVo.h"
#include "socket/command/s11/SCMD11A.h"
#include "model/scene/vo/FindVo.h"
#include "socket/command/c11/CCMD110.h"
#include "socket/command/s13/SCMD139.h"
#include "socket/command/s12/SCMD12F.h"
#include "socket/command/s12/SCMD12D.h"
#include "socket/command/s0f/SCMD0F1.h"
#include "socket/command/s0f/SCMD0F2.h"

class SceneListenerMediator: public BaseMediator
{
public:
	enum
	{
		//SCENE_STARTBGCOMPLETE = 0,
		//REMOVE_LISTENER,
		//GOTO_FIGHT_SCENE,
		START_SCENE_LISTENER,
		REMOVE_SCENE_LISTENER,
	};

	SceneMediator* _sceneMediator;

public:
	SceneListenerMediator();
	virtual void handleNotification(int M2Vcmd, char* data);
	void startSceneListener();
	void removeSceneListener();
	void gotoFightScene();
	void resetLocation(SCMD11C* cmd);
	void gotoScene(int type, int id);
	void roleMoveHandler(SCMD11B* cmd);
	void playerMoveHandler(SCMD111* cmd);
	void tradeplayerMoveHandler(SCMD12F* cmd);
	void playerViewInHandler(SCMD112* cmd);
	void playerViewOutHandler(SCMD113* cmd);
	void roleMapSkip(SCMD118* cmd);
	void initProcess(SCMD11D* cmd);
	void continueFindPath();
	void addProcess(SCMD120* cmd);
	void worldProcess(SCMD124* cmd);

	void pveFightStart(SCMD131* cmd);
	void pveReportFightStart(SCMD135* cmd);
	void pvpFightStart(SCMD13C* cmd);
	
	void playerLevelUp(SCMD35D* cmd);
	void merAttributeChange(SCMD35F* cmd);
	void roleMove(CCNode* n, void* data);
	void walkCompleteHandler(CCNode* n, void* data);
	void npcMove(CCNode* n, void* data);
	void stopAndAttackCompleteHandler(CCNode* n, void* data);
	std::vector<CCPoint> changeToMapPoint(std::vector<CCPoint>& path);
	void rolePos(CCNode* n, void* data);
	void npc_removedeadbody(CCNode* n, void* data);
	void triggerExit(CCNode* n, void* data);
	void captainExit(SceneVo& sceneVo);
	void memberExit(SceneVo& sceneVo);
	void attackMonster(CCNode* n, void* data);
	void dialogNPC(CCNode* n, void* data);
	bool businessEndCheck(int npcId);
	void walkStartHandler(CCNode* n, void* data);
	std::vector<CCMD110Node> changeToCCMD110Node(std::vector<CCPoint>& path);
	void walkStartNodeHandler(CCNode* n, void* data);
	void clickPlayerHandler(CCNode* n, void* data);
	void cancelPlayerHandler(CCNode* n, void* data);
	void createPlayerFinish(CCNode* n, void* data);
	void playerViewGetHandler(SCMD11A* cmd);
	void findElementHandler(CCNode* n, void* data);
	void findElement(FindVo* findVo);
	void getProcess(CCNode*n, void* data);
	void elementLayout(CCNode* n, void* data);
	void walkPathChangeHandler(CCNode* n, void* data);
	bool meditationCheck(int npcId);
	void updateRole(SCMD139* cmd);

	void createTradePlayerFinish(CCNode* n, void* data);
	void creatTradeHandler(SCMD12D* cmd);
	void tradeWalkStartNodeHandler(CCNode* n, void* data);
	void tradeplayerViewGetHandler(SCMD0F1* cmd);
	void tradeplayerViewOutHandler(SCMD0F2* cmd);

};

#endif