#include "SCMD323.h"
#include "LoginManage.h"
#include "manager/ViewManager.h"
#include "view/levy/LevyMediator.h"

bool	SCMD323::Read()
{ 
	a_type = readByte();
	b_rest = readByte();
	c_max = readByte();
	e_uniteNum = readShort();
	f_starNum = readShort();
	g_reward = readInt();
	h_cost = readInt();
	return true;
}

int32 	SCMD323::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD323Handler::Execute(this) ;
}


uint32 SCMD323Handler::Execute(SCMD323* pPacket)
{
	if (!pPacket) return 1;

	//add code here
	//if ( ViewManager * pManager = ViewManager::getInstance() )
	//{
	//	if ( CDPanel* pCDPanel = pManager->cdList )
	//	{
	//		pCDPanel->initLevyLabel(pPacket);
	//	}
	//}
	if ( g_pLevyMediator )
	{
		g_pLevyMediator->levyInitHandler( pPacket );
	}
	
	return 0;
}