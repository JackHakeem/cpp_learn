/**
	����BOSS��͹�����
	WMSG_WORLDBOSS_INSPIRE_RES = 0X2CC			
	�����->�ͻ���, ���ṹ
	Uint8			������
	�������룺
	0�����ɹ�
	1������ѽ���
	2���������������
	3������Ҳ���
	4������������
	5������������ʧ��
	6����ϵͳ�ڲ�����

*/

#ifndef _SCMD2CC_H_
#define _SCMD2CC_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD2CC : public Packet
{
public:
	SCMD2CC() {}
	virtual ~SCMD2CC() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLDBOSS_INSPIRE_RES;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint8 a_result;		// ������ 
};


class SCMD2CCFactory: public MessageFactory
{
public :

	virtual ~SCMD2CCFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2CC();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLDBOSS_INSPIRE_RES;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2CCHandler 
{
public:
	static uint32 Execute(SCMD2CC* pPacket) ;
};

#endif