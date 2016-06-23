#ifndef HLQS_DungeonEntrysMediator_H_
#define HLQS_DungeonEntrysMediator_H_
#include "../BaseMediator.h"
#include "components/DungeonEntrysView.h"
#include "components/StoryMapsView.h"
#include "components/ChallengeMapsView.h"
#include "model/scene/vo/SceneVo.h"
#include "socket/command/s3d/SCMD3DB.h"
#include "socket/command/s37/SCMD373.h"
#include "socket/command/s37/SCMD375.h"

class DungeonEntrysMediator: public BaseMediator
{
public:
	DungeonEntrysMediator();
	virtual void handleNotification(int M2Vcmd, char* data);
	void openDungeonEntrysView();
	void closeDungeonEntrysView();
	void loadMainEntrys();
	void onMainEntrysLoaded();
	void initMainEntrysData();
	void onClickFunctionEnter(CCNode*n, void* data);
	void onClickFunctionClose(CCNode* n, void* data);
	void openStoryMapsView(int id = 0);
	void initStoryEntrysData(int id = 0);
	void openChallengeMapsView();
	void openLairView();
	void openWorldBossView();
	void openSilverMineView();
	void openDragonTowerView();
	void openRankingView();
	void openCampFight();
	void onClickStoryCityTab(CCNode* n, void* data);
	void onClickStoryCityClose(CCNode* n, void* data);
	void closeStoryMapsView();
	void onClickStoryMapIcon(CCNode* n, void* data);
	void handleMapsOfCityInfo(SCMD3DB* packet);
	void initChallengeEntrysData();
	void applyForChallengeTimes();
	void HandleChallengeTimesApply(SCMD373* packet);
	void applyForBuyChaTimes();
	void HandleUpdateForBuyChaTimes(SCMD375* packet);
public:
	enum
	{
		CLICK_FUNCTION_ENTER = 0,
		CLICK_FUNCTION_CLOSE,
		CLICK_STORY_CITY_TAB,
		CLICK_STORY_CITY_CLOSE,
		CLICK_STORY_MAP_ICON,
		CLICK_CHALLENGE_MAP_ICON,
		CLICK_CHALLENGE_MAP_CLOSE,
		OPEN_DUNGEON_ENTRYS_VIEW,
		CLOSE_DUNGEON_ENTRYS_VIEW,
		OPEN_LAIR_ENTRYS_VIEW,
		OPEN_STORY_ENTRYS_VIEW,
	};

	DungeonEntrysView* dungeonEntrysView;
	StoryMapsView* storyMapsView;
	ChallengeMapsView* challengeMapsView;
	//WorldBossProxy* WorldBossProxy;
	std::vector<int>* cityIDs;
	std::vector<SceneVo*> challengeMapIDs;
	int minTaskId;
	std::map<int, int> entrysOpenedDic;
};

#endif