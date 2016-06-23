/**
* Server -> client package structure
* Uint8 verify the results verified by the need to create a new account 3 version is too low, 4 prohibit Login
(If verified) will these data, otherwise is 0 or an empty string
* Uint32, User Id
* Uint8 distribution lines
* Uint32, line IP
* Uint16 line port
* Uint32, random verification Key figures
* String random verification SN string
 */

#ifndef _SCMD102_H_
#define _SCMD102_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD102 : public Packet
{
public:
	SCMD102() {}
	virtual ~SCMD102() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return SMSG_LOGIN_RESPONSE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8	a_result;	uint32	b_accountId;	int32	c_guild;	int8	d_line;	std::string	e_ip;	int16	f_port;	int32	g_key;	std::string	h_sn;
};


class SCMD102Factory: public MessageFactory
{
public :
	
	virtual ~SCMD102Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD102();}

	virtual PacketID_t	GetPacketID ()const  {return SMSG_LOGIN_RESPONSE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD102Handler 
{
public:
	static uint32 Execute(SCMD102* pPacket) ;
};

#endif 