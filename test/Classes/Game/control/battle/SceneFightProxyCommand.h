#ifndef _SCENEFIGHTPROXYCOMMAND_H_
#define _SCENEFIGHTPROXYCOMMAND_H_


#include "mvc/SimpleCommand.h"
#include "model/battle/FightProxy.h"

class SceneFightProxyCommand:public SimpleCommand{

public:
	enum 
	{
		JOIN_ELEMENT = 0,
		INIT_PVE_SCENEVO,
		INIT_PVP_SCENEVO,
		INIT_PVE_DATA,
		INIT_PVP_DATA,

		ADD_FIGHTPACK,
		ADD_FIGHTRET,
		ADD_REWARD,
		ADD_FOLLOW_PROCESS,
		ADD_NEW_MERC
	};


public :
	FightProxy* _fightProxy;


public:
	SceneFightProxyCommand();
	~SceneFightProxyCommand(){};
	virtual void execute(int32 command, char* data);

	void joinElement();
	void addMonsters();
	void addPlayers();

	void setPVEFightSceneVo(char* data);
	void setPVPFightSceneVo(char* data);

};



#endif