#ifndef _CCMD182_H_
#define _CCMD182_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/* * 

	Request for CD player cleared 

	CMSG_WORLD_CLEAR_CD = 0 x182 (386) 

	The client-> the server, package structure 

	Byte CD type 

	Byte 0 1 free charge 

	*/ 

class CCMD182 : public Packet
{
public:
	CCMD182() {}
	virtual ~CCMD182() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_CLEAR_CD;}

	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	int8 a_type;
	int8 b_free;
};


class CCMD182Factory: public MessageFactory
{
public :

	virtual ~CCMD182Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_CLEAR_CD;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};
#endif 