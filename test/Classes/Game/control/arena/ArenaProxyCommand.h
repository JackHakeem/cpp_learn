#ifndef _ARENAPROXYCOMMAND_H_
#define _ARENAPROXYCOMMAND_H_

#include "mvc/SimpleCommand.h"



class ArenaProxyCommand:public SimpleCommand
{
public:
	enum 
	{
		PVP_QUALIFYING_STAR = 0,
		PVP_QUALIFYING_RESULT,
		PVP_ARENACONTEST_REQUEST,
		PVP_ARENACOUTEST_LIST,
	};

public:
	~ArenaProxyCommand(){}
	virtual void execute(int32 command, char* data);

private:
	//BagProxy* 
};

#endif