#include "SCMD44B.h"
#include "socket/network/GameServerSocket.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "manager/LangManager.h"
#include "view/gong/GongMediator.h"
#include "manager/ViewManager.h"
#include "view/mainUI/components/RoleUI.h"

bool	SCMD44B::Read()
{
	a_gongExpBuffCount = readInt();
	return true;
}

int32 	SCMD44B::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD44BHandler::Execute(this) ;
}


uint32 SCMD44BHandler::Execute(SCMD44B* pPacket)
{
	if (!pPacket) return 1;

	RoleManage::Instance()->_accountInfo._gongExpBuffCount = pPacket->a_gongExpBuffCount;

	if(ViewManager::getInstance()->_roleUI)
	{

		CCNode* pBtn = ViewManager::getInstance()->_roleUI->getChildByTag(1004);
		if (!pBtn)
			return 1;
		if (pPacket->a_gongExpBuffCount > 0)
			pBtn->setIsVisible(true);
		else
			pBtn->setIsVisible(false);
	}
	return 0;
}