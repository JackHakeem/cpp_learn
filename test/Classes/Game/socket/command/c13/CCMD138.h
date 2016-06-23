
#ifndef HLQS_IPAD_SCMD138_h
#define HLQS_IPAD_SCMD138_h

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD138 : public Packet
{
public:
	CCMD138(){}
	CCMD138(int8 type) { _type = type; }
	virtual ~CCMD138() {}
    
    
	virtual bool	Write();	//virtual int32 	Execute() {return 0;};

    
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_BATTLE_EXIT;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
    
    public :
    int8 _type;
    
};


class CCMD138Factory: public MessageFactory
{
    public :
	
	virtual ~CCMD138Factory ()  {}
    
	virtual Packet*		CreateMessage () {return 0;};
    
	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_BATTLE_EXIT;}
    
	virtual uint32		GetMessageMaxSize ()const  {return 0;}
    
};

#endif
