/*
 * CMSG_WORLD_ADDTRADEPLAYER = 0x12c ()
 */

#ifndef _CCMD12C_H_
#define _CCMD12C_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "../s11/SCMD111.h"

class CCMD12C : public Packet
{
public:
    CCMD12C()
    {
    }

    virtual ~CCMD12C() {}

    virtual bool Write()
	{
		std::vector<SCMD111Node>::iterator iter = d_path.begin();
		int16 size = (int16)d_path.size();
		writeShort(size);
		for(; iter != d_path.end(); ++iter)
		{
			writeShort(iter->a_x);
			writeShort(iter->b_y);
		}

		return true;
	}

    virtual PacketID_t getPacketID() const { return CMSG_WORLD_ADDTRADEPLAYER; }

    virtual int32 GetMessageSize() const { return 0; }

public:
	//int16 b_startX;
	//int16 c_startY;

	std::vector<SCMD111Node>d_path;
};

class CCMD12CFactory : public MessageFactory
{
public:
    
    virtual ~CCMD12CFactory () {}

    virtual Packet* CreateMessage () { return 0; }

    virtual PacketID_t getPacketID () const { return CMSG_WORLD_ADDTRADEPLAYER; }

    virtual uint32 GetMessageMaxSize () const { return 0; }
};


#endif
