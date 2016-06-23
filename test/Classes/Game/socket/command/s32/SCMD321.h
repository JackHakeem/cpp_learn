/**��������Ӧ���ս����
WMSG_WORLD_IMPOSE_RESULT = 0x321,(801)
byte		���ճɹ���ʶ��0���ɹ���1��CD��(������ǰ��ÿͻ����ж�)��2��ʣ�����մ���Ϊ�㣨�ͻ���Ҳ����������ǰ�жϣ���3������������գ�ǿ������4�����պ󳬹�����������ޣ�5�����պ󳬹�������ޡ�
Byte		�������ͣ�1����ͨ���գ�2��ǿ������
Uint16      ��һ��ǿ��������
Uint16 		��ͨ����ʣ������������������ͣ������ǿ�����վ���ǿ��������
byte		��ͨ���մ������ƣ������������ͣ������ǿ�����վ���0��
uint16		������մ���
byte		���������ý����Ŀ
uint32		���պ���������������ʧ��Ϊ 0��
uint32		���պ�������������ʧ��Ϊ 0��
uint16 		����Ƽ��ȼ�
uint16 		ÿ��Ŀ��������
**/

#ifndef _SCMD321_H_
#define _SCMD321_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD321 : public Packet
{
public:
	SCMD321() {}
	virtual ~SCMD321() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_IMPOSE_RESULT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_isSuccess;
	int8 b_type;
	uint16 c_levyCost;
	uint16 d_rest;
	int8 e_limit;
	int8 h_luckyGold;
	uint32 i_silver;
	uint32 j_gold;
	uint16 k_uniteLev;
	uint16 l_starNum;
};


class SCMD321Factory: public MessageFactory
{
public :

	virtual ~SCMD321Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD321();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_IMPOSE_RESULT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD321Handler 
{
public:
	static uint32 Execute(SCMD321* pPacket) ;
};

#endif