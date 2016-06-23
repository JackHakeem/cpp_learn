/**
 * ��Ӫս��ս����
 * CMSG_CAMPFIGHT_FIGHT_REQ                        = 0X454, //	��Ӫս��ս����	
 * �ͻ���->�����, ���ṹ
 */

#ifndef _CCMD454_H_
#define _CCMD454_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD454 : public Packet
{
public:
	CCMD454()
	{
	}

	virtual ~CCMD454() {}


	virtual bool	Write()
	{
		return true;
	}
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_CAMPFIGHT_FIGHT_REQ;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
};


class CCMD454Factory: public MessageFactory
{
public :
	
	virtual ~CCMD454Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_CAMPFIGHT_FIGHT_REQ;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 