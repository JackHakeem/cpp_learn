/**
 *
 Updated mercenaries attribute information
 WMSG_WORLD_BS_CHANGE = 0 x35E (862)
 The server-> the client, package structure
 Uint32 role only ID
 Int new fighting
 */

#ifndef _SCMD35E_H_
#define _SCMD35E_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD35E : public Packet
{
public:
	SCMD35E() {}
	virtual ~SCMD35E() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_BS_CHANGE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	int32 a_mercId;
	int32 b_att;
};


class SCMD35EFactory: public MessageFactory
{
public :

	virtual ~SCMD35EFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD35E();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_BS_CHANGE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD35EHandler 
{
public:
	static uint32 Execute(SCMD35E* pPacket) ;
};

#endif