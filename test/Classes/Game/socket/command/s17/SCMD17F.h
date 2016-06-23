/*
* server response initialization CD player on the list 

* WMSG_WORLD_LOGIN_CD_FEEDBACK = 0 x17F (383) 
* the server-> the client, package structure 
* short of the number of existing CD 
* byte CD type (ID) 
* byte is in CD 
* uint32 over time
*/
#ifndef _SCMD17F_H_
#define _SCMD17F_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD17F : public Packet
{
public:
	SCMD17F() {};
	virtual ~SCMD17F() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_LOGIN_CD_FEEDBACK;}

	virtual	int32		GetMessageSize( ) const { return 0; }

public:
	struct SCMD17FNode
	{
		int8 a_type;
		int8 b_incd;
		int c_time;
	};

	std::vector<SCMD17FNode> a_cd;
};


class SCMD17FFactory: public MessageFactory
{
public :

	virtual ~SCMD17FFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD17F();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_LOGIN_CD_FEEDBACK;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD17FHandler 
{
public:
	static uint32 Execute(SCMD17F* pPacket) ;
};

#endif