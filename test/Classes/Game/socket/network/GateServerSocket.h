/****************************************************************************
 Copyright (c) 2011 4399
 Copyright (c) 2011 ำเฯในคื๗สา

 author	:zhangcheng
 email	:45612592@qq.com
 web	:http://45612592.qzone.qq.com
 data	:2011/11/19
 ****************************************************************************/

#ifndef _GAMESERVERSOCKET_H_
#define _GAMESERVERSOCKET_H_


#include "BaseType.h"
#include "PacketBuffer.h"
#include <string>

class Packet;
class GateServerSocket: public cocos2d::CCNode//cocos2d::SelectorProtocol//cocos2d::CCLayer//
{
public:
	GateServerSocket(void);
	static GateServerSocket *s_NetWorkModule;
	bool m_bConnect;
	int  m_refHandler;

	void recv(float dt);

public:
	static GateServerSocket* getInstance(void);
	static void destroyInstance(void);
	void sendMessage(Packet *packet);
	bool connect(const std::string& host, unsigned short port);	
	void registerScriptHandler( int refHandler );

	virtual ~GateServerSocket(void);
	PacketBuffer g_packetBuffer;
};

#endif//_LUA_NETWORK_H
