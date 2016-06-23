#ifndef _SCMD39C_H_
#define _SCMD39C_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD39C : public Packet
{
public:
	SCMD39C() {}

	virtual ~SCMD39C() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return 0;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	/**server responses all PVP list
	 WMSG_COMMU_PVP_ARENACONTEST_LIST = 0x39C(921),	
	server->client pack
	Short			
	Int				account ID
	Byte			ring level
	Byte			ring type
	Char			role name
	 **/
	struct SCMD39CNode
	{
		int32	a_accountId;
		int8	b_ringLev;
		int8	c_ringType;
		std::string	d_roleName;
	};

	std::vector<SCMD39CNode> a_mirror;
};


class SCMD39CFactory: public MessageFactory
{
public :

	virtual ~SCMD39CFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD39C();}

	virtual PacketID_t	GetPacketID ()const  {return 0;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD39CHandler 
{
public:
	static uint32 Execute(SCMD39C* pPacket) ;
};

#endif