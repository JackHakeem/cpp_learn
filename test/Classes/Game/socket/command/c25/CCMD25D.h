/**
*   客户端请求玩家排名信息
*   CMSG_WORLD_RANK_PLAYER_INFO_REQUEST = 0X25D (),
*   客户端->服务端, 包结构
*   Uint8:	排行榜类型
*   Int32:    玩家ID 
**/

#ifndef _CCMD25D_H_
#define _CCMD25D_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD25D : public Packet
{
public:

    CCMD25D()
    {
        a_type = 0;
        b_playerId = 0;
    }

    virtual ~CCMD25D() {}

    virtual bool Write();

    virtual PacketID_t getPacketID() const { return CMSG_WORLD_RANK_PLAYER_INFO_REQUEST; }

    virtual int32 GetMessageSize() { return 0; }

public:

    int8    a_type;
    int32   b_playerId;
};

class CCMD25DFactory : public MessageFactory
{
public:

    virtual ~CCMD25DFactory() {}

    virtual Packet* CreateMessage() { return 0; }

    virtual PacketID_t GetPacketID() const { return CMSG_WORLD_RANK_PLAYER_INFO_REQUEST; }

    virtual uint32 GetMessageMaxSize() const { return 0; }

};

#endif
