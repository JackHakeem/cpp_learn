#ifndef _SCMD39B_H_
#define _SCMD39B_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD39B : public Packet
{
public:
	SCMD39B() {}

	virtual ~SCMD39B() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return 0;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	/**server responses arena contest list
	 WMSG_COMMU_PVP_ARENACONTEST_REQUEST = 0x39B(920),	
	 server->client pack
	 Short			
	 Int			account ID
	 Short			figure ID
	 Byte			crystal level
	 Byte			ring type
	 Int			award
	 Char			role name
	 **/

	int8	a_rankId;

	struct SCMD39BNode
	{
		int32	a_accountId;
		int16	b_frigureId;
		int8	c_crystalLev;
		int8	d_ringType;
		int32	e_award;
		std::string	f_roleName;
	};
};


class SCMD39BFactory: public MessageFactory
{
public :

	virtual ~SCMD39BFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD39B();}

	virtual PacketID_t	GetPacketID ()const  {return 0;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD39BHandler 
{
public:
	static uint32 Execute(SCMD39B* pPacket) ;
};

#endif