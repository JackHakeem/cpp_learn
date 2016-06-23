/**
		 *�����û��ʼ���ϸ����
			GMSG_COMMU_MAIL_DETAIL_RESPONSE = 0x1A3 (419)
			�����<->�ͻ���, ���ṹ
			Int:		�ʼ�ΨһID
			Char:	�����˽�ɫ��
			Char:	�ʼ�����
			Byte:	�ʼ�����
			Byte:	�ռ���״̬(δ��0���Ѷ�1)
			Int:		����ʱ��
			Byte:	������ȡ״̬
			Char:	�ʼ�����
			short: 	������Ʒԭ��ID
			Int:		��Ʒ����
		 * 
		 */	

#ifndef _SCMD1A3_H_
#define _SCMD1A3_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD1A3 : public Packet
{
public:
	SCMD1A3() {}
	virtual ~SCMD1A3() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_MAIL_CONTENT;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint32 a_mailId;			//�ʼ�ΨһID
	std::string b_senderName;	//�����˽�ɫ��
	std::string c_mailTitle;	//�ʼ�����
	uint8 d_mailType;			//�ʼ�����
	uint8 e_mailStatus;		//�ռ���״̬(δ��0���Ѷ�1)
	uint32 f_sendTime;			//����ʱ��
	uint8 g_attachStatus;		//������ȡ״̬(δ��ȡ0������ȡ1���޸���״̬2)
	std::string h_mailContent;	//�ʼ�����
	uint16 i_attachId;
	uint32 j_goodsNum;
};


class SCMD1A3Factory: public MessageFactory
{
public :
	
	virtual ~SCMD1A3Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1A3();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_MAIL_CONTENT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1A3Handler 
{
public:
	static uint32 Execute(SCMD1A3* pPacket) ;
};

#endif 