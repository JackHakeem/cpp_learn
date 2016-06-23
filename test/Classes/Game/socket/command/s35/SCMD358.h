/**
* end to return to training package
* WMSG_WORLD_TRAIN_END_RESP = Ox358
* the server-> the client, package structure
* int32: role ID
* int8: processing results (0 failure, 1 success)
*
* / / * *
* change training mode to return to pack
* WMSG_WORLD_TRAIN_CHANGE_MODEL_RESP = Ox358
* the server-> the client, package structure
* int32: role ID
* int8: training mode
 */ 
#ifndef _SCMD358_H_
#define _SCMD358_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD358 : public Packet
{
public:
	SCMD358() {}
	virtual ~SCMD358() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_TRAIN_END_RESP;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int32 a_playerId;
	int8 b_result;
};


class SCMD358Factory: public MessageFactory
{
public :

	virtual ~SCMD358Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD358();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_TRAIN_END_RESP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD358Handler 
{
public:
	static uint32 Execute(SCMD358* pPacket) ;
};

#endif 