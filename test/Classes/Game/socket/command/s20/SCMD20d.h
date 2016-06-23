	/**
	 * ɾ������
	GMSG_COMMU_FRIENDS_DEL_FRIEND = 0x20B (),			
	�����->�ͻ���, ���ṹ
	Int��				ɾ�����ID,
	String��			ɾ��������� 
	 * @author bobolive
	 * 
	 */		

#ifndef _SCMD20d_H_
#define _SCMD20d_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD20d : public Packet
{
public:
	SCMD20d() {}
	virtual ~SCMD20d() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_FRIENDS_BLACK_A_FRIEND;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	/**��ҳ��*/
	int32 a_ID;
	/**��ǰҳ��*/
	std::string b_delName;
};


class SCMD20dFactory: public MessageFactory
{
public :
	
	virtual ~SCMD20dFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD20d();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_FRIENDS_BLACK_A_FRIEND;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD20dHandler 
{
public:
	static uint32 Execute(SCMD20d* pPacket) ;
};

#endif 