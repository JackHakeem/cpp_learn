/**
* Players out of the vision
* WMSG_WORLD_PLAYER_VIEW_OUT = 0x113,
* Server -> client package structure
* Short: the number of players
* Int: Account id
* ... (The other players information)

 */

#ifndef _SCMD113_H_
#define _SCMD113_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

struct SCMD113Node
{
	int32 a_AccountId;

	SCMD113Node()
	{
		a_AccountId = 0;
	}
};

class SCMD113 : public Packet
{
public:
	SCMD113()
	{
	}

	virtual ~SCMD113() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_PLAYER_VIEW_OUT;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	std::vector<SCMD113Node>a_Accounts;
};


class SCMD113Factory: public MessageFactory
{
public :
	
	virtual ~SCMD113Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD113();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_PLAYER_VIEW_OUT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD113Handler 
{
public:
	static uint32 Execute(SCMD113* pPacket) ;
};

#endif