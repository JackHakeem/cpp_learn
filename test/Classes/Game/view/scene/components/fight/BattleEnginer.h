#ifndef _BATTLEENGINER_H_
#define _BATTLEENGINER_H_
#include "BaseType.h"
#include "socket/command/s13/SCMD131.h"
#include "socket/command/s13/SCMD132.h"
#include "socket/command/s13/SCMD133.h"
#include "view/scene/layer/FightLayer.h"
#include "view/scene/components/fight/ActionHandler.h"
#include "socket/command/s13/SCMD13D.h"
#include "socket/command/s3b/SCMD3B1.h"
#include "utils/effect/FightEffectGroup.h"

class BattleEnginer:public CCObject
{	
public :
	
	BattleEnginer();

	std::vector<SCMD132>* _fightPack ;    //132战斗过程包
	
	SCMD13D *_fightReward;
	SCMD3B1 *_battleReport;

	//std::list<SCMD132*>_fightPack ;
	std::vector<SCMD132::SCMD132Node1> _actions;  //每回合战斗动作集合
	SCMD133* _fightRet;         //战斗结果
	int32 _type;
	//FightLayer*  _context;

	ActionHandler *_actionHandler;
	//FightEffectGroup *_feGroup;

	int32 _round;
	int32 _action_num;
	float32 _rate;
	int _id;
	std::list<SCMD132::SCMD132Node4> _buffs;

public :
	static BattleEnginer *getInstance();
	static void Release();
	void execute();
	void nextRound();
	void stop();

	void nextActions(CCNode* n = NULL, void* data = NULL);
	void playOneAction(SCMD132::SCMD132Node1 action);
	bool haveNextEffect();

	void playResult();
	void playBuffs(std::list<SCMD132::SCMD132Node4>& buffs);
	void dispose();

};



#endif