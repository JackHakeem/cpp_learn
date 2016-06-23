/**
*   服务端返回排行榜列表信息
*   GMSG_WORLD_RANK_LIST_RESP = 0X25C (),
*   服务端->客户端, 包结构
*   Uint8:	排行榜类型
*   Uint8:	等级区域（0:0-40，1:41-60，2:61-80，3:81-100，4:101-120）
*   Uint16: 玩家自己的排名(若榜上无名，则排名为0)
*   Uint16：排行榜数量
*   Uint16:  排名列表起始位置
*   Short：		排名数量
*       Uint16：排名序号
*       Int32:   玩家ID
*       String:	玩家名称
*       String:  公会名(若无加入公会，则返回空)
*       Uint32:	Value(装备总分/名声值/战斗力/进度ID)
*       uint8:	主角等级
*       uint16:	主角原型ID
**/

#ifndef _SCMD25C_H_
#define _SCMD25C_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

struct SCMD25CNode
{
    SCMD25CNode()
    {
        a_rank = 0;
        b_playerId = 0;
        c_name = "";
        d_guild = "";
        e_grade = 0;
        f_lev = 0;
        g_roleId = 0;
        h_trend = 0;
    }

    int16       a_rank;
    int32       b_playerId;
    std::string c_name;
    std::string d_guild;
    int32       e_grade;
    int8        f_lev;
    int32       g_roleId;
    int16       h_trend;

};

class SCMD25C : public Packet
{
public:
    SCMD25C() {}

    virtual ~SCMD25C() {}

    virtual bool Read();

public:

    virtual int32 Execute();

    virtual PacketID_t getPacketID() { return GMSG_WORLD_RANK_LIST_RESP; }

    virtual int32 GetMessageSize() const { return 0; }

public:

    int8 a_type;

    int16 b_myRank;

    int16 c_num;

    int16 d_begin;

    std::vector<SCMD25CNode> e_ranks;

};

class SCMD25CFactory : public MessageFactory
{
public:

    virtual ~SCMD25CFactory() {}

    virtual Packet* CreateMessage() { return new SCMD25C(); }

    virtual PacketID_t GetPacketID() const { return GMSG_WORLD_RANK_LIST_RESP; }

    virtual uint32 GetMessageMaxSize() const { return 0; }

};

class SCMD25CHandler
{
public:
    static uint32 Execute(SCMD25C* pPacket);
};

#endif 
