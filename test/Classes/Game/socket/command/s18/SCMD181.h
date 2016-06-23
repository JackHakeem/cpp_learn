#ifndef _SCMD181_H_
#define _SCMD181_H_
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
* agreement number: 0 x181;
* s-> c;
* Int8: whether to strengthen success, 0 success, 1-6 failure, the code says the reason for failure:
* 1: the maximum level can be improved, 2: more than protagonist level, 3: downgraded below minimum level, 4: improved function in CD,
* 5: not enough silver, 6: not enough gold, 7: the server the strengthening of the probability has changed, 8: improved failure.
* Int8: equipment in what position, on 1, 2 package;
* Int8: equipment in the body position or in the position of the parcel, must and the first bit corresponding
* Int8: whether to use the VIP welfare to strengthen equipment, 0 no, 1 is
* Int8: the current strengthening probability
* Int8: the next aggrandizement trend is up or down, and 0 drop, 1 litre
* Int: role ID
* Int8: enhanced level
*/	
class SCMD181 : public Packet
{
public:
	SCMD181() {}
	virtual ~SCMD181() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_ITEM_STRENGTHEN_RESULT; }

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_isSuccess;
	int8 b_typeSit;
	int8 c_sit;
	int8 d_isVIP;
	int8 e_probability;
	int8 f_strengChange;
	int32 g_roleID;
	int8 h_strengLevle;

};


class SCMD181Factory: public MessageFactory
{
public :

	virtual ~SCMD181Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD181();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_ITEM_STRENGTHEN_RESULT; }

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD181Handler 
{
public:
	static uint32 Execute(SCMD181* pPacket) ;
};

#endif 