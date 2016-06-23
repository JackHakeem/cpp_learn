#include "SCMD3AE.h"
#include "view/tower/TowerMediator.h"

bool SCMD3AE::Read()
{
	a_result = readUbyte();
	b_inspire = readUbyte();
	c_nextPrac = readInt();

	return true;
}

int32 SCMD3AE::Execute()
{
	if(!Read())
	{
		return 1;
	}

	return SCMD3AEHandler::Execute(this);
}

uint32 SCMD3AEHandler::Execute( SCMD3AE *pPacket )
{
	if(!pPacket)
	{
		return 1;
	}

	g_pTowerMediator->cmdInspire(pPacket);

	return 0;
}
