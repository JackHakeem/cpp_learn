/*
CMSG_WORLD_VIP_AWARD_INFO_REQ
*/
#ifndef _CCMD29D_H_
#define _CCMD29D_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD29D : public Packet
{
public:
	CCMD29D() {}
	virtual ~CCMD29D() {}


	virtual bool Write()
	{
		writeInt(0);
		return true;
	}
public :
	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_VIP_AWARD_INFO_REQ;}	
	virtual	int32 GetMessageSize( ) const { return 0;}
};


class CCMD29DFactory: public MessageFactory
{
public :

	virtual ~CCMD29DFactory ()  {}

	virtual Packet*	CreateMessage () {return 0;};

	virtual PacketID_t GetPacketID ()const  {return CMSG_WORLD_VIP_AWARD_INFO_REQ;}

	virtual uint32 GetMessageMaxSize ()const  {return 0;}

};

#endif 