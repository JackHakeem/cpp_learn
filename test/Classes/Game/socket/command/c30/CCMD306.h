// request for employ list
#ifndef _CCMD306_H_
#define _CCMD306_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD306 : public Packet
{
public:
	CCMD306() 
	{
		//a_byte = 0;
	}

	virtual ~CCMD306() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_WORLD_MERCENARY_EMPLOYNPC;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	//int8 a_byte;

};


class CCMD306Factory: public MessageFactory
{
public :

	virtual ~CCMD306Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_MERCENARY_EMPLOYNPC;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif