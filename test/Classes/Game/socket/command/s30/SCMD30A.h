/**
Installation information to the client push mercenary
WMSG_WORLD_MERCENARY_EQUIP_INFO = 0x30A (778)
The service side -> client package structure
Short can with the equipment number
the uint32 mercenary unique ID
uint8 equipment location
the uint32 equipment unique ID
the uint16 equipment prototype ID
byte enhanced level of
are uint16 equipment magic of the physical properties
are uint16 equipment magic of the wrist property
are uint16 equipment magic of intellectual property
*/

#ifndef _SCMD30A_H_
#define _SCMD30A_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

struct SCMD30ANode
{
	int32 a_figureId;
	int8 b_sitGrid;
	int32 c_eqpId;
	int16 d_eqpGoodsId;
	int8 e_superLv;
	int16 f_stamina;			//The magic of the physical number of
	int16 g_wrist;			//The number of magic of the wrist
	int16 h_intellect;		//Fel Intellect number
	int16 i_sp_stamina;
	int16 j_sp_wrist;
	int16 k_sp_intellect;
	int8 l_blue;
	int8 m_purple;
	int8 n_red;

	SCMD30ANode()
	{
		a_figureId = 0;
		b_sitGrid = 0;
		c_eqpId = 0;
		d_eqpGoodsId = 0;
		e_superLv = 0;
		f_stamina = 0;			//The magic of the physical number of
		g_wrist = 0;			//The number of magic of the wrist
		h_intellect = 0;		//Fel Intellect number
		i_sp_stamina = 0;
		j_sp_wrist = 0;
		k_sp_intellect = 0;
		l_blue = 0;
		m_purple = 0;
		n_red = 0;
	}
};

class SCMD30A : public Packet
{
public:
	SCMD30A() {}
	virtual ~SCMD30A() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_MERCENARY_EQUIP_INFO;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16	count;
	std::vector<SCMD30ANode> a_eqpList;
};


class SCMD30AFactory: public MessageFactory
{
public :
	
	virtual ~SCMD30AFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD30A();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_MERCENARY_EQUIP_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD30AHandler 
{
public:
	static uint32 Execute(SCMD30A* pPacket) ;
};

#endif