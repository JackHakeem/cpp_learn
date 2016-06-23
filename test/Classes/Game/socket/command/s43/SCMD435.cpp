#include "SCMD435.h"
#include "manager/LangManager.h"
#include "view/ore/OreMediator.h"
#include "control/AppFacade.h"

bool SCMD435::Read()
{
	a_plantStates = readUint();
	return true;
}

int32 SCMD435::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD435Handler::Execute(this);
}

uint32 SCMD435Handler::Execute( SCMD435* pPacket )
{
	OreMediator * pOreMediator = (OreMediator *)g_pFacade->retrieveMediator(AppFacade_ORE);
	if (pOreMediator)
	{
		pOreMediator->UpdatePlantProgress(pPacket->a_plantStates);
	}
	return 0;
}
