/**
 *GMSG_COMMU_GUILD_DONATE_BY_IMPOSE = 0x324()		// 这是由征收产生的捐献，通知客户端
Int:		银币数 
 */
#ifndef _SCMD324_H_
#define _SCMD324_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD324 : public Packet
{
public:
	SCMD324() {}
	virtual ~SCMD324() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_GUILD_DONATE_BY_IMPOSE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int a_silver;
};


class SCMD324Factory: public MessageFactory
{
public :

	virtual ~SCMD324Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD324();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_GUILD_DONATE_BY_IMPOSE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD324Handler 
{
public:
	static uint32 Execute(SCMD324* pPacket) ;
};

#endif