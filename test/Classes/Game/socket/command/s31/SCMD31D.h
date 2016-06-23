/**
* save mercenaries to return to training information pack
WMSG_WORLD_MERCENARY_FOSTER_SAVE = 0 x31D (797)
The server-> the client, package structure
Byte: success
Int: role ID
Short: achievement (achievement)
Short: physical
Short: intelligence
 */

#ifndef _SCMD31D_H_
#define _SCMD31D_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD31D : public Packet
{
public:
	SCMD31D() {}
	virtual ~SCMD31D() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_MERCENARY_FOSTER_SAVE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	int8 a_isSuccess;
	int32 b_figureId;
	int16 c_strength;
	int16 d_stamina;
	int16 e_intellect;
};


class SCMD31DFactory: public MessageFactory
{
public :

	virtual ~SCMD31DFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD31D();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_MERCENARY_FOSTER_SAVE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD31DHandler 
{
public:
	static uint32 Execute(SCMD31D* pPacket) ;
};

#endif