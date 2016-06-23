/**
		 *�û����յ����ʼ�
		 GMSG_COMMU_MAIL_RECV = 0x1A9(425)		//�û����յ����ʼ�
		 �����<->�ͻ���, ���ṹ
		 |Int:	�ʼ�ΨһID
		 |Char:	�����˽�ɫ�� 
		 |Char:	�ʼ�����
		 |Byte:	�ʼ����ͣ�ȫ��0�����1��ϵͳ2��
		 |Byte:	�ռ���״̬(δ��0���Ѷ�1)
		 |Int:	����ʱ��
		 |Byte:	������ȡ״̬(δ��ȡ0������ȡ1���޸���״̬2)
		 */	

#ifndef _SCMD1A9_H_
#define _SCMD1A9_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD1A9 : public Packet
{
public:
	SCMD1A9() {}
	virtual ~SCMD1A9() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_MAIL_RECV;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint32 a_mailId;			//�ʼ�ΨһID
	std::string b_senderName;	//�����˽�ɫ�� 
	std::string c_mailTitle;	//�ʼ�����
	uint8 d_mailType;			//�ʼ����ͣ�ȫ��0�����1��ϵͳ2��
	uint8 e_mailStatus;		//�ռ���״̬(δ��0���Ѷ�1)
	uint32 f_sendTime;			//����ʱ��
	uint8 g_attachStatus;		//������ȡ״̬(δ��ȡ0������ȡ1���޸���״̬2)
};


class SCMD1A9Factory: public MessageFactory
{
public :
	
	virtual ~SCMD1A9Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1A9();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_MAIL_RECV;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1A9Handler 
{
public:
	static uint32 Execute(SCMD1A9* pPacket) ;
};

#endif 