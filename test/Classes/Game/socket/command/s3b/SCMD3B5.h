#ifndef _SCMD3B5_H_
#define _SCMD3B5_H_

/**
	����˷��ش򿪻����������Ϣ
	WMSG_WORLD_APPLY_CLIMB_TOWER	= 0X3B5,		
	�����->�ͻ���, ���ṹ
	Uint8		��ѽ���ʣ�����
	Uint8		���ս������������Ѵ����⣩
	Uint8		��ǰ����¥��
	Uint8		��ʷ��ߴ���¥��
	Uint32		��ǰ���ڲ�Ĺ���ID
	Uint16		��ǰ��Ĺ̶���������
		Uint32�� ����ID (����100Ϊ��Ʒ�����ID)
		Uint32	��������
	Uint8		�Ƿ���ʾ��ǰ������boss(0,��)
	Uint32 		�²����ID������Ϊ�����ҽ�������Ϊ����
	Uint16		�²�̶���������
		Uint32�� ����ID (����100Ϊ��Ʒ�����ID)
		Uint32	��������
	Uint8		�Ƿ���ʾ�²�����boss(0,��)
	Uint8		����ٷֱȣ�����0-100��
	Uint32		�´�����������������ֵ
 */

#include "socket/network/Packet.h"
#include "socket/message/MessageFactory.h"
#include "socket/message/SocketCMDConst.h"
#include "BaseType.h"


struct SCMD3B5Node
{
	int a_rewardId;
	int b_rewardNum;
	SCMD3B5Node()
	{
		a_rewardId = 0;
		b_rewardNum = 0;
	}
};

class SCMD3B5 : public Packet
{
public:
	SCMD3B5()
	{
		a_numFree = 0;
		b_numPay = 0;
		c_curFloor = 0;
		d_maxFloor = 0;
		e_curMonsterId = 0;

		g_showCurBoss = 0;
		h_nextMonsterId = 0;

		j_showNextBoss = 0;
		k_inspire = 0;
		l_inspirePrac = 0;
	}
	~SCMD3B5()
	{
	}

	virtual int32 Execute();

	virtual bool Read();

	virtual PacketID_t getPacketID()const { return WMSG_WORLD_APPLY_CLIMB_TOWER;}

public:

	int8 a_numFree;
	int8 b_numPay;
	int8 c_curFloor;
	int8 d_maxFloor;
	int e_curMonsterId;
	std::list<SCMD3B5Node> f_curRewards;
	int8 g_showCurBoss;
	int h_nextMonsterId;
	std::list<SCMD3B5Node> i_nextRewards;
	int8 j_showNextBoss;
	int8 k_inspire;
	int l_inspirePrac;
};


class SCMD3B5Factory : public MessageFactory
{
	virtual Packet* CreateMessage() {return new SCMD3B5();}

	virtual PacketID_t GetPacketID()const {return WMSG_WORLD_APPLY_CLIMB_TOWER;}

	virtual uint32 GetMessageMaxSize()const {return 0;}

};


class SCMD3B5Handler 
{
public:
	static uint32 Execute(SCMD3B5 *pPacket) ;
};

#endif
