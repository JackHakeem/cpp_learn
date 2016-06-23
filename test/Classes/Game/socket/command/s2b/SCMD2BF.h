#ifndef  _SCMD2BF_H__
#define  _SCMD2BF_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
 *�����̶���Ϣ
WMSG_WORLD_TRADE_INFO= 0x2BF (703)
�ͻ���->�����, ���ṹ
uint32		�������Id
short		�����Ʒ����(0-400)
short		�����Ʒ����(100/200/300/400)
byte		�Ƿ�ɱ���� 
 * short		���̾���������
 */ 

class SCMD2BF : public Packet
{
public:
	SCMD2BF() {}
	virtual ~SCMD2BF() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_TRADE_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int a_playerId;
	int16 b_goodsNum;
	int16 c_totalNum;
	int8 d__robOrNot;
	int16 e_energyCost;
};


class SCMD2BFFactory: public MessageFactory
{
public :

	virtual ~SCMD2BFFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2BF();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_TRADE_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2BFHandler 
{
public:
	static uint32 Execute(SCMD2BF* pPacket) ;
};
#endif