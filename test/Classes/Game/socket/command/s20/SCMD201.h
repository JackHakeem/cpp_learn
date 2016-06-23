	/**
	 * GMSG_COMMU_FRIENDS_LIST = 0x201 (),			
	 �����->�ͻ���, ���ṹ
	 Short��				��ҳ��,
	 Short��				��ǰҳ��,
	 Short��				��ҳ�����,
		 Int��			���ID,
		 Short��			�������ɫӶ��ID,
		 String��		�������,
		 Byte��			��֮ˮ���ȼ�,
		 Byte��			����״̬		0 �C ���� / 1 �C ���� 
		 Byte��			�ܷ�ף����־	0 �C ���� / 1 �C ���� 
	 * @author bobolive
	 * 
	 */		

#ifndef _SCMD201_H_
#define _SCMD201_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "SCMD201Node.h"

class SCMD201 : public Packet
{
public:
	SCMD201() {}
	virtual ~SCMD201() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_FRIENDS_LIST;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	/**��ҳ��*/
	int16 a_total;
	/**��ǰҳ��*/
	int16 b_page;
	/**��ҳ��*/
	std::list<SCMD201Node> c_nodeArr;
};


class SCMD201Factory: public MessageFactory
{
public :
	
	virtual ~SCMD201Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD201();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_FRIENDS_LIST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD201Handler 
{
public:
	static uint32 Execute(SCMD201* pPacket) ;
};

#endif 