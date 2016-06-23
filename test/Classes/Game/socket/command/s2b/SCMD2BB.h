#ifndef  _SCMD2BB_H__
#define  _SCMD2BB_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
	�������̻�Ӧ
	WMSG_WORLD_TRADE_END_RESP= 0x2BB (699)
	�ͻ���->�����, ���ṹ
	short: 		�������: 0�����ɹ�, >0Ϊ����ʧ��, �������ErrorCode
	int:			�����������
	byte:		�Ƿ�������� (0 �ޱ���1 С����2 ��)
	int:		����
	byte:       �Ƿ�˫��ʱ�� (0 �� 1 ��)
 */

class SCMD2BB : public Packet
{
public:
	SCMD2BB() {}
	virtual ~SCMD2BB() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_TRADE_END_RESP;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16 a_err;
	int b_silver;
	int8 c_bj;
	int d_pop;
	int8 e_doubleTime;
};


class SCMD2BBFactory: public MessageFactory
{
public :

	virtual ~SCMD2BBFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2BB();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_TRADE_END_RESP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2BBHandler 
{
public:
	static uint32 Execute(SCMD2BB* pPacket) ;
};
#endif