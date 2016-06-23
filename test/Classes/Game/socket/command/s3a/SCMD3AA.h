/**
 *
 Delivery to the client new talent power information
 WMSG_WORLD_ADD_TALENT = 0 x3AA (938)
 The server-> the client, package structure
 Uint16 talent skills ID
 Uint8 skill level
 */

#ifndef _SCMD3AA_H_
#define _SCMD3AA_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD3AA : public Packet
{
public:
	SCMD3AA()
	{
		a_tltId = 0;
		b_tltLv = 0;
	}

	virtual ~SCMD3AA() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_ADD_TALENT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	int16 a_tltId ;
	int8 b_tltLv ;

};


class SCMD3AAFactory: public MessageFactory
{
public :

	virtual ~SCMD3AAFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD3AA();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_ADD_TALENT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD3AAHandler 
{
public:
	static uint32 Execute(SCMD3AA* pPacket) ;
};

#endif 