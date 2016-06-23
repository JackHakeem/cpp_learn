#ifndef HLQS_BattleData_H_
#define HLQS_BattleData_H_
#include "socket/command/s13/SCMD133.h"
#include "socket/command/s13/SCMD13D.h"
#include "socket/command/s13/SCMD131.h"
#include "socket/command/s13/SCMD132.h"
#include "view/fight/callback/FightFollowStoryAction.h"


class BaseAction;
class BattleData
{
public:
	BattleData();
    ~BattleData();
	int type;  // PVE or PVP
	int id;   // group monster ID

	int formation;  // formation ID
	int oppositeFormation; // posite formation ID
	std::vector<SCMD131Node> players;

	int procid;

	std::vector<SCMD132> _pack; 
	SCMD133* _fightRet;
	SCMD13D* _fightAward;

	std::vector<BaseAction*> _callbacks;


	FightFollowStoryAction * _tailStoryAction;
	//public var _callbacks:Array

	void dispose();
};

#endif