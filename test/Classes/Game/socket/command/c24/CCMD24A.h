/**
* client requests battle winning streak info
CMSG_COMMU_REGISTER_REQUEST = 0x24A
Client -> server, the package structure
byte 0
 
 */

#ifndef _CCMD24A_H_
#define _CCMD24A_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD24A : public Packet
{
public:
	CCMD24A() 
	{
		a_account = "";
		b_role = "";
	}

	virtual ~CCMD24A() {}

	virtual bool	Write();	 

	virtual PacketID_t getPacketID() const { return CMSG_COMMU_REGISTER_REQUEST;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	std::string a_account;
	std::string b_role;

};


class CCMD24AFactory: public MessageFactory
{
public :

	virtual ~CCMD24AFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_REGISTER_REQUEST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif