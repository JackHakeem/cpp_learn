/**
 * ����ƶ�һ����֤
 * CMSG_WORLD_MOVE_STEP			= 0x114,			// ����ƶ�һ����֤	
 * �ͻ���->�����, ���ṹ
 * short:		��ǰ�����X����
 * short:		��ǰ�����Y����
 */

#ifndef _CCMD114_H_
#define _CCMD114_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD114 : public Packet
{
public:
	CCMD114()
	{
		a_x = 0;
		b_y = 0;
	}

	virtual ~CCMD114() {}


	virtual bool	Write();
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_MOVE_STEP;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	int16 a_x;
	int16 b_y;
};


class CCMD114Factory: public MessageFactory
{
public :
	
	virtual ~CCMD114Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_MOVE_STEP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 