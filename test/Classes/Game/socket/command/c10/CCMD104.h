/**
* CMSG_CREATE_ACCOUNT = 0x104, 
* Client -> server, the package structure:
* string			account
* string			rolename
* uint8			sex 0female,1male
* uint16			merh model id
* uint16			platform SN
*/

#ifndef _CCMD104_H_
#define _CCMD104_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "LoginManage.h"


class CCMD104 : public Packet
{
public:
	CCMD104() 
	{
		a_account = g_pLoginManage->getAccount();
		b_roleName = g_pLoginManage->getRoleName();
		c_roleId = g_pLoginManage->getRoleID();
		d_accid = g_pLoginManage->getAccID();
	}
	virtual ~CCMD104() {}


	virtual bool	Write();
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_CREATE_ACCOUNT;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	std::string a_account;
	std::string b_roleName;
	uint16 c_roleId;
	uint16 d_accid;
};


class CCMD104Factory: public MessageFactory
{
public :
	
	virtual ~CCMD104Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_CREATE_ACCOUNT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 