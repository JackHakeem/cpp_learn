/**
*   服务端返回玩家排名信息
*   GMSG_WORLD_RANK_PLAYER_INFO_RESP = 0X25E (),
*   服务端->客户端, 包结构
*   Uint8:	类型
*   uint32:	玩家ID
*   uint16:	装备数组
*      uint16:	装备原形ID
*      uint8:	强化等级
*      uint16: 体格(魔化属性)
*      uint16: 腕力(魔化属性)
*      uint16: 智力(魔化属性)
**/

#ifndef _SCMD25E_H_
#define _SCMD25E_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

struct SCMD25ENode
{
    SCMD25ENode()
    {
        a_id = 0;
        b_lev = 0;
        c_stamina = 0;
        d_wrist = 0;
        e_intellect = 0;
    }

    int16   a_id;
    int8    b_lev;
    int16   c_stamina;
    int16   d_wrist;
    int16   e_intellect;

};

class SCMD25E : public Packet
{
public:
    SCMD25E() 
    {
    }
    virtual ~SCMD25E() {}

    virtual bool Read();

public:
    virtual int32 Execute();

    virtual PacketID_t getPacketID() const { return GMSG_WORLD_RANK_PLAYER_INFO_RESP; }

    virtual int32 GetMessageSize() const { return 0; }

public:
    int8    a_type;
    int32   b_player;
    std::vector<SCMD25ENode> c_equips;
};

class SCMD25EFactory : public MessageFactory
{
public:

    virtual ~SCMD25EFactory() {}

    virtual Packet* CreateMessage() { return new SCMD25E(); }

    virtual PacketID_t GetPacketID() const { return GMSG_WORLD_RANK_PLAYER_INFO_RESP; }

    virtual uint32 GetMessageMaxSize() const { return 0; }

};

class SCMD25EHandler
{
public:
    static uint32 Execute(SCMD25E* pPacket);
};

#endif


