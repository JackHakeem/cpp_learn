#include "SCMD363.h"
#include "model/arena/ArenaProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool	SCMD363::Read()
{
	a_rank = readUint();
	b_result = readByte();
	return true;
}

int32 	SCMD363::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD363Handler::Execute(this) ;
}


uint32 SCMD363Handler::Execute(SCMD363* pPacket)
{
	if (!pPacket) return 1;

	ArenaProxy* _arenaProxy = (ArenaProxy*)g_pFacade->retrieveProxy(AppFacade_ARENA_PROXY);
	if (_arenaProxy)
		_arenaProxy->doArenaPkRes(pPacket);
	return 0;
}