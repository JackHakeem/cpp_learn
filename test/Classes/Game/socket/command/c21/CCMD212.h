#ifndef _CCMD212_H_
#define _CCMD212_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
Player requests crystal required for the upgrade CD time
CMSG_WORLD_REQ_UPGRADE_TIME = 0x200 (412)
Client -> server, the package structure
Byte type of request, 1: passive skills; 2: formation; 3: Crystal
Short skills (formation / crystal) ID
 */

class CCMD212 : public Packet
{
public:
	CCMD212() {}
	virtual ~CCMD212() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_COMMU_FRIENDS_VIEW_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :


	std::string a_name;


};


class CCMD212Factory: public MessageFactory
{
public :

	virtual ~CCMD212Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_FRIENDS_VIEW_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif