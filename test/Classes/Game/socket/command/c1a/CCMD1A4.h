#ifndef _CCMD1A4_H_
#define _CCMD1A4_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
		 *�û�ɾ���ʼ�
			CMSG_COMMU_MAIL_DEL = 0x1A4 (420),
			�ͻ���<->�����, ���ṹ
			Short��		ɾ���ʼ�������
				Int:		�ʼ�ΨһId

		 * 
		 */	

class CCMD1A4 : public Packet
{
public:
	CCMD1A4() {}
	virtual ~CCMD1A4() {a_mailIdList.clear();}


	virtual bool	Write();


	virtual PacketID_t getPacketID() const { return CMSG_COMMU_MAIL_DELETE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :
	/**�ʼ�ΨһId�б�ɾ������һ���ʼ�*/
	std::list<uint> a_mailIdList;
};


class CCMD1A4Factory: public MessageFactory
{
public :

	virtual ~CCMD1A4Factory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_MAIL_DELETE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif