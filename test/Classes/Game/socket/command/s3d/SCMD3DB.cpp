#include "SCMD3DB.h"


#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/formation/FormationMediator.h"
#include "view/dungeonEntrys/DungeonEntrysMediator.h"

bool	SCMD3DB::Read()
{   
	 
	b_mapsInfo.clear();

	a_cityId = readShort();
	int16 cnt = readShort();
	for(int i=0;i < cnt; ++i)
	{
		SCMD3DBNode node;
		node.a_id = readShort();   
		node.b_star = readByte();
		b_mapsInfo.push_back(node);
	}
	return true;
}

int32 	SCMD3DB::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD3DBHandler::Execute(this) ;
}


uint32 SCMD3DBHandler::Execute(SCMD3DB* pPacket)
{
	if (!pPacket) return 1;
	//SkillCommand* cmd = (SkillCommand*)g_pFacade->retrieveController(AppFacade_SKILL_COMMAND);
	DungeonEntrysMediator* m = (DungeonEntrysMediator*)g_pFacade->retrieveMediator(AppFacade_DungeonEntrysMediator);
	if(m)
	{
		m->handleMapsOfCityInfo(pPacket);
	}
	return 0;
}