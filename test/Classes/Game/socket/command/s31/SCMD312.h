
/**
* The client requests to enable the formation to return the package
* WMSG_WORLD_FORMATION_ENABLED = 0x312
* Server -> client package structure
* Uint8 whether the operation was successful
* Uint16 enable the formation ID
* Uint16 Disable formation ID
 */ 

#ifndef _SCMD312_H_
#define _SCMD312_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD312 : public Packet
{
public:
	SCMD312() {}
	virtual ~SCMD312() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_FORMATION_ENABLED;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint8 a_isOk ;
	uint16 b_startId ;
	uint16 c_stopId ;
	 
};


class SCMD312Factory: public MessageFactory
{
public :

	virtual ~SCMD312Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD312();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_FORMATION_ENABLED;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD312Handler 
{
public:
	static uint32 Execute(SCMD312* pPacket) ;
};

#endif 