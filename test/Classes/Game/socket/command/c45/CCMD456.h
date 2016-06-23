/**
 * 阵营战取消参战申请
 * CMSG_CAMPFIGHT_CANCEL_REQ                       = 0X456, //	阵营战取消参战申请	
 * 客户端->服务端, 包结构
 */

#ifndef _CCMD456_H_
#define _CCMD456_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD456 : public Packet
{
public:
	CCMD456()
	{
	}

	virtual ~CCMD456() {}


	virtual bool	Write()
	{
		return true;
	}
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_CAMPFIGHT_CANCEL_REQ;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
};


class CCMD456Factory: public MessageFactory
{
public :
	
	virtual ~CCMD456Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_CAMPFIGHT_CANCEL_REQ;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 