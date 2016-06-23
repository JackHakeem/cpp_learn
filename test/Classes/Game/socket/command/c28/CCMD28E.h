
#ifndef _CCMD28E_H_
#define _CCMD28E_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD28E : public Packet
{
public:
	CCMD28E() {}
	virtual ~CCMD28E() {}

	virtual bool	Write()
	{
		writeUint(accId);
		return true;
	}
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_TRADE_ROB_INFO;}
	virtual	int32		GetMessageSize( ) const { return 0;}

	uint32 accId;
};

class CCMD28EFactory: public MessageFactory
{
public :
	virtual ~CCMD28EFactory ()  {}
	virtual Packet*		CreateMessage () {return 0;};
	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_TRADE_ROB_INFO;}
	virtual uint32		GetMessageMaxSize ()const  {return 0;}
};

#endif 