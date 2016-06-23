/**
 * 阵营战信息申请
 * CMSG_CAMPFIGHT_INFO_REQ                         = 0X458, //	阵营战信息申请
 * 客户端->服务端, 包结构
 */

#ifndef _CCMD458_H_
#define _CCMD458_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD458 : public Packet
{
public:
	CCMD458()
	{
	}

	virtual ~CCMD458() {}


	virtual bool	Write()
	{
		return true;
	}
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_CAMPFIGHT_INFO_REQ;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
};


class CCMD458Factory: public MessageFactory
{
public :
	
	virtual ~CCMD458Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_CAMPFIGHT_INFO_REQ;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 