#include "SCMD2DF.h"
#include "view/mainStreng/MainStrengMediator.h"

bool SCMD2DF::Read()
{
	a_type = readByte();
	b_streng = readByte();
	c_location = readByte();
	d_sit = readByte();
	e_roleId = readInt();
	f_streng = readByte();
	g_location = readByte();;
	h_sit = readByte();;
	i_roleId = readInt();
	j_stamina = readShort();
	k_wrist = readShort();
	l_intellect = readShort();

	return true;
}

int32 SCMD2DF::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2DFHandler::Execute(this) ;
}

uint32 SCMD2DFHandler::Execute(SCMD2DF* pPacket)
{
	if (!pPacket) return 1;

	if ( g_pMainStrengMediator )
	{
		g_pMainStrengMediator->returnHeritageResult(pPacket);
	}
	return 0;
}