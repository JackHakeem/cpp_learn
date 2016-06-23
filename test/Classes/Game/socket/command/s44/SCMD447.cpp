#include "SCMD447.h"
#include "socket/network/GameServerSocket.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "manager/LangManager.h"
#include "view/scene/SceneMediator.h"
#include "view/mainUI/components/SecNavigate.h"
#include "manager/ViewManager.h"

bool	SCMD447::Read()
{
	a_gongActive = readByte();

	return true;
}

int32 	SCMD447::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD447Handler::Execute(this) ;
}


uint32 SCMD447Handler::Execute(SCMD447* pPacket)
{
	if (!pPacket) return 1;

	int lev = RoleManage::Instance()->roleLev();
	if (lev >= 25)
	{
		SecNavigate * pSecNav = (SecNavigate *)ViewManager::getInstance()->_secNavigate;
		if (pPacket->a_gongActive == 1)
		{
			pSecNav->addButton(SecNavigate::TAG_GONG, -1, false);
		}
		else
		{
			pSecNav->removeButton(SecNavigate::TAG_GONG);
		}
	}
	return 0;
}