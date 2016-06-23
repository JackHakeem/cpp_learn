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

#ifndef _SCMD213_H_
#define _SCMD213_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD213 : public Packet
{
public:
	SCMD213() {}
	virtual ~SCMD213() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_FRIENDS_VIEW_INFO;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int32 a_playerId;
	std::string b_name;
	int16 c_avatarId;
	int8 d_mainCyLev;
};


class SCMD213Factory: public MessageFactory
{
public :
	
	virtual ~SCMD213Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD213();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_FRIENDS_VIEW_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD213Handler 
{
public:
	static uint32 Execute(SCMD213* pPacket) ;
};

#endif 