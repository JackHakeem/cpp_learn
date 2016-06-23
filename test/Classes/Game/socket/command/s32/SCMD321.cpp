#include "SCMD321.h"
#include "view/levy/LevyMediator.h"

bool	SCMD321::Read()
{  
	a_isSuccess = readByte();
	b_type = readByte();
	c_levyCost = readUshort();
	d_rest = readUshort();
	e_limit = readByte();
	h_luckyGold = readByte();
	i_silver = readUint();
	j_gold = readUint();
	k_uniteLev = readUshort();
	l_starNum = readUshort();
	
	return true;
}

int32 	SCMD321::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD321Handler::Execute(this) ;
}


uint32 SCMD321Handler::Execute(SCMD321* pPacket)
{
	if (!pPacket) return 1;

	//add code here
	if ( g_pLevyMediator )
		g_pLevyMediator->levyResultHandler( pPacket );

	return 0;
}