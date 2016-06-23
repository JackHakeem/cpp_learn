#ifndef _CCMD1A0_H_
#define _CCMD1A0_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
	 *�ʼ�ͷ�б�����
	 * @author Administrator
	 * 
	 */
/**
		 *CMSG_COMMU_MAIL_LIST_REQUEST = 0x1A0(416),		
			�ͻ���<->�����, ���ṹ
			byte:		�ʼ�����			(ȫ��0�����1��ϵͳ2��
			Short��		�����б���ʼ���	(��Ŵ�0��ʼ�ź�)
			Short��		�����б�����
		 * 
		 */	

class CCMD1A0 : public Packet
{
public:
	CCMD1A0() : a_mailType(0),b_startNum(0),c_mailNum(0)
	{}
	virtual ~CCMD1A0() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_COMMU_MAIL_LIST;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

	uint8 a_mailType;		//�ʼ����ͣ�ȫ��0�����1��ϵͳ2��
	uint16 b_startNum;		//�ʼ��б���ʼ���	(��Ŵ�0��ʼ�ź�)
	uint16 c_mailNum;		//�ʼ��б�����;
};


class CCMD1A0Factory: public MessageFactory
{
public :

	virtual ~CCMD1A0Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_MAIL_LIST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif