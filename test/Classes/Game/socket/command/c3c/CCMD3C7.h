#ifndef _CCMD3C7_H_
#define _CCMD3C7_H_


/**客户端请求体验VIP信息
CMSG_WORLD_REQ_TRIAL_VIP	= 0X3C7;
*/

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD3C7 : public Packet
{
public:
	CCMD3C7() 
	{
	}

	virtual ~CCMD3C7() {}

	virtual bool	Write()
	{
		return true;
	}

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_REQ_TRIAL_VIP;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
};


class CCMD3C7Factory: public MessageFactory
{
public :

	virtual ~CCMD3C7Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_REQ_TRIAL_VIP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif