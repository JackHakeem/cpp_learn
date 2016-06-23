#ifndef _CCMD2D6_H_
#define _CCMD2D6_H_
/**
 *CMSG_WORLD_ENCHANT = 0x2D6 （726）
clent->server, struct
Uint8		位置类型（背包，身上）
Uint8 		位置
Uint32 		物品唯一ID
Uint8		是否使用VIP魔化，0，不使用；3，VIP3
 */

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2D6 : public Packet
{
public:
	CCMD2D6() {}
	virtual ~CCMD2D6() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const { return CMSG_WORLD_ENCHANT;}

	virtual	int32		GetMessageSize( ) const { return 0;}
	
	int8 a_type;
	int8 b_sit;
	int c_id;
	int8 d_vip;
};

bool CCMD2D6::Write()
{
	writeByte( a_type );
	writeByte( b_sit );
	writeInt( c_id );
	writeByte( d_vip );

	return true;
}


class CCMD2D6Factory: public MessageFactory
{
public :

	virtual ~CCMD2D6Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_ENCHANT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif