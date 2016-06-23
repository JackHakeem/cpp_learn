/**
 * ����ƶ�һ����֤
 * CMSG_WORLD_TRADER_MOVE_STEP	= 0x0F0,			// ����ƶ�һ����֤	
 * �ͻ���->�����, ���ṹ
 * short:		��ǰ�����X����
 * short:		��ǰ�����Y����
 */

#ifndef _CCMD0F0_H_
#define _CCMD0F0_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD0F0 : public Packet
{
public:
	CCMD0F0()
	{
		a_x = 0;
		b_y = 0;
	}

	virtual ~CCMD0F0() {}


	virtual bool	Write()
	{
		writeShort(a_x);
		writeShort(b_y);

		return true;
	}
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_WORLD_TRADER_MOVE_STEP;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	int16 a_x;
	int16 b_y;
};


class CCMD0F0Factory: public MessageFactory
{
public :
	
	virtual ~CCMD0F0Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_WORLD_TRADER_MOVE_STEP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 