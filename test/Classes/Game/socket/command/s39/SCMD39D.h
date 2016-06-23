#ifndef _SCMD39D_H_
#define _SCMD39D_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD39D : public Packet
{
public:
	SCMD39D() {}

	virtual ~SCMD39D() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_PVP_REPORT_LIST;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	/**server responses PVP report list
	 * WMSG_WORLD_PVP_ARENACONTEST_LIST = 0x39D
	 * server->client pack structure

	   Uint32		time
	   Uint8		is Challenger
	   String		enemy name
       Uint8		is win
       Short		rank
	   Uint64		battle id
	 * */

	struct SCMD39DNode
	{
		int32		a_time;
		int8		b_isChallenge;
		std::string c_enemyName;
		int8		d_isSucess;
		int16		e_rank;
		uint32		f_fightingId1;
		uint32		g_fightingId2;
	};

	std::vector<SCMD39DNode> a_pvpReport;
};


class SCMD39DFactory: public MessageFactory
{
public :

	virtual ~SCMD39DFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD39D();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_PVP_REPORT_LIST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD39DHandler 
{
public:
	static uint32 Execute(SCMD39D* pPacket) ;
};

#endif