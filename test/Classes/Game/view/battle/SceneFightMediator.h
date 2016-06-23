#ifndef _SCENEFIGHTMEDIATOR_H_
#define _SCENEFIGHTMEDIATOR_H_

#include "mvc/Mediator.h"
#include "model/battle/FightProxy.h"
#include "view/scene/layer/FightLayer.h"
#include "view/scene/components/fight/BattleEnginer.h"
#include "../BaseMediator.h"
#include "../scene/components/FightScene.h"

class SceneFightMediator : public BaseMediator{

	public:
	enum 
	{
		INTO_FIGHT=0,
		FIGHT_START= 1,
		ABORT_FIGHT=2,
	};


public:
	FightProxy* _fightProxy;
	BattleEnginer* enginer ;
	FightLayer* fightLayer ;
	float32  rate;      // play speed
	FightScene* _fightScene;


public:

	SceneFightMediator();
	virtual void handleNotification(int M2Vcmd, char* data);

	void loadWarRes();
	void configFightScene();
	void addFollowProcess(char * data);

	void playEffect();
	void play();
	void abortFight();
	void addBattleContent(char* data);
	void addBattleFinish(char* data);
	void loadWarFormation();
	//void dungeonAward( SCMD376& param );
	void fightOutHandler(int type, int battleType);

};


#endif