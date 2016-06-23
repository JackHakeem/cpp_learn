#ifndef HLQS_SceneProxyCommand_H_
#define HLQS_SceneProxyCommand_H_
#include "mvc/SimpleCommand.h"
#include "model/scene/SceneProxy.h"
#include "socket/command/s11/SCMD11D.h"
#include "cocos2d.h"
USING_NS_CC;

class SceneProxyCommand: public SimpleCommand
{
public:
	SceneProxyCommand();
	void execute(int32 command, char* data);
	void setPerfectInfo(SCMD11D* cmd);
	void movePlayer(char* data);
	void addPlayers(char* data);
	void removePlayer(char* data);
	void addRoleSElement();
	void mapSkip(char* data);
	void addNPCs();
	void addMonsters();
	void addExit();

	void moveTradePlayer( char* data );
	void creatTrader( char* data );
	void removeTradePlayer(char* data);
	void addTrader( char* data );
	void addTraders();

public:
	//stMonsterDic
	//stMonsterArr
	SceneProxy* _sceneProxy;
	//TeamProxy* _teamProxy;

	enum
	{
		ROLE_POS_CHANGE = 0,
		MOVE_PLAYER,
		ADD_PLAYER,
		REMOVE_PLAYER,
		REMOVE_NPC,
		MAP_SKIP,
		INIT_PROCESS,
		ADD_PROCESS,
		INIT_SCENE_PROCESS,
		ADD_SCENE_PROCESS,
		MOVE_TRADEPLAYER,
		CREAT_TRADEPLAYER,
		ADD_TRADEPLAYER,
		REMOVE_TRADEPLAYER,
	};
};

#endif