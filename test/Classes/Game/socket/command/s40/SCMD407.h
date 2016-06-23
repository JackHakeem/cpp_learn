/** 
 * @author shenzhiqiang
 * @version 1.1.7.0
 * @description ����˷���-����Ӧ��
WMSG_EGG_OPEN = 0x405
����� -> �ͻ���, ���ṹ:
Uint8		��Ӧ��
����:0�ɹ�/1�����ռ䲻��/2��������/3�������/4��������/5ϵͳ�ڲ�����

 * @data 2012-3-26 ����11:58:19 
 * 
 */ 
#ifndef _SCMD407_H_
#define _SCMD407_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD407 : public Packet
{
public:
	SCMD407()
	{
	}

	virtual ~SCMD407() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_EGG_PICK;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_type;
};


class SCMD407Factory: public MessageFactory
{
public :
	
	virtual ~SCMD407Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD407();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_EGG_PICK;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD407Handler 
{
public:
	static uint32 Execute(SCMD407* pPacket) ;
};

#endif