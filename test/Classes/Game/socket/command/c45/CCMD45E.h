/**
 * ��Ӫս��������
 * CMSG_CAMPFIGHT_INSPIRE_REQ                      = 0X45E, // ��Ӫս��������
 * �ͻ���->�����, ���ṹ
 * int8 ���跽ʽ 0 �� ��ҹ��� 1����������
 */

#ifndef _CCMD45E_H_
#define _CCMD45E_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class CCMD45E : public Packet
{
public:
	CCMD45E()
	{
	}

	virtual ~CCMD45E() {}


	virtual bool	Write()
	{
		writeByte(a_mod);
		return true;
	}
public :
	//virtual int32 	Execute() {return 0;};

	virtual PacketID_t getPacketID() const  { return CMSG_CAMPFIGHT_INSPIRE_REQ;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
public:
	int8 a_mod;
};


class CCMD45EFactory: public MessageFactory
{
public :
	
	virtual ~CCMD45EFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_CAMPFIGHT_INSPIRE_REQ;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

//class CCMD101Handler 
//{
//public:
//	static uint32 Execute(CCMD101* pMessage) ;
//};

#endif 