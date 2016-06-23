#ifndef _SCMD191_H__
#define _SCMD191_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
 * GMSG_COMMU_WORLD_CHAT = 0x191(401)��			//�������죬����Ϣ��������㲥
 * �����<->����, ���ṹ
 * Int:		������ID
 * string:	�����߽�ɫ��
 * string:  ��������
	 string:		�������ݣ�ս����չʾ��Ʒ�ȣ�
 * byte:	��·
 * byte:	�������ʺ����� // 1-�ο� ; 2-��ͨ���; 3-GM
 */

class SCMD191 : public Packet
{
public:
	SCMD191() {}
	virtual ~SCMD191() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_WORLD_CHAT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:		 
	int32 a_id;
	std::string b_name;
	std::string c_content;
	std::string d_data;
	int8 d_line;
	int8 e_accountType;
};


class SCMD191Factory: public MessageFactory
{
public :

	virtual ~SCMD191Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD191();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_WORLD_CHAT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD191Handler 
{
public:
	static uint32 Execute(SCMD191* pPacket) ;
};
#endif