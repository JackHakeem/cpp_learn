/**
 * WMSG_SILVERMINE_MOVE_RES = 0x2E8 
�����->�ͻ���, ���ṹ
	Uint32		Ŀ������ID
	Uint8		�ƶ������0���ƶ���Ŀ������1��ԭ��ͣ����
	Uint32		�ж�CD
	Uint8		�Ƿ��ж�CD�У�0����1����  2 ����ս���� 
	Uint32      �ڿ�CD
	Uint8       �Ƿ��ڿ�CD�У�0����1���ǣ� 
	Uint32      ��ǰ��������
 */
#ifndef _SCMD2E8_H_
#define _SCMD2E8_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD2E8 : public Packet
{
public:
	SCMD2E8() {}
	virtual ~SCMD2E8() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_SILVERMINE_MOVE_RES;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint32 a_mineId;
	int8 b_moveRet;
	uint32 c_actionCD;
	int8 d_inCD;
	uint32 e_digCD;
	int8 f_inDigCD;
	uint32 h_online;
};


class SCMD2E8Factory: public MessageFactory
{
public :

	virtual ~SCMD2E8Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2E8();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_SILVERMINE_MOVE_RES;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2E8Handler 
{
public:
	static uint32 Execute(SCMD2E8* pPacket) ;
};

#endif