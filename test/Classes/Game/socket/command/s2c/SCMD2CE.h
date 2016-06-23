/**
���ʹ�ø�����
WMSG_WORLDBOSS_RELIVE = 0X2CE			
�����->�ͻ���, ���ṹ
Uint8			����ģʽ
Uint8			��������
�������룺
0�����ɹ�
1������ѽ���
2������Ҳ���
3����ϵͳ�ڲ�����
*/

#ifndef _SCMD2CE_H_
#define _SCMD2CE_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD2CE : public Packet
{
public:
	SCMD2CE() {}
	virtual ~SCMD2CE() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLDBOSS_RELIVE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint8 a_mode;	// ����ģʽ
	uint8 b_result;	// �������� 0�ɹ� 1��ѽ��� 2��Ҳ��� 3ϵͳ�ڲ�����
};


class SCMD2CEFactory: public MessageFactory
{
public :

	virtual ~SCMD2CEFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2CE();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLDBOSS_RELIVE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2CEHandler 
{
public:
	static uint32 Execute(SCMD2CE* pPacket) ;
};

#endif