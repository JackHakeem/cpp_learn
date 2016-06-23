/**
 * 客户端获取下一次银矿战开启时间	
CMSG_SILVERMINE_GETOPENTIME = 0x2EC 
客户端->服务端, 包结构（无）
 */

#ifndef _CCMD2EC_H_
#define _CCMD2EC_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD2EC : public Packet
{
public:
	CCMD2EC() 
	{
	}

	virtual ~CCMD2EC() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_SILVERMINE_GETOPENTIME;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
};


class CCMD2ECFactory: public MessageFactory
{
public :

	virtual ~CCMD2ECFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_SILVERMINE_GETOPENTIME;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif