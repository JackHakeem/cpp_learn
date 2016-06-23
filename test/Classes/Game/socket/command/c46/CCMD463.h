/**
 * 
打开占星面板请求信息
 */

#ifndef _CCMD463_H_
#define _CCMD463_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD463 : public Packet
{
public:
	CCMD463() 
	{
	}

	virtual ~CCMD463() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_ZX_OPEN_ZX;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
};


class CCMD463Factory: public MessageFactory
{
public :

	virtual ~CCMD463Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_ZX_OPEN_ZX;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif