/**
 * 玩家使用银矿战令牌	
	CMSG_SILVERMINE_TOKEN = 0x2EE 
	客户端->服务端, 包结构
	Uint8		令牌ID——0【袭】；1【扰】；2【驰】；3【查】
	Uint32		目标银矿ID
 */

#ifndef _CCMD2EE_H_
#define _CCMD2EE_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2EE : public Packet
{
public:
	CCMD2EE() 
	{
		a_type = 0;
		b_mineID = 0;
	}

	virtual ~CCMD2EE() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_SILVERMINE_TOKEN;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	int8 a_type;
	uint32 b_mineID;
};


class CCMD2EEFactory: public MessageFactory
{
public :

	virtual ~CCMD2EEFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_SILVERMINE_TOKEN;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif