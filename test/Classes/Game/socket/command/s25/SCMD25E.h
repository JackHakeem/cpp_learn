/**
*   ����˷������������Ϣ
*   GMSG_WORLD_RANK_PLAYER_INFO_RESP = 0X25E (),
*   �����->�ͻ���, ���ṹ
*   Uint8:	����
*   uint32:	���ID
*   uint16:	װ������
*      uint16:	װ��ԭ��ID
*      uint8:	ǿ���ȼ�
*      uint16: ���(ħ������)
*      uint16: ����(ħ������)
*      uint16: ����(ħ������)
**/

#ifndef _SCMD25E_H_
#define _SCMD25E_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

struct SCMD25ENode
{
    SCMD25ENode()
    {
        a_id = 0;
        b_lev = 0;
        c_stamina = 0;
        d_wrist = 0;
        e_intellect = 0;
    }

    int16   a_id;
    int8    b_lev;
    int16   c_stamina;
    int16   d_wrist;
    int16   e_intellect;

};

class SCMD25E : public Packet
{
public:
    SCMD25E() 
    {
    }
    virtual ~SCMD25E() {}

    virtual bool Read();

public:
    virtual int32 Execute();

    virtual PacketID_t getPacketID() const { return GMSG_WORLD_RANK_PLAYER_INFO_RESP; }

    virtual int32 GetMessageSize() const { return 0; }

public:
    int8    a_type;
    int32   b_player;
    std::vector<SCMD25ENode> c_equips;
};

class SCMD25EFactory : public MessageFactory
{
public:

    virtual ~SCMD25EFactory() {}

    virtual Packet* CreateMessage() { return new SCMD25E(); }

    virtual PacketID_t GetPacketID() const { return GMSG_WORLD_RANK_PLAYER_INFO_RESP; }

    virtual uint32 GetMessageMaxSize() const { return 0; }

};

class SCMD25EHandler
{
public:
    static uint32 Execute(SCMD25E* pPacket);
};

#endif


