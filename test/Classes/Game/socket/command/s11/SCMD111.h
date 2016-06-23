/**
* Player Mobile Broadcasting (to confirm the players move command)
* WMSG_WORLD_MOVE = 0x111, / / player mobile broadcasting (to confirm the players move command)
* Server -> client package structure
* Short: the number of path points
* Short: 1X coordinate point
* Short: 1Y coordinate point
* ... (Other information)
 */

#ifndef _SCMD111_H_
#define _SCMD111_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

struct SCMD111Node
{
	int16 a_x;
	int16 b_y;

	SCMD111Node()
	{
		a_x = 0;
		b_y = 0;
	}
};

class SCMD111 : public Packet
{
public:
	SCMD111()
	{
		a_AccountId = 0;
		b_startX = 0;
		c_startY = 0;
	}

	virtual ~SCMD111() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_MOVE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int32 a_AccountId;
	int16 b_startX;
	int16 c_startY;

	std::vector<SCMD111Node>d_path;
};


class SCMD111Factory: public MessageFactory
{
public :
	
	virtual ~SCMD111Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD111();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_MOVE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD111Handler 
{
public:
	static uint32 Execute(SCMD111* pPacket) ;
};

#endif