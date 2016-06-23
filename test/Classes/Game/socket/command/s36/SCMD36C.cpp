#include "SCMD36C.h"
#include "view/arena/ArenaMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool	SCMD36C::Read()
{
	
	return true;
}

int32 	SCMD36C::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD36CHandler::Execute(this) ;
}


uint32 SCMD36CHandler::Execute(SCMD36C* pPacket)
{
	if (!pPacket) return 1;


	return 0;
}