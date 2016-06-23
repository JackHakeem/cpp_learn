
#ifndef HLQS_IPAD_SCMD13B_h
#define HLQS_IPAD_SCMD13B_h

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD13B : public Packet
{
public:
	CCMD13B(){}
	virtual ~CCMD13B() {}
    
    
	virtual bool	Write();	//virtual int32 	Execute() {return 0;};

    
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_BATTLE_PK_START;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
    
    public :
	uint32 a_accountId;
    
};


class CCMD13BFactory: public MessageFactory
{
    public :
	
	virtual ~CCMD13BFactory ()  {}
    
	virtual Packet*		CreateMessage () {return 0;};
    
	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_BATTLE_PK_START;}
    
	virtual uint32		GetMessageMaxSize ()const  {return 0;}
    
};

#endif
