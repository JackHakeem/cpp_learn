/**
*怪物组合PVE攻略列表	
*WMSG_COMMU_BATTLE_REPORT_MONSTERGROUP = 0x225 (549),	
*服务端->客户端, 包结构
*int:			怪物组合ID	
*short:			攻略条数
*int:		战斗ID
*int：		账号ID
*byte:		水晶等级 
*char:		名字
*/	

#ifndef _SCMD137_H_
#define _SCMD137_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD137 : public Packet
{
public:
    SCMD137() {}
    virtual ~SCMD137() {}

    virtual bool Read();

public:
    virtual int32 Execute();

    virtual PacketID_t getPacketID() const { return WMSG_WORLD_BATTLE_REPORT_MONSTERGROUP; }

    virtual int32 GetMessageSize() const { return 0; }

public:
    struct SCMD137Node
    {
        uint32 a_battleId1;
        uint32 b_battleId2;
        int32 c_acountId;
        int8 d_lev;
        std::string e_playerName;
    };

    int32 a_groupId;
    std::vector<SCMD137Node> b_SCMD137Node;
};

class SCMD137Factory : public MessageFactory
{
public:

    virtual ~SCMD137Factory() {}

    virtual Packet* CreateMessage() { return new SCMD137(); }

    virtual PacketID_t GetPacketID() const { return WMSG_WORLD_BATTLE_REPORT_MONSTERGROUP; }

    virtual uint32 GetMessageMaxSize() const { return 0; }
};

class SCMD137Handler
{
public:
    static uint32 Execute(SCMD137* pPacket);
}; 

#endif

