#ifndef _SCMD186_H_
#define _SCMD186_H_
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
Server activated crystal
WMSG_WORLD_ACTIVATE_CRYSTAL = 0x186 (390)
The service side -> client package structure
byte 2: successfully activated
the byte crystal type (ID)
byte crystal level
 */

class SCMD186 : public Packet
{
public:
	SCMD186() {}
	virtual ~SCMD186() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_ACTIVATE_CRYSTAL	;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint8 a_result;	//2: successfully activated
	uint8 b_id;		//Crystal type (ID)
	uint8 c_level;	//Crystal Level


};


class SCMD186Factory: public MessageFactory
{
public :

	virtual ~SCMD186Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD186();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_ACTIVATE_CRYSTAL	;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD186Handler 
{
public:
	static uint32 Execute(SCMD186* pPacket) ;
};

#endif 