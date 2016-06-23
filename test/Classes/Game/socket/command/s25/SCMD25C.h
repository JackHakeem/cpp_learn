/**
*   ����˷������а��б���Ϣ
*   GMSG_WORLD_RANK_LIST_RESP = 0X25C (),
*   �����->�ͻ���, ���ṹ
*   Uint8:	���а�����
*   Uint8:	�ȼ�����0:0-40��1:41-60��2:61-80��3:81-100��4:101-120��
*   Uint16: ����Լ�������(������������������Ϊ0)
*   Uint16�����а�����
*   Uint16:  �����б���ʼλ��
*   Short��		��������
*       Uint16���������
*       Int32:   ���ID
*       String:	�������
*       String:  ������(���޼��빫�ᣬ�򷵻ؿ�)
*       Uint32:	Value(װ���ܷ�/����ֵ/ս����/����ID)
*       uint8:	���ǵȼ�
*       uint16:	����ԭ��ID
**/

#ifndef _SCMD25C_H_
#define _SCMD25C_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

struct SCMD25CNode
{
    SCMD25CNode()
    {
        a_rank = 0;
        b_playerId = 0;
        c_name = "";
        d_guild = "";
        e_grade = 0;
        f_lev = 0;
        g_roleId = 0;
        h_trend = 0;
    }

    int16       a_rank;
    int32       b_playerId;
    std::string c_name;
    std::string d_guild;
    int32       e_grade;
    int8        f_lev;
    int32       g_roleId;
    int16       h_trend;

};

class SCMD25C : public Packet
{
public:
    SCMD25C() {}

    virtual ~SCMD25C() {}

    virtual bool Read();

public:

    virtual int32 Execute();

    virtual PacketID_t getPacketID() { return GMSG_WORLD_RANK_LIST_RESP; }

    virtual int32 GetMessageSize() const { return 0; }

public:

    int8 a_type;

    int16 b_myRank;

    int16 c_num;

    int16 d_begin;

    std::vector<SCMD25CNode> e_ranks;

};

class SCMD25CFactory : public MessageFactory
{
public:

    virtual ~SCMD25CFactory() {}

    virtual Packet* CreateMessage() { return new SCMD25C(); }

    virtual PacketID_t GetPacketID() const { return GMSG_WORLD_RANK_LIST_RESP; }

    virtual uint32 GetMessageMaxSize() const { return 0; }

};

class SCMD25CHandler
{
public:
    static uint32 Execute(SCMD25C* pPacket);
};

#endif 
