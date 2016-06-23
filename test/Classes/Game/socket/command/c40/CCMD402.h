#ifndef _CCMD402_H_
#define _CCMD402_H_

/** 
 * @author shenzhiqiang
 * @version 1.1.7.0
 * @description �ͻ�������-��Ը
CMSG_EGG_PLEGE = 0x402
����� <- �ͻ���, ���ṹ:
Uint8		��Ը����(1������Ը��/2ʥ����Ը��)
Uint16		��Ը����(1��/10��/50��)
 * @data 2012-3-26 ����11:56:14 
 * 
 */ 

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class CCMD402 : public Packet
{
public:
	CCMD402()
	{
	}
	virtual ~CCMD402() {}


	virtual bool	Write()
	{
		writeByte(a_type);
		writeShort(b_num);
		return true;
	}

public :
	virtual PacketID_t getPacketID() const { return CMSG_EGG_PLEGE;}

	virtual	int32		GetMessageSize( ) const { return 0;}
	
	int8 a_type;
	int16 b_num;
};



class CCMD402Factory: public MessageFactory
{
public :

	virtual ~CCMD402Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_EGG_PLEGE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

#endif