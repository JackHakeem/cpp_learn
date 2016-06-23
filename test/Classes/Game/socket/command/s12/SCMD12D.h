/**
* Player Mobile Broadcasting (to confirm the players move command)
* WMSG_WORLD_CREATETRADEPLAYER = 12d, / / player mobile broadcasting (to confirm the players move command)
* Server -> client package structure
* Short: the number of path points
* Short: 1X coordinate point
* Short: 1Y coordinate point
* ... (Other information)
 */

#ifndef _SCMD12D_H_
#define _SCMD12D_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "../s11/SCMD11A.h"


class SCMD12D : public Packet
{
public:
	SCMD12D()
	{
		//a_AccountId = 0;
		//b_startX = 0;
		//c_startY = 0;
	}

	virtual ~SCMD12D() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_CREATETRADEPLAYER;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	//int32 a_AccountId;
	//int16 b_startX;
	//int16 c_startY;

	//std::vector<SCMD111Node>d_path;
	SCMD11ANode a_node;
};


class SCMD12DFactory: public MessageFactory
{
public :
	
	virtual ~SCMD12DFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD12D();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_CREATETRADEPLAYER;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD12DHandler 
{
public:
	static uint32 Execute(SCMD12D* pPacket) ;
};

#endif