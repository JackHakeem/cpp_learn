	/**
	 * �鿴�����Ϣ
	 * GMSG_COMMU_FRIENDS_VIEW_INFO = 0x213 (),			
	�����->�ͻ���, ���ṹ
	// todo����Ҫ��Щ��Ϣ?
	Uint32��		���ID
	String��		�������
	Short��			�������ԭ��ID
	Byte:        ��֮ˮ���ȼ�
	 * @author bobolive
	 * 
	 */		

#ifndef _SCMD219_H_
#define _SCMD219_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD219 : public Packet
{
public:
	SCMD219() {}
	virtual ~SCMD219() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_FRIENDS_BLESS;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_limit;
	int8 b_hasBlessNum;
	int8 c_hasBlessedNum;
};


class SCMD219Factory: public MessageFactory
{
public :
	
	virtual ~SCMD219Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD219();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_FRIENDS_BLESS;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD219Handler 
{
public:
	static uint32 Execute(SCMD219* pPacket) ;
};

#endif 