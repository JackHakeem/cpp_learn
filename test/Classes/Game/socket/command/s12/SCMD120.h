/**
* WMSG_WORLD_COMPLETE_PROCESS = 0x120 (288), / / ​​to complete a progress
* Server -> client package structure
* Short: map Id
* Short: the progress of Id
 */

#ifndef _SCMD120_H_
#define _SCMD120_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD120 : public Packet
{
public:
	SCMD120()
	{
		a_mapId = 0;
		b_process = 0;
	}

	virtual ~SCMD120() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_COMPLETE_PROCESS;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16 a_mapId;
	int16 b_process;
};


class SCMD120Factory: public MessageFactory
{
public :
	
	virtual ~SCMD120Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD120();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_COMPLETE_PROCESS;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD120Handler 
{
public:
	static uint32 Execute(SCMD120* pPacket) ;
};

#endif