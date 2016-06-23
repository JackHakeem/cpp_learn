#include "SCMD107.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"

#include "socket/command/c11/CCMD11E.h"
#include "../c31/CCMD317.h"
#include "view/login/LoginMediator.h"
#include "manager/BattleManager.h"
#include "view/crystal/components/CrystalView.h"
#include "../c18/CCMD189.h"
#include "../c30/CCMD308.h"
#include "events/GameDispatcher.h"
#include "manager/GlobalManage.h"
#include "socket/command/c41/CCMD41E.h"


bool	SCMD107::Read()
{
	a_AccountId = readUint();
	b_mapId = readUshort();
	c_x = readShort();
	d_y = readShort();
	e_id = readInt();
	f_name = readString();
	g_silvere = readInt();
	h_gold = readInt();
	i_practice = readInt();
	j_popularity = readInt();
	k_energy = readShort();
	_remainVigourBuffCount = readByte();
	_gongExpBuffCount = readInt();
	l_serverTime = readUint();
	m_vipLev = readByte();
	n_vipGold = readUint();
	o_onlineTime = readUint();
	p_accountType = readByte();
	q_trainSitNum = readByte();
	r_crystalListNum = readByte();
	s_guildName = readString();
	t_stone = readInt();
	u_blue = readInt();
	v_puple = readInt();
	w_red = readInt();
	x_isOnbussiness = readByte();
	y_restTraderCnt = readShort();

	return true;
}

int32 	SCMD107::Execute()
{
	if (!Read())
	{
		return 1;
		GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::LOGIN_FAILED, NULL);
	}

	return SCMD107Handler::Execute(this) ;
}


uint32 SCMD107Handler::Execute(SCMD107* pPacket)
{
	if (!pPacket) return 1;

	cocos2d::CCLog("---------------------------------------getuserinfo");
	g_pGlobalManage->setIsInGame(true);

	//Doyang 20120725
	if(g_pLoginManage->_ignoreSoketsList[LoginManage::IS_SCMD107])
	{
		g_pLoginManage->_ignoreSoketsList[LoginManage::IS_SCMD107] = false;
		return 0;
	}
	LoginMediator* loginMediator = (LoginMediator*)g_pFacade->retrieveMediator(AppFacade_LOGIN_MEDIATOR);

	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::LOGIN_SUCCESS, NULL);
	loginMediator->initRoleInfo(pPacket);
	loginMediator->sendClientType();

	//Begin Kenfly 20130202 : send delay
	g_pGlobalManage->g_netDelay = Timer::millisecondNow();
	CCMD41E msg;
	msg.a_req = 0;
	GameServerSocket::getInstance()->sendMessage(&msg);
	//End Kenfly 20130202

	//g_pLoginManage->getUserInfo();//To apply for the player a variety of information
	 
	//*GPH 2012.3.20  
	//Application for formation
	//CCMD317* s = new CCMD317();
	//if (s)
	//{
	//	s->a_type=1;
	//	GameServerSocket* pSocket = GameServerSocket::getInstance();
	//	if (pSocket)
	//		pSocket->sendMessage(s);

	//	cocos2d::CCLog("sheng qing zhen xing: CCMD317");
	//}
	//SAFE_DELETE(s);
 

	////The GPH 2012.3.28 test open battle
	/*g_pBattleManager->sendBattleRequestHandler();
	cocos2d::CCLog("g_pBattleManager->sendBattleRequestHandler();");*/

	//ˮ������ by LH
// 	CCMD189* s = new CCMD189();
// 	if (s)
// 	{
// 		GameServerSocket* pSocket = GameServerSocket::getInstance();
// 		if (pSocket)
// 			pSocket->sendMessage(s);
// 		cocos2d::CCLog("Crystal Info Request:CCMD189");
// 	}
// 	SAFE_DELETE(s);

	return 0;
}
