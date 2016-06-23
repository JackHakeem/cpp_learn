
#include "LoginManage.h"
#include "socket/network/GateServerSocket.h"
#include "socket/network/GameServerSocket.h"
#include "socket/message/MessageFactoryManager.h"
#include "socket/command/c10/CCMD101.h"
#include "socket/command/c10/CCMD106.h"
#include "socket/command/c16/CCMD164.h"
#include "socket/command/c15/CCMD15F.h"
#include "socket/command/c35/CCMD351.h"
#include "events/GameDispatcher.h"
#include "socket/command/c10/CCMD104.h"
#include "socket/command/s10/SCMD105.h"
#include "Message.h"
#include "view/login/components/LoginMain.h"
#include "view/login/components/LoginView.h"
#include "utils/ValuesUtil.h"
#include "manager/ConnectionManager.h"
#include "manager/GlobalManage.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "utils/http/ghttp.h"
#include "netdb.h"
#include "arpa/inet.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "utils/http/ghttp.h"
#include "netdb.h"
#include "arpa/inet.h"
#endif
#include "view/login/components/LoginNewMain.h"


#include "utils/thread/BaseThread.h"
#include "utils/thread/MessageMgr.h"

LoginManage* g_pLoginManage = 0;

LoginManage::LoginManage()
{
	setIsGuestLogin(false);
	setAccID(0);
	setIs91Platform(false);
	setRoleID(5);
	setRecommendServId(0);
	_pLoginView = 0;
	_enterBackground = false;

	//Doyang 20120725
	_ignoreSoketsList.push_back(false);
}

LoginManage::~LoginManage()
{
}

void LoginManage::gSocketConnectHandler()
{
	GateServerSocket* pSocket = GateServerSocket::getInstance();
	
	CCMD101 pack;
	pSocket->sendMessage(&pack);
	//else
	//{
	//	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::GATE_SERVER_CONNECT_FAILED, NULL);
	//}
}


void LoginManage::sendConnectWorld()
{
	//GAMESERVER starting to connect
	GameServerSocket* pSocket = GameServerSocket::getInstance();

	std::string strIP = parseDomain2IPAddr(e_ip);
	bool result = pSocket->connect(strIP.c_str(),f_port);//Reading configuration, written just here first
	if (result)
	{
		//Doyang 20120725
		ConnectionManager::Instance()->setIsConnect(true);
		socketConnectHandler();
	}
	else
	{
		//Connection GAMESERVER failure
		GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::GAME_SERVER_CONNECT_FAILED, NULL);
		cocos2d::CCLog("connect failed....");
	}
}

void LoginManage::socketConnectHandler()
{
	CCMD106* s = new CCMD106();
	if (s)
	{
		s->a_accountId = b_accountId;
		s->b_key = g_key;
		s->c_sn = h_sn;
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
		{
			pSocket->sendMessage(s);
		}
		else
		{
			GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::LOGIN_FAILED, NULL);
		}
	}
	SAFE_DELETE(s);
}

void LoginManage::gSocketLoginSucc( SCMD102 *pData )
{
	if(!pData)
	{
		return;
	}

	b_accountId = pData->b_accountId;
	e_ip = pData->e_ip;
	f_port = pData->f_port;
	g_key = pData->g_key;
	c_guild = pData->c_guild;
	h_sn = pData->h_sn;
	d_line = pData->d_line;


	g_pGlobalManage->guild = c_guild;

	//Begin to connect GAMESERVER
	sendConnectWorld();
}

void LoginManage::createHandler(CCObject * pSender)
{
	GateServerSocket *pSocket = GateServerSocket::getInstance();
	//bool result = pSocket->connect(g_pLoginManage->getServIPAddr(), g_pLoginManage->getServIPPort());
	//CCLog("result = %d",result);
	CCMD104 *cmd = new CCMD104();
	if (pSocket)
	{
		pSocket->sendMessage(cmd);
		CC_SAFE_DELETE(cmd); // LH0712LEAK
	}
	else
	{
		//reConnectSocket();
	}
}

void LoginManage::onCreateAccHandler(char * data)
{
	SCMD105 * cmd = (SCMD105 *)data;
	switch(cmd->a_result)
	{
	case ERR_CREATE_NAME_TOO_LONG:
		//Message::Instance()->show("LG026",ccc3(233,25,12),1);
		CCMessageBox(ValuesUtil::Instance()->getString("LG026").c_str(),ValuesUtil::Instance()->getString("LG033").c_str());
		break;
	case ERR_CREATE_NAME_ALREDY_EXIST:
		//Message::Instance()->show("LG027",ccc3(233,25,12),1);
		CCMessageBox(ValuesUtil::Instance()->getString("LG027").c_str(),ValuesUtil::Instance()->getString("LG033").c_str());
		break;
	case ERR_CREATE_ROLE_NOT_EXIST:
		//Message::Instance()->show("LG028",ccc3(233,25,12),1);
		CCMessageBox(ValuesUtil::Instance()->getString("LG028").c_str(),ValuesUtil::Instance()->getString("LG033").c_str());
		break;
	case ERR_CREATE_INVALID:
		//Message::Instance()->show("LG029",ccc3(233,25,12),1);
		CCMessageBox(ValuesUtil::Instance()->getString("LG029").c_str(),ValuesUtil::Instance()->getString("LG033").c_str());
		break;
	case ERR_CREATE_FAILED:
		//Message::Instance()->show("LG030",ccc3(233,25,12),1);
		CCMessageBox(ValuesUtil::Instance()->getString("LG030").c_str(),ValuesUtil::Instance()->getString("LG033").c_str());
		break;
	case ERR_CREATE_NAME_INVALID:
		//Message::Instance()->show("LG031",ccc3(233,25,12),1);
		CCMessageBox(ValuesUtil::Instance()->getString("LG031").c_str(),ValuesUtil::Instance()->getString("LG033").c_str());
		break;
	default:
		break;
	}
}

