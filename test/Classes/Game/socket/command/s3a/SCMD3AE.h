#ifndef _SCMD3AE_H_
#define _SCMD3AE_H_

/**
	����˷��ع�����
	WMSG_WORLD_TOWER_INSPIRE	= 0X3AE
	�����->�ͻ���, ���ṹ
	Uint8		������������ʧ�ܣ������ɹ����������䣨���������Ϣ��
	Uint8		����ٷֱ�(����)
	Uint32		�´�����������������ֵ
 */

#include "socket/network/Packet.h"
#include "socket/message/MessageFactory.h"
#include "socket/message/SocketCMDConst.h"
#include "BaseType.h"

class SCMD3AE : public Packet
{
public:
	SCMD3AE()
	{
		a_result = 0;
		b_inspire = 0;
		c_nextPrac = 0;
	}
	~SCMD3AE()
	{
	}

	virtual int32 Execute();

	virtual bool Read();

	virtual PacketID_t getPacketID()const { return WMSG_WORLD_TOWER_INSPIRE;}

public:
	int8 a_result;
	int8 b_inspire;
	int c_nextPrac;
};


class SCMD3AEFactory : public MessageFactory
{
	virtual Packet* CreateMessage() {return new SCMD3AE();}

	virtual PacketID_t GetPacketID()const {return WMSG_WORLD_TOWER_INSPIRE;}

	virtual uint32 GetMessageMaxSize()const {return 0;}

};


class SCMD3AEHandler 
{
public:
	static uint32 Execute(SCMD3AE *pPacket) ;
};

#endif
