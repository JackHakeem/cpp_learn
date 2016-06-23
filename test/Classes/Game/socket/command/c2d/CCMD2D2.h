#ifndef _CCMD2D2_H_
#define _CCMD2D2_H_
/**
* the client melting items 

CMSG_WORLD_SMELT = 0 x2D2 (722) 

The client-> the server, package structure 

Uint8 VIP level melting (ordinary VIP0 / gold VIP3 / platinum VIP5 / the supreme VIP8) 

Uint32 items 1 world only ID 

Uint32 items 2 the world only ID 

Uint32 items 3 the world only ID 

*/

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2D2 : public Packet
{
public:
	CCMD2D2() {}
	virtual ~CCMD2D2() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_SMELT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

	int8 a_vip;
	int b_id1;
	int c_id2;
	int d_id3;
};

bool CCMD2D2::Write()
{
	writeByte( a_vip );
	writeInt( b_id1 );
	writeInt( c_id2 );
	writeInt( d_id3 );

	return true;
}


class CCMD2D2Factory: public MessageFactory
{
public :
	
	virtual ~CCMD2D2Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_SMELT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif