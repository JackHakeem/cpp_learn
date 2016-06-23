/**
 *response magic result
WMSG_WORLD_ENCHANT = 0x2D7 ��727��
Uint8		ħ���Ƿ�ɹ���0���ɹ���1��ʧ�ܣ����ڳɹ��ʣ�2�����岻����3��װ��������Ҫ��4��ħ�����Դﵽ����
Uint8		����ɹ�����ħ�����ͣ��ͻ��˶�Ӧ��ħ����������1��0�����1��������2������
Uint32		ʣ�ྦྷ����
Uint8		ǿ���ȼ�
Uint8       ��Ʒ����λ�����ͣ�����/���ϣ�
Uint8 		��Ʒ����λ��
Uint32 		��Ʒ������ٸ��ID���ڱ�����Ϊ0�� 
 */
#ifndef _SCMD2D7_H_
#define _SCMD2D7_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD2D7 : public Packet
{
public:
	SCMD2D7() {}
	virtual ~SCMD2D7() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_ENCHANT;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_type;
	int8 b_attribute;
	int c_sparNum;
	int8 d_streng;
	int8 e_location;
	int8 f_sit;
	int g_roleId;
};


class SCMD2D7Factory: public MessageFactory
{
public :
	
	virtual ~SCMD2D7Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2D7();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_ENCHANT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2D7Handler 
{
public:
	static uint32 Execute(SCMD2D7* pPacket) ;
};

#endif