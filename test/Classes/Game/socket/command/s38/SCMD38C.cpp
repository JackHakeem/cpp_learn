#include "SCMD38C.h"
#include "model/arena/ArenaProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool	SCMD38C::Read()
{
	a_buy = readByte();
	return true;
}

int32 	SCMD38C::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD38CHandler::Execute(this) ;
}


uint32 SCMD38CHandler::Execute(SCMD38C* pPacket)
{
	if (!pPacket) return 1;

	ArenaProxy* _arenaProxy = (ArenaProxy*)g_pFacade->retrieveProxy(AppFacade_ARENA_PROXY);
	if (_arenaProxy)
		_arenaProxy->doArenaBuyRes(pPacket);


	
	return 0;
}