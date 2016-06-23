#include "SCMD39D.h"
#include "view/arena/ArenaMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD39D::Read()
{
	return true;
}

int32 	SCMD39D::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD39DHandler::Execute(this) ;
}

uint32 SCMD39DHandler::Execute(SCMD39D* pPacket)
{
	if (!pPacket) return 1;

  	ArenaMediator* arenaMediator = (ArenaMediator*)g_pFacade->retrieveMediator(AppFacade_ARENA_MEDIATOR);
  	arenaMediator->athleticsReportHandler(pPacket);

	return 0;
}