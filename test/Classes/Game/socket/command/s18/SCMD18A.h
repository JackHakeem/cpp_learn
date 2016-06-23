#ifndef _SCMD18A_H_
#define _SCMD18A_H_
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
WMSG_WORLD_LOGIN_CRYSTAL_FEEDBACK = 0x18A (394)
Client -> server-side package structure (none)
The number of short crystal
Byte crystal type
Byte crystal level
 */

class SCMD18A : public Packet
{
public:
	SCMD18A() {}
	virtual ~SCMD18A() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_LOGIN_CRYSTAL_FEEDBACK	;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	//uint16 SCMD18ANodeNum;
	 struct SCMD18ANode
	 {
            uint8   a_id ;
		    uint8   b_level ;
	 };

	 std::list<SCMD18ANode> a_items;


};


class SCMD18AFactory: public MessageFactory
{
public :

	virtual ~SCMD18AFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD18A();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_LOGIN_CRYSTAL_FEEDBACK	;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD18AHandler 
{
public:
	static uint32 Execute(SCMD18A* pPacket) ;
};

#endif 