
#ifndef HLQS_IPAD_SCMD134_h
#define HLQS_IPAD_SCMD134_h

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD134 : public Packet
{
public:
	CCMD134(){}
	virtual ~CCMD134() {}
    
    
	virtual bool	Write();	//virtual int32 	Execute() {return 0;};

    
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_BATTLE_REPORT_REQUEST;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
    
    public :
	uint32 a_battleId1;//int64分成两个int
	uint32 b_battleId2;
    
};


class CCMD134Factory: public MessageFactory
{
    public :
	
	virtual ~CCMD134Factory ()  {}
    
	virtual Packet*		CreateMessage () {return 0;};
    
	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_BATTLE_REPORT_REQUEST;}
    
	virtual uint32		GetMessageMaxSize ()const  {return 0;}
    
};

#endif
