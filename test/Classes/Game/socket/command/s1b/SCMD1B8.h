#ifndef _SCMD1B8_H_
#define _SCMD1B8_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
	������ʾ��Ϣ
	GMSG_COMMU_GUILD_NEW_RESP = 0x1B8 (439),		
	�����->�ͻ���, ���ṹ
	Byte��		��ʾ����  // 1 �C ְ���� / 2 �C ����  /  3 �C ������� / 4 �C �޸Ĺ��� / 5 - �Ƽ�����
	String:		����������
	String:		�������������� // 1ʱΪ�Է����� 2ʱ�� 3ʱΪ�Է����� 4ʱΪ�������� 5��
	Int:		����1	// ����1ʱΪԭְ��ID 2ʱΪ�Ƽ�ID 3��4�գ�5�Ƽ�ID
	Int:		����2	// ����1ʱΪ��ְ��ID 2ʱΪ���׶� 3��4�գ�5�Ƽ��ȼ�
 */
class SCMD1B8 : public Packet
{
public:
	SCMD1B8() {}
	virtual ~SCMD1B8() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_GUILD_TIP_RESP;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
	
	int8 a_type;
	string b_operator;
	string c_target;
	int d_param1;
	int e_param2;
};


class SCMD1B8Factory: public MessageFactory
{
public :
	
	virtual ~SCMD1B8Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1B8();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_GUILD_TIP_RESP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1B8Handler 
{
public:
	static uint32 Execute(SCMD1B8* pPacket) ;
};

#endif 