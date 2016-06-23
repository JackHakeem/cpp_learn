#ifndef HLQS_SceneMediator_H_
#define HLQS_SceneMediator_H_
#include "view/scene/components/Scene.h"
#include "../BaseMediator.h"
#include "components/StoryScene.h"

class DungeonView;

class SceneMediator: public BaseMediator
{
public:
	Scene* _scene;
	StoryScene *_storyScene;

public:
	enum{
		STARTUP_GAME_SCENE = 0,		
		BUILD_SCENE,
		ADDROLE,
		ADDPLAYER,
		REMOVEPLAYER,
		MOVEPLAYER,
		MOVEPLAYERADJUST,
		ADDNPC,
		REMOVENPC,
		UPDATEEXIT,
		ADDEXIT,
		REMOVEEXIT,
		ADDSTATUE,
		ROLE_POS_CHANGE,
		FOCUS_POS_CHANGE,
		ROLE_STOPANDNPC_MOVE,
		ROLE_STOP,
		REMOVE_FIGHT_SCENE,
		REMOVE_ARMY_SCENE,
		ADD_STORY_SCENE,
		REMOVE_STORY_SCENE,
		MOVE_ROLE,
		ROLE_MOVE_PATH,
		MOVE_NPC,
		ROLE_TO_NPC,
		ROLE_TO_EXIT,
		CANCEL_CLICK_TARGET,
		NPC_ICO_CHANGE,
		MEDITATION_FIND_PATH,
		INIT_RED_PROCESS_ID,

		ADDPTRADELAYER,
		MOVETRADEPLAYER,
		REMOVETRADERPLAYER,
	};

public:
	SceneMediator();
	~SceneMediator();

	void addToLayer();
	virtual void handleNotification(int M2Vcmd, char* data);
	void buildScene(char* data);
	void startGameScene();
	void closeWorldScene();
	void buildScene(std::string mapName);
	void addRole(char* data);
	void movePlayer(char* data);
	void addPlayer(char* data);
	void removePlayer(char* data);
	void removeNPC(char* data);
	void showNPC(char* data, bool val);
	void NPCName(int id, const char* name);
	void NPCColor(char* data, cocos2d::ccColor3B color);
	void updateExit(char* data);
	void addExit(char* data);
	void removeExit(char* data);
	void rolePosChange(char* data);
	void focusPosChange(char* data);
	void roleStopAndNPCMove(char* data);
	void roleStop(char* data);
	void removeFightScene(char* data);
	void onTailStoryCallback(CCNode*, void*);
	void fightOutCallback();
	void removeArmyScene(char* data);
	void showUILayer();
	void addStoryScene(char* data);
	void removeStoryScene(char* data);
	void updateIco(char* data);
	void roleMove(char* data);
	void roleMoveByPath(char* data);
	void npcMove(char* data);
	void changeToMapPath();
	void roleToExit(char* data);
	void meditationFindPath();
	void movePlayerAdjust(char* data);
	void addNPC(char* data);
	void roleToNPC(char* data);
	void cancelClickTarget();
	std::vector<CCPoint> changeToMapPath(std::vector<CCPoint>& path);
	void removeArmySceneHandler();
	void cdEnergyHandler();
	void addStatue(char* data);
	void raiseCityName(char* data);
	bool isHiddenNpc(int npcId);
	void clearBattle();

	void addTradePlayer( char* data );
	void moveTradePlayer( char* data );
	void removeTradePlayer(char* data);
	int changeSceneTipsPopCallBack();

	DungeonView* _dungeonView;  // 副本通关View
};

#endif