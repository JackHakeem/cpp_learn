#include "CampFightMediator.h"
#include "control/campFight/campFightCommand.h"
#include "socket/command/c45/CCMD458.h"
#include "socket/network/GameServerSocket.h"

CampFightMediator::CampFightMediator()
{
	m_pCampFightView = NULL;
	/*GameDispatcher* _dispatcher = GameDispatcher::getInstance();
	if (_dispatcher)
	{
		_dispatcher->addEventListener(GameDispatcher::MSG_OPEN_CAMPFIGHT_VIEW,this,
			callfuncND_selector(CampFightMediator::OpenCampFightView));
	}*/
}

CampFightMediator::~CampFightMediator()
{
	/*GameDispatcher* _dispatcher = GameDispatcher::getInstance();
	if (_dispatcher)
		_dispatcher->removeEventListener(GameDispatcher::MSG_OPEN_CAMPFIGHT_VIEW);
*/
}
void CampFightMediator::handleNotification(int M2Vcmd, char* data)
{
	switch(M2Vcmd)
	{
	case UPDATE_CAMPFIGHT:
		{
			UpdateCamp();
		}
		break;
	case UPDATE_MY_INFO_VIEW:
		{
			UpdateMyInfo();
		}
		break;
	default:
		break;
	}
}
void CampFightMediator::OpenCampFightView(int32 ApplyRes)
{
	if (ApplyRes != 0)
	{
		return;
	}
	if ( !m_pCampFightView )
	{
		m_pCampFightView = new CampFightView();
	}
	if (!m_pCampFightView->init())
	{
		CC_SAFE_DELETE(m_pCampFightView);

	}
	CCMD458 cmd;
	GameServerSocket::getInstance()->sendMessage(&cmd);
}

void CampFightMediator::CloseCampFightView(int32 ApplyRes)
{
	if (m_pCampFightView)
	{
		m_pCampFightView->closeView(ApplyRes);
	}
}
//通知commmand去修改proxy
void CampFightMediator::UpdateCampFightSceneInfo(SCMD45B* pPacket)
{
	sendNotification(Facade_Command,AppFacade_CampFight_Proxy_Change,
		(char*)pPacket, CampFightCommand::UPDATE_CAMPFIGHT_INFO);		
}
//通知commmand去修改proxy
void CampFightMediator::UpdateMyInfo(SCMD459* pPacket)
{
	sendNotification(Facade_Command,AppFacade_CampFight_Proxy_Change,
		(char*)pPacket, CampFightCommand::UPDATE_MY_INFO);
}
void CampFightMediator::UpdateCamp()
{
	if (!m_pCampFightView)
	{
		return;
	}
	if (!m_pCampFightView->getisPop())
	{
		return;
	}
	m_pCampFightView->UpdateCampFightSceneInfo();
}
void CampFightMediator::UpdateMyInfo()
{
	if (!m_pCampFightView)
	{
		return;
	}
	if (!m_pCampFightView->getisPop())
	{
		return;
	}
	m_pCampFightView->UpdateMyInfo();
}