/**
* tip mercenaries attribute information change
* WMSG_WORLD_MER_ATTRIBUTE_CHANGE = 0 x35F
* the server-> the client, package structure
* Uint32 role only ID
* Uint32 MAXHP
* Int change HP
* Int change physical attacks
* Int change magical attacks
* Int change physical defense
* Int change magic defense
* uint16 mercenaries achievement
Uint16 mercenaries intelligence
Uint16 mercenaries physical
Uint16 enchantment achievement
Uint16 enchantment intelligence
Uint16 enchantment frame
 */

#ifndef _SCMD35F_H_
#define _SCMD35F_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD35F : public Packet
{
public:
	SCMD35F() {}
	virtual ~SCMD35F() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_MER_ATTRIBUTE_CHANGE;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	int32 a_id;
	int32  b_maxHp;
	int32  c_Dhp;
	int32  d_DphsicsAttack;
	int32  e_DmagicAttack;
	int32  f_DphsicsDefend;
	int32  g_DmagicDefend;
	int16  h_str;
	int16  i_int;
	int16  j_sta;
	int16  k_plusStr;
	int16 l_plusInt;
	int16 m_plusSta;
	int16 n_sp_Str;
	int16 o_sp_Int;
	int16 p_sp_Sta;
};


class SCMD35FFactory: public MessageFactory
{
public :

	virtual ~SCMD35FFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD35F();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_MER_ATTRIBUTE_CHANGE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD35FHandler 
{
public:
	static uint32 Execute(SCMD35F* pPacket) ;
};

#endif