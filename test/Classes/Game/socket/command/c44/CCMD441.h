/**
 * 
客户端->服务端, 包结构（无）
 */

#ifndef _CCMD441_H_
#define _CCMD441_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD441 : public Packet
{
public:
	CCMD441() 
	{
	}

	virtual ~CCMD441() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_GONG_GETOPENTIME;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
};


class CCMD441Factory: public MessageFactory
{
public :

	virtual ~CCMD441Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_GONG_GETOPENTIME;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif