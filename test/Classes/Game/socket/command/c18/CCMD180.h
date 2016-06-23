/**
* agreement number: 0 x180;
* c-> s;
* Int8: equipment in what position, ITEM_POS_NONE = 0, / / no position
ITEM_POS_BAG = 1, / / parcel
ITEM_POS_BANK = 2, / / warehouse
ITEM_POS_ROLE = 3, / / role body
* Int8: equipment in the body position or in the position of the parcel, must and the first bit corresponding;
* Int8: whether to use the VIP welfare to strengthen equipment, 0 no, 1 is
* Int8: improved upgrade or demoted, 0 drop, 1 to upgrade
* Int8: client the current strengthening probability
* Int: role ID
*/
#ifndef _CCMD180_H_
#define _CCMD180_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD180 : public Packet
{
public:
	CCMD180() {}
	virtual ~CCMD180() {}


	virtual bool	Write();
public :
	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_ITEM_STRENGTHEN;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	int8 a_typeSit;
	int8 b_sit;
	int8 c_isVIP;
	int8 d_strengType;
	int8 e_probability;
	int32 f_roleID;
};


class CCMD180Factory: public MessageFactory
{
public :
	
	virtual ~CCMD180Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_ITEM_STRENGTHEN;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif 