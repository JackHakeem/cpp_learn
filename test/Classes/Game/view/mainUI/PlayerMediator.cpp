#include "PlayerMediator.h"
#include "socket/command/c13/CCMD13B.h"
#include "model/player/vo/PlayerInfoVo.h"
#include "model/player/RoleManage.h"
#include "manager/CDManage.h"
#include "Message.h"
#include "utils/ValuesUtil.h"

PlayerMediator::PlayerMediator()
{

}

void PlayerMediator::handleNotification(int M2Vcmd, char* data)
{
	switch(M2Vcmd) 
	{
	case STARTUP_PLAYER_UI:
		startUPView(data);
		break;
	case REMOVE_VIEW:
		clear();
		break;
	case PLAYER_PK:
		playerPk(data);
		break;
	}
}

void PlayerMediator::startUPView(char* data)
{

}

void PlayerMediator::clear()
{

}

void PlayerMediator::playerPk(char* data)
{
	if(!data)
		return;

	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(!info)
		return;

	PkParm* parm = (PkParm*)data;
	//SceneVo* sceneVo = SceneManager::Instance()->getSceneDic(info->playerBaseInfo.mapId);
	//int token = TokenManager.getInstance().getNum(TokenManager.TOKEN_PK);
	int token = 0;

	int roleLev = RoleManage::Instance()->roleLev();

	int energy = 0;
	AccountInfoVo* ac = RoleManage::Instance()->accountInfo();
	if(ac)
	{
		energy = ac->energy();
	}

	if(CDManage::Instance()->getLockBytype(CDManage::FIGHT) == 1)
	{				
		Message::Instance()->show(ValuesUtil::Instance()->getString("MUI109"));
		return;
	}
	else if( parm->noLev != 0 && parm->noLev != 1 && checkPkLev(parm->lev, roleLev) == false)
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("MUI110"));
		return;
	}
	else if(energy + token <= 0)
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("MUI111"));
		return;
	}

	CCMD13B ccmd;
	ccmd.a_accountId = parm->id;
	GameServerSocket::getInstance()->sendMessage(&ccmd);
	//_socket.sendMessage(SocketCMDConst.CMSG_WORLD_BATTLE_PK_START, int(obj.id));
}

bool PlayerMediator::checkPkLev(int aLev, int bLev)
{
	if(21 <= aLev && 21 <= bLev && aLev <= 40 && bLev <= 40)
	{
		return true;
	}
	if(41 <= aLev && 41 <= bLev && aLev <= 60 && bLev <= 60)
	{
		return true;
	}
	if(61 <= aLev && 61 <= bLev && aLev <= 80 && bLev <= 80)
	{
		return true;
	}
	if(81 <= aLev && 81 <= bLev && aLev <= 100 && bLev <= 100)
	{
		return true;
	}
	if(101 <= aLev && 101 <= bLev && aLev <= 120 && bLev <= 120)
	{
		return true;
	}
	return false;
}