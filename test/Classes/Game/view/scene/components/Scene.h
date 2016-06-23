#ifndef HLQS_Scene_h
#define HLQS_Scene_h

#include "view/scene/components/BaseScene.h"
#include "LiveThing.h"
#include "Npc.h"
//#include "MapMonsters.h"
#include "StoryScene.h"

class StoryScene;

class Scene: public BaseScene
{
public:
	Scene();
	~Scene();
	void levUpEffect(int accountId);
	virtual void focusPosChangeHandler(CCPoint focusPos);
	virtual void buildScene(int width, int height, int mapRank, int offsetX, int offsetY,std::string path, CCPoint focusPos);
	void rolePosChangeHandler(CCPoint rolePos);
	void roleIcon(int index);
	virtual void step();
	virtual void removeNPC(int id);
	virtual void showNPC(int id, bool val);
	virtual void NPCColor(int id, cocos2d::ccColor3B color);
	virtual void NPCName(int id, const char* name);
	void focusChangedHandler();
	void addRole(int scale = 1);
	void roleWalkPathChangeHandler(CCNode* n, void* data);
	void roleChangePositionHandler(CCNode* n, void* data);
	void roleWalkStartHandler(CCNode* n, void* data);
	void roleWalkStartNodeHandler(CCNode* n, void* data);
	void playerHonor(int honorId, int last, int total);
	void doubleReward();
	void missionComplete(std::string name, std::string desc);
	void playOnce();
	void mcPlayOnce();
	void roleWalkCompleteHandler(CCNode* n, void* data);
	void roleReDress();
	void canMoveChange(CCNode* n, void* data);
	void roleToExit(int id);
	void roleToNPC(int id);
	void addStoryScene(StoryScene &storyScene);
	void rmFightScene();
	void roleStopAndNPCMove(int id, int type = 0);
	void monsterAutoMoveStop();
	void npcMove(LiveThing* npc);
	void onFinishTween(LiveThing* npc);
	void attactComplete(CCNode* n, void* data);
	void monsterAutoMoveStart();
	void roleAttackMonster(MapNPC* monster);
	void roleDialogNPC(MapNPC* npc);
	bool checkFightCD();
	void rmStoryScene();
	virtual void dispose();
	virtual void clickSceneHandler(CCPoint point);
	void roleDeadHandler(CCNode* n, void* data);
	virtual MapNPC* addNPC(NPCVo* pNPCVo);
	void processMonster();
	void roleStateChangeHandler(CCNode* n, void* data);
	void initRedProgress(char *data);
	void updateDirection();
	int getFirstRedProgress();
	void resetDirArrow();
    
    //Doyang 20120731
    bool isTaskCityMonster(MapNPC *pMonster);
	//LH20121114
	CCSize getMapSizePixels();
	void tradeWalkStartNodeHandler(CCNode* n, void* data);
	bool getIsCanDialogPop(int npcId);
	void roleStopMove();
	int changeSceneTipsPopCallBack();
	void roleDialogTrader(Player* pPlayer);

public:
	bool _focusChanged;
	std::vector<int> _redProgress;
	bool _needDirPoint;
	float _oldDirection;
	float _newDirection;
	float _step;
	std::map<int, CCPoint>_posDic;
};

#endif