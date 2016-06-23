/**
 * ������Ӫս����
 * CMSG_CAMPFIGHT_ENTER_REQ	= 0x450,			// ������Ӫս����	
 * �ͻ���->�����, ���ṹ
 * short:		��ǰ�����X����
 * short:		��ǰ�����Y����
 */

#ifndef _CCMD450_H_
#define _CCMD450_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD450 : public Packet
{
public:
	CCMD450()
	{
	}

	virtual ~CCMD450() {}


	virtual bool	Write()
	{
		return true;
	}
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_CAMPFIGHT_ENTER_REQ;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
};


class CCMD450Factory: public MessageFactory
{
public :
	
	virtual ~CCMD450Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_CAMPFIGHT_ENTER_REQ;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 