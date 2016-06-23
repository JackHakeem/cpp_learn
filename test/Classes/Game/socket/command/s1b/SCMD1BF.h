#ifndef _SCMD1BF_H_
#define _SCMD1BF_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

/**
�鿴������Ϣ
GMSG_COMMU_GUILD_INFO = 0x1BF (447)��			 
�����->�ͻ���, ���ṹ
String:		�������֣�
String��	    �᳤����,
Short��		���յȼ���
Short��		����ȼ���
Short��		����������
Short��		��Ա����
Short��		��Ա���ޣ�
String��	����ʱ�䣬
String��	QQȺ��
String��	����
byte:   ״̬ 1Ϊ��ɢ��
*/
class SCMD1BF : public Packet
{
public:
	SCMD1BF() {}
	virtual ~SCMD1BF() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_GUILD_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	/**��������*/
	string a_guildName;
	string b_leaderName;
	/**���յȼ�*/
	int16 c_emblemLevel;
	int16 d_guildLevel;
	int16 e_guildRank;
	int16 f_memberNum;
	int16 g_memberLimit;
	string h_createDate;
	string i_qqGN;
	string j_notice;
	string l_intro;
	int8 m_state;
	int n_abortTime;
};


class SCMD1BFFactory: public MessageFactory
{
public :

	virtual ~SCMD1BFFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1BF();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_GUILD_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1BFHandler 
{
public:
	static uint32 Execute(SCMD1BF* pPacket) ;
};

#endif 