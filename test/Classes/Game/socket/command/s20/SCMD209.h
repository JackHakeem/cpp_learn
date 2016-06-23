	/**
	 *��Ӻ�������	
	// ������ӳɹ�,֪ͨ�ͻ�����Ӻ��� ���ʧ�ܲμ��쳣����
	GMSG_COMMU_FRIENDS_ADD_FRIEND = 0x209 (),		
	�����->�ͻ���, ���ṹ
	Int��				��������ID,
	String��			������������ 
	 * @author bobolive
	 * 
	 */			

#ifndef _SCMD209_H_
#define _SCMD209_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD209 : public Packet
{
public:
	SCMD209() {}
	virtual ~SCMD209() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_FRIENDS_ADD_FRIEND;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	/**�������ID*/
	int32 a_ID;
	/**�����������*/
	std::string b_name;
};


class SCMD209Factory: public MessageFactory
{
public :
	
	virtual ~SCMD209Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD209();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_FRIENDS_ADD_FRIEND;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD209Handler 
{
public:
	static uint32 Execute(SCMD209* pPacket) ;
};

#endif 