/**
* Players out of the vision
* WMSG_WORLD_TRADE_PLAYER_VIEW_OUT = 0x0f2,
* Server -> client package structure
* Short: the number of players
* Int: Account id
* ... (The other players information)

 */

#ifndef _SCMD0F2_H_
#define _SCMD0F2_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

struct SCMD0F2Node
{
	int32 a_AccountId;

	SCMD0F2Node()
	{
		a_AccountId = 0;
	}
};

class SCMD0F2 : public Packet
{
public:
	SCMD0F2()
	{
	}

	virtual ~SCMD0F2() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_TRADE_PLAYER_VIEW_OUT;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	std::vector<SCMD0F2Node>a_Accounts;
};


class SCMD0F2Factory: public MessageFactory
{
public :
	
	virtual ~SCMD0F2Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD0F2();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_TRADE_PLAYER_VIEW_OUT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD0F2Handler 
{
public:
	static uint32 Execute(SCMD0F2* pPacket) ;
};

#endif