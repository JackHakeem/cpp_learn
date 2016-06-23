/**
 * 
客户端->服务端, 包结构（无）
 */

#ifndef _CCMD449_H_
#define _CCMD449_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD449 : public Packet
{
public:
	CCMD449() 
	{
	}

	virtual ~CCMD449() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_GONG_MB_UIINFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
};


class CCMD449Factory: public MessageFactory
{
public :

	virtual ~CCMD449Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_GONG_MB_UIINFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif