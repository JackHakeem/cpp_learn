#ifndef _CCMD3DA_H_
#define _CCMD3DA_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD3DA : public Packet
{
public:
	CCMD3DA()
	{
		_id = 0;
	}
	virtual ~CCMD3DA() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_MAPS_OF_CITY_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}
	
	int16 _id;
};

bool CCMD3DA::Write()
{
	writeShort(_id);
	return true;
}


class CCMD3DAFactory: public MessageFactory
{
public :

	virtual ~CCMD3DAFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_MAPS_OF_CITY_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif