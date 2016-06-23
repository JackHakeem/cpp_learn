#ifndef _SCMD39A_H_
#define _SCMD39A_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD39A : public Packet
{
public:
	SCMD39A() {}

	virtual ~SCMD39A() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return CMSG_WORLD_PVP_QUALIFYING_REQUEST;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	/**client requests PVP list
	 * CMSG_WORLD_PVP_QUALIFYING_REQUEST = 0x398(920)
	 * Byte			level
       Short	    		
	   Int			account ID
	   Short		figure ID
	   Byte			crystal level
       Byte			rankiing
       Char			role name
	 * */

	int8	a_arenaLev;

	struct SCMD39ANode
	{
		int32	a_accountId;
		int16	b_frigureId;
		int8	c_crystalLev;
		int8	d_ranking;
		std::string	e_roleName;
		int32	f_threat;
	};
};


class SCMD39AFactory: public MessageFactory
{
public :

	virtual ~SCMD39AFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD39A();}

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_PVP_QUALIFYING_REQUEST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD39AHandler 
{
public:
	static uint32 Execute(SCMD39A* pPacket) ;
};

#endif