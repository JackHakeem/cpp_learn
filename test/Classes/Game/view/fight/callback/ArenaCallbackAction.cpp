#include "ArenaCallbackAction.h"
#include "manager/PopManage.h"
#include "events/GameDispatcher.h"


#include "socket/network/GameServerSocket.h"
#include "model/player/RoleManage.h"

#include "manager/ViewManager.h"
#include "manager/LangManager.h"
#include "socket/command/c36/CCMD360.h"
#include "socket/command/c28/CCMD284.h"

ArenaCallbackAction::ArenaCallbackAction()
{
	_dispatcher = 0;
	_dispatcher = GameDispatcher::getInstance();
	_arenaUI = 0;
	
}

bool ArenaCallbackAction::init(ArenaUI* arenaUI)
{
	if (!arenaUI)
		return false;

	_arenaUI = arenaUI;

	return true;
}

ArenaCallbackAction::~ArenaCallbackAction()
{

}

void ArenaCallbackAction::doAction()
{
	//TweenLite.to(_arenaUI, 0.3, {alpha:1});
			
	CCMD360* cmd360 = new CCMD360();
	if (cmd360)
	{
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(cmd360);
	}
	SAFE_DELETE(cmd360);


	CCMD284* cmd284 = new CCMD284();
	if (cmd284)
	{
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(cmd284);
	}
	SAFE_DELETE(cmd284);
}

