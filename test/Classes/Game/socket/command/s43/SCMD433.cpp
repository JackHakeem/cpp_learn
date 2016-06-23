#include "SCMD433.h"
#include "manager/LangManager.h"
#include "view/ore/OreMediator.h"
#include "control/AppFacade.h"

bool SCMD433::Read()
{
	a_flag = readUint();
	return true;
}

int32 SCMD433::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD433Handler::Execute(this);
}

uint32 SCMD433Handler::Execute( SCMD433* pPacket )
{
	OreMediator * pOreMediator = (OreMediator *)g_pFacade->retrieveMediator(AppFacade_ORE);
	if (pOreMediator)
	{
		pOreMediator->HandleResponse(pPacket->a_flag);
	}
	return 0;
}
