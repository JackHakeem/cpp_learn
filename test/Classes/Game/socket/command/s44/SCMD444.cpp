#include "SCMD444.h"
#include "socket/network/GameServerSocket.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "manager/LangManager.h"
#include "view/scene/SceneMediator.h"

bool	SCMD444::Read()
{
	a_show = readByte();
	return true;
}

int32 	SCMD444::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD444Handler::Execute(this) ;
}


uint32 SCMD444Handler::Execute(SCMD444* pPacket)
{
	if (!pPacket) return 1;


	SceneMediator* m = (SceneMediator*)g_pFacade->retrieveMediator(AppFacade_SCENE_MEDIATOR);
	if (m)
	{
		for (int i = 9001; i <= 9030; i++)
			m->showNPC((char*)&i, ((int)pPacket->a_show == 0)?false:true);
	}	
	
	return 0;
}