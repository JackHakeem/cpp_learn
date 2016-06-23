#include "SCMD366.h"
#include "model/arena/ArenaProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "view/arena/ArenaMediator.h"

bool SCMD366::Read()
{
	a_isSucess = readByte();
	b_arenaType = readByte();

	return true;
}

int32 	SCMD366::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD366Handler::Execute(this) ;
}


uint32 SCMD366Handler::Execute(SCMD366* pPacket)
{
	if (!pPacket) return 1;

	ArenaMediator* m = (ArenaMediator*)g_pFacade->retrieveProxy(AppFacade_ARENA_MEDIATOR);
	if (m)
		m->challengeErrorHandler(pPacket);

	return 0;
}