#ifndef _SCMD3B7_H_
#define _SCMD3B7_H_

/**
	����˷���ս�������Ϣ(����ս�ɹ�������Ӧ��¥�㽱��)
	WMSG_WORLD_RESULT_CLIMB_TOWER	= 0X3B7,	
	�����->�ͻ���, ���ṹ
	Uint8		�Ƿ����ǰ����һ��(1,�ǣ�������)
	Uint8		�Ƿ񴥷��齱���ͻ��˵����齱��壩
	Uint8		��ѽ���ʣ�����
	Uint8		���ս������������Ѵ����⣩
	Uint8		��սǰ��¥��
	Uint8		��ս���¥��(����ǰ����ս�ɹ����Ѿ�������߲㣬�ͻ��˷���������; ��ʧ���������սǰ��¥��)
	Uint8		��ʷ��ߴ���¥��
	Uint32		��ǰ���ڲ�Ĺ���ID
	Uint16		��ǰ��Ĺ̶���������
	Uint32��    ����ID (����100Ϊ��Ʒ�����ID)
	Uint32	    ��������
	Uint8		�Ƿ���ʾ��ǰ������boss(0,��)
	Uint32 		�²����ID������Ϊ�����ҽ�������Ϊ����
	Uint16		�²�̶���������
	Uint32��    ����ID (����100Ϊ��Ʒ�����ID)
	Uint32	    ��������
	Uint8		�Ƿ���ʾ�²�����boss(0,��)
	Uint8		����ٷֱȣ�������
	Uint32		�´�����������������ֵ
 */

#include "socket/network/Packet.h"
#include "socket/message/MessageFactory.h"
#include "socket/message/SocketCMDConst.h"
#include "BaseType.h"
#include "SCMD3B5.h"

class SCMD3B7 : public Packet
{
public:
	SCMD3B7()
	{
		a_isWin = 0;
		b_isLottery = 0;
		c_numFree = 0;
		d_numPay = 0;
		e_beforeFloor = 0;
		f_afterFloor = 0;
		g_maxFloor = 0;
		h_curMonsterId = 0;
		j_showCurBoss = 0;
		k_nextMonsterId = 0;
		m_showNextBoss = 0;
		n_inspire = 0;
		o_inspirePrac = 0;
	}
	~SCMD3B7()
	{
	}

	virtual int32 Execute();

	virtual bool Read();

	virtual PacketID_t getPacketID()const { return WMSG_WORLD_RESULT_CLIMB_TOWER;}

public:

	int8 a_isWin;
	int8 b_isLottery;
	int8 c_numFree;
	int8 d_numPay;
	int8 e_beforeFloor;
	int8 f_afterFloor;
	int8 g_maxFloor;
	int h_curMonsterId;
	std::list<SCMD3B5Node> i_curRewards;
	int8 j_showCurBoss;
	int k_nextMonsterId;
	std::list<SCMD3B5Node> l_nextRewards;
	int8 m_showNextBoss;
	int8 n_inspire;
	int o_inspirePrac;
};


class SCMD3B7Factory : public MessageFactory
{
	virtual Packet* CreateMessage() {return new SCMD3B7();}

	virtual PacketID_t GetPacketID()const {return WMSG_WORLD_RESULT_CLIMB_TOWER;}

	virtual uint32 GetMessageMaxSize()const {return 0;}

};


class SCMD3B7Handler 
{
public:
	static uint32 Execute(SCMD3B7 *pPacket) ;
};

#endif
