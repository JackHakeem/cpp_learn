/**
星魂空间的星魂更新
 */

#ifndef _SCMD465_H_
#define _SCMD465_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "SCMD464_466Node.h"

class SCMD465 : public Packet
{
public:

	SCMD465()
	{
	}

	virtual ~SCMD465() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_XHBANK_ITEM_UPDATE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	std::list<SCMD464_465Node>		a_XHList;
};


class SCMD465Factory: public MessageFactory
{
public :
	
	virtual ~SCMD465Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD465();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_XHBANK_ITEM_UPDATE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD465Handler 
{
public:
	static uint32 Execute(SCMD465* pPacket) ;
};

#endif