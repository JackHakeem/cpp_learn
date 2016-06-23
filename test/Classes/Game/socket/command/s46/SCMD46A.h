/**
Ó¶±øÐÇ»ê¸üÐÂ
 */

#ifndef _SCMD46A_H_
#define _SCMD46A_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "SCMD46ANode.h"

class SCMD46A : public Packet
{
public:

	SCMD46A()
	{
	}

	virtual ~SCMD46A() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_XHROLE_ITEM_UPDATE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	std::list<SCMD46ANode>		a_XHEquipList;
};


class SCMD46AFactory: public MessageFactory
{
public :
	
	virtual ~SCMD46AFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD46A();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_XHROLE_ITEM_UPDATE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD46AHandler 
{
public:
	static uint32 Execute(SCMD46A* pPacket) ;
};

#endif