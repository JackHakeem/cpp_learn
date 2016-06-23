#ifndef HLQS_BattleType_H_
#define HLQS_BattleType_H_

class BattleType
{
public:
	const static int BATTLE_TYPE_PVE = 0;
	const static int BATTLE_TYPE_PVP_RANKING = 1;
	const static int BATTLE_TYPE_PVP_ARENA = 2;
	const static int BATTLE_TYPE_PVP_FIELD = 3;
	const static int BATTLE_TYPE_PK = 4;
	const static int BATTLE_TYPE_TEAM_PVE_NORMAL = 5;   //And general strange fight
	const static int BATTLE_TYPE_TEAM_PVE_RANDOM = 6;   //And random strange fight
	const static int BATTLE_TYPE_DUNGEON_PVE_NORMAL = 7;  //And general strange fight
	const static int BATTLE_TYPE_DUNGEON_PVE_RANDOM = 8;  //And random strange fight
	const static int BATTLE_TYPE_TOWER_FIGHT = 12;        //HuanLong tower battle
	const static int BATTLE_TYPE_TOWER_HIDEBOSS_FIGHT = 13; //Hidden Boss fight
	const static int BATTLE_TYPE_TOWER_NAMED_FIGHT = 14;    //HuanLong tower name battle

	// SCMD11F follow story type
	const static int	PLAN_PROC_TYPE_DIALOG		= 1;			// dialog
	const static int	PLAN_PROC_TYPE_CG			= 2;			// animation
	const static int	PLAN_PROC_TYPE_BATLLE		= 3;			// fight
	const static int	PLAN_PROC_TYPE_DREAM		= 5;			// dream story

public:
	BattleType();
};

#endif