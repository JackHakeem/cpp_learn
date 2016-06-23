#ifndef _SCMD197_H__
#define _SCMD197_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
 * GMSG_COMMU_PRIVATE_CHAT = 0x197(407),			//��������
 * �����<->�ͻ���, ���ṹ
 * Int: 		������ID
 * string:		�����߽�ɫ��
 * string:     ��������
	 string:		�������ݣ�ս����չʾ��Ʒ�ȣ�
 * byte:	��·
 * int:		���ն���ID
 * string:		����������
 * byte:	�������ʺ����� // 1-�ο� ; 2-��ͨ���; 3-GM
 */
class SCMD197 : public Packet
{
public:
	SCMD197() {}
	virtual ~SCMD197() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_PRIVATE_CHAT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:		 
	int32 a_fromId;
	std::string b_fromName;
	std::string c_content;
	std::string d_data;
	int8 d_line;
	int32 e_toId;
	std::string f_toName;
	int8 g_accountType;

};


class SCMD197Factory: public MessageFactory
{
public :

	virtual ~SCMD197Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD197();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_PRIVATE_CHAT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD197Handler 
{
public:
	static uint32 Execute(SCMD197* pPacket) ;
};
#endif