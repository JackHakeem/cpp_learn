#ifndef HLQS_PlayerMediator_H_
#define HLQS_PlayerMediator_H_
#include "../BaseMediator.h"

struct PkParm 
{
	int id;
	int lev;
	std::string name;
	int noLev; // 0: false, 1:true, others: not defined
	PkParm()
	{
		id = 0;
		lev = 0;
		noLev = 0;
	}
};

class PlayerMediator: public BaseMediator
{
public:
	enum
	{
		STARTUP_PLAYER_UI = 0,
		REMOVE_VIEW,
		PLAYER_PK,
	};

public:
	PlayerMediator();
	void startUPView(char* data);
	void clear();
	virtual void handleNotification(int M2Vcmd, char* data);
	void playerPk(char* data);
	bool checkPkLev(int aLev, int bLev);
};

#endif