/**团战副本战队列表请求
CMSG_WORLD_GROUPLIST_REQ = 0x270 
客户端->服务端, 包结构
Uint16		团战副本ID*/

#ifndef _CCMD270_H_
#define _CCMD270_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD270 : public Packet
{
public:
	CCMD270():a_fbId(0)
	{}
	virtual ~CCMD270() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_GROUPLIST_REQ;}

	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	uint16 a_fbId;
};

bool CCMD270::Write()
{
	writeShort(a_fbId);
	return true;
}


class CCMD270Factory: public MessageFactory
{
public :
	
	virtual ~CCMD270Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_GROUPLIST_REQ;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif