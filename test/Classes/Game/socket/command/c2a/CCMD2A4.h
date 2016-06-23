/**客户端请求俑兵属性鉴定*/

#ifndef _CCMD2A4_H_
#define _CCMD2A4_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2A4 : public Packet
{
public:
	CCMD2A4() {}
	virtual ~CCMD2A4() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_MOD_IDENTIFY_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	int32 a_mercId;
	uint8 b_useItem;

};

class CCMD2A4Factory: public MessageFactory
{
public :

	virtual ~CCMD2A4Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_MOD_IDENTIFY_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif