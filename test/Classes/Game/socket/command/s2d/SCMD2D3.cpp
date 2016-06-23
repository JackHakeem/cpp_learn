#include "SCMD2D3.h"
#include "view/mainStreng/MainStrengMediator.h"

bool SCMD2D3::Read()
{
	a_type = readByte();
	b_sparBum = readInt();

	return true;
}

int32 SCMD2D3::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2D3Handler::Execute(this) ;
}

uint32 SCMD2D3Handler::Execute(SCMD2D3* pPacket)
{
	if (!pPacket) return 1;

	if ( g_pMainStrengMediator )
	{
		g_pMainStrengMediator->returnMeltingInfo(pPacket);
	}
	return 0;
}