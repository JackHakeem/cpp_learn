/**
星魂背包物品更新
 */

#ifndef _SCMD464_H_
#define _SCMD464_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "SCMD464_466Node.h"

class SCMD464 : public Packet
{
public:

	SCMD464()
	{
		
	}

	virtual ~SCMD464() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_XHBAG_ITEM_UPDATE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	std::list<SCMD464_465Node>		a_XHList;
};


class SCMD464Factory: public MessageFactory
{
public :
	
	virtual ~SCMD464Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD464();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_XHBAG_ITEM_UPDATE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD464Handler 
{
public:
	static uint32 Execute(SCMD464* pPacket) ;
};

#endif