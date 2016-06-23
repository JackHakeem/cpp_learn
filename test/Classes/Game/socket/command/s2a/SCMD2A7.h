/**服务端返回临时鉴定结果*/

#ifndef _SCMD2A7_H_
#define _SCMD2A7_H_

#include "../../network/Packet.h"
#include "../../message/MessageFactory.h"
#include "../../message/SocketCMDConst.h"

class SCMD2A7 : public Packet
{
public:
	SCMD2A7() {}
	virtual ~SCMD2A7() {}


	virtual bool Read();
public :
	virtual int32 Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_SAVE_IDENTIFY;}

	virtual	int32 GetMessageSize( ) const { return 0;}

public:
	
};


class SCMD2A7Factory: public MessageFactory
{
public :
	virtual ~SCMD2A7Factory ()  {}

	virtual Packet* CreateMessage () {return new SCMD2A7();}

	virtual PacketID_t GetPacketID ()const  {return WMSG_WORLD_SAVE_IDENTIFY;}

	virtual uint32 GetMessageMaxSize ()const  {return 0;}

};

class SCMD2A7Handler 
{
public:
	static uint32 Execute(SCMD2A7* pPacket) ;
};
#endif