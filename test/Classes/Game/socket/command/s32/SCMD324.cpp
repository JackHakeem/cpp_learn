#include "SCMD324.h"
#include "view/levy/LevyMediator.h"

bool	SCMD324::Read()
{  
	a_silver = readInt();
	return true;
}

int32 	SCMD324::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD324Handler::Execute(this) ;
}


uint32 SCMD324Handler::Execute(SCMD324* pPacket)
{
	if (!pPacket) return 1;

	//add code here
	if ( g_pLevyMediator )
		g_pLevyMediator->guildImpose( pPacket );

	return 0;
}