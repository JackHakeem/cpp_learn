#ifndef _CCMD200_H_
#define _CCMD200_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
Player requests crystal required for the upgrade CD time
CMSG_WORLD_REQ_UPGRADE_TIME = 0x200 (412)
Client -> server, the package structure
Byte type of request, 1: passive skills; 2: formation; 3: Crystal
Short skills (formation / crystal) ID
 */

class CCMD200 : public Packet
{
public:
	CCMD200() {}
	virtual ~CCMD200() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_COMMU_FRIENDS_LIST;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :


	int16 a_page;


};


class CCMD200Factory: public MessageFactory
{
public :

	virtual ~CCMD200Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_FRIENDS_LIST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif