/**
	客户端请求排行榜列表信息
	CMSG_WORLD_RANK_LIST_REQUEST = 0X25B (),
	客户端->服务端, 包结构
	Uint8:	排行榜类型(0:装备排行；1：名声排行；2:战斗力排行；)
	Uint8:	等级区域（0:0-40，1:41-60，2:61-80，3:81-100）
	Uint16:  排名列表起始位置
	Uint16:  排名列表截止位置 
 */

#ifndef _CCMD25B_H_
#define _CCMD25B_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD25B : public Packet
{
public:
    CCMD25B()
    {
		a_type = 0;
        //b_lev = 0;
        c_begin = 0;
        d_end = 0;
    }

    virtual ~CCMD25B() {}

    virtual bool Write();

    virtual PacketID_t getPacketID() const { return CMSG_WORLD_RANK_LIST_REQUEST; }

    virtual int32 GetMessageSize() const { return 0; }

public:

	uint8 a_type;
    //int8 b_lev;
    int16 c_begin;
    int16 d_end;
};

class CCMD25BFactory : public MessageFactory
{
public:

    virtual ~CCMD25BFactory () {}

    virtual Packet*     CreateMessage() { return 0; }

    virtual PacketID_t  getPacketID() const { return CMSG_WORLD_RANK_LIST_REQUEST; }

    virtual uint32      GetMessageMaxSize() const { return 0; }

};

#endif 

