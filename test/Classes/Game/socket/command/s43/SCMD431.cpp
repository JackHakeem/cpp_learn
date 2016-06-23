#include "SCMD431.h"
#include "manager/LangManager.h"
#include "view/ore/OreMediator.h"
#include "control/AppFacade.h"

bool SCMD431::Read()
{
	a_stoneNum = readByte();
	b_oreNum = readUint();
	c_buyCount = readUint();
	return true;
}

int32 SCMD431::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD431Handler::Execute(this);
}

uint32 SCMD431Handler::Execute( SCMD431* pPacket )
{
	OreMediator * pOreMediator = (OreMediator *)g_pFacade->retrieveMediator(AppFacade_ORE);
	if (pOreMediator)
	{
		pOreMediator->UpdateOre(pPacket->a_stoneNum, pPacket->b_oreNum, pPacket->c_buyCount );
	}
	return 0;
}
