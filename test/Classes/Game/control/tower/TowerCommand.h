#ifndef _TowerCommand_H_
#define _TowerCommand_H_

#include "BaseType.h"
#include "mvc/SimpleCommand.h"
#include "model/tower/TowerProxy.h"

struct TypeObject
{
	string rewardStr;
	string iconStr;
	TypeObject()
	{
		rewardStr = "";
		iconStr = "";
	}
};

class TowerCommand:public SimpleCommand
{
public:
	enum 
	{
		UPDATE_PANEL_1,
		UPDATE_PANEL_2,
		TOWER_FIGHT_RESULT,
		TOWER_RANKING,
	};

public:
	TowerCommand();
	~TowerCommand();

	virtual void execute(int32 command, char* data);
	void updatePanel1( char* data );
	void updatePanel2( char* data );
	void getFightResult( char* data );
	void updateTowerRanking( char* data );
	TypeObject getRewardType(int id);
	TowerProxy* _towerProxy;
};

#endif