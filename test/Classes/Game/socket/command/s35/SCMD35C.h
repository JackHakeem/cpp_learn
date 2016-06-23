/**
* return to package by leaps and bounds
* WMSG_WORLD_TRAIN_SPEED_UP_RESP = 0 x35C
* the server-> the client, package structure
* int32: role ID
* int32: sudden fly experience value
* Int16: gold tu fly prices
* int32: VIP crit experience value
 */

#ifndef _SCMD35C_H_
#define _SCMD35C_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD35C : public Packet
{
public:
	SCMD35C() {}
	virtual ~SCMD35C() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_TRAIN_SPEED_UP_RESP;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int32 a_playerId;
	int32 b_rapidExp;
	int16 c_goldPrice;
	int32 d_critExp;
};


class SCMD35CFactory: public MessageFactory
{
public :

	virtual ~SCMD35CFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD35C();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_TRAIN_SPEED_UP_RESP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD35CHandler 
{
public:
	static uint32 Execute(SCMD35C* pPacket) ;
};

#endif 