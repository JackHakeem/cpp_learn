#ifndef _SCMD1CD_H_
#define _SCMD1CD_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
	/**
	 *退出公会
	GMSG_COMMU_GUILD_QUIT = 0x1CD(),
	Byte		成功标志	// 0 – 成功 / 1 – 失败
	 * @author zhouwenbo
	 * 
	 */	
class SCMD1CD : public Packet
{
public:
	SCMD1CD() {}
	virtual ~SCMD1CD() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_GUILD_QUIT;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

	int8 a_flag;
};


class SCMD1CDFactory: public MessageFactory
{
public :
	
	virtual ~SCMD1CDFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1CD();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_GUILD_QUIT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1CDHandler 
{
public:
	static uint32 Execute(SCMD1CD* pPacket) ;
};

#endif 