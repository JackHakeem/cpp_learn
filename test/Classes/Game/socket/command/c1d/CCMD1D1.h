

#ifndef _CCMD1D1_H_
#define _CCMD1D1_H_
/**
 * CMSG_COMMU_GUILD_DONATE = 0x1D1 (),					
 * 服务端<-客户端, 包结构
 * Short：	科技ID，
 * Int：		捐献数
 */
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD1D1 : public Packet
{
public:
	CCMD1D1() {}
	virtual ~CCMD1D1() {}


	virtual bool	Write()
	{
		writeShort(a_id);
		writeInt(b_money);
		return true;
	}
public :
	virtual PacketID_t getPacketID() const { return CMSG_COMMU_GUILD_DONATE;}

	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	int16 a_id;
	int b_money;
};

class CCMD1D1Factory: public MessageFactory
{
public :

	virtual ~CCMD1D1Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_GUILD_DONATE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif