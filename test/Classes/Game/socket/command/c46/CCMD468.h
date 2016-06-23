/**
 * 
打开星魂面板请求信息
 */

#ifndef _CCMD468_H_
#define _CCMD468_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD468 : public Packet
{
public:
	CCMD468() 
	{
	}

	virtual ~CCMD468() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_ZX_OPEN_XH;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
};


class CCMD468Factory: public MessageFactory
{
public :

	virtual ~CCMD468Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_ZX_OPEN_XH;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif