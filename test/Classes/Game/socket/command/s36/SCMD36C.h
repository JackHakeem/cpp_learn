#ifndef _SCMD36C_H_
#define _SCMD36C_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD36C : public Packet
{
public:
	SCMD36C()
	{
		a_popularity = 0;
		b_straightNum = 0;
		c_star1 = 0;
		d_star2 = 0;
		e_star3 = 0;
		f_star4 = 0;
		g_star5 = 0;
	}

	virtual ~SCMD36C() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_AREANA_WORSHIPINFO_REQ;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	/**	server responses client winning streak info
		WMSG_WORLD_PVP_QUALIFYING_STAR = 0x361(865),
		server->client pack
		Int			reputaion
		Int			num
		Byte		star1£¨0 not open£¬1 win£¬2 lose£©
		Byte		star2
		Byte		star3
		Byte		star4
		Byte		star5
    **/
	int32	a_popularity;
	int32	b_straightNum;
	int8	c_star1;
	int8	d_star2;
	int8	e_star3;
	int8	f_star4;
	int8	g_star5;
};


class SCMD36CFactory: public MessageFactory
{
public :

	virtual ~SCMD36CFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD36C();}

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_AREANA_WORSHIPINFO_REQ;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD36CHandler 
{
public:
	static uint32 Execute(SCMD36C* pPacket) ;
};

#endif