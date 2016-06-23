/*
 * CMSG_WORLD_BATTLE_REPORT_MONSTERGROUP
 */

#ifndef _CCMD136_H_
#define _CCMD136_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD136 : public Packet
{
public:
    CCMD136()
    {
    }

    virtual ~CCMD136() {}

    virtual bool Write();

    virtual PacketID_t getPacketID() const { return CMSG_WORLD_BATTLE_REPORT_MONSTERGROUP; }

    virtual int32 GetMessageSize() const { return 0; }

public:
    int32 a_monsterId; 
};

class CCMD136Factory : public MessageFactory
{
public:

    virtual ~CCMD136Factory() {}

    virtual Packet* CreateMessage() { return 0; }

    virtual PacketID_t getPacektID() const { return CMSG_WORLD_BATTLE_REPORT_MONSTERGROUP; }

    virtual uint32 GetMessageMaxSize() const { return 0; }
};

#endif
