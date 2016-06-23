/*
 * CCMD10F.h
 *
 *  Created on: 2012-10-26
 *      Author: doyang
 */

#ifndef CCMD10F_H_
#define CCMD10F_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "LoginManage.h"


class CCMD10F : public Packet
{
public:
    CCMD10F()
    {

    }

    virtual ~CCMD10F() {}

    int8 a_type;
	uint32 b_accId;

    virtual bool    Write();
public :
    //virtual int32     Execute() {return 0;};

    virtual PacketID_t getPacketID() const { return CMSG_CLIENT_SY_LOGIN;}

    virtual int32       GetMessageSize( ) const { return 0;}
};


class CCMD10FFactory: public MessageFactory
{
public :

    virtual ~CCMD10FFactory ()  {}

    virtual Packet*     CreateMessage () {return 0;};

    virtual PacketID_t  GetPacketID ()const  {return CMSG_CLIENT_SY_LOGIN;}

    virtual uint32      GetMessageMaxSize ()const  {return 0;}

};

#endif /* CCMD10F_H_ */
