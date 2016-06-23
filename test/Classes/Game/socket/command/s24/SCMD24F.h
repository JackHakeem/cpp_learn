#ifndef _SCMD24F_H_
#define _SCMD24F_H_

#include "../../network/Packet.h"
#include "../../message/MessageFactory.h"
#include "../../message/SocketCMDConst.h"

struct 	SCMD24FNode
{
	int16 a_type;
	int8 b_num;
};

class SCMD24F : public Packet
{
public:
	SCMD24F() 
	{
	}
	virtual ~SCMD24F() {}


	virtual bool Read();
public :
	virtual int32 Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_FREE_TOKEN_INFO_RESP;}

	virtual	int32 GetMessageSize( ) const { return 0;}

public:
	std::list<SCMD24FNode> a_tokens;
};


class SCMD24FFactory: public MessageFactory
{
public :
	virtual ~SCMD24FFactory ()  {}

	virtual Packet* CreateMessage () {return new SCMD24F();}

	virtual PacketID_t GetPacketID ()const  {return WMSG_WORLD_FREE_TOKEN_INFO_RESP;}

	virtual uint32 GetMessageMaxSize ()const  {return 0;}

};

class SCMD24FHandler 
{
public:
	static uint32 Execute(SCMD24F* pPacket) ;
};
#endif