/**
*   ����˷�����Ӫս������Ϣ
*   WMSG_CAMPFIGHT_INFO_RES                         = 0X459, //	��Ӫս��Ϣ����
*   �����->�ͻ���, ���ṹ
*   Uint16��ʤ��
*   uint16:	�����ʷ��ʤ����
*   uint16:	�ܵĻ������
*   Uint32:	�ܵĻ������
*   uint16:	��ҵ�״̬
**/

#ifndef _SCMD459_H_
#define _SCMD459_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD459 : public Packet
{
public:
	SCMD459() {}

	virtual ~SCMD459() {}

	virtual bool Read();

public:

	virtual int32 Execute();

	virtual PacketID_t getPacketID() { return WMSG_CAMPFIGHT_INFO_RES; }

	virtual int32 GetMessageSize() const { return 0; }

public:
	uint16 a_score;
	uint16 b_hisContiWinTms;
	uint16 c_sumPop;
	uint32 d_sumSilver;
	uint16 e_state;
};

class SCMD459Factory : public MessageFactory
{
public:

	virtual ~SCMD459Factory() {}

	virtual Packet* CreateMessage() { return new SCMD459(); }

	virtual PacketID_t GetPacketID() const { return WMSG_CAMPFIGHT_INFO_RES; }

	virtual uint32 GetMessageMaxSize() const { return 0; }

};

class SCMD459Handler
{
public:
	static uint32 Execute(SCMD459* pPacket);
};

#endif 