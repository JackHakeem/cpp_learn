#ifndef _CCMD20E_H_
#define _CCMD20E_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
	/**
	 * ����������Ͻ�������
	CMSG_COMMU_FRIENDS_ADD_BLACK = 0x20E����,		
	�����<-�ͻ���, ���ṹ
	String:				�����������
	 * @author bobolive
	 * 
	 */	

class CCMD20E : public Packet
{
public:
	CCMD20E() {}
	virtual ~CCMD20E() {}


	virtual bool	Write();	 


	virtual PacketID_t getPacketID() const { return CMSG_COMMU_FRIENDS_ADD_BLACK;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public :


	std::string a_name;


};


class CCMD20EFactory: public MessageFactory
{
public :

	virtual ~CCMD20EFactory ()  {}

	virtual Packet*		CreateMessage () {return 0;};

	virtual PacketID_t	GetPacketID ()const  {return CMSG_COMMU_FRIENDS_ADD_BLACK;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};




#endif