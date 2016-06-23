/**
* CMSG_LOGIN = 0x101 (257), / / ​​Gate user login
* Client -> server-side package structure
* Uint32, the client version number
* String user account
* Uint8 logon type: normal login and 1 Guest Sign In
* Int: random verification code
* String: encryption SN
 */

#ifndef _CCMD101_H_
#define _CCMD101_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "LoginManage.h"


class CCMD101 : public Packet
{
public:
	CCMD101() 
	{
		a_clientversion = 1;
		b_account = g_pLoginManage->getAccount();
		//passwd = g_pGlobalManage->getPasswd();
		c_loginType = g_pLoginManage->getIsGuestLogin() ? 1 : 0;		
		d_times = 0;
		e_flag = "";
	}
	CCMD101(string account, string passwd) 
	{
		account = account;
		passwd = passwd;
	}
	virtual ~CCMD101() {}

	uint32 a_clientversion;
	std::string b_account;
	//std::string passwd;
	uint8 c_loginType;		
	int32 d_times;
	std::string e_flag;

	virtual bool	Write();
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const { return CMSG_LOGIN;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
};


class CCMD101Factory: public MessageFactory
{
public :
	
	virtual ~CCMD101Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_LOGIN;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 