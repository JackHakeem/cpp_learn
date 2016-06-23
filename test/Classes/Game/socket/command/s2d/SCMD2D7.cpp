#include "SCMD2D7.h"
#include "view/mainStreng/MainStrengMediator.h"

bool SCMD2D7::Read()
{
	a_type = readByte();
	b_attribute = readByte();
	c_sparNum = readInt();
	d_streng = readByte();
	e_location = readByte();
	f_sit = readByte();
	g_roleId = readInt();

	return true;
}

int32 SCMD2D7::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2D7Handler::Execute(this) ;
}

uint32 SCMD2D7Handler::Execute(SCMD2D7* pPacket)
{
	if (!pPacket) return 1;

	if ( g_pMainStrengMediator )
	{
		g_pMainStrengMediator->returnMagicResult(pPacket);
	}
	return 0;
}