/**
 * 
客户端->服务端, 包结构（无）
 */

#ifndef _CCMD445_H_
#define _CCMD445_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD445 : public Packet
{
public:
	CCMD445() 
	{
	}

	virtual ~CCMD445() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_GONG_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
};


class CCMD445Factory: public MessageFactory
{
public :

	virtual ~CCMD445Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_GONG_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif