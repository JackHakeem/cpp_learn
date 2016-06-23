#ifndef HLQS_SceneProxy_H_
#define HLQS_SceneProxy_H_
#include "mvc/Proxy.h"
#include "model/scene/vo/SceneInfoVo.h"
#include "utils/findPath/FindPath8.h"
#include "cocos2d.h"
#include "vo/NPCVo.h"
#include "vo/ExitVo.h"
#include "../player/vo/PlayerBaseVo.h"
#include "socket/command/s12/SCMD123.h"
#include "socket/command/s11/SCMD11D.h"
#include "socket/command/s12/SCMD120.h"

using namespace cocos2d;

class BaseAction;

class SceneProxy: public Proxy
{
private:

public:
	SceneInfoVo* _sceneInfoVo;
	FindPath8 _findPath;
	bool isLoadMap;
	CCPoint _rolePos;
	CCPoint oRolePos;
	CCPoint _focusPos;
	std::map<int, NPCVo> _npcDic;
	std::map<int, PlayerBaseVo> _playerDic;
	std::map<int, PlayerBaseVo> _traderplayerDic;
	std::map<int, ExitVo> _elementDic;
	std::map<int/*map_id*/, int/*status*/>_sceneProgress; //Scene progress
	std::map<int, int> _progressDic; //The process of single map
	std::map<int, int> shootDic;
	//shootDic
	NPCVo* _clickNPC;
	int _curSceneId;//The recent push chart scene Id
	std::vector<int> _curDuplicates;//Keep a copy of the last two scene Id

	std::vector<PlayerBaseVo> _waitAddPlayers;
	std::map<int, PlayerBaseVo> _waitAddDic;
	std::vector<int> _waitRemovePlayers;
	std::vector<BaseAction*> _callbacks;

public:
	SceneProxy();
	void setSceneInfoVo(SceneInfoVo value, FindPath8& _findPath);
	SceneInfoVo* sceneInfoVo();
	int pid();
	void addNPC(NPCVo& value);
	int getMonsterGroupLev(int gmProgressID);
	void removeNPC(int id);
	NPCVo* getNPC(int id);
	void setClickNPC(int id);
	NPCVo* getClickNPC();
	CCPoint getNPCPos(int id);
	void setNPCPos(int id, CCPoint pos);
	void movePlayer(int id, std::vector<CCPoint>* path);
	void movePlayerAdjust(int id, std::vector<CCPoint>* path, float ranger);
	void addPlayer(PlayerBaseVo* playerVo);
	void addPlayerHander(PlayerBaseVo* playerVo);
	void removePlayer(int id);
	void removeTradePlayer(int id);
	void removePlayerHandler(int id);
	PlayerBaseVo* getPlayer(int id);
	void addElement(ExitVo* exitVo);
	void removeElement(int id);
	ExitVo* getElement(int id);
	vector<CCPoint> findPath(CCPoint startPoint, CCPoint endPoint);
	void addRole();
	void initSceneProgress(SCMD123* data);
	void addSceneProgress(SCMD123* data);
	void initProgress(SCMD11D* cmd);
	CCPoint rolePos();
	void rolePos(CCPoint value);
	int checkTilePoint(CCPoint point);
	CCPoint findMinEndPoint(CCPoint endPoint);
	void showPlayersHandler();
	//void step();
	void virtualPos(CCPoint value);
	void focusPos(CCPoint value);
	CCPoint focusPos();
	void setOtherPlayerPos(int id, CCPoint pos);
	CCPoint getOtherPlayerPos(int id);
	bool isInProgress(int progressId);
	std::vector<int> maptotalProgress();
	void addProgress(SCMD120* cmd);
	void setSceneThrough(int id);
	bool isSceneOpened(int id);
	int getSceneStatus(int id);
	void dispose();
	std::map<int, int>* sceneProgress();
	std::vector<int>* curDuplicates();
	int curSceneId();
	void addTradePalyer(PlayerBaseVo* playerVo);
	void moveTradePlayer(int id, std::vector<CCPoint>* path);
};

#endif