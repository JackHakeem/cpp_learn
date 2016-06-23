

#ifndef _CCMD1D5_H_
#define _CCMD1D5_H_
	/**
	// 请求捐献银币界面数据 CMSG_COMMU_GUILD_DONATE_REQ
	 **/
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD1D5 : public Packet
{
public:
	CCMD1D5() {}
	virtual ~CCMD1D5() {}


	virtual bool	Write()
	{
		return true;
	}

public :
	virtual PacketID_t getPacketID() const { return CMSG_COMMU_GUILD_DONATE_REQ;}

	virtual	int32		GetMessageSize( ) const { return 0;}
};

class CCMD1D5Factory: public MessageFactory
{
public :

	virtual ~CCMD1D5Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_GUILD_DONATE_REQ;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif