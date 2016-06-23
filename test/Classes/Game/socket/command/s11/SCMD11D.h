/**
* The map has been completed progress information
WMSG_WORLD_MAP_PROCESS = 0x11D (285), / / ​​map has complete schedule information
The service side -> client package structure
short: map Id
byte: map perfectly status: 0 No clearance, a clearance, two layer perfect, three all perfect
byte: whether to obtain a perfect reward
short: the progress of the number of
short: to complete the progress number
byte: Star (0-3)
short: the number of random progress
short: random progress of the ID
 
		 * 
		 */	

#ifndef _SCMD11D_H_
#define _SCMD11D_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

struct SCMD11DNode
{
	int16 a_process;
	int8  b_starLev;

	SCMD11DNode()
	{
		a_process = 0;
		b_starLev = 0;
	}
};

struct SCMD11DNode2
{
	int16 mgId;

	SCMD11DNode2()
	{
		mgId = 0;
	}
};


class SCMD11D : public Packet
{
public:
	SCMD11D()
	{
		a_mapId = 0;
		b_mapStatus = 0;
		c_isAward = 0;
	}

	virtual ~SCMD11D() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_MAP_PROCESS;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16	a_mapId;
	int8	b_mapStatus;
	int8	c_isAward;
	std::vector<SCMD11DNode>d_finisheds;
	std::vector<SCMD11DNode2>e_randMg;
};


class SCMD11DFactory: public MessageFactory
{
public :
	
	virtual ~SCMD11DFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD11D();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_MAP_PROCESS;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD11DHandler 
{
public:
	static uint32 Execute(SCMD11D* pPacket) ;
};

#endif