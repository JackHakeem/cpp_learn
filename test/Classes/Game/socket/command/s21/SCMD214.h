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

#ifndef _SCMD214_H_
#define _SCMD214_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD214 : public Packet
{
public:
	SCMD214() {}
	virtual ~SCMD214() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_FRIENDS_ERR_CODE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint8 a_flag;
};


class SCMD214Factory: public MessageFactory
{
public :
	
	virtual ~SCMD214Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD214();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_FRIENDS_ERR_CODE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD214Handler 
{
public:
	static uint32 Execute(SCMD214* pPacket) ;
};

#endif 