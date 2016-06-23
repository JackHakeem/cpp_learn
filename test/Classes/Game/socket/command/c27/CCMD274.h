/** 新建战队请求
CMSG_WORLD_GROUPCREATE = 0x274 	
客户端->服务端, 包结构
Uint16		副本ID
Uint8		限制类型（0:无限制，1：公会）
Int8		自动开战人数（-1为手动开战）*/

#ifndef _CCMD274_H_
#define _CCMD274_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD274 : public Packet
{
public:
	CCMD274():a_fbId(0) , b_type(0) , c_auto(0)
	{}
	virtual ~CCMD274() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_GROUPCREATE;}

	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	uint16 a_fbId;
	uint8 b_type;
	int c_auto;
};

bool CCMD274::Write()
{
	writeShort(a_fbId);
	writeByte(b_type);
	writeInt(c_auto);
	return true;
}


class CCMD274Factory: public MessageFactory
{
public :
	
	virtual ~CCMD274Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_GROUPCREATE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif