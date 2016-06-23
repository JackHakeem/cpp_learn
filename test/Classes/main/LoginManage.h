#ifndef _LOGINMANAGE_H_
#define _LOGINMANAGE_H_

#include "BaseType.h"
#include "socket/command/s10/SCMD102.h"
#include "view/login/components/ServerListVo.h"

class LoginView;

class LoginManage
{
public:
	LoginManage();
	~LoginManage();

public:

	void gSocketConnectHandler (); // connection of the GATE after treatment
	void gSocketCloseHandler () {} // and GATE disconnect
	void sendConnectWorld (); // try to connect GAME
	void socketConnectHandler (); // connection of the GAME after treatment
	void socketCloseHandler () {} // and the GAME off
	//void getUserInfo();
	void gSocketLoginSucc(SCMD102 *pData);
	void createHandler(CCObject * pSender);
	void onCreateAccHandler(char * data);

	void LoginFor91Platform(std::string token , int recommendServId);

    //Doyang 20120821
    void LoginFor4399Platform(std::string account , int recommendServId);

	// LH20121025 domain
	bool isContainAlpha(std::string str);
	std::string parseDomain2IPAddr(std::string IPurl);
	void saveServerMap2List();
	std::vector<ServerListVo> & getServerList();

public:
	std::string	e_ip;
	std::string	h_sn;
	int8	d_line;
	int16	f_port;
	int32	g_key;
	uint32	b_accountId;
	int32	c_guild;//GlobalManage.getInstance().guild

	//Doyang 20120724
	bool _enterBackground;
	enum IgnoreSockets
	{
		IS_SCMD107 = 0,

	};
	std::vector<bool> _ignoreSoketsList;

	CC_SYNTHESIZE(string, account, Account);
	CC_SYNTHESIZE(string, passwd, Passwd);
	CC_SYNTHESIZE(string, rolename, RoleName);
	CC_SYNTHESIZE(uint16, roleID, RoleID);
	CC_SYNTHESIZE(uint16, accID, AccID);
	CC_SYNTHESIZE(bool, isGuestLogin, IsGuestLogin);
	CC_SYNTHESIZE(std::string, servIPAddr, ServIPAddr);
	CC_SYNTHESIZE(std::string, exchargeServerId, ExchargeServerId);
	CC_SYNTHESIZE(unsigned short, servIPPort, ServIPPort);
	CC_SYNTHESIZE(int, servState, ServState);
	CC_SYNTHESIZE(bool, is91Platform, Is91Platform);
	CC_SYNTHESIZE(int, _recommendServId, RecommendServId);

	std::map<int/*areaID*/,std::map<int/*servID*/,ServerListVo> > _serverListVoDic;
	std::vector<ServerListVo> _serverVoList;
	LoginView * _pLoginView;
	ServerListVo  _CurServListVo;

public:
	enum
	{
		ERR_CREATE_NAME_TOO_LONG = 16,		
		ERR_CREATE_NAME_ALREDY_EXIST = 17,
		ERR_CREATE_ROLE_NOT_EXIST = 18,		
		ERR_CREATE_INVALID = 19,		//
		ERR_CREATE_FAILED = 20,		//
		ERR_CREATE_NAME_INVALID = 21,		
	};
	
};

extern LoginManage* g_pLoginManage;

#endif 
