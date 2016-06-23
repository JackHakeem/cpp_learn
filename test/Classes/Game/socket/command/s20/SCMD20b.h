	/**
	 * ɾ������
	GMSG_COMMU_FRIENDS_DEL_FRIEND = 0x20B (),			
	�����->�ͻ���, ���ṹ
	Int��				ɾ�����ID,
	String��			ɾ��������� 
	 * @author bobolive
	 * 
	 */		

#ifndef _SCMD20b_H_
#define _SCMD20b_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD20b : public Packet
{
public:
	SCMD20b() {}
	virtual ~SCMD20b() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_FRIENDS_DEL_FRIEND;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	/**��ҳ��*/
	int32 a_ID;
	/**��ǰҳ��*/
	std::string b_delName;
};


class SCMD20bFactory: public MessageFactory
{
public :
	
	virtual ~SCMD20bFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD20b();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_FRIENDS_DEL_FRIEND;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD20bHandler 
{
public:
	static uint32 Execute(SCMD20b* pPacket) ;
};

#endif 