/**
 *
 Delivery to the client talent skills information list
 WMSG_WORLD_Req_Talent = 0 x3c9 (969)
 The server-> the client, package structure
 The number Uint16 skills
	Uint16 skills ID
	Uint8 skill level
 */

#ifndef _SCMD3C9_H_
#define _SCMD3C9_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

struct SCMD3C9Node
{
	int16 a_talentId;
	int8 b_talentLv;

	SCMD3C9Node()
	{
		a_talentId = 0;
		b_talentLv = 0;
	}
}; 


class SCMD3C9 : public Packet
{
public:
	SCMD3C9() {}
	virtual ~SCMD3C9() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_Req_Talent;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	std::vector<SCMD3C9Node> a_TalentArr;
	 
	 
};


class SCMD3C9Factory: public MessageFactory
{
public :

	virtual ~SCMD3C9Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD3C9();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_Req_Talent;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD3C9Handler 
{
public:
	static uint32 Execute(SCMD3C9* pPacket) ;
};

#endif 