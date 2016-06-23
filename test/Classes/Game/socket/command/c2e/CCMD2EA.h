/**
 * 客户端采集银矿	
	CMSG_SILVERMINE_DIG = 0x2EA 
	客户端->服务端, 包结构
	Uint8		采集模式 
 */

#ifndef _CCMD2EA_H_
#define _CCMD2EA_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2EA : public Packet
{
public:
	CCMD2EA() 
	{
		a_pickMode = 0;
	}

	virtual ~CCMD2EA() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_SILVERMINE_DIG;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	 int8 a_pickMode;
};


class CCMD2EAFactory: public MessageFactory
{
public :

	virtual ~CCMD2EAFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_SILVERMINE_DIG;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif