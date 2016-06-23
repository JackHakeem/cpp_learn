/* 
Request role to return to training package
* WMSG_WORLD_TRAIN_RESP = Ox36A
* the server-> the client, package structure
* int32: role ID
* int32: training over time
	*/ 

#ifndef _SCMD35A_H_
#define _SCMD35A_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD35A : public Packet
{
public:
	SCMD35A() {}
	virtual ~SCMD35A() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_TRAIN_RESP;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int32 a_playerId;
	int32 b_time;
};


class SCMD35AFactory: public MessageFactory
{
public :

	virtual ~SCMD35AFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD35A();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_TRAIN_RESP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD35AHandler 
{
public:
	static uint32 Execute(SCMD35A* pPacket) ;
};

#endif 