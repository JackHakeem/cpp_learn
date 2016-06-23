/**
 * 
点击占星师
 */

#ifndef _CCMD461_H_
#define _CCMD461_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD461 : public Packet
{
public:
	CCMD461() 
	{
		zxerIndex = 0;
	}

	virtual ~CCMD461() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_ZX_CLICK_ZXER;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	uint8 zxerIndex;//占星师id 0~4
};


class CCMD461Factory: public MessageFactory
{
public :

	virtual ~CCMD461Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_ZX_CLICK_ZXER;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif