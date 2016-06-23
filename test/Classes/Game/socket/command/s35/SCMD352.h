/**
* character training information to return to pack
* WMSG_WORLD_TRAIN_INFO_RESP = Ox352
* the server-> the client, package structure
* Int16: gold tu fly prices
* Int8: training position number / / buy a training a want how much gold
* int16: several training roles
*	int32: role ID
*	int8: training mode
*	int32: training over time
 */ 


#ifndef _SCMD352_H_
#define _SCMD352_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD352 : public Packet
{
public:
	SCMD352() {}
	virtual ~SCMD352() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_TRAIN_INFO_RESP;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16 a_goldPrice;  

	struct SCMD352Node
	{
		int32 a_playerId;
		int8 b_mode;
		int32 c_time;
	};

	std::list<SCMD352Node> b_players;
};


class SCMD352Factory: public MessageFactory
{
public :

	virtual ~SCMD352Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD352();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_TRAIN_INFO_RESP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD352Handler 
{
public:
	static uint32 Execute(SCMD352* pPacket) ;
};

#endif 