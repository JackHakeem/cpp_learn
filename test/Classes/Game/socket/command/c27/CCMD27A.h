/** 队员位置调整请求
CMSG_WORLD_GROUPADJ = 0x27A 
客户端->服务端, 包结构
Uint16		副本ID
Uint16		战队ID
Uint8		原位置
Uint8		新位置*/

#ifndef _CCMD27A_H_
#define _CCMD27A_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD27A : public Packet
{
public:
	CCMD27A():a_fbId(0) , b_teamId(0),c_oldPos(0),d_newPos(0)
	{}
	virtual ~CCMD27A() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_GROUPADJ;}

	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	uint16 a_fbId;
	uint16 b_teamId;
	uint8 c_oldPos;
	uint8 d_newPos;
};

bool CCMD27A::Write()
{
	writeShort(a_fbId);
	writeShort(b_teamId);
	writeByte(c_oldPos);
	writeByte(d_newPos);
	return true;
}


class CCMD27AFactory: public MessageFactory
{
public :
	
	virtual ~CCMD27AFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_GROUPADJ;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif