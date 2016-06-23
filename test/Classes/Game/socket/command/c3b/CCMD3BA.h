#ifndef _CCMD3BA_H_
#define _CCMD3BA_H_

/**¿Í»§¶ËÀëËþ
public static const CMSG_WORLD_LEAVE_TOWER:uint	= 0X3BA;
*/

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD3BA : public Packet
{
public:
	CCMD3BA() 
	{
	}

	virtual ~CCMD3BA() {}

	virtual bool	Write()
	{
		return true;
	}

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_LEAVE_TOWER;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
};


class CCMD3BAFactory: public MessageFactory
{
public :

	virtual ~CCMD3BAFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_LEAVE_TOWER;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif