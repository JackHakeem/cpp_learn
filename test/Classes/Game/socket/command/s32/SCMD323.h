
/**
* server response to obtain information collection 

WMSG_WORLD_FEEKBACK_IMPOSE_INFO = 0 x323, (803) 

Byte remaining on ordinary times 

Byte maximum number of ordinary collection 

Uint16 gold coin collection times 

Uint16 guild science and technology level 

Uint16 target number a week stars 

Uint32 collection can win in the number of silver 

Uint32 collected compulsively will use the gold number 

 */

#ifndef _SCMD323_H_
#define _SCMD323_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD323 : public Packet
{
public:
	SCMD323() {}
	virtual ~SCMD323() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_FEEKBACK_IMPOSE_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_type;
	int8 b_rest;
	int8 c_max;
	int16 e_uniteNum;
	int16 f_starNum;
	int g_reward;
	int h_cost;
};


class SCMD323Factory: public MessageFactory
{
public :

	virtual ~SCMD323Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD323();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_FEEKBACK_IMPOSE_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD323Handler 
{
public:
	static uint32 Execute(SCMD323* pPacket) ;
};

#endif