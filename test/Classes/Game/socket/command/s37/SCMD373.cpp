#include "SCMD373.h"
#include "mvc/Facade.h"
#include "view/dungeonEntrys/DungeonEntrysMediator.h"
/*
#include "socket/network/GameServerSocket.h"

#include "control/AppFacade.h"
#include "manager/GlobalManage.h"
#include "manager/BattleManager.h"
#include "manager/LangManager.h"
#include "manager/LayerManager.h"
#include "view/dungeonEntrys/components/ChallengeGuaView.h"
#include "model/backpack/GoodsManager.h"
#include "utils/ColorUtil.h"
*/

bool	SCMD373::Read()
{
	a_canDungeonTimes = readByte();
	b_buyDungeonTimes = readByte();
	return true;
}

int32 	SCMD373::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD373Handler::Execute(this) ;
}


uint32 SCMD373Handler::Execute(SCMD373* pPacket)
{
	if (!pPacket) 
		return 1;
	DungeonEntrysMediator* m = (DungeonEntrysMediator*)g_pFacade->retrieveMediator(AppFacade_DungeonEntrysMediator);
	if(m)
	{
		m->HandleChallengeTimesApply(pPacket);
	}
	return 0;
}