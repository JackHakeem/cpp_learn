/**
 * 
 * buy to return to training position bag
 WMSG_WORLD_TRAIN_BUY_PLACE_RESP = Ox354, (852)
 The server-> the client, package structure
 Uint8: buy success: 0, beyond the biggest can buy queue number; 1, not enough gold; 2, buy success
 Int8: the existing training position number
 */

#ifndef _SCMD354_H_
#define _SCMD354_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD354 : public Packet
{
public:
	SCMD354() {}
	virtual ~SCMD354() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_TRAIN_BUY_PLACE_RESP;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_result;
	int8 b_posiNum;
};


class SCMD354Factory: public MessageFactory
{
public :

	virtual ~SCMD354Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD354();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_TRAIN_BUY_PLACE_RESP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD354Handler 
{
public:
	static uint32 Execute(SCMD354* pPacket) ;
};

#endif 