#ifndef  _SCMD2C3_H__
#define  _SCMD2C3_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
 *��������ظ�
WMSG_WORLD_TRADE_ATTACK_REP= 0x2C3 (707)
�ͻ���->�����, ���ṹ
Uint32		�������ID
Byte		�����0����������ɹ�����ʼս������0����������ʧ�ܼ���ԭ��
 
 */
class SCMD2C3 : public Packet
{
public:
	SCMD2C3() {}
	virtual ~SCMD2C3() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_TRADE_ATTACK_REP;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int a_id;
	int8 b_result;
};


class SCMD2C3Factory: public MessageFactory
{
public :

	virtual ~SCMD2C3Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2C3();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_TRADE_ATTACK_REP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2C3Handler 
{
public:
	static uint32 Execute(SCMD2C3* pPacket) ;
};
#endif