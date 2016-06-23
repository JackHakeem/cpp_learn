/**
 * ����ս��Ϣ����	
WMSG_SILVERMINE_INFO = 0x2E6 
�����->�ͻ���, ���ṹ
uint8	��ǰ�Ƿ�������սʱ�䣨0�����ǣ�1���ǣ�
uint32		�ж�CDʱ�����
uint8		�ж��Ƿ�CD�У�0�����ǣ�1���ǣ�
uint32		�ɿ�CDʱ��
uint8		�ɿ��Ƿ�CD�У�0�����ǣ�1���ǣ�
uint32		��ǰ��������ID
uint32		��ǰ������������
Uint32		��ǰ��������ӳɰٷֱ�
Uint32		��ǰ���ع���ӳɰٷֱ�
Uint8		����0����
Uint8		����1����
uint32      ������������ 
������Ӫ��Ϣ���飺
	Uint32	����ID
	Uint32  ��ǰ����� 
	int8	��ǰռ����ӪID��-1���տ�0~2����ӪID��
	uint8	�Ƿ�˫����0����1���ǣ�
	 * 
	 * 
 */
#ifndef _SCMD2E6_H_
#define _SCMD2E6_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "SCMD2E6Node.h"

class SCMD2E6 : public Packet
{
public:
	SCMD2E6() {}
	virtual ~SCMD2E6() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_SILVERMINE_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	int8 a_intime;
	uint32 b_actionCD;
	int8 c_inActionCD;
	uint32 d_digCD;
	int8 e_inDigCD;
	uint32 f_mineId;
	uint32 g_onMine;
	uint32 h_attPlus;
	uint32 i_defPlus;
	int8 j_token0;
	int8 k_token1;
	uint32 l_silver;
 	int8 m_mojinshi;
	std::list<SCMD2E6Node> m_mineArr;

};


class SCMD2E6Factory: public MessageFactory
{
public :

	virtual ~SCMD2E6Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2E6();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_SILVERMINE_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2E6Handler 
{
public:
	static uint32 Execute(SCMD2E6* pPacket) ;
};

#endif