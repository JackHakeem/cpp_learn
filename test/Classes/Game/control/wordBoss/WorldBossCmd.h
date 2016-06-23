#pragma once
#include "mvc/SimpleCommand.h"

class WorldBossCmd : public SimpleCommand
{
public:
	WorldBossCmd();
	virtual ~WorldBossCmd();
	virtual void execute(int32 command, char* data);

	void requestWorldBossInfo();
	void showQuitConfirm();
	void clickQuit(CCObject * pSender);
	void clickCancel(CCObject * pSender);

public:
	enum
	{
		IS_OPEN_TIME,
		UPDATE_BOSS_INFO,
		UPDATE_PLAYER_INFO,
		RELIVE,
		BOOST,
		MAP_SKIP,
		INIT_WORLD_BOSS_PROXY,
		ON_CLICK_QUIT,
	};

protected:
private:
};