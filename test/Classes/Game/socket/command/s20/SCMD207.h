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

#ifndef _SCMD207_H_
#define _SCMD207_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "SCMD207Node.h"

class SCMD207 : public Packet
{
public:
	SCMD207() {}
	virtual ~SCMD207() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_FRIENDS_BLACK_LIST;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	/**��ҳ��*/
	int16 a_total;
	/**��ǰҳ��*/
	int16 b_page;
	/**��ҳ��*/
	std::list<SCMD207Node> c_nodeArr;
};


class SCMD207Factory: public MessageFactory
{
public :
	
	virtual ~SCMD207Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD207();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_FRIENDS_BLACK_LIST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD207Handler 
{
public:
	static uint32 Execute(SCMD207* pPacket) ;
};

#endif 