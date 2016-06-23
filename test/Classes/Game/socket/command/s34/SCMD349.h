
/**  
349Node
WMSG_WORLD_OPEN_UPGRADE_BALL_PANEL = 0x349 (791)
*/

#ifndef _SCMD349_H_
#define _SCMD349_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD349 : public Packet
{
public:
	SCMD349()
	{
		a_blue = 0;
		b_purple = 0;
		c_red = 0;
	}
	virtual ~SCMD349() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_OPEN_UPGRADE_BALL_PANEL;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	struct SCMD349node2
	{
		int8 a_spType;
		int16 b_spLv;
		int32 c_exp;
		int32 d_lvUpExp;
	};

	struct SCMD349node1
	{
		int32 a_mercId;
		int16 b_merOId;
		int32 c_jadeId;
		int16 d_jadeOId;
		std::vector<SCMD349node2> e_spList;
	};

	int32 a_blue;
	int32 b_purple;
	int32 c_red;
	std::vector<SCMD349node1> d_MercList;

};


class SCMD349Factory: public MessageFactory
{
public :

	virtual ~SCMD349Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD349();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_OPEN_UPGRADE_BALL_PANEL;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD349Handler 
{
public:
	static uint32 Execute(SCMD349* pPacket) ;
};

#endif 