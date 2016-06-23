#ifndef _SCMD361_H_
#define _SCMD361_H_

	/**
		������Ҿ�������Ϣ
		WMSG_WORLD_QUALIFYING_INFO = 0x361(865),
		�����->�ͻ���, ���ṹ
		Uint8		���״̬��0������ս��1�������ƣ�
		Uint32		��ǰ������0~999��
		Uint32		�������
		Uint32		��ʤ��
		Uint32		������սCDʱ��
		Uint32		��������ˢ��CDʱ��
		Uint32		���տ���ս����
		Uint32      �������۸�
		Uint32      �����ѹ������		
		����ս������飺
			Uint32	��λ
			Uint32  ����˺�ID
			string	����
			Uint32	�ȼ�
			Uint16	����ԭ��id
		���������ս������飺
			Int8	ս�������<0:ʧ�ܣ�>0ʤ����
		���5��ս�����飺
			Uint32	ս��ʱ��
			String	��������
			Uint8	��������0�����˽�����1�����˷��أ�
			int8	����ʤ�������С��0ʧ�ܣ�����0ʤ����
			int8	������λ�����С��0�½�������0���䣬����0������
			uint64	ս��ID
	*/

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "SCMD361Node.h"
#include "SCMD361Node2.h"

class SCMD361 : public Packet
{
public:
	SCMD361()
	{
		a_state = 0;
		b_rank = 0;
		c_maxRank = 0;
		d_winstreak = 0;
		e_cd = 0;
		l_refreshcd = 0; //hwj
		f_quota = 0;
		g_price = 0;
		h_buyed = 0;		
	}

	virtual ~SCMD361() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_QUALIFYING_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_state;
	uint32 b_rank;
	uint32 c_maxRank;
	uint32 d_winstreak;
	uint32 e_cd;
	uint32 l_refreshcd;
	uint32 f_quota;
	uint32 g_price;
	uint32 h_buyed;
	

	std::vector<SCMD361Node> i_challengeArr;
	std::vector<int> j_resultArr;
	std::vector<SCMD361Node2> k_reportArr;
};


class SCMD361Factory: public MessageFactory
{
public :

	virtual ~SCMD361Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD361();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_QUALIFYING_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD361Handler 
{
public:
	static uint32 Execute(SCMD361* pPacket) ;
};

#endif