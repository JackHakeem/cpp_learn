#ifndef _CCMD1A6_H_
#define _CCMD1A6_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
		 *�û������ʼ�
		CMSG_COMMU_MAIL_SEND = 0x1A6 (422),
		�ͻ���<->�����, ���ṹ
		Char:	�����˽�ɫ��
		Char:	�ʼ�����
		Char:	�ʼ�����
		 * 
		 */

class CCMD1A6 : public Packet
{
public:
	CCMD1A6() {}
	virtual ~CCMD1A6() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_COMMU_MAIL_SEND;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :

	std::string a_recvName;		//�����˽�ɫ��
	std::string b_mailTitle;	//�ʼ�����
	std::string c_mailContent;	//�ʼ�����
};


class CCMD1A6Factory: public MessageFactory
{
public :

	virtual ~CCMD1A6Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_MAIL_SEND;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif