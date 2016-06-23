#ifndef _SCMD1C3_H_
#define _SCMD1C3_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
	/**�鿴��Ա��Ϣ
	 GMSG_COMMU_GUILD_MEMBER_INFO = 0x1C3 (451)��			
	 �����->�ͻ���, ���ṹ
	 Short:		��ҳ��
	 Short:		��ǰҳ��		// �����0���������Ǿ�ȷ���ҵĽ����������ģ��
	 Short:		��ҳ����,
		 byte:		ְ��,
		 Int:		���ID,
		 String��	����,
		 short��		�ȼ�,
		 Int��		�ƺ�,
		 String��	״̬			// ������ʾ��·��������ʾʱ��
	 
	 */
class SCMD1C3 : public Packet
{
public:
	SCMD1C3() {}
	virtual ~SCMD1C3() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_GUILD_MEMBER_INFO;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16 a_total;
	int16 b_page;
	struct SCMD1C3Node
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
	};

	std::list<SCMD1C3Node> c_nodeArr;
};


class SCMD1C3Factory: public MessageFactory
{
public :
	
	virtual ~SCMD1C3Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1C3();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_GUILD_MEMBER_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1C3Handler 
{
public:
	static uint32 Execute(SCMD1C3* pPacket) ;
};

#endif 