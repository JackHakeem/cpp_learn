/**
 * ����BOSS�����ʱ��
 * WMSG_WORLDBOSS_OPENTIME	= 0X2C7
 * �����->�ͻ���, ���ṹ
 * Uint32			�´λ��ʼʱ��
*/

#ifndef _SCMD2C7_H_
#define _SCMD2C7_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD2C7 : public Packet
{
public:
	SCMD2C7() {}
	virtual ~SCMD2C7() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLDBOSS_OPENTIME;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint32 a_nextTime;		// �´�����BOSS�ʱ��
	uint8 b_inTime;			// �Ƿ��ڻ�� 0���� 1��
};


class SCMD2C7Factory: public MessageFactory
{
public :

	virtual ~SCMD2C7Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2C7();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLDBOSS_OPENTIME;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2C7Handler 
{
public:
	static uint32 Execute(SCMD2C7* pPacket) ;
};

#endif