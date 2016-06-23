/**
 * 
客户端->服务端, 包结构（无）
 */

#ifndef _CCMD448_H_
#define _CCMD448_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD448 : public Packet
{
public:
	CCMD448() 
	{
		a_MBType = 0;
	}

	virtual ~CCMD448() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_GONG_MB;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	uint8 a_MBType;
};


class CCMD448Factory: public MessageFactory
{
public :

	virtual ~CCMD448Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_GONG_MB;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif