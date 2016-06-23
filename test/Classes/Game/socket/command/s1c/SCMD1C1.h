#ifndef _SCMD1C1_H_
#define _SCMD1C1_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
	/**
	 * GMSG_COMMU_GUILD_MEMBER_LIST = 0x1C1 (449)��			
	 �����->�ͻ���, ���ṹ
	 Short:		��ҳ��
	 Short:		��ǰҳ��
	 Short:		��ҳ����,
		 int8:		ְ��,
		 Int��		���ID,
		 String��	����,
		 short��		�ȼ�,
		 Int��		�ƺ�,
		 String��	״̬		// -1 ����   0 ����  else ����X��
		 Int:		���׶�
	 */	
class SCMD1C1 : public Packet
{
public:
	SCMD1C1() {}
	virtual ~SCMD1C1() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_GUILD_MEMBER_LIST;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16 a_total;
	int16 b_page;
	struct SCMD1C1Node
	{
		/**ְ��*/
		int8 a_position;
		int b_pID;
		string c_pName;
		int16 d_pLevel;
		/**�ƺ�*/
		int e_emblem;
		/**״̬*/
		string g_pState;
		/**���׶�*/
		int h_con;
	};

	std::list<SCMD1C1Node> c_pArr;
};


class SCMD1C1Factory: public MessageFactory
{
public :
	
	virtual ~SCMD1C1Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1C1();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_GUILD_MEMBER_LIST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1C1Handler 
{
public:
	static uint32 Execute(SCMD1C1* pPacket) ;
};

#endif 