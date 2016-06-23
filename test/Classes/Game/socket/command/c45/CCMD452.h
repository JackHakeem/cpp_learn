/**
 * 进入阵营战申请
 * CMSG_CAMPFIGHT_QUIT_REQ                         = 0X452, //	阵营战离开申请	
 * 客户端->服务端, 包结构
 */

#ifndef _CCMD452_H_
#define _CCMD452_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD452 : public Packet
{
public:
	CCMD452()
	{
	}

	virtual ~CCMD452() {}


	virtual bool	Write()
	{
		return true;
	}
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_CAMPFIGHT_QUIT_REQ;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
};


class CCMD452Factory: public MessageFactory
{
public :
	
	virtual ~CCMD452Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_CAMPFIGHT_QUIT_REQ;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 