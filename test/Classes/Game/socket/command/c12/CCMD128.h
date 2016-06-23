/*
 * CMSG_WORLD_PROCESS_GET_PERFECT = 0x128 (296)
 */

#ifndef _CCMD128_H_
#define _CCMD128_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD128 : public Packet
{
public:
    CCMD128()
    {
        a_mapID = 0;
    }

    virtual ~CCMD128() {}

    virtual bool Write();

    virtual PacketID_t getPacketID() const { return CMSG_WORLD_PROCESS_GET_PERFECT; }

    virtual int32 GetMessageSize() const { return 0; }

public:
    int16 a_mapID;
};

class CCMD128Factory : public MessageFactory
{
public:
    
    virtual ~CCMD128Factory () {}

    virtual Packet* CreateMessage () { return 0; }

    virtual PacketID_t getPacketID () const { return CMSG_WORLD_PROCESS_GET_PERFECT; }

    virtual uint32 GetMessageMaxSize () const { return 0; }
};


#endif
