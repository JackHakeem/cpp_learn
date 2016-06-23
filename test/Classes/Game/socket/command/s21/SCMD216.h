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

#ifndef _SCMD216_H_
#define _SCMD216_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD216 : public Packet
{
public:
	SCMD216() {}
	virtual ~SCMD216() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_FRIENDS_HAS_APPLY;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int32 a_ID;
	std::string b_name;
	int16 c_hiredID;
	int8 d_mainLev;
};


class SCMD216Factory: public MessageFactory
{
public :
	
	virtual ~SCMD216Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD216();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_FRIENDS_HAS_APPLY;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD216Handler 
{
public:
	static uint32 Execute(SCMD216* pPacket) ;
};

#endif 