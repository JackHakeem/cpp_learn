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

#ifndef _SCMD205_H_
#define _SCMD205_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "SCMD205Node.h"

class SCMD205 : public Packet
{
public:
	SCMD205() {}
	virtual ~SCMD205() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_FRIENDS_SAME_LEVEL;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	/**��ҳ��*/
	int16 a_total;
	/**��ǰҳ��*/
	int16 b_page;
	/**��ҳ��*/
	std::list<SCMD205Node> c_nodeArr;
};


class SCMD205Factory: public MessageFactory
{
public :
	
	virtual ~SCMD205Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD205();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_FRIENDS_SAME_LEVEL;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD205Handler 
{
public:
	static uint32 Execute(SCMD205* pPacket) ;
};

#endif 