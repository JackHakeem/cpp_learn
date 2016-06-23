#include "ArenaProxyCommand.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "model/arena/ArenaProxy.h"


void ArenaProxyCommand::execute(int32 command, char* data)
{
	//ArenaProxy* _arenaProxy = (ArenaProxy*)g_pFacade->retrieveProxy(AppFacade_ARENA_PROXY);
	switch(command)
	{
	case PVP_QUALIFYING_STAR:
		break;
	case PVP_QUALIFYING_RESULT:
		break;
	case PVP_ARENACONTEST_REQUEST:
		break;
	case PVP_ARENACOUTEST_LIST:
		break;
	default:
		break;
	}
}