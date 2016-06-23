/** 
 * @author shenzhiqiang
 * @version 1.1.7.0
 * @description ����˷���-��Ը��Ӧ��
WMSG_EGG_PLEGE = 0x403
����� -> �ͻ���, ���ṹ:
Uint8		��Ӧ��
����:0�ɹ�/1��Ҳ���/2��ʱ�ֿ�ռ䲻��/3ϵͳ�ڲ�����

 * @data 2012-3-26 ����11:58:02 
 * 
 */ 
#ifndef _SCMD403_H_
#define _SCMD403_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD403 : public Packet
{
public:
	SCMD403()
	{
	}

	virtual ~SCMD403() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_EGG_PLEGE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_type;
};


class SCMD403Factory: public MessageFactory
{
public :
	
	virtual ~SCMD403Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD403();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_EGG_PLEGE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD403Handler 
{
public:
	static uint32 Execute(SCMD403* pPacket) ;
};

#endif