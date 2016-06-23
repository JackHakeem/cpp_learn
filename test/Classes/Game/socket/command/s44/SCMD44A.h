/**
 
 */
#ifndef _SCMD44A_H_
#define _SCMD44A_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "model/gong/vo/GongRanking.h"
#include "SCMD44ANode.h"

class SCMD44A : public Packet
{
public:
	SCMD44A() {
	}
	virtual ~SCMD44A() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_GONG_MB_UIINFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:


	std::string a_heroname;
	uint32 b_accountid;
	uint32 c_score;
	uint32 d_beMBCount;
	std::vector<SCMD44ANode> e_names;
};


class SCMD44AFactory: public MessageFactory
{
public :

	virtual ~SCMD44AFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD44A();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_GONG_MB_UIINFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD44AHandler 
{
public:
	static uint32 Execute(SCMD44A* pPacket) ;
};

#endif