bool LoginManage::isContainAlpha(std::string str)
{
	bool isAlpha = false;
	int len = str.length();
	int i = 0;
	while(i < len-1) 
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
		{
			isAlpha = true;
			break;
		}
		++i;
	}
	return isAlpha;
}

std::string LoginManage::parseDomain2IPAddr(std::string IPurl)
{
	std::string strDomainOrIP = g_pLoginManage->getServIPAddr();
	if (isContainAlpha(strDomainOrIP))
	{
		hostent * pHost = gethostbyname(strDomainOrIP.c_str());
		if (!pHost)
		{
			CCMessageBox(ValuesUtil::Instance()->getString("LG040") .c_str() , ValuesUtil::Instance()->getString("LG033") .c_str());
			return "";
		}
		sockaddr_in sa;
		std::string strHostIP("");
		//int port = 0;
		std::list<std::string> IPList;
		for (int nAdapter= 0; pHost->h_addr_list[nAdapter] ; nAdapter++)
		{
			memcpy(&sa.sin_addr.s_addr , pHost->h_addr_list[nAdapter] , pHost->h_length);
			strHostIP = inet_ntoa(sa.sin_addr);
			IPList.push_back(strHostIP);
			//port = sa.sin_port;
		}
		std::string strIP("");
		if (!IPList.empty())
		{
			strIP = IPList.front();
			g_pLoginManage->setServIPAddr(IPList.front());
		}
		return strIP;
	}
	return strDomainOrIP;
}

void LoginManage::LoginFor91Platform(std::string token , int recommendServId)
{
	setIs91Platform(true);
	setAccount(token);
	setPasswd("");
	setRecommendServId(recommendServId);
/*	
	LoginMain * pLoginMain = 0;
	if (_pLoginView)
	{
		pLoginMain = (LoginMain *)_pLoginView->getChildByTag(LoginView::TAG_UserPwdLayer);
	}

	if (pLoginMain)
	{
		pLoginMain->onServerMenuClick(0); // LH20121124
	}
*/
}


void LoginManage::LoginFor4399Platform(std::string token , int recommendServId)
{
	setIs91Platform(true);
	setAccount(token);
	setPasswd("");
	setRecommendServId(recommendServId);


	BaseThread * pThread = new BaseThread((void *)&LoginNewMain::getServerInfoFromRemote,0);
	pThread->run();

/*
	LoginMain * pLoginMain = 0;
	if (_pLoginView)
	{
		pLoginMain = (LoginMain *)_pLoginView->getChildByTag(LoginView::TAG_UserPwdLayer);
	}
	
	if (pLoginMain)
	{
		pLoginMain->onServerMenuClick(0);
	}
	*/
}

void LoginManage::saveServerMap2List()
{
	_serverVoList.clear();
	std::map<int/*areaID*/,std::map<int/*servID*/,ServerListVo> >::iterator iter = _serverListVoDic.begin();
	for (iter ; iter != _serverListVoDic.end() ; iter++)
	{
		std::map<int/*servID*/,ServerListVo> listVoMap = iter->second;
		std::map<int/*servID*/,ServerListVo>::iterator it = listVoMap.begin();
		for (it ; it != listVoMap.end() ; it++)
		{
			_serverVoList.push_back(it->second);
		}
	}

	int len = _serverVoList.size();
	for(int i=0; i<=len/2; ++i)
	{
		ServerListVo vo = _serverVoList[i];
		_serverVoList[i] = _serverVoList[len - i - 1];
		_serverVoList[len - i - 1] = vo;
	}
}

std::vector<ServerListVo> & LoginManage::getServerList()
{
	return _serverVoList;
}

/*
//void LoginManage::getUserInfo()
//{
//	GameServerSocket* pSocket = GameServerSocket::getInstance();
//	if ( !pSocket ) return;
//
//	CCMD164 s;
//	pSocket->sendMessage( &s );
//
//	// 任务
//	CCMD15F *cCMD15F = new CCMD15F();
//	if(cCMD15F)
//	{
//		if (pSocket)
//			pSocket->sendMessage(cCMD15F);
//	}
//	SAFE_DELETE(cCMD15F);
//	
//	CCMD351 packet351;	//1个包,  请求挂机训练情况列表 
//	pSocket->sendMessage( &packet351 );
//
//}
*/


