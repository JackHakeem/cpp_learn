#include "SCMD375.h"
#include "mvc/Facade.h"
#include "view/dungeonEntrys/DungeonEntrysMediator.h"
/*
#include "socket/network/GameServerSocket.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "manager/GlobalManage.h"
#include "manager/BattleManager.h"
#include "manager/LangManager.h"
#include "manager/LayerManager.h"
#include "view/dungeonEntrys/components/ChallengeGuaView.h"
#include "model/backpack/GoodsManager.h"
#include "utils/ColorUtil.h"
*/
bool	SCMD375::Read()
{
	a_errorCode       = readByte();
	b_canDungeonTimes = readByte();
	c_buyDungeonTimes = readByte();
	return true;
}

int32 	SCMD375::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD375Handler::Execute(this) ;
}


uint32 SCMD375Handler::Execute(SCMD375* pPacket)
{
	if (!pPacket) 
		return 1;
	DungeonEntrysMediator* m = (DungeonEntrysMediator*)g_pFacade->retrieveMediator(AppFacade_DungeonEntrysMediator);
	if(m)
	{
		m->HandleUpdateForBuyChaTimes(pPacket);
	}	
	return 0;
}