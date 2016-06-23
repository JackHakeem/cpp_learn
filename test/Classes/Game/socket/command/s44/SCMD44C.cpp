#include "SCMD44C.h"
#include "socket/network/GameServerSocket.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "manager/LangManager.h"
#include "view/gong/GongMediator.h"
#include "manager/ViewManager.h"
#include "view/mainUI/components/RoleUI.h"
#include "view/scene/SceneMediator.h"

bool	SCMD44C::Read()
{
	a_hasHero = readByte();
	b_heroName = readString();
	return true;
}

int32 	SCMD44C::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD44CHandler::Execute(this) ;
}


uint32 SCMD44CHandler::Execute(SCMD44C* pPacket)
{
	if (!pPacket) return 1;
	if (pPacket->a_hasHero != 1 || pPacket->b_heroName.size() <= 0)
		return 0;

	SceneMediator* m = (SceneMediator*)g_pFacade->retrieveMediator(AppFacade_SCENE_MEDIATOR);
	if (m)
	{
		m->NPCName(9999, pPacket->b_heroName.c_str());
	}	
	return 0;
}