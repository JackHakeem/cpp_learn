#ifndef HLQL_SystemManage_H_
#define HLQL_SystemManage_H_
#include "utils/Singleton.h"
#include "utils/flash/CCIEventDispatcher.h"

class SystemManage: public Singleton<SystemManage>, public CCIEventDispatcher
{
public:
	SystemManage();
	void soundOn(bool value);
	void showPlayers(bool value);
	bool soundOn();
	bool showPlayers();

public:
	enum
	{
		SHOW_PLAYER_CHANGE = 0,
	};

	bool _soundOn;
	bool _showPlayers;

};

#endif