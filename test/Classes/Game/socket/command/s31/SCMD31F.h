/**
* refresh mercenaries training information to return to pack
WMSG_WORLD_MERCENARY_FOSTER_REFRESH = 0 x31F (799)
The server-> the client, package structure
Byte: success
Int: role ID
Short: achievement (achievement)
Short: physical
Short: intelligence
	 
	 */

#ifndef _SCMD31F_H_
#define _SCMD31F_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD31F : public Packet
{
public:
	SCMD31F() {}
	virtual ~SCMD31F() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_MERCENARY_FOSTER_REFRESH;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	int8 a_isSuccess;
	int32 b_figureId;
	int16 c_strength;
	int16 d_stamina;
	int16 e_intellect;
};


class SCMD31FFactory: public MessageFactory
{
public :

	virtual ~SCMD31FFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD31F();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_MERCENARY_FOSTER_REFRESH;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD31FHandler 
{
public:
	static uint32 Execute(SCMD31F* pPacket) ;
};

#endif