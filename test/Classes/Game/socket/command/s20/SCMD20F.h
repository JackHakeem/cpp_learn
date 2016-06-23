	/**
	 * ����������Ͻ�������
	GMSG_COMMU_FRIENDS_ADD_BLACK = 0x20F (),			
	�����->�ͻ���, ���ṹ
	Int��				�������ID,
	String��			����������� 
	 * @author bobolive
	 * 
	 */	

#ifndef _SCMD20F_H_
#define _SCMD20F_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD20F : public Packet
{
public:
	SCMD20F() {}
	virtual ~SCMD20F() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_FRIENDS_ADD_BLACK;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	/**��ҳ��*/
	int32 a_ID;
	/**��ǰҳ��*/
	std::string b_delName;
};


class SCMD20FFactory: public MessageFactory
{
public :
	
	virtual ~SCMD20FFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD20F();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_FRIENDS_ADD_BLACK;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD20FHandler 
{
public:
	static uint32 Execute(SCMD20F* pPacket) ;
};

#endif 