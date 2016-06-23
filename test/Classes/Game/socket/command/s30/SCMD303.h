/**
* Recruitment of mercenaries return package
* WMSG_WORLD_MERCENARY_RECRUIT = 0x303
* Server -> client package structure
* Uint16 mercenaries ID.
* Uint32, mercenary unique ID
 */

#ifndef _SCMD303_H_
#define _SCMD303_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD303 : public Packet
{
public:
	SCMD303()
	{
		a_prototypeId = 0;
		b_mercenaryId = 0;
	}

	virtual ~SCMD303() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_MERCENARY_RECRUIT;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16	a_prototypeId;
	int32	b_mercenaryId;
};


class SCMD303Factory: public MessageFactory
{
public :
	
	virtual ~SCMD303Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD303();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_MERCENARY_RECRUIT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD303Handler 
{
public:
	static uint32 Execute(SCMD303* pPacket) ;
};

#endif