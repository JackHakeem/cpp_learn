#ifndef _CCMD19E_H_
#define _CCMD19E_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/* * 
414) request for CD player cleared gold COINS 
*/ 

class CCMD19E : public Packet
{
public:
	CCMD19E() {}
	virtual ~CCMD19E() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_CLEAR_CD_COST;}

	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	int8 a_type;
};


class CCMD19EFactory: public MessageFactory
{
public :

	virtual ~CCMD19EFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_CLEAR_CD_COST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};
#endif 