#ifndef HLQS_PlayerQueueManager_H_
#define HLQS_PlayerQueueManager_H_
#include "view/interfaces/IRender.h"
#include "utils/Singleton.h"
#include "../SceneProxy.h"

struct MoveObj
{
	int accountId;
	std::vector<CCPoint> path;
	MoveObj()
	{
		accountId = 0;
	}
};

class PlayerQueueManager : public IRender, public Singleton<PlayerQueueManager>
{
public:
	PlayerQueueManager();
	virtual void step();
	void addPlayer(PlayerBaseVo* playerBaseVo);
	void removePlayer(int playerId);
	void clearPlayerBaseVo(int playerId);
	void movePlayer(int accountId, std::vector<CCPoint>&path);
	void clearChangeScene();

public:
	std::vector<PlayerBaseVo*>queue;
	std::map<int, PlayerBaseVo*>dic;
	std::vector<MoveObj>moveQueue;
	std::map<int, MoveObj>moveDic;
	SceneProxy* _sceneProxy;

};

#endif