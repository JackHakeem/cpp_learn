#ifndef _SCMD1D6_H_
#define _SCMD1D6_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
 * GMSG_COMMU_GUILD_DONATE = 0x1D6()	// ���ص��վ������ޡ��Ѿ�����
 * �����->�ͻ���,���ṹ
 * int:		���վ�������,
 * int��		�Ѿ���
 */
class SCMD1D6 : public Packet
{
public:
	SCMD1D6() {}
	virtual ~SCMD1D6() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_GUILD_DONATE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

	int a_limit;
	int b_donate;
};


class SCMD1D6Factory: public MessageFactory
{
public :
	
	virtual ~SCMD1D6Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1D6();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_GUILD_DONATE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1D6Handler 
{
public:
	static uint32 Execute(SCMD1D6* pPacket) ;
};

#endif 