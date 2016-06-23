#ifndef _SCMD1B2_H_
#define _SCMD1B2_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
	/**
	 �鿴�����б���ҳ��
	 GMSG_COMMU_GUILD_GET_LIST = 0x1B2 (434)��			 
	 �����->�ͻ���, ���ṹ
	 Short��		��ҳ��,
	 Short:		��ǰҳ��,
	 Short��		��ҳ������,
		 * Short��		������
		 * String��	�������֣�
		 * String��	�᳤���֣�
		 * Short��		����ȼ���
		 * Short��		��Ա����
		 * Short��		��Ա������
		 * String:      ������� 
		 * Byte��		�����־		// 0 �C δ���� / 1 �C ������
	 */
class SCMD1B2 : public Packet
{
public:
	SCMD1B2() {}
	virtual ~SCMD1B2() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_GUILD_GET_LIST;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16 a_total;
	int16 b_page;
	struct SCMD1B2Node
	{
		/**��������*/
		int16 a_rank;
		string b_guildName;
		string c_leadName;
		int16 d_emblemLevel;
		/**�����Ա��*/
		int16 e_memberNum;
		/**�����Ա����*/
		int16 f_memberLimit;
		/**�������*/
		string g_guildIntr;
		/**�����־,0δ����,1������*/
		int8 h_flag;
	};

	std::list<SCMD1B2Node> e_guildArr;
};


class SCMD1B2Factory: public MessageFactory
{
public :
	
	virtual ~SCMD1B2Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1B2();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_GUILD_GET_LIST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1B2Handler 
{
public:
	static uint32 Execute(SCMD1B2* pPacket) ;
};

#endif 