/**
 * ����ƶ�һ����֤
 * CMSG_WORLD_MOVE_STOP			= 0x115,			// ·�߸��� 277
 * �ͻ���->�����, ���ṹ
 * short:		��ǰ�����X����
 * short:		��ǰ�����Y����
 */

#ifndef _CCMD115_H_
#define _CCMD115_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD115 : public Packet
{
public:
	CCMD115() 
	{
		a_x = 0;
		b_y = 0;
	}

	virtual ~CCMD115() {}


	virtual bool	Write();
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_MOVE_STOP;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	int16 a_x;
	int16 b_y;
};


class CCMD115Factory: public MessageFactory
{
public :
	
	virtual ~CCMD115Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_MOVE_STOP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 