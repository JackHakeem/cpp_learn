/**
* Player Mobile Broadcasting (to confirm the players move command)
* WMSG_WORLD_TRADEMOVE = 12f, / / player mobile broadcasting (to confirm the players move command)
* Server -> client package structure
* Short: the number of path points
* Short: 1X coordinate point
* Short: 1Y coordinate point
* ... (Other information)
 */

#ifndef _SCMD12F_H_
#define _SCMD12F_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "../s11/SCMD111.h"


class SCMD12F : public Packet
{
public:
	SCMD12F()
	{
		a_AccountId = 0;
		b_startX = 0;
		c_startY = 0;
	}

	virtual ~SCMD12F() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_TRADEMOVE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int32 a_AccountId;
	int16 b_startX;
	int16 c_startY;

	std::vector<SCMD111Node>d_path;
};


class SCMD12FFactory: public MessageFactory
{
public :
	
	virtual ~SCMD12FFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD12F();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_TRADEMOVE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD12FHandler 
{
public:
	static uint32 Execute(SCMD12F* pPacket) ;
};

#endif