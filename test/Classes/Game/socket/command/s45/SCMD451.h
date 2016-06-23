/**
*   ����˷�����Ӫս˫����Ա��Ϣ
*   WMSG_CAMPFIGHT_ENTER_RES = 0X451,
*   �����->�ͻ���, ���ṹ
*   int32: ��½��Ӫ����ֵ 
*         0���ɹ���
*         -1����Ӫս������ÿ���
*         -2����Ӫս�ʱ��δ��
*         -3����ҵȼ���������ӪսҪ��
*         -4����Ӫս��������
*         -5�����״̬�쳣
*         -6����ʼ����Ӫս��ɫ�쳣
*         -7����ӪID����
*         -8����������쳣
**/

#ifndef _SCMD451_H_
#define _SCMD451_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD451 : public Packet
{
public:
	SCMD451() {}

	virtual ~SCMD451() {}

	virtual bool Read();

public:

	virtual int32 Execute();

	virtual PacketID_t getPacketID() { return WMSG_CAMPFIGHT_ENTER_RES; }

	virtual int32 GetMessageSize() const { return 0; }

public:
	int32  a_res;
};

class SCMD451Factory : public MessageFactory
{
public:

	virtual ~SCMD451Factory() {}

	virtual Packet* CreateMessage() { return new SCMD451(); }

	virtual PacketID_t GetPacketID() const { return WMSG_CAMPFIGHT_ENTER_RES; }

	virtual uint32 GetMessageMaxSize() const { return 0; }

};

class SCMD451Handler
{
public:
	static uint32 Execute(SCMD451* pPacket);
};

#endif 