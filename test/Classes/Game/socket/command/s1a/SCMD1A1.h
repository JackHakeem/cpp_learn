/**
 * GMSG_COMMU_MAIL_LIST_RESPONSE = 0x1A1(417)
�����<->�ͻ���, ���ṹ
byte:		�ʼ����ͣ�ȫ��0�����1��ϵͳ2��
Short:		�������ʼ��б�������
Short:		�ʼ��б���ʼ���
Short:		�ʼ�ͷ����
	Int:	�ʼ�ΨһID
	Char:	�����˽�ɫ��
	Char:	�ʼ�����
	Byte:	�ʼ�����
	Byte:	�ռ���״̬(δ��0���Ѷ�1)
	Int:    ����ʱ��
	Byte:	������ȡ״̬(δ��ȡ0������ȡ1���޸���״̬2)
 */
#ifndef _SCMD1A1_H_
#define _SCMD1A1_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

/**
		 *�ʼ�ͷ��Ϣ
		 * Int:	�ʼ�ΨһID
		Char:	�����˽�ɫ��
		Char:	�ʼ�����
		Byte:	�ʼ�����
		Byte:	�ռ���״̬(δ��0���Ѷ�1)
		Int:	����ʱ��
		Byte:	������ȡ״̬(δ��ȡ0������ȡ1���޸���״̬2)

		 */

struct SCMD1A1Node
{
	uint32 a_mailId;		//�ʼ�ΨһID
	std::string b_senderName;	//�����˽�ɫ��
	std::string c_mailTitle;		
	uint8 d_mailType;
	uint8 e_mailStatus;			//״̬(δ��0���Ѷ�1)
	uint32 f_sendTime;				//����ʱ��
	uint8 g_attachStatus;			//������ȡ״̬(δ��ȡ0������ȡ1���޸���״̬2)
	SCMD1A1Node()
	{
		a_mailId = 0;
		b_senderName = "";
		c_mailTitle = "";
		d_mailType = 0;
		e_mailStatus = 0;
		f_sendTime = 0;
		g_attachStatus = 0;
	}
};

class SCMD1A1 : public Packet
{
public:
	SCMD1A1() {}
	virtual ~SCMD1A1() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_MAIL_LIST;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint8 a_mailType;		//�ʼ����ͣ�ȫ��0�����1��ϵͳ2��
	uint16 b_mailCount;	//�������ʼ��б�������
	uint16 c_startNum;	//�ʼ��б���ʼ���
	std::list<SCMD1A1Node> d_mailList;
};


class SCMD1A1Factory: public MessageFactory
{
public :
	
	virtual ~SCMD1A1Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1A1();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_MAIL_LIST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1A1Handler 
{
public:
	static uint32 Execute(SCMD1A1* pPacket) ;
};

#endif 