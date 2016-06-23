#ifndef _CCMD21c_H_
#define _CCMD21c_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "CCMD21CNode.h"
/**
	Byte:			ÈËÊý
	   Int£º			ID 
 */

class CCMD21c : public Packet
{
public:
	CCMD21c() {}
	virtual ~CCMD21c() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_COMMU_FRIENDS_APPLY_BAT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :


	
	std::list<CCMD21CNode> a_listNode;

};


class CCMD21cFactory: public MessageFactory
{
public :

	virtual ~CCMD21cFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_FRIENDS_APPLY_BAT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif