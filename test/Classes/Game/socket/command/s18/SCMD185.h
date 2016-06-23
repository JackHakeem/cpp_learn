#ifndef _SCMD185_H_
#define _SCMD185_H_
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
Server response crystal upgrade results
WMSG_WORLD_UPGRADE_CRYSTAL_RESULT = 0x185 (389)
The service side -> client package structure
	 
 */
class SCMD185 : public Packet
{
public:
	SCMD185() {}
	virtual ~SCMD185() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_UPGRADE_CRYSTAL_RESULT	;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	 
	uint8   a_result ;  //Success, 0: success 1: more than can be upgraded upper limit
	short	b_id ;            //  Crystal type (ID)
	uint8   c_level ;    //Crystal Level

};


class SCMD185Factory: public MessageFactory
{
public :

	virtual ~SCMD185Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD185();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_UPGRADE_CRYSTAL_RESULT	;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD185Handler 
{
public:
	static uint32 Execute(SCMD185* pPacket) ;
};

#endif